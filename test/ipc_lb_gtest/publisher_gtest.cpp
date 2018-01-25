#define CLASS_IMPLEMENTATION
 
#include "gtest/gtest.h"
#include "ipc.h"
#include "publisher.h"
#include "mailbox.h"

static union Mailbox Subscribable_Mbx = {NULL};
static union Mail Subs_Mbx_Buff[23] = {0};
 
TEST(Publisher, Subscribe)
{
   IPC_MID_T mid = IPC_GTEST_PBC_MID;

   Populate_Mailbox(&Subscribable_Mbx, GTEST_FWK_WORKER_TID, Subs_Mbx_Buff, Num_Elems(Subs_Mbx_Buff));

   IPC_Register_Mailbox(&Subscribable_Mbx);

   ASSERT_TRUE( Publisher_Subscribe(GTEST_FWK_WORKER_TID, mid) );
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

   IPC_Unregister_Mailbox(&Subscribable_Mbx);
   ASSERT_TRUE( Publisher_Unsubscribe(GTEST_FWK_WORKER_TID, mid) );
   _delete(&Subscribable_Mbx);
}
