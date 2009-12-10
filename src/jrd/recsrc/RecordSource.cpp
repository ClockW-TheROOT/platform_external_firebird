
#include "firebird.h"
#include "../jrd/common.h"
#include "../jrd/jrd.h"
#include "../jrd/btr.h"
#include "../jrd/intl.h"
#include "../jrd/req.h"
#include "../jrd/rse.h"
#include "../jrd/cmp_proto.h"
#include "../jrd/dpm_proto.h"
#include "../jrd/err_proto.h"
#include "../jrd/intl_proto.h"
#include "../jrd/met_proto.h"
#include "../jrd/rlck_proto.h"
#include "../jrd/vio_proto.h"
#include "../jrd/DataTypeUtil.h"

#include "RecordSource.h"

using namespace Firebird;
using namespace Jrd;


// Record source class
// -------------------

void RecordSource::dumpName(thread_db* tdbb, const Firebird::string& name, UCharBuffer& buffer)
{
	size_t nameLength = name.length();
	const UCHAR* namePtr = (UCHAR*) name.c_str();

	MoveBuffer nameBuffer;

	const CHARSET_ID charset = tdbb->getCharSet();
	if (charset != CS_METADATA && charset != CS_NONE)
	{
		const size_t bufferLength = INTL_convert_bytes(tdbb, charset, NULL, 0,
													   CS_METADATA, namePtr, nameLength, ERR_post);
		nameBuffer.getBuffer(bufferLength);
		nameLength = INTL_convert_bytes(tdbb, charset, nameBuffer.begin(), bufferLength,
										CS_METADATA, namePtr, nameLength, ERR_post);

		namePtr = nameBuffer.begin();
	}

	fb_assert(nameLength <= MAX_UCHAR);

	buffer.add((UCHAR) nameLength);
	buffer.add(namePtr, nameLength);
}

void RecordSource::dumpInversion(thread_db* tdbb, const jrd_nod* inversion, UCharBuffer& buffer)
{
	// spit out the node type
	switch (inversion->nod_type)
	{
	case nod_bit_and:
		buffer.add(isc_info_rsb_and);
		break;
	case nod_bit_or:
	case nod_bit_in:
		buffer.add(isc_info_rsb_or);
		break;
	case nod_bit_dbkey:
		buffer.add(isc_info_rsb_dbkey);
		break;
	case nod_index:
		buffer.add(isc_info_rsb_index);
		break;
	}

	// dump sub-nodes or the actual index info
	switch (inversion->nod_type)
	{
	case nod_bit_and:
	case nod_bit_or:
	case nod_bit_in:
		dumpInversion(tdbb, inversion->nod_arg[0], buffer);
		dumpInversion(tdbb, inversion->nod_arg[1], buffer);
		break;
	case nod_index:
		{
			const IndexRetrieval* const retrieval =
				(IndexRetrieval*) inversion->nod_arg[e_idx_retrieval];

			Firebird::MetaName indexName;
			MET_lookup_index(tdbb, indexName, retrieval->irb_relation->rel_name,
							 (USHORT) (retrieval->irb_index + 1));

			dumpName(tdbb, indexName.c_str(), buffer);
		}
		break;
	}
}

void RecordSource::saveRecord(thread_db* tdbb, record_param* rpb)
{
	MemoryPool* const pool = tdbb->getDefaultPool();

	SaveRecordParam* rpb_copy = rpb->rpb_copy;
	if (rpb_copy)
	{
		delete rpb_copy->srpb_rpb->rpb_record;
	}
	else
	{
		rpb->rpb_copy = rpb_copy = FB_NEW(*pool) SaveRecordParam();
	}

	memcpy(rpb_copy->srpb_rpb, rpb, sizeof(record_param));

	Record* const record = rpb->rpb_record;

	if (record)
	{
		const USHORT size = record->rec_length;
		Record* rec_copy = FB_NEW_RPT(*pool, size) Record(*pool);
		rpb_copy->srpb_rpb->rpb_record = rec_copy;

		rec_copy->rec_length = size;
		rec_copy->rec_format = record->rec_format;
		rec_copy->rec_number = record->rec_number;
		memcpy(rec_copy->rec_data, record->rec_data, size);
	}
	else
	{
		rpb_copy->srpb_rpb->rpb_record = NULL;
	}
}

void RecordSource::restoreRecord(thread_db* tdbb, record_param* rpb)
{
	MemoryPool* const pool = tdbb->getDefaultPool();

	SaveRecordParam* rpb_copy = rpb->rpb_copy;
	if (rpb_copy)
	{
		Record* record = rpb->rpb_record;
		Record* const rec_copy = rpb_copy->srpb_rpb->rpb_record;

		if (rec_copy)
		{
			if (!record)
				BUGCHECK(284);	// msg 284 cannot restore singleton select data

			const USHORT size = rec_copy->rec_length;
			if (size > record->rec_length)
			{
				// hvlad: saved copy of record have longer format, reallocate
				// given record to make enough space for saved data
				record = VIO_record(tdbb, rpb, rec_copy->rec_format, pool);
			}
			else
			{
				record->rec_length = size;
				record->rec_format = rec_copy->rec_format;
			}
			record->rec_number = rec_copy->rec_number;
			memcpy(record->rec_data, rec_copy->rec_data, size);

			delete rec_copy;
		}

		memcpy(rpb, rpb_copy->srpb_rpb, sizeof(record_param));

		rpb->rpb_record = record;

		delete rpb_copy;
		rpb->rpb_copy = NULL;
	}
}


// RecordStream class
// ------------------

RecordStream::RecordStream(CompilerScratch* csb, UCHAR stream, Format* format)
	: m_stream(stream), m_format(format ? format : csb->csb_rpt[stream].csb_format)
{
	fb_assert(m_format);
}

bool RecordStream::refetchRecord(thread_db* tdbb)
{
	jrd_req* const request = tdbb->getRequest();
	jrd_tra* const transaction = request->req_transaction;

	record_param* const org_rpb = &request->req_rpb[m_stream];

	if (org_rpb->rpb_stream_flags & RPB_s_refetch)
	{
		if (!DPM_get(tdbb, org_rpb, LCK_read) ||
			!VIO_chase_record_version(tdbb, org_rpb, transaction, tdbb->getDefaultPool(), true))
		{
			return false;
		}

		VIO_data(tdbb, org_rpb, tdbb->getDefaultPool());

		org_rpb->rpb_stream_flags &= ~RPB_s_refetch;
	}

	return true;
}

bool RecordStream::lockRecord(thread_db* tdbb)
{
	jrd_req* const request = tdbb->getRequest();
	jrd_tra* const transaction = request->req_transaction;

	record_param* const org_rpb = &request->req_rpb[m_stream];
	jrd_rel* const relation = org_rpb->rpb_relation;

	fb_assert(relation && !relation->rel_view_rse);

	RLCK_reserve_relation(tdbb, transaction, relation, true);

	return VIO_writelock(tdbb, org_rpb, transaction);
}

void RecordStream::markRecursive()
{
	m_recursive = true;
}

void RecordStream::findUsedStreams(UCHAR* streams)
{
	for (UCHAR i = 1; i <= streams[0]; i++)
	{
		if (m_stream == streams[i])
		{
			return;
		}
	}

	fb_assert(streams[0] < MAX_STREAMS);
	streams[++streams[0]] = m_stream;
}

void RecordStream::invalidateRecords(jrd_req* request)
{
	record_param* const rpb = &request->req_rpb[m_stream];
	rpb->rpb_number.setValid(false);
}

void RecordStream::nullRecords(thread_db* tdbb)
{
	jrd_req* const request = tdbb->getRequest();
	record_param* const rpb = &request->req_rpb[m_stream];

	rpb->rpb_number.setValid(false);

	// Make sure a record block has been allocated. If there isn't
	// one, first find the format, then allocate the record block.

	Record* record = rpb->rpb_record;

	if (!record)
	{
		record = VIO_record(tdbb, rpb, m_format, tdbb->getDefaultPool());
	}

	if (record->rec_format)
	{
		record->rec_fmt_bk = record->rec_format;
	}

	record->rec_format = NULL;
}

void RecordStream::saveRecords(thread_db* tdbb)
{
	jrd_req* const request = tdbb->getRequest();
	saveRecord(tdbb, &request->req_rpb[m_stream]);
}

void RecordStream::restoreRecords(thread_db* tdbb)
{
	jrd_req* const request = tdbb->getRequest();
	restoreRecord(tdbb, &request->req_rpb[m_stream]);
}