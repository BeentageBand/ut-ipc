#undef Dbg_FID
#define Dbg_FID DBG_FID_DEF(GTEST_FID,0)
 
#include "gtest/gtest.h"
#include "ipc.h"
#include "dbg_log.h"

TEST(Dbg_Log, Info)
{
   Dbg_Verb("Log Verbose %d %s", 200, "String");
   Dbg_Info("Log Info %d %s", 200, "String");
   Dbg_Warn("Log Warn %d %s", 200, "String");
   Dbg_Fault("Log Fault %d %s", 200, "String");
}
