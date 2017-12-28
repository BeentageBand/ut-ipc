#include "gtest/gtest.h"
#include "mail.h"
 
static union Mail GMail;
 
TEST(Mail, Ctor)
{
   int a = 3;
   Populate_Mail(&GMail, IPC_GTEST_EV_MID, IPC_GTEST_1_WORKER, GTEST_FWK_WORKER, &a, sizeof(a));

   EXPECT_EQ(IPC_GTEST_EV_MID, GMail.mid);
   EXPECT_EQ(IPC_GTEST_1_WORKER, GMail.sender);
   EXPECT_EQ(GTEST_FWK_WORKER, GMail.receiver);
   EXPECT_FALSE(GMail.is_dumpable);
   EXPECT_EQ(sizeof(a), GMail.pay_size);

   ASSERT_FALSE(NULL == GMail.payload);
   EXPECT_EQ(a, (*(int *)GMail.payload));


}

TEST(Mail, Set_payload)
{
   char str[] = "Helloworld!";
   GMail.vtbl->set_payload(&GMail, str, sizeof(str));

   EXPECT_EQ(IPC_GTEST_EV_MID, GMail.mid);
   EXPECT_EQ(IPC_GTEST_1_WORKER, GMail.sender);
   EXPECT_EQ(GTEST_FWK_WORKER, GMail.receiver);
   EXPECT_FALSE(GMail.is_dumpable);
   EXPECT_EQ(sizeof(str), GMail.pay_size);

   ASSERT_FALSE(NULL == GMail.payload);
   EXPECT_STRCASEEQ(str, ((char const *)GMail.payload));

   GMail.vtbl->set_mid(&GMail, IPC_GTEST_SUBS_MID);

   EXPECT_EQ(IPC_GTEST_SUBS_MID, GMail.mid);
   EXPECT_EQ(IPC_GTEST_1_WORKER, GMail.sender);
   EXPECT_EQ(GTEST_FWK_WORKER, GMail.receiver);
   EXPECT_FALSE(GMail.is_dumpable);
   EXPECT_EQ(sizeof(str), GMail.pay_size);

   ASSERT_FALSE(NULL == GMail.payload);
   EXPECT_STRCASEEQ(str, ((char const *)GMail.payload));

   GMail.vtbl->set_sender(&GMail, IPC_GTEST_2_WORKER);

   EXPECT_EQ(IPC_GTEST_SUBS_MID, GMail.mid);
   EXPECT_EQ(IPC_GTEST_2_WORKER, GMail.sender);
   EXPECT_EQ(GTEST_FWK_WORKER, GMail.receiver);
   EXPECT_FALSE(GMail.is_dumpable);
   EXPECT_EQ(sizeof(str), GMail.pay_size);

   ASSERT_FALSE(NULL == GMail.payload);
   EXPECT_STRCASEEQ(str, ((char const *)GMail.payload));

   GMail.vtbl->set_receiver(&GMail, IPC_GTEST_1_WORKER);

   EXPECT_EQ(IPC_GTEST_SUBS_MID, GMail.mid);
   EXPECT_EQ(IPC_GTEST_2_WORKER, GMail.sender);
   EXPECT_EQ(IPC_GTEST_1_WORKER, GMail.receiver);
   EXPECT_FALSE(GMail.is_dumpable);
   EXPECT_EQ(sizeof(str), GMail.pay_size);

   ASSERT_FALSE(NULL == GMail.payload);
   EXPECT_STRCASEEQ(str, ((char const *)GMail.payload));
}

TEST(Mail, Destroy)
{
   GMail.object_vtbl->destroy(&GMail.object);

   EXPECT_TRUE(NULL == GMail.payload);
   EXPECT_EQ(0UL, GMail.pay_size);
}
/*=====================================================================================* 
 * mail_gtest.cpp
 *=====================================================================================*
 * Log History
 *
 *=====================================================================================*/
