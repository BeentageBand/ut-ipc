#define CLASS_IMPLEMENTATION
 
#include "gtest/gtest.h"
#include "publisher.h"
#include "mailbox.h"

static union Mailbox Subscribable_Mbx = {NULL};
static union Mail Subs_Mbx_Buff[23] = {0};
 
TEST(Publisher, Subscribe)
{
   IPC_MID_T mid = IPC_GTEST_PBC_MID;

   Populate_Mailbox(&Subscribable_Mbx, GTEST_FWK_WORKER_TID, Subs_Mbx_Buff, Num_Elems(Subs_Mbx_Buff));

   ASSERT_TRUE( Publisher_Subscribe(&Subscribable_Mbx, mid) );
}

TEST(Publisher, Publish)
{
	Publisher_Publish(IPC_GTEST_PBC_MID, NULL, 0);

	union Mail retrieved_mail = {NULL};
	Subscribable_Mbx.vtbl->retrieve(&Subscribable_Mbx, &retrieved_mail);
	EXPECT_EQ(IPC_GTEST_PBC_MID, retrieved_mail.mid );

	Publisher_Publish(IPC_GTEST_INT_MID, NULL, 0);
	Subscribable_Mbx.vtbl->retrieve(&Subscribable_Mbx, &retrieved_mail);
}

TEST(Publisher, Unsubscribe)
{
   IPC_MID_T mid = IPC_GTEST_PBC_MID;
   ASSERT_TRUE( Publisher_Unsubscribe(&Subscribable_Mbx, mid) );
   _delete(&Subscribable_Mbx);
}
