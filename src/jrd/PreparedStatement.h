/*
 *  The contents of this file are subject to the Initial
 *  Developer's Public License Version 1.0 (the "License");
 *  you may not use this file except in compliance with the
 *  License. You may obtain a copy of the License at
 *  http://www.ibphoenix.com/main.nfs?a=ibphoenix&page=ibp_idpl.
 *
 *  Software distributed under the License is distributed AS IS,
 *  WITHOUT WARRANTY OF ANY KIND, either express or implied.
 *  See the License for the specific language governing rights
 *  and limitations under the License.
 *
 *  The Original Code was created by Adriano dos Santos Fernandes
 *  for the Firebird Open Source RDBMS project.
 *
 *  Copyright (c) 2008 Adriano dos Santos Fernandes <adrianosf@uol.com.br>
 *  and all contributors signed below.
 *
 *  All Rights Reserved.
 *  Contributor(s): ______________________________________.
 */

#ifndef JRD_PREPARED_STATEMENT_H
#define JRD_PREPARED_STATEMENT_H

#include "firebird.h"
#include "../jrd/common.h"
#include "../jrd/dsc.h"
#include "../common/classes/alloc.h"
#include "../common/classes/array.h"
#include "../common/classes/fb_string.h"
#include "../common/classes/MetaName.h"
#include "../common/classes/TriState.h"

namespace Jrd {

class thread_db;
class jrd_tra;
class Attachment;
class dsql_req;
class dsql_msg;
class ResultSet;


class PreparedStatement : public Firebird::PermanentStorage
{
friend class ResultSet;

public:
	class Builder
	{
	private:
		enum Type
		{
			TYPE_SLONG,
			TYPE_METANAME,
			TYPE_STRING,
		};

	public:
		Builder(const Firebird::string& aText)
			: text(aText),
			  params(0)
		{
		}

	public:
		Builder& operator <<(const char* chunk)
		{
			text += chunk;
			return *this;
		}

		Builder& operator <<(SLONG& param)
		{
			types.add(TYPE_SLONG);
			addresses.add(&param);
			specifiedAddresses.add(NULL);

			text += "?";
			++params;
			return *this;
		}

		Builder& operator <<(Firebird::string& param)
		{
			types.add(TYPE_STRING);
			addresses.add(&param);
			specifiedAddresses.add(NULL);

			text += "?";
			++params;
			return *this;
		}

		Builder& operator <<(Firebird::MetaName& param)
		{
			types.add(TYPE_METANAME);
			addresses.add(&param);
			specifiedAddresses.add(NULL);

			text += "?";
			++params;
			return *this;
		}

		template <typename T> Builder& operator <<(TriStateType<T>& param)
		{
			*this << param.value;
			specifiedAddresses[specifiedAddresses.getCount() - 1] = &param.specified;
			return *this;
		}

	public:
		const Firebird::string& getText() const
		{
			return text;
		}

		void moveToStatement(thread_db* tdbb, PreparedStatement* stmt) const;

	private:
		Firebird::string text;
		Firebird::Array<Type> types;
		Firebird::Array<void*> addresses;
		Firebird::Array<bool*> specifiedAddresses;
		unsigned params;
	};

private:
	// Auxiliary class to use positional parameters with C++ variables.
	class PosBuilder
	{
	public:
		explicit PosBuilder(const Firebird::string& aText)
			: text(aText),
			  params(0)
		{
		}

		PosBuilder& operator <<(const char* chunk)
		{
			text += chunk;
			return *this;
		}

		PosBuilder& operator <<(unsigned& param)
		{
			text += "?";
			param = ++params;
			return *this;
		}

		operator const Firebird::string& ()
		{
			return text;
		}

	private:
		Firebird::string text;
		unsigned params;
	};

public:
	// Create a PreparedStatement builder to use positional parameters with C++ variables.
	static PosBuilder build(const Firebird::string& text)
	{
		return PosBuilder(text);
	}

	// Escape a metadata name accordingly to SQL rules.
	static Firebird::string escapeName(const Firebird::MetaName& s)
	{
		Firebird::string ret;

		for (const char* p = s.begin(); p != s.end(); ++p)
		{
			ret += *p;
			if (*p == '\"')
				ret += '\"';
		}

		return ret;
	}

	// Escape a string accordingly to SQL rules.
	template <typename T> static Firebird::string escapeString(const T& s)
	{
		Firebird::string ret;

		for (const char* p = s.begin(); p != s.end(); ++p)
		{
			ret += *p;
			if (*p == '\'')
				ret += '\'';
		}

		return ret;
	}

public:
	PreparedStatement(thread_db* tdbb, Firebird::MemoryPool& aPool, Attachment* attachment,
		jrd_tra* transaction, const Firebird::string& text, bool isInternalRequest);
	PreparedStatement(thread_db* tdbb, Firebird::MemoryPool& aPool, Attachment* attachment,
		jrd_tra* transaction, const Builder& aBuilder, bool isInternalRequest);
	~PreparedStatement();

private:
	void init(thread_db* tdbb, Attachment* attachment, jrd_tra* transaction,
		const Firebird::string& text, bool isInternalRequest);

public:
	void setDesc(thread_db* tdbb, unsigned param, const dsc& value);

	void setNull(unsigned param)
	{
		fb_assert(param > 0);

		const dsc* desc = &inValues[(param - 1) * 2 + 1];
		fb_assert(desc->dsc_dtype == dtype_short);
		*reinterpret_cast<SSHORT*>(desc->dsc_address) = -1;
	}

	void setInt(thread_db* tdbb, unsigned param, SLONG value)
	{
		fb_assert(param > 0);

		dsc desc;
		desc.makeLong(0, &value);

		setDesc(tdbb, param, desc);
	}

	void setString(thread_db* tdbb, unsigned param, const Firebird::AbstractString& value)
	{
		fb_assert(param > 0);

		dsc desc;
		desc.makeText((USHORT) value.length(), inValues[(param - 1) * 2].getTextType(),
			(UCHAR*) value.c_str());

		setDesc(tdbb, param, desc);
	}

	void setString(thread_db* tdbb, unsigned param, const Firebird::MetaName& value)
	{
		fb_assert(param > 0);

		dsc desc;
		desc.makeText((USHORT) value.length(), inValues[(param - 1) * 2].getTextType(),
			(UCHAR*) value.c_str());

		setDesc(tdbb, param, desc);
	}

	void execute(thread_db* tdbb, jrd_tra* transaction);
	ResultSet* executeQuery(thread_db* tdbb, jrd_tra* transaction);
	unsigned executeUpdate(thread_db* tdbb, jrd_tra* transaction);

	int getResultCount() const;

	dsql_req* getRequest()
	{
		return request;
	}

	static void parseDsqlMessage(const dsql_msg* dsqlMsg, Firebird::Array<dsc>& values,
		Firebird::UCharBuffer& blr, Firebird::UCharBuffer& msg);
	static void generateBlr(const dsc* desc, Firebird::UCharBuffer& blr);

private:
	const Builder* builder;
	dsql_req* request;
	Firebird::Array<dsc> inValues, outValues;
	Firebird::UCharBuffer inBlr, outBlr;
	Firebird::UCharBuffer inMessage, outMessage;
	ResultSet* resultSet;
};


}	// namespace

#endif	// JRD_PREPARED_STATEMENT_H
