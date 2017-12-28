#include "gtest/gtest.h"
#include "mail.h"
 
static union Mail GMail = {NULL};
 
TEST(Mail, Ctor)
{
   int a = 3;
   Populate_Mail(&GMail, IPC_GTEST_INT_MID, IPC_GTEST_1_WORKER_TID, GTEST_FWK_WORKER_TID, &a, sizeof(a));

   EXPECT_EQ(IPC_GTEST_INT_MID, GMail.mid);
   EXPECT_EQ(IPC_GTEST_1_WORKER_TID, GMail.sender);
   EXPECT_EQ(GTEST_FWK_WORKER_TID, GMail.receiver);
   EXPECT_EQ(sizeof(a), GMail.pay_size);

   ASSERT_FALSE(NULL == GMail.payload);
   EXPECT_EQ(a, (*(int *)GMail.payload));
}

TEST(Mail, Set_payload)
{
   char str[] = "Helloworld!";
   GMail.vtbl->set_payload(&GMail, str, sizeof(str));

   EXPECT_EQ(IPC_GTEST_INT_MID, GMail.mid);
   EXPECT_EQ(IPC_GTEST_1_WORKER_TID, GMail.sender);
   EXPECT_EQ(GTEST_FWK_WORKER_TID, GMail.receiver);
   EXPECT_EQ(sizeof(str), GMail.pay_size);

   ASSERT_FALSE(NULL == GMail.payload);
   EXPECT_STRCASEEQ(str, ((char const *)GMail.payload));

   GMail.vtbl->set_mid(&GMail, IPC_GTEST_PBC_MID);

   EXPECT_EQ(IPC_GTEST_PBC_MID, GMail.mid);
   EXPECT_EQ(IPC_GTEST_1_WORKER_TID, GMail.sender);
   EXPECT_EQ(GTEST_FWK_WORKER_TID, GMail.receiver);
   EXPECT_EQ(sizeof(str), GMail.pay_size);

   ASSERT_FALSE(NULL == GMail.payload);
   EXPECT_STRCASEEQ(str, ((char const *)GMail.payload));

   GMail.vtbl->set_sender(&GMail, IPC_GTEST_2_WORKER_TID);

   EXPECT_EQ(IPC_GTEST_PBC_MID, GMail.mid);
   EXPECT_EQ(IPC_GTEST_2_WORKER_TID, GMail.sender);
   EXPECT_EQ(GTEST_FWK_WORKER_TID, GMail.receiver);
   EXPECT_EQ(sizeof(str), GMail.pay_size);

   ASSERT_FALSE(NULL == GMail.payload);
   EXPECT_STRCASEEQ(str, ((char const *)GMail.payload));

   GMail.vtbl->set_receiver(&GMail, IPC_GTEST_1_WORKER_TID);

   EXPECT_EQ(IPC_GTEST_PBC_MID, GMail.mid);
   EXPECT_EQ(IPC_GTEST_2_WORKER_TID, GMail.sender);
   EXPECT_EQ(IPC_GTEST_1_WORKER_TID, GMail.receiver);
   EXPECT_EQ(sizeof(str), GMail.pay_size);

   ASSERT_FALSE(NULL == GMail.payload);
   EXPECT_STRCASEEQ(str, ((char const *)GMail.payload));
}

TEST(Mail, Destroy)
{
   _delete(&GMail);

   EXPECT_TRUE(NULL == GMail.payload);
   EXPECT_EQ(0UL, GMail.pay_size);
}
