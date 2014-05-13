LOCAL_PATH := $(call my-dir)

#original path: temp/Release/common.a
include $(CLEAR_VARS)

LOCAL_CFLAGS:= -DFB_SEND_FLAGS=MSG_NOSIGNAL -DLINUX -DAMD64 \
-fmessage-length=0 -fno-omit-frame-pointer -fexceptions

LOCAL_CPPFLAGS:= -fno-rtti

# fixed flags
LOCAL_CFLAGS+= -ffunction-sections -fdata-sections

LOCAL_C_INCLUDES:= \
	$(LOCAL_PATH)/src/include/gen\
	$(LOCAL_PATH)/src/include\
	external/icu4c/common\
	external/ncurses/include\
	external/libtommath\
	external/icu4c/i18n
LOCAL_SRC_FILES:= \
	src/common/security.cpp\
	src/common/isc_sync.cpp\
	src/common/StatusArg.cpp\
	src/common/TextType.cpp\
	src/common/dsc.cpp\
	src/common/utils.cpp\
	src/common/IntlParametersBlock.cpp\
	src/common/UtilSvc.cpp\
	src/common/db_alias.cpp\
	src/common/xdr.cpp\
	src/common/ThreadStart.cpp\
	src/common/CharSet.cpp\
	src/common/pretty.cpp\
	src/common/IntlUtil.cpp\
	src/common/Auth.cpp\
	src/common/thd.cpp\
	src/common/isc_file.cpp\
	src/common/fb_exception.cpp\
	src/common/ThreadData.cpp\
	src/common/dllinst.cpp\
	src/common/cvt.cpp\
	src/common/enc.cpp\
	src/common/BigInteger.cpp\
	src/common/unicode_util.cpp\
	src/common/ScanDir.cpp\
	src/common/isc.cpp\
	src/common/StatusHolder.cpp\
	src/common/StatementMetadata.cpp\
	src/common/call_service.cpp\
	src/common/MsgMetadata.cpp\
	src/common/sdl.cpp\
	src/common/sha.cpp\
	src/common/os/posix/isc_ipc.cpp\
	src/common/os/posix/SyncSignals.cpp\
	src/common/os/posix/os_utils.cpp\
	src/common/os/posix/path_utils.cpp\
	src/common/os/posix/mod_loader.cpp\
	src/common/os/posix/guid.cpp\
	src/common/os/posix/divorce.cpp\
	src/common/os/posix/fbsyslog.cpp\
	src/common/classes/NoThrowTimeStamp.cpp\
	src/common/classes/SyncObject.cpp\
	src/common/classes/ClumpletWriter.cpp\
	src/common/classes/ClumpletReader.cpp\
	src/common/classes/DbImplementation.cpp\
	src/common/classes/BlrWriter.cpp\
	src/common/classes/UserBlob.cpp\
	src/common/classes/BaseStream.cpp\
	src/common/classes/semaphore.cpp\
	src/common/classes/fb_string.cpp\
	src/common/classes/TempFile.cpp\
	src/common/classes/locks.cpp\
	src/common/classes/alloc.cpp\
	src/common/classes/SafeArg.cpp\
	src/common/classes/MsgPrint.cpp\
	src/common/classes/MetaName.cpp\
	src/common/classes/InternalMessageBuffer.cpp\
	src/common/classes/Switches.cpp\
	src/common/classes/ImplementHelper.cpp\
	src/common/classes/Synchronize.cpp\
	src/common/classes/init.cpp\
	src/common/classes/timestamp.cpp\
	src/common/config/ConfigCache.cpp\
	src/common/config/config_file.cpp\
	src/common/config/dir_list.cpp\
	src/common/config/config.cpp\
	src/common/config/os/posix/config_root.cpp\
	src/common/config/os/posix/binreloc.c
LOCAL_MODULE := common

include $(BUILD_STATIC_LIBRARY)


#original path: gen/Release/firebird/lib/libfbclient.so.3.0.0
include $(CLEAR_VARS)


LOCAL_CPPFLAGS:= -DFB_SEND_FLAGS=MSG_NOSIGNAL -DLINUX -DAMD64 \
-fmessage-length=0 -fno-omit-frame-pointer -fno-rtti 

LOCAL_LDFLAGS:= -shared  -Wl,--version-script,$(LOCAL_PATH)/gen/firebird.vers \
-Wl,-soname,libfbclient.so.2 

# fixed flags
LOCAL_CFLAGS+= -ffunction-sections -fdata-sections

LOCAL_C_INCLUDES:= \
	$(LOCAL_PATH)/src/include/gen\
	$(LOCAL_PATH)/src/include\
	external/icu4c/common\
	external/ncurses/include\
	external/libtommath\
	external/icu4c/i18n
LOCAL_SRC_FILES:= \
	src/yvalve/MasterImplementation.cpp\
	src/yvalve/alt.cpp\
	src/yvalve/preparse.cpp\
	src/yvalve/perf.cpp\
	src/yvalve/user_dsql.cpp\
	src/yvalve/gds.cpp\
	src/yvalve/why.cpp\
	src/yvalve/PluginManager.cpp\
	src/yvalve/keywords.cpp\
	src/yvalve/utl.cpp\
	src/yvalve/DistributedTransaction.cpp\
	temp/Release/yvalve/blob.cpp\
	temp/Release/yvalve/array.cpp\
	src/remote/remote.cpp\
	src/remote/protocol.cpp\
	src/remote/merge.cpp\
	src/remote/inet.cpp\
	src/remote/parser.cpp\
	src/auth/SecureRemotePassword/srp.cpp\
	src/remote/client/interface.cpp\
	src/remote/client/BlrFromMessage.cpp\
	src/auth/SecureRemotePassword/client/SrpClient.cpp\
	src/auth/SecurityDatabase/LegacyClient.cpp\
	src/plugins/crypt/arc4/Arc4.cpp
LOCAL_STATIC_LIBRARIES:= \
	libncurses\
	common\
	libtommath
LOCAL_MODULE := libfbclient

include $(BUILD_SHARED_LIBRARY)


#original path: gen/Release/firebird/plugins/libEngine0.so
include $(CLEAR_VARS)


LOCAL_CPPFLAGS:= -DFB_SEND_FLAGS=MSG_NOSIGNAL -DLINUX -DAMD64 \
-fmessage-length=0 -fno-omit-frame-pointer -fno-rtti 

LOCAL_LDFLAGS:= -shared  -Wl,--version-script,$(LOCAL_PATH)/gen/fbplugin.vers \
-Wl,-soname,libEngine0.so 

# fixed flags
LOCAL_CFLAGS+= -ffunction-sections -fdata-sections

LOCAL_C_INCLUDES:= \
	$(LOCAL_PATH)/src/include/gen\
	$(LOCAL_PATH)/src/include\
	external/icu4c/common\
	external/ncurses/include\
	external/libtommath\
	external/icu4c/i18n
LOCAL_SRC_FILES:= \
	src/jrd/idx.cpp\
	src/jrd/nodebug.cpp\
	src/jrd/sdw.cpp\
	src/jrd/flu.cpp\
	src/jrd/Optimizer.cpp\
	src/jrd/PreparedStatement.cpp\
	src/jrd/ResultSet.cpp\
	src/jrd/opt.cpp\
	src/jrd/cch.cpp\
	src/jrd/cvt2.cpp\
	src/jrd/ods.cpp\
	src/jrd/RuntimeStatistics.cpp\
	src/jrd/RecordBuffer.cpp\
	src/jrd/exe.cpp\
	src/jrd/Routine.cpp\
	src/jrd/rpb_chain.cpp\
	src/jrd/tpc.cpp\
	src/jrd/cvt.cpp\
	src/jrd/UserManagement.cpp\
	src/jrd/btr.cpp\
	src/jrd/CryptoManager.cpp\
	src/jrd/sort.cpp\
	src/jrd/SysFunction.cpp\
	src/jrd/DebugInterface.cpp\
	src/jrd/sqz.cpp\
	src/jrd/intl.cpp\
	src/jrd/vio.cpp\
	src/jrd/DatabaseSnapshot.cpp\
	src/jrd/pag.cpp\
	src/jrd/Attachment.cpp\
	src/jrd/event.cpp\
	src/jrd/svc_tab.cpp\
	src/jrd/GlobalRWLock.cpp\
	src/jrd/jrd.cpp\
	src/jrd/DataTypeUtil.cpp\
	src/jrd/mov.cpp\
	src/jrd/tra.cpp\
	src/jrd/blb.cpp\
	src/jrd/TempSpace.cpp\
	src/jrd/GarbageCollector.cpp\
	src/jrd/Relation.cpp\
	src/jrd/VirtualTable.cpp\
	src/jrd/status.cpp\
	src/jrd/filters.cpp\
	src/jrd/JrdStatement.cpp\
	src/jrd/ext.cpp\
	src/jrd/builtin.cpp\
	src/jrd/err.cpp\
	src/jrd/rlck.cpp\
	src/jrd/btn.cpp\
	src/jrd/svc.cpp\
	src/jrd/ExtEngineManager.cpp\
	src/jrd/cmp.cpp\
	src/jrd/Mapping.cpp\
	src/jrd/nbak.cpp\
	src/jrd/par.cpp\
	src/jrd/RandomGenerator.cpp\
	src/jrd/lck.cpp\
	src/jrd/intl_builtin.cpp\
	src/jrd/Collation.cpp\
	src/jrd/validation.cpp\
	src/jrd/Database.cpp\
	src/jrd/shut.cpp\
	src/jrd/blob_filter.cpp\
	src/jrd/IntlManager.cpp\
	src/jrd/RecordSourceNodes.cpp\
	src/jrd/evl.cpp\
	src/jrd/inf.cpp\
	temp/Release/jrd/met.cpp\
	temp/Release/jrd/dfw.cpp\
	temp/Release/jrd/fun.cpp\
	temp/Release/jrd/scl.cpp\
	temp/Release/jrd/pcmet.cpp\
	temp/Release/jrd/dpm.cpp\
	temp/Release/jrd/Function.cpp\
	temp/Release/jrd/dyn_util.cpp\
	temp/Release/jrd/grant.cpp\
	temp/Release/jrd/ini.cpp\
	src/jrd/os/posix/unix.cpp\
	src/dsql/ddl.cpp\
	src/dsql/make.cpp\
	src/dsql/DsqlCompilerScratch.cpp\
	src/dsql/Parser.cpp\
	src/dsql/BlrDebugWriter.cpp\
	src/dsql/StmtNodes.cpp\
	src/dsql/movd.cpp\
	src/dsql/BoolNodes.cpp\
	src/dsql/WinNodes.cpp\
	src/dsql/utld.cpp\
	src/dsql/dsql.cpp\
	src/dsql/DSqlDataTypeUtil.cpp\
	src/dsql/errd.cpp\
	src/dsql/pass1.cpp\
	src/dsql/AggNodes.cpp\
	src/dsql/gen.cpp\
	src/dsql/ExprNodes.cpp\
	temp/Release/dsql/PackageNodes.cpp\
	temp/Release/dsql/DdlNodes.cpp\
	temp/Release/dsql/metd.cpp\
	temp/Release/dsql/parse.cpp\
	src/jrd/extds/InternalDS.cpp\
	src/jrd/extds/ExtDS.cpp\
	src/jrd/extds/IscDS.cpp\
	src/jrd/recsrc/SortedStream.cpp\
	src/jrd/recsrc/FirstRowsStream.cpp\
	src/jrd/recsrc/WindowedStream.cpp\
	src/jrd/recsrc/ConditionalStream.cpp\
	src/jrd/recsrc/AggregatedStream.cpp\
	src/jrd/recsrc/FullTableScan.cpp\
	src/jrd/recsrc/BufferedStream.cpp\
	src/jrd/recsrc/VirtualTableScan.cpp\
	src/jrd/recsrc/HashJoin.cpp\
	src/jrd/recsrc/MergeJoin.cpp\
	src/jrd/recsrc/IndexTableScan.cpp\
	src/jrd/recsrc/Union.cpp\
	src/jrd/recsrc/FilteredStream.cpp\
	src/jrd/recsrc/RecordSource.cpp\
	src/jrd/recsrc/FullOuterJoin.cpp\
	src/jrd/recsrc/SkipRowsStream.cpp\
	src/jrd/recsrc/ProcedureScan.cpp\
	src/jrd/recsrc/Cursor.cpp\
	src/jrd/recsrc/BitmapTableScan.cpp\
	src/jrd/recsrc/ExternalTableScan.cpp\
	src/jrd/recsrc/RecursiveStream.cpp\
	src/jrd/recsrc/NestedLoopJoin.cpp\
	src/jrd/recsrc/SingularStream.cpp\
	src/jrd/recsrc/LockedStream.cpp\
	src/jrd/trace/TraceConfigStorage.cpp\
	src/jrd/trace/TraceLog.cpp\
	src/jrd/trace/TraceObjects.cpp\
	src/jrd/trace/TraceManager.cpp\
	src/jrd/trace/TraceService.cpp\
	src/jrd/trace/TraceCmdLine.cpp\
	src/lock/lock.cpp\
	src/alice/alice_meta.cpp\
	src/alice/alice.cpp\
	src/alice/exe.cpp\
	src/alice/tdr.cpp\
	src/burp/mvol.cpp\
	src/burp/burp.cpp\
	src/burp/misc.cpp\
	src/burp/canonical.cpp\
	temp/Release/burp/OdsDetection.cpp\
	temp/Release/burp/backup.cpp\
	temp/Release/burp/restore.cpp\
	src/utilities/gsec/gsec.cpp\
	src/utilities/gstat/ppg.cpp\
	temp/Release/utilities/gstat/dba.cpp\
	src/utilities/nbackup/nbackup.cpp
LOCAL_STATIC_LIBRARIES:= \
	libncurses\
	libtommath\
	libfbclient\
	common
LOCAL_MODULE := libEngine0

include $(BUILD_SHARED_LIBRARY)


#original path: gen/Release/firebird/intl/libfbintl.so
include $(CLEAR_VARS)


LOCAL_CPPFLAGS:= -DFB_SEND_FLAGS=MSG_NOSIGNAL -DLINUX -DAMD64 \
-fmessage-length=0 -fno-omit-frame-pointer -fno-rtti 

LOCAL_LDFLAGS:= -shared  -Wl,--version-script,$(LOCAL_PATH)/gen/fbintl.vers \
-Wl,-soname,libintl.so.1 

# fixed flags
LOCAL_CFLAGS+= -ffunction-sections -fdata-sections

LOCAL_C_INCLUDES:= \
	$(LOCAL_PATH)/src/include/gen\
	$(LOCAL_PATH)/src/include\
	external/icu4c/common\
	external/ncurses/include\
	external/libtommath\
	external/icu4c/i18n
LOCAL_SRC_FILES:= \
	src/intl/lc_dos.cpp\
	src/intl/lc_narrow.cpp\
	src/intl/ld.cpp\
	src/intl/lc_ascii.cpp\
	src/intl/lc_big5.cpp\
	src/intl/cs_unicode_fss.cpp\
	src/intl/cs_narrow.cpp\
	src/intl/cs_icu.cpp\
	src/intl/cv_ksc.cpp\
	src/intl/lc_gb2312.cpp\
	src/intl/lc_jis.cpp\
	src/intl/lc_iso8859_2.cpp\
	src/intl/cs_big5.cpp\
	src/intl/cv_jis.cpp\
	src/intl/cs_unicode_ucs2.cpp\
	src/intl/cv_gb2312.cpp\
	src/intl/lc_icu.cpp\
	src/intl/cv_icu.cpp\
	src/intl/cs_gb2312.cpp\
	src/intl/cv_big5.cpp\
	src/intl/lc_iso8859_13.cpp\
	src/intl/cv_narrow.cpp\
	src/intl/lc_iso8859_1.cpp\
	src/intl/lc_unicode_ucs2.cpp\
	src/intl/cs_ksc.cpp\
	src/intl/cs_jis.cpp\
	src/intl/kanji.cpp\
	src/intl/lc_ksc.cpp\
	src/intl/cv_unicode_fss.cpp
LOCAL_STATIC_LIBRARIES:= \
	libncurses\
	libfbclient\
	common\
	libtommath
LOCAL_MODULE := libfbintl

include $(BUILD_SHARED_LIBRARY)


#original path: gen/Release/firebird/bin/firebird
include $(CLEAR_VARS)


LOCAL_CPPFLAGS:= -DFB_SEND_FLAGS=MSG_NOSIGNAL -DLINUX -DAMD64 \
-fmessage-length=0 -fno-omit-frame-pointer -fno-rtti 

LOCAL_LDFLAGS:= -Wl,--version-script,$(LOCAL_PATH)/gen/empty.vers 

# fixed flags
LOCAL_CFLAGS+= -ffunction-sections -fdata-sections
LOCAL_LDFLAGS+=  -Wl,--gc-sections -static

LOCAL_C_INCLUDES:= \
	$(LOCAL_PATH)/src/include/gen\
	$(LOCAL_PATH)/src/include\
	external/icu4c/common\
	external/ncurses/include\
	external/libtommath\
	external/icu4c/i18n
LOCAL_SRC_FILES:= \
	src/remote/remote.cpp\
	src/remote/protocol.cpp\
	src/remote/merge.cpp\
	src/remote/inet.cpp\
	src/remote/parser.cpp\
	src/auth/SecureRemotePassword/srp.cpp\
	src/remote/server/server.cpp\
	src/remote/server/os/posix/inet_server.cpp\
	src/auth/SecureRemotePassword/server/SrpServer.cpp
LOCAL_STATIC_LIBRARIES:= \
	libfbclient\
	libncurses\
	common\
	libtommath
LOCAL_MODULE := firebird

include $(BUILD_EXECUTABLE)

