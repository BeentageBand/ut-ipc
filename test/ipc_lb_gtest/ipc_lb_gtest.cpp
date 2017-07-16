/*=====================================================================================*/
/**
 * ipc_lb_gtest.cpp
 * author : puch
 * date : Oct 22 2015
 *
 * description : Any comments
 *
 */
/*=====================================================================================*/
#define CLASS_IMPLEMENTATION
#undef Dbg_FID
#define Dbg_FID Dbg_FID_Def(GTEST_FID,1)
/*=====================================================================================*
 * Project Includes
 *=====================================================================================*/
#include "gtest/gtest.h"
#include "dbg_log.h"
#include "gtest_task_ext.h"
#include "ipc.h"
#include "ipc_ext.h"
#include "ipc_gtest_worker.h"
#include "ipc_light.h"
#include "ipc_linux_task.h"
#include "ipc_linux_timestamp.h"
#include "task_ext.h"
/*=====================================================================================* 
 * Standard Includes
 *=====================================================================================*/
#include <iostream>
#include <unistd.h>
/*=====================================================================================* 
 * Local X-Macros
 *=====================================================================================*/

/*=====================================================================================* 
 * Local Define Macros
 *=====================================================================================*/

/*=====================================================================================* 
 * Local Type Definitions
 *=====================================================================================*/
 
/*=====================================================================================* 
 * Local Function Prototypes
 *=====================================================================================*/

/*=====================================================================================* 
 * Local Object Definitions
 *=====================================================================================*/
static IPC_Mail_Id_T Gtest_Mailist[] =
{
      IPC_GTEST_SUBS_MID
};
/*=====================================================================================* 
 * Exported Object Definitions
 *=====================================================================================*/

/*=====================================================================================* 
 * Local Inline-Function Like Macros
 *=====================================================================================*/

/*=====================================================================================* 
 * Local Function Definitions
 *=====================================================================================*/
bool_t Task_Register_To_Process(Task_T * const task)
{
   IPC_T * ipc = NULL;
   IPC_get_instance(&ipc);
   Isnt_Nullptr(ipc, false);
   return ipc->vtbl->register_task(ipc, task);
}

bool_t Task_Unregister_To_Process(Task_T * const task)
{
   IPC_T * ipc = NULL;
   IPC_get_instance(&ipc);
   Isnt_Nullptr(ipc, false);
   return ipc->vtbl->unregister_task(ipc, task);
}

void IPC_get_instance(IPC_T ** singleton)
{
   static IPC_Linux_Task_T linux_task = IPC_Linux_Task();
   static IPC_Linux_Timestamp_T linux_timestamp = IPC_Linux_Timestamp();
   static IPC_Light_T light = IPC_Light();
   static bool_t once = false;

   if(!once)
   {
      linux_task.vtbl->ctor(&linux_task,&light.IPC);
      linux_timestamp.vtbl->ctor(&linux_timestamp, &linux_task.IPC_Decorator.IPC);
   }

   *singleton = &linux_timestamp.IPC_Decorator.IPC;
}
/*=====================================================================================* 
 * Exported Function Definitions
 *=====================================================================================*/
TEST(Init, tasks)
{
   static IPC_Gtest_Worker_T w1 = IPC_Gtest_Worker();
   static IPC_Gtest_Worker_T w2 = IPC_Gtest_Worker();

   w1.vtbl->ctor(&w1, IPC_GTEST_1_WORKER, 64);
   w2.vtbl->ctor(&w2, IPC_GTEST_2_WORKER, 64);

   Task_Register_To_Process(NULL);
   IPC_Create_Mailbox(64, 256);
   IPC_Task_Ready();

   IPC_Run(IPC_GTEST_1_WORKER);
   IPC_Run(IPC_GTEST_2_WORKER);

   sleep(1);
   ASSERT_EQ(GTEST_FWK_WORKER, IPC_Self_Task_Id());
}

TEST(Timestamp, functions)
{
   EXPECT_TRUE(0 < IPC_Timestamp());

   IPC_Timestamp_T sleep_ms = IPC_Timestamp() + 1000U;
   EXPECT_FALSE(IPC_Time_Elapsed(sleep_ms));
   Dbg_Warn("sleep_ms = %u", sleep_ms);

   sleep(2);
   EXPECT_TRUE(IPC_Time_Elapsed(sleep_ms));
}

TEST(Retrieve_mail, mail)
{
   Mail_T const * mail = NULL;
   IPC_Send(IPC_GTEST_1_WORKER, IPC_GTEST_EV_MID, NULL, 0);
   IPC_Send(IPC_GTEST_2_WORKER, IPC_GTEST_EV_MID, NULL, 0);
   sleep(1);
   for(uint8_t i = 2; i; --i)
   {
      mail = IPC_Retreive_Mail(2000);
      ASSERT_FALSE(NULL == mail);
      EXPECT_EQ(mail->mail_id, IPC_GTEST_EV_MID);
   }
}

TEST(Retrieve_Mail, timeout)
{
   IPC_Timestamp_T timestamp = IPC_RETRIEVE_TOUT_MS + IPC_Timestamp();
   Mail_T const * mail = IPC_Retreive_Mail(IPC_RETRIEVE_TOUT_MS);
   sleep(1);
   EXPECT_TRUE(IPC_Time_Elapsed(timestamp));
   ASSERT_TRUE(NULL == mail);
}

TEST(Publish, mail)
{
   IPC_Publish(IPC_GTEST_SUBS_MID, NULL, 0);

   if(IPC_Subscribe_Mail_List(Gtest_Mailist, sizeof(Gtest_Mailist)) )
   {
      Mail_T const * mail = NULL;

      for(uint8_t i = 2; i; --i)
      {
         mail = IPC_Retreive_From_Mail_List(Gtest_Mailist,
               sizeof(Gtest_Mailist), 2000);
         ASSERT_FALSE(NULL == mail);
         EXPECT_EQ(mail->mail_id, IPC_GTEST_SUBS_MID);
      }
      mail = IPC_Retreive_From_Mail_List(Gtest_Mailist,
                     sizeof(Gtest_Mailist), IPC_RETRIEVE_TOUT_MS);
      ASSERT_TRUE(NULL == mail);

      bool_t success = IPC_Unsubscribe_Mail_List(Gtest_Mailist, sizeof(Gtest_Mailist));
      ASSERT_TRUE(success);
   }
   else
   {
      FAIL();
   }
}


TEST(Shutdown, mail)
{
   IPC_Broadcast(WORKER_SHUTDOWN_MID, NULL, 0);
//   IPC_Wait(IPC_GTEST_1_WORKER);
//   IPC_Wait(IPC_GTEST_2_WORKER);
}

int Gtest_Task_Cbk(int argc, char ** argv)
{
   std::cout << "Gtest_Task_Cbk main()\n";
   testing::InitGoogleTest(&argc, argv);
   return RUN_ALL_TESTS();
}

/*=====================================================================================* 
 * ipc_lb_gtest.cpp
 *=====================================================================================*
 * Log History
 *
 *=====================================================================================*/
