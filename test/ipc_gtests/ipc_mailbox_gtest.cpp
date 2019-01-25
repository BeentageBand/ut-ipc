#include "gmock/gmock.h"
#include "ccmailbox.h"

using namespace cc;
using namespace std;
using namespace ::testing;

class Mock_Mailbox_Mux : public Mailbox::Mux
{
    public:
    MOCK_METHOD1(lock, bool (uint32_t const tout_ms));
    MOCK_METHOD1(wait, bool (uint32_t const wait_ms));
    MOCK_METHOD0(signal, void ());
    MOCK_METHOD0(unlock, void ());
};

class Gtest_Mailbox : public Test
{
    public:
    IPC_TID_T tid;
    shared_ptr<Mock_Mailbox_Mux> mock_mux;
    shared_ptr<Mailbox> mailbox;

    void SetUp(void)
    {
        this->tid = IPC_GTEST_1_WORKER_TID;
        this->mock_mux = make_shared<NiceMock<Mock_Mailbox_Mux>>();
        this->mailbox = make_shared<Mailbox>(this->tid, this->mock_mux);
    }
};

TEST(Mailbox, constructor)
{
    shared_ptr<Mock_Mailbox_Mux> mock_mux = make_shared<NiceMock<Mock_Mailbox_Mux>>();
    shared_ptr<Mailbox> mailbox = make_shared<Mailbox>(IPC_GTEST_1_WORKER_TID, mock_mux);
    ASSERT_EQ(mailbox->tid, IPC_GTEST_1_WORKER_TID);
}

TEST_F(Gtest_Mailbox, push_and_tail)
{
    using ::testing::Return;
    Mail mail(WORKER_INT_SHUTDOWN_MID, this->tid);
    EXPECT_CALL(*this->mock_mux, lock(200)).WillOnce(Return(true));
    EXPECT_CALL(*this->mock_mux, signal());
    EXPECT_CALL(*this->mock_mux, unlock());
    this->mailbox->push(mail);

    shared_ptr<Mail> rcv_mail = this->mailbox->tail(1000);
    ASSERT_TRUE(rcv_mail);
}

TEST_F(Gtest_Mailbox, tail)
{

}

TEST_F(Gtest_Mailbox, tail_with_mid)
{

}
