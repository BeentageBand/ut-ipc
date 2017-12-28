#define CLASS_IMPLEMENTATION
 
#include "gtest/gtest.h"
#include "mailbox.h"
 
struct Mailpayload
{
   IPC_MID_T mid;
   IPC_TID_T tid;
};

class Mailbox_Test_Obj : public ::testing::TestWithParam<struct Mailpayload>
{};
 
static union Mailbox GMailbox = {NULL};
static union Mail GMailbox_Buff[64] = {0};

static struct Mailpayload MailData [] =
{
   {IPC_GTEST_PBC_MID, IPC_GTEST_1_WORKER_TID},
   {IPC_GTEST_PBC_MID, IPC_GTEST_2_WORKER_TID},
   {IPC_GTEST_PBC_MID, GTEST_FWK_WORKER_TID},
   {IPC_GTEST_INT_MID, IPC_GTEST_1_WORKER_TID},
   {IPC_GTEST_INT_MID, IPC_GTEST_2_WORKER_TID},
   {IPC_GTEST_INT_MID, GTEST_FWK_WORKER_TID},
   {WORKER_INT_SHUTDOWN_MID, IPC_GTEST_1_WORKER_TID},
   {WORKER_INT_SHUTDOWN_MID, IPC_GTEST_2_WORKER_TID},
   {WORKER_INT_SHUTDOWN_MID, GTEST_FWK_WORKER_TID},
};
 
TEST(Mailbox, Populate)
{
   Populate_Mailbox(&GMailbox, GTEST_FWK_WORKER_TID, GMailbox_Buff, Num_Elems(GMailbox_Buff));

   EXPECT_EQ(GTEST_FWK_WORKER_TID, GMailbox.tid);
   EXPECT_EQ(64UL, GMailbox.mailbox.capacity);
}

TEST_P(Mailbox_Test_Obj, Push_Mail)
{
	union Mail mail = {NULL};
	struct Mailpayload const & test_mail = GetParam();

	Populate_Mail(&mail, test_mail.mid, test_mail.tid, GTEST_FWK_WORKER_TID, NULL, 0);

	GMailbox.vtbl->push_mail(&GMailbox, &mail);

	union Mail actual_mail = {NULL};
	GMailbox.vtbl->retrieve(&GMailbox, &actual_mail);

	EXPECT_EQ(mail.mid, actual_mail.mid);

	_delete(&mail);
}

INSTANTIATE_TEST_CASE_P(Mailist, Mailbox_Test_Obj, ::testing::ValuesIn(MailData));

TEST(Mailbox, Delete)
{
	_delete(&GMailbox);
   EXPECT_EQ(0U, GMailbox.mailbox.i);
}
