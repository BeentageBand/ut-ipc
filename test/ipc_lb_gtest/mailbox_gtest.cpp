/*=====================================================================================*/
/**
 * mailbox_gtest.cpp
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
#include "mailbox.h"
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
struct MailData
{
   IPC_Mail_Id_T mid;
   IPC_Task_Id_T tid;
};

class Mailbox_Test_Obj : public ::testing::TestWithParam<struct MailData>
{};
/*=====================================================================================* 
 * Local Function Prototypes
 *=====================================================================================*/

/*=====================================================================================* 
 * Local Object Definitions
 *=====================================================================================*/
static Mailbox_T GMailbox;

static struct MailData MailData [] =
{
   {IPC_GTEST_SUBS_MID, IPC_GTEST_1_WORKER},
   {IPC_GTEST_SUBS_MID, IPC_GTEST_2_WORKER},
   {IPC_GTEST_SUBS_MID, GTEST_FWK_WORKER},
   {IPC_GTEST_EV_MID, IPC_GTEST_1_WORKER},
   {IPC_GTEST_EV_MID, IPC_GTEST_2_WORKER},
   {IPC_GTEST_EV_MID, GTEST_FWK_WORKER},
   {WORKER_SHUTDOWN_MID, IPC_GTEST_1_WORKER},
   {WORKER_SHUTDOWN_MID, IPC_GTEST_2_WORKER},
   {WORKER_SHUTDOWN_MID, GTEST_FWK_WORKER},
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

/*=====================================================================================* 
 * Exported Function Definitions
 *=====================================================================================*/
TEST(Mailbox, Ctor)
{
   GMailbox = Mailbox();
   GMailbox.vtbl->ctor(&GMailbox, GTEST_FWK_WORKER, 64, 64);

   EXPECT_EQ(GTEST_FWK_WORKER, GMailbox.owner);
   EXPECT_EQ(64UL, GMailbox.data_size);
}

TEST_P(Mailbox_Test_Obj, Push_Mail)
{
   Mail_T mail = Mail();
   struct MailData const & test_mail = GetParam();

   mail.vtbl->ctor(&mail, test_mail.mid, test_mail.tid, GTEST_FWK_WORKER, NULL, 0);

   GMailbox.vtbl->push_mail(&GMailbox, &mail);

   Mail_T const * actual_mail = GMailbox.vtbl->pop_mail(&GMailbox);

   ASSERT_FALSE(NULL == actual_mail);
   EXPECT_EQ(mail.mail_id, actual_mail->mail_id);

   mail.object_vtbl->destroy(&mail.object);
}

TEST_P(Mailbox_Test_Obj, Pop_Mail)
{
   Mail_T const * mail = GMailbox.vtbl->pop_mail(&GMailbox);

   ASSERT_FALSE(NULL == mail);
   EXPECT_EQ(GetParam().mid, mail->mail_id);
   EXPECT_EQ(GetParam().tid, mail->sender_task);
   EXPECT_EQ(GetParam().tid, mail->receiver_task);
   EXPECT_EQ(0U, mail->data_size);
   ASSERT_TRUE(NULL == mail->data);
}

INSTANTIATE_TEST_CASE_P(Mailist, Mailbox_Test_Obj, ::testing::ValuesIn(MailData));

TEST(Mailbox, dump)
{
   GMailbox.vtbl->dump(&GMailbox);
   EXPECT_EQ(0U, GMailbox.mailbox.size);
   EXPECT_TRUE(GMailbox.mailbox.vtbl->empty(&GMailbox.mailbox));
}
/*=====================================================================================* 
 * mailbox_gtest.cpp
 *=====================================================================================*
 * Log History
 *
 *=====================================================================================*/
