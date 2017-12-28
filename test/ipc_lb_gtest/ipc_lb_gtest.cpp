#undef Dbg_FID
#define Dbg_FID DBG_FID_DEF(GTEST_FID,1)
 
#include "gtest/gtest.h"
#include "dbg_log.h"
#include "gtest_task_ext.h"
#include "ipc.h"
#include "ipc_helper.h"
#include "ipc_gtest_worker.h"
#include "thread.h"
 
#include <iostream>
#include <unistd.h>
 
static IPC_MID_T const Gtest_Mailist[] =
{
      IPC_GTEST_PBC_MID
};

static IPC_Gtest_Worker_T w1 = {NULL};
static IPC_Gtest_Worker_T w2 = {NULL};
static union Mail w1_mailbox[64] = {0};
static union Mail w2_mailbox[64] = {0};

TEST(Init, tasks)
{
	static union Mail gtest_mailbox [64] = {0};
	static union Mailbox mbx = {NULL};

	Populate_IPC_Gtest_Worker(&w1, IPC_GTEST_1_WORKER_TID, w1_mailbox, Num_Elems(w1_mailbox));
	Populate_IPC_Gtest_Worker(&w2, IPC_GTEST_2_WORKER_TID, w2_mailbox, Num_Elems(w2_mailbox));

	Task_Register_To_Process(NULL);
	Populate_Mailbox(&mbx, GTEST_FWK_WORKER_TID, gtest_mailbox, Num_Elems(gtest_mailbox));

	IPC_Register_Mailbox(&mbx);
	IPC_Task_Ready();

	IPC_Run(IPC_GTEST_1_WORKER_TID);
	IPC_Run(IPC_GTEST_2_WORKER_TID);

	sleep(1);
	ASSERT_EQ(GTEST_FWK_WORKER_TID, IPC_Self());
}

TEST(Timestamp, functions)
{
   EXPECT_TRUE(0 < IPC_Clock());

   IPC_Clock_T sleep_ms = IPC_Clock() + 1000U;
   EXPECT_FALSE(IPC_Clock_Elapsed(sleep_ms));
   Dbg_Warn("sleep_ms = %u", sleep_ms);

   sleep(2);
   EXPECT_TRUE(IPC_Clock_Elapsed(sleep_ms));
}

TEST(Retrieve_mail, mail)
{
   union Mail mail = {NULL};
   IPC_Send(IPC_GTEST_1_WORKER_TID, IPC_GTEST_INT_MID, NULL, 0);
   IPC_Send(IPC_GTEST_2_WORKER_TID, IPC_GTEST_INT_MID, NULL, 0);
   sleep(1);
   for(uint8_t i = 2; i; --i)
   {
      ASSERT_TRUE(IPC_Retrieve_Mail(&mail, 2000));
      EXPECT_EQ(mail.mid, IPC_GTEST_INT_MID);
   }
}

TEST(Retrieve_Mail, timeout)
{
   IPC_Clock_T timestamp = IPC_RETRIEVE_TOUT_MS + IPC_Clock();
   union Mail mail = {NULL};
   EXPECT_TRUE( IPC_Retrieve_Mail(&mail, IPC_RETRIEVE_TOUT_MS) );
   sleep(1);
   EXPECT_TRUE(IPC_Clock_Elapsed(timestamp));
}

TEST(Publish, mail)
{
   IPC_Publish(IPC_GTEST_PBC_MID, NULL, 0);

   if(IPC_Subscribe_Mailist(Gtest_Mailist, sizeof(Gtest_Mailist)) )
   {
      union Mail mail = {NULL};

      for(uint8_t i = 2; i; --i)
      {
         EXPECT_TRUE( IPC_Retrieve_From_Mailist(&mail, 2000UL, Gtest_Mailist,
               sizeof(Gtest_Mailist)) );
         EXPECT_EQ(mail.mid, IPC_GTEST_INT_MID);
      }
      EXPECT_FALSE(IPC_Retrieve_From_Mailist(&mail, IPC_RETRIEVE_TOUT_MS, Gtest_Mailist,
                     sizeof(Gtest_Mailist)) );

      EXPECT_TRUE(IPC_Unsubscribe_Mailist(Gtest_Mailist, sizeof(Gtest_Mailist)) );
   }
   else
   {
      FAIL();
   }
}


TEST(Shutdown, mail)
{
   IPC_Publish(WORKER_INT_SHUTDOWN_MID, NULL, 0);
//   IPC_Wait(IPC_GTEST_1_WORKER);
//   IPC_Wait(IPC_GTEST_2_WORKER);
}

int Gtest_Task_Cbk(int argc, char ** argv)
{
   std::cout << "Gtest_Task_Cbk main()\n";
   testing::InitGoogleTest(&argc, argv);
   return RUN_ALL_TESTS();
}
