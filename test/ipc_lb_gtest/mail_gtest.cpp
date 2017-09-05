/*=====================================================================================*/
/**
 * mail_gtest.cpp
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
#include "mail.h"
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
static Mail_T GMail;
/*=====================================================================================* 
 * Exported Object Definitions
 *=====================================================================================*/

/*=====================================================================================* 
 * Local Inline-Function Like Macros
 *=====================================================================================*/

/*=====================================================================================* 
 * Local Function Definitions
 *=====================================================================================*/

/*=====================================================================================* 
 * Exported Function Definitions
 *=====================================================================================*/
TEST(Mail, Ctor)
{
   GMail = Mail();
   int a = 3;
   GMail.vtbl->ctor(&GMail, IPC_GTEST_EV_MID, IPC_GTEST_1_WORKER, GTEST_FWK_WORKER, &a, sizeof(a));

   EXPECT_EQ(IPC_GTEST_EV_MID, GMail.mail_id);
   EXPECT_EQ(IPC_GTEST_1_WORKER, GMail.sender_task);
   EXPECT_EQ(GTEST_FWK_WORKER, GMail.receiver_task);
   EXPECT_FALSE(GMail.is_dumpable);
   EXPECT_EQ(sizeof(a), GMail.data_size);

   ASSERT_FALSE(NULL == GMail.data);
   EXPECT_EQ(a, (*(int *)GMail.data));


}

TEST(Mail, Set_Data)
{
   char str[] = "Helloworld!";
   GMail.vtbl->set_data(&GMail, str, sizeof(str));

   EXPECT_EQ(IPC_GTEST_EV_MID, GMail.mail_id);
   EXPECT_EQ(IPC_GTEST_1_WORKER, GMail.sender_task);
   EXPECT_EQ(GTEST_FWK_WORKER, GMail.receiver_task);
   EXPECT_FALSE(GMail.is_dumpable);
   EXPECT_EQ(sizeof(str), GMail.data_size);

   ASSERT_FALSE(NULL == GMail.data);
   EXPECT_STRCASEEQ(str, ((char const *)GMail.data));

   GMail.vtbl->set_mail_id(&GMail, IPC_GTEST_SUBS_MID);

   EXPECT_EQ(IPC_GTEST_SUBS_MID, GMail.mail_id);
   EXPECT_EQ(IPC_GTEST_1_WORKER, GMail.sender_task);
   EXPECT_EQ(GTEST_FWK_WORKER, GMail.receiver_task);
   EXPECT_FALSE(GMail.is_dumpable);
   EXPECT_EQ(sizeof(str), GMail.data_size);

   ASSERT_FALSE(NULL == GMail.data);
   EXPECT_STRCASEEQ(str, ((char const *)GMail.data));

   GMail.vtbl->set_sender_task(&GMail, IPC_GTEST_2_WORKER);

   EXPECT_EQ(IPC_GTEST_SUBS_MID, GMail.mail_id);
   EXPECT_EQ(IPC_GTEST_2_WORKER, GMail.sender_task);
   EXPECT_EQ(GTEST_FWK_WORKER, GMail.receiver_task);
   EXPECT_FALSE(GMail.is_dumpable);
   EXPECT_EQ(sizeof(str), GMail.data_size);

   ASSERT_FALSE(NULL == GMail.data);
   EXPECT_STRCASEEQ(str, ((char const *)GMail.data));

   GMail.vtbl->set_receiver_task(&GMail, IPC_GTEST_1_WORKER);

   EXPECT_EQ(IPC_GTEST_SUBS_MID, GMail.mail_id);
   EXPECT_EQ(IPC_GTEST_2_WORKER, GMail.sender_task);
   EXPECT_EQ(IPC_GTEST_1_WORKER, GMail.receiver_task);
   EXPECT_FALSE(GMail.is_dumpable);
   EXPECT_EQ(sizeof(str), GMail.data_size);

   ASSERT_FALSE(NULL == GMail.data);
   EXPECT_STRCASEEQ(str, ((char const *)GMail.data));
}

TEST(Mail, Destroy)
{
   GMail.object_vtbl->destroy(&GMail.object);

   EXPECT_TRUE(NULL == GMail.data);
   EXPECT_EQ(0UL, GMail.data_size);
}
/*=====================================================================================* 
 * mail_gtest.cpp
 *=====================================================================================*
 * Log History
 *
 *=====================================================================================*/
