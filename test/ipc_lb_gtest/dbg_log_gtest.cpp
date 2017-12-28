#undef Dbg_FID
#define Dbg_FID DBG_FID_DEF(GTEST_FID,0)
 
#include "gtest/gtest.h"
#include "ipc.h"
#include "dbg_log.h"

TEST(Dbg_Log, Info)
{
   Dbg_Verb("Log Verbose %s %d", "\"String\"", 200);
   Dbg_Info("Log Info %s %d", "\"String\"", 200);
   Dbg_Warn("Log Warn %s %d", "\"String\"", 200);
   Dbg_Fault("Log Fault %s %d", "\"String\"", 200);
}
