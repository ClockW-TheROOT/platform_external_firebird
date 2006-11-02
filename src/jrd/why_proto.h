/*
 *	PROGRAM:	JRD Access Method
 *	MODULE:		why_proto.h
 *	DESCRIPTION:	Prototype header file for why.cpp
 *
 * The contents of this file are subject to the Interbase Public
 * License Version 1.0 (the "License"); you may not use this file
 * except in compliance with the License. You may obtain a copy
 * of the License at http://www.Inprise.com/IPL.html
 *
 * Software distributed under the License is distributed on an
 * "AS IS" basis, WITHOUT WARRANTY OF ANY KIND, either express
 * or implied. See the License for the specific language governing
 * rights and limitations under the License.
 *
 * The Original Code was created by Inprise Corporation
 * and its predecessors. Portions created by Inprise Corporation are
 * Copyright (C) Inprise Corporation.
 *
 * All Rights Reserved.
 * Contributor(s): ______________________________________.
 */

#ifndef JRD_WHY_PROTO_H
#define JRD_WHY_PROTO_H

#ifdef __cplusplus
extern "C" {
#endif


#ifndef WHY_NO_API
#ifndef JRD_IBASE_H
ISC_STATUS API_ROUTINE isc_dsql_allocate_statement(ISC_STATUS*, FB_API_HANDLE*, FB_API_HANDLE*);
ISC_STATUS API_ROUTINE isc_dsql_alloc_statement2(ISC_STATUS*, FB_API_HANDLE*, FB_API_HANDLE*);
ISC_STATUS API_ROUTINE isc_dsql_describe(ISC_STATUS *, FB_API_HANDLE*, USHORT, XSQLDA*);
ISC_STATUS API_ROUTINE isc_dsql_describe_bind(ISC_STATUS*, FB_API_HANDLE*,
												 USHORT, XSQLDA*);
ISC_STATUS API_ROUTINE isc_dsql_execute(ISC_STATUS*, FB_API_HANDLE*, FB_API_HANDLE*,
										USHORT, XSQLDA*);
ISC_STATUS API_ROUTINE isc_dsql_execute_m(ISC_STATUS*, FB_API_HANDLE*, FB_API_HANDLE*, USHORT,
											const SCHAR*, USHORT, USHORT, SCHAR*);
ISC_STATUS API_ROUTINE isc_dsql_execute2(ISC_STATUS*, FB_API_HANDLE*, FB_API_HANDLE*, USHORT,
											XSQLDA*, XSQLDA*);
ISC_STATUS API_ROUTINE isc_dsql_execute2_m(ISC_STATUS*, FB_API_HANDLE*,
											  FB_API_HANDLE*, USHORT, const SCHAR*,
											  USHORT, USHORT, SCHAR*, USHORT,
											  SCHAR*, USHORT, USHORT,
											  SCHAR*);
ISC_STATUS API_ROUTINE isc_dsql_execute_immediate(ISC_STATUS*, FB_API_HANDLE*,
													 FB_API_HANDLE*, USHORT,
													 const SCHAR*, USHORT,
													 XSQLDA*);
ISC_STATUS API_ROUTINE isc_dsql_exec_immed2(ISC_STATUS*, FB_API_HANDLE*,
											   FB_API_HANDLE*, USHORT,
											   const SCHAR*, USHORT, XSQLDA*,
											   XSQLDA*);
ISC_STATUS API_ROUTINE isc_dsql_execute_immediate_m(ISC_STATUS*,
													   FB_API_HANDLE*,
													   FB_API_HANDLE*, USHORT,
													   const SCHAR*, USHORT,
													   USHORT, const SCHAR*,
													   USHORT, USHORT,
													   SCHAR*);
ISC_STATUS API_ROUTINE isc_dsql_exec_immed2_m(ISC_STATUS*, FB_API_HANDLE*,
												 FB_API_HANDLE*, USHORT,
												 const SCHAR*, USHORT, USHORT,
												 const SCHAR*, USHORT, USHORT,
												 SCHAR*, USHORT, SCHAR*,
												 USHORT, USHORT, SCHAR*);
ISC_STATUS API_ROUTINE isc_dsql_exec_immed3_m(ISC_STATUS*, FB_API_HANDLE*,
												 FB_API_HANDLE*, USHORT,
												 const SCHAR*, USHORT, USHORT,
												 const SCHAR*, USHORT, USHORT,
												 SCHAR*, USHORT, SCHAR*,
												 USHORT, USHORT, SCHAR*);
ISC_STATUS API_ROUTINE isc_dsql_fetch(ISC_STATUS*, FB_API_HANDLE*, USHORT, XSQLDA*);
#ifdef SCROLLABLE_CURSORS
ISC_STATUS API_ROUTINE isc_dsql_fetch2(ISC_STATUS*, FB_API_HANDLE*, USHORT,
										  XSQLDA*, USHORT, SLONG);
#endif
ISC_STATUS API_ROUTINE isc_dsql_fetch_m(ISC_STATUS*, FB_API_HANDLE*, USHORT,
										   const SCHAR*, USHORT, USHORT, SCHAR*);
#ifdef SCROLLABLE_CURSORS
ISC_STATUS API_ROUTINE isc_dsql_fetch2_m(ISC_STATUS*, FB_API_HANDLE*, USHORT,
											const SCHAR*, USHORT, USHORT, SCHAR*,
											USHORT, SLONG);
#endif
ISC_STATUS API_ROUTINE isc_dsql_free_statement(ISC_STATUS*, FB_API_HANDLE*, USHORT);
ISC_STATUS API_ROUTINE isc_dsql_insert(ISC_STATUS*, FB_API_HANDLE*, USHORT, XSQLDA*);
ISC_STATUS API_ROUTINE isc_dsql_insert_m(ISC_STATUS*, FB_API_HANDLE*, USHORT,
											const SCHAR*, USHORT,
											USHORT, const SCHAR*);
ISC_STATUS API_ROUTINE isc_dsql_prepare(ISC_STATUS*, FB_API_HANDLE*,
										   FB_API_HANDLE*, USHORT, const SCHAR*,
										   USHORT, XSQLDA*);
ISC_STATUS API_ROUTINE isc_dsql_prepare_m(ISC_STATUS*, FB_API_HANDLE*,
											 FB_API_HANDLE*, USHORT, const SCHAR*,
											 USHORT, USHORT, const SCHAR*, USHORT,
											 SCHAR*);
ISC_STATUS API_ROUTINE isc_dsql_set_cursor_name(ISC_STATUS*, FB_API_HANDLE*,
												   const SCHAR*, USHORT);
ISC_STATUS API_ROUTINE isc_dsql_sql_info(ISC_STATUS*, FB_API_HANDLE*, SSHORT,
											const SCHAR*, SSHORT, SCHAR*);
//ISC_STATUS API_ROUTINE isc_prepare_transaction2(ISC_STATUS*, FB_API_HANDLE*, USHORT,
//												   UCHAR*);
// Deprecated in favor of FPTR_EVENT_CALLBACK
//typedef void event_ast_routine(UCHAR*, USHORT, UCHAR*);
//ISC_STATUS API_ROUTINE isc_que_events(ISC_STATUS*, FB_API_HANDLE*, SLONG*,
//										 USHORT, const UCHAR*,
//										FPTR_EVENT_CALLBACK, void*);
//#ifdef SCROLLABLE_CURSORS
//ISC_STATUS API_ROUTINE isc_receive2(ISC_STATUS*, FB_API_HANDLE*, USHORT,
//									   USHORT, SCHAR*, SSHORT, USHORT,
//									   ULONG);
//#endif
//ISC_STATUS API_ROUTINE isc_rollback_transaction(ISC_STATUS*, FB_API_HANDLE*);
//ISC_STATUS API_ROUTINE_VARARG isc_start_transaction(ISC_STATUS*,
//													   FB_API_HANDLE*, SSHORT,
//													   ...);


ISC_STATUS API_ROUTINE isc_attach_database(ISC_STATUS*, SSHORT, const TEXT*,
											FB_API_HANDLE* , SSHORT, const SCHAR*);

ISC_STATUS API_ROUTINE isc_blob_info(ISC_STATUS*, FB_API_HANDLE*, SSHORT, const SCHAR*,
									 SSHORT, SCHAR*);

ISC_STATUS API_ROUTINE isc_cancel_blob(ISC_STATUS*, FB_API_HANDLE*);

ISC_STATUS API_ROUTINE isc_cancel_events(ISC_STATUS*, FB_API_HANDLE*, SLONG*);

ISC_STATUS API_ROUTINE isc_close_blob(ISC_STATUS*, FB_API_HANDLE*);

ISC_STATUS API_ROUTINE isc_commit_transaction(ISC_STATUS*, FB_API_HANDLE*);

ISC_STATUS API_ROUTINE isc_commit_retaining(ISC_STATUS*, FB_API_HANDLE*);

ISC_STATUS API_ROUTINE isc_compile_request(ISC_STATUS*, FB_API_HANDLE*, FB_API_HANDLE*,
											USHORT, const SCHAR*);

ISC_STATUS API_ROUTINE isc_compile_request2(ISC_STATUS*, FB_API_HANDLE*, FB_API_HANDLE*,
											USHORT, const SCHAR*);

ISC_STATUS API_ROUTINE isc_create_blob(ISC_STATUS*, FB_API_HANDLE*, FB_API_HANDLE*,
										FB_API_HANDLE*, SLONG*);

ISC_STATUS API_ROUTINE isc_create_blob2(ISC_STATUS*, FB_API_HANDLE*, FB_API_HANDLE*,
										FB_API_HANDLE*, SLONG*, SSHORT, const UCHAR*);

ISC_STATUS API_ROUTINE isc_create_database(ISC_STATUS*, USHORT, const TEXT*,
											FB_API_HANDLE*, SSHORT, const UCHAR*,
											USHORT);

ISC_STATUS API_ROUTINE isc_database_info(ISC_STATUS*, FB_API_HANDLE*, SSHORT,
										const SCHAR*, SSHORT, SCHAR*);

ISC_STATUS API_ROUTINE isc_ddl(ISC_STATUS*, FB_API_HANDLE*, FB_API_HANDLE*, SSHORT, const UCHAR*);

ISC_STATUS API_ROUTINE isc_detach_database(ISC_STATUS*, FB_API_HANDLE*);

ISC_STATUS API_ROUTINE isc_drop_database(ISC_STATUS*, FB_API_HANDLE*);

ISC_STATUS API_ROUTINE isc_get_segment(ISC_STATUS*, FB_API_HANDLE*, USHORT*, USHORT,
										UCHAR*);

ISC_STATUS API_ROUTINE isc_get_slice(ISC_STATUS*, FB_API_HANDLE*, FB_API_HANDLE*, ISC_QUAD*,
									 USHORT, const UCHAR*, USHORT, const UCHAR*,
									 SLONG, UCHAR*, SLONG*);

ISC_STATUS API_ROUTINE isc_open_blob(ISC_STATUS*, FB_API_HANDLE*, FB_API_HANDLE*, FB_API_HANDLE*,
									 SLONG*);

ISC_STATUS API_ROUTINE isc_open_blob2(ISC_STATUS*, FB_API_HANDLE*, FB_API_HANDLE*, FB_API_HANDLE*,
									  SLONG*, SSHORT, const UCHAR*);

ISC_STATUS API_ROUTINE isc_prepare_transaction(ISC_STATUS*, FB_API_HANDLE*);

ISC_STATUS API_ROUTINE isc_prepare_transaction2(ISC_STATUS*, FB_API_HANDLE*, USHORT,
												const UCHAR*);

ISC_STATUS API_ROUTINE isc_put_segment(ISC_STATUS*, FB_API_HANDLE*, USHORT, const UCHAR*);

ISC_STATUS API_ROUTINE isc_put_slice(ISC_STATUS*, FB_API_HANDLE*, FB_API_HANDLE*, ISC_QUAD*,
									 USHORT, const UCHAR*, USHORT, const SLONG*,
									 SLONG, UCHAR*);

ISC_STATUS API_ROUTINE isc_que_events(ISC_STATUS*, FB_API_HANDLE*, SLONG*, USHORT,
									  const UCHAR*,
									  FPTR_EVENT_CALLBACK, void*);

ISC_STATUS API_ROUTINE isc_receive(ISC_STATUS*, FB_API_HANDLE*, USHORT, USHORT,
									SCHAR*, SSHORT);

#ifdef SCROLLABLE_CURSORS
ISC_STATUS API_ROUTINE isc_receive2(ISC_STATUS*, FB_API_HANDLE*, USHORT, USHORT, SCHAR*,
									SSHORT, USHORT, ULONG);
#endif

ISC_STATUS API_ROUTINE isc_reconnect_transaction(ISC_STATUS*, FB_API_HANDLE*, FB_API_HANDLE*,
												SSHORT, const UCHAR*);

ISC_STATUS API_ROUTINE isc_release_request(ISC_STATUS*, FB_API_HANDLE*);

ISC_STATUS API_ROUTINE isc_request_info(ISC_STATUS*, FB_API_HANDLE*, SSHORT, SSHORT,
										const SCHAR*, SSHORT, SCHAR*);

ISC_STATUS API_ROUTINE isc_rollback_retaining(ISC_STATUS*, FB_API_HANDLE*);

ISC_STATUS API_ROUTINE isc_rollback_transaction(ISC_STATUS*, FB_API_HANDLE*);

ISC_STATUS API_ROUTINE isc_seek_blob(ISC_STATUS*, FB_API_HANDLE*, SSHORT, SLONG,
									 SLONG*);

ISC_STATUS API_ROUTINE isc_send(ISC_STATUS*, FB_API_HANDLE*, USHORT, USHORT, const SCHAR*,
								SSHORT);

ISC_STATUS API_ROUTINE isc_service_attach(ISC_STATUS*, USHORT, const TEXT*, FB_API_HANDLE*,
										  USHORT, const SCHAR*);

ISC_STATUS API_ROUTINE isc_service_detach(ISC_STATUS*, FB_API_HANDLE*);

ISC_STATUS API_ROUTINE isc_service_query(ISC_STATUS*, FB_API_HANDLE*, ULONG*, USHORT,
										const SCHAR*, USHORT, const SCHAR*,
										USHORT, SCHAR*);

ISC_STATUS API_ROUTINE isc_service_start(ISC_STATUS*, FB_API_HANDLE*, ULONG*, USHORT,
										 const SCHAR*);

ISC_STATUS API_ROUTINE isc_start_and_send(ISC_STATUS*, FB_API_HANDLE*, FB_API_HANDLE*,
										  USHORT, USHORT, const SCHAR*, SSHORT);

ISC_STATUS API_ROUTINE isc_start_request(ISC_STATUS*, FB_API_HANDLE*, FB_API_HANDLE*, SSHORT);

ISC_STATUS API_ROUTINE isc_start_multiple(ISC_STATUS*, FB_API_HANDLE*, SSHORT, void*);

ISC_STATUS API_ROUTINE_VARARG isc_start_transaction(ISC_STATUS*, FB_API_HANDLE*,
													SSHORT, ...);

ISC_STATUS API_ROUTINE isc_transact_request(ISC_STATUS*, FB_API_HANDLE*, FB_API_HANDLE*,
											USHORT, const SCHAR*, USHORT,
											SCHAR*, USHORT, SCHAR*);

ISC_STATUS API_ROUTINE isc_transaction_info(ISC_STATUS*, FB_API_HANDLE*, SSHORT,
											const SCHAR*, SSHORT, UCHAR*);

ISC_STATUS API_ROUTINE isc_unwind_request(ISC_STATUS*, FB_API_HANDLE*, SSHORT);
#ifndef REQUESTER
ISC_STATUS API_ROUTINE isc_wait_for_event(ISC_STATUS*, FB_API_HANDLE*, USHORT,
										const UCHAR*, UCHAR*);
#endif

#endif	/* JRD_IBASE_H */
#endif	/* WHY_NO_API */

typedef void DatabaseCleanupRoutine(FB_API_HANDLE*, void*);

#ifdef CANCEL_OPERATION
#define CANCEL_disable	1
#define CANCEL_enable	2
#define CANCEL_raise	3
ISC_STATUS API_ROUTINE gds__cancel_operation(ISC_STATUS*, FB_API_HANDLE*, USHORT);
#endif

ISC_STATUS API_ROUTINE isc_database_cleanup(ISC_STATUS*, FB_API_HANDLE*,
												DatabaseCleanupRoutine*, void*);
int API_ROUTINE gds__disable_subsystem(TEXT*);
int API_ROUTINE gds__enable_subsystem(TEXT*);

ISC_STATUS gds__handle_cleanup(ISC_STATUS*, FB_API_HANDLE*);

#define INTL_FUNCTION_CHAR_LENGTH		1
ISC_STATUS API_ROUTINE gds__intl_function(ISC_STATUS*, FB_API_HANDLE*, USHORT, UCHAR, USHORT, const UCHAR*, USHORT*);

#define DSQL_CACHE_USE		1
#define DSQL_CACHE_RELEASE	2
ISC_STATUS API_ROUTINE gds__dsql_cache(ISC_STATUS*, FB_API_HANDLE*, USHORT, int, const char*, bool*);

ISC_STATUS API_ROUTINE gds__sql_text(ISC_STATUS*, FB_API_HANDLE*, USHORT, const char*);

typedef void TransactionCleanupRoutine(FB_API_HANDLE, void*);
ISC_STATUS API_ROUTINE gds__transaction_cleanup(ISC_STATUS*, FB_API_HANDLE*,
												   TransactionCleanupRoutine*, void*);
void WHY_cleanup_transaction(struct why_hndl* transaction);

#ifdef SERVER_SHUTDOWN
BOOLEAN WHY_set_shutdown(BOOLEAN);
BOOLEAN WHY_get_shutdown();
#endif /* SERVER_SHUTDOWN*/


#ifdef __cplusplus
} /* extern "C"*/
#endif

struct why_hndl* WHY_alloc_handle(int implementation, int handle_type);
struct why_hndl* WHY_translate_handle(FB_API_HANDLE handle);
void WHY_free_handle(FB_API_HANDLE handle);

#endif // JRD_WHY_PROTO_H

