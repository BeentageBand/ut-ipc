/*=====================================================================================*/
/**
 * ipc_gtest.cpp
 * author : puch
 * date : Oct 22 2015
 *
 * description : Any comments
 *
 */
/*=====================================================================================*/
#define CLASS_IMPLEMENTATION
/*=====================================================================================*
 * Project Includes
 *=====================================================================================*/
#include "gtest/gtest.h"
#include "ipc_gtest.h"
#include "ipc.h"
#include "ipc_ext.h"
#include "ipc_linux_task.h"
#include "ipc_linux_timestamp.h"
#include "ipc_light.h"
#include "task_ext.h"
#include "publisher_ext.h"
/*=====================================================================================* 
 * Standard Includes
 *=====================================================================================*/

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
      IPC_GTEST_SUBS
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
   return true;
}

bool_t Task_Unregister_To_Process(Task_T * const task)
{
   return true;
}


void IPC_get_instance(IPC_T ** singleton)
{
   static IPC_Linux_Task_T linux_task = IPC_Linux_Task();
   static IPC_Linux_Timestamp_T linux_timestamp = IPC_Linux_Timestamp();
   static IPC_Light_T light = IPC_Light();

   linux_task.vtbl->ctor(&linux_task,&light.IPC);
   linux_timestamp.vtbl->ctor(&linux_timestamp, &linux_task.IPC_Decorator.IPC);
   *singleton = &linux_timestamp.IPC_Decorator.IPC;
}


void Publisher_get_instance(Publisher_T ** singleton)
{

}
/*=====================================================================================* 
 * Exported Function Definitions
 *=====================================================================================*/
TEST(Init, tasks)
{
   static Task_T test = Task();
   static IPC_Gtest_Worker_T w1 = IPC_Gtest_Worker();
   static IPC_Gtest_Worker_T w2 = IPC_Gtest_Worker();

   test.vtbl->ctor(&test, GTEST_FWK_WORKER);
   w1.vtbl->ctor(&w1, IPC_GTEST_1_WORKER, 64);
   w2.vtbl->ctor(&w2, IPC_GTEST_2_WORKER, 64);

   Task_Register_To_Process(NULL);
   IPC_Create_Mailbox(64, 256);
   IPC_Task_Ready();

   w1.Worker.Task.vtbl->run(&w1.Worker.Task);
   w2.Worker.Task.vtbl->run(&w2.Worker.Task);
}

TEST(Retrieve_mail, mail)
{
   Mail_T * mail = NULL;

   for(uint8_t i = 2; i; --i)
   {
      mail = IPC_Retreive_Mail(IPC_RETRIEVE_TOUT_MS);
      ASSERT_FALSE(NULL == mail);
      EXPECT_EQ(mail->mail_id, IPC_GTEST_EV);
   }

}

TEST(Retrieve_Mail, timeout)
{
   IPC_Timestamp_T timestamp = IPC_RETRIEVE_TOUT_MS + IPC_Timestamp();
   Mail_T * mail = IPC_Retreive_Mail(IPC_RETRIEVE_TOUT_MS);

   EXPECT_TRUE(IPC_Time_Elapsed(timestamp));
   ASSERT_TRUE(NULL == mail);
}

TEST(Publish, mail)
{
   IPC_Publish(IPC_GTEST_SUBS, NULL, 0);

   if(IPC_Subscribe_Mail_List(Gtest_Mailist, sizeof(Gtest_Mailist)) )
   {
      Mail_T * mail = NULL;

      for(uint8_t i = 2; i; --i)
      {
         mail = IPC_Retreive_From_Mail_List(Gtest_Mailist,
               sizeof(Gtest_Mailist), IPC_RETRIEVE_TOUT_MS);
         ASSERT_FALSE(NULL == mail);
         EXPECT_EQ(mail->mail_id, IPC_GTEST_SUBS);
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
   IPC_Broadcast(WORKER_SHUTDOWN, NULL, 0);
}

/*=====================================================================================* 
 * ipc_gtest.cpp
 *=====================================================================================*
 * Log History
 *
 *=====================================================================================*/
