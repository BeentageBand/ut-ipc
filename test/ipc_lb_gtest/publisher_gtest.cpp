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
	union Mail published_mail = {NULL};

	Populate_Mail(&published_mail, IPC_GTEST_PBC_MID, GTEST_FWK_WORKER_TID, (IPC_TID_T const)0, NULL, 0);
	Publisher_Publish(&published_mail);

	_delete(&published_mail);

	union Mail retrieved_mail = {NULL};
	Subscribable_Mbx.vtbl->retrieve(&Subscribable_Mbx, &retrieved_mail);
	EXPECT_EQ(IPC_GTEST_PBC_MID, retrieved_mail.mid );

	Populate_Mail(&published_mail, IPC_GTEST_INT_MID, GTEST_FWK_WORKER_TID, (IPC_TID_T const)0, NULL, 0);
	Publisher_Publish(&published_mail);
	Subscribable_Mbx.vtbl->retrieve(&Subscribable_Mbx, &retrieved_mail);

	_delete(&published_mail);
}

TEST(Publisher, Unsubscribe)
{
   IPC_MID_T mid = IPC_GTEST_PBC_MID;
   ASSERT_TRUE( Publisher_Unsubscribe(&Subscribable_Mbx, mid) );
   _delete(&Subscribable_Mbx);
}
