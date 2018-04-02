#define CLASS_IMPLEMENTATION
 
#include "gtest/gtest.h"
#include "ipc.h"
#include "publisher.h"
#include "mailbox.h"

 
TEST(Publisher, Subscribe)
{
   IPC_MID_T mid = IPC_GTEST_PBC_MID;

   ASSERT_TRUE( Publisher_Subscribe(GTEST_FWK_WORKER_TID, mid) );
}

TEST(Publisher, Publish)
{
	Publisher_Publish(IPC_GTEST_PBC_MID, NULL, 0);

	union Mail retrieved_mail = {NULL};
	bool is_published = IPC_Retrieve_Mail(&retrieved_mail, 2000);
	EXPECT_TRUE(is_published);
	EXPECT_EQ(IPC_GTEST_PBC_MID, retrieved_mail.mid );

	Publisher_Publish(IPC_GTEST_INT_MID, NULL, 0);

	is_published = IPC_Retrieve_Mail(&retrieved_mail, 2000);
	EXPECT_FALSE(is_published);
}

TEST(Publisher, Unsubscribe)
{
   IPC_MID_T mid = IPC_GTEST_PBC_MID;

   ASSERT_TRUE( Publisher_Unsubscribe(GTEST_FWK_WORKER_TID, mid) );
}
