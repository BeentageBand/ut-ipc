#include "ipc_factory_mock.h"
#include "ccmailbox.h"

using namespace cc;
using namespace std;
using namespace ::testing;

class Mock_Mux : public Mutex
{
    public:
    MOCK_METHOD1(lock, bool (uint32_t const tout_ms));
    MOCK_METHOD0(unlock, void ());
};

class Mock_Cond_Var : public Cond_Var
{
    public:
    MOCK_METHOD1(with_mutex, bool (shared_ptr<Mutex> mux));
    MOCK_METHOD1(wait, bool (uint32_t const wait_ms));
    MOCK_METHOD0(signal, void ());
};

class Gtest_Mailbox : public Test
{
    public:
    IPC_TID_T tid;
    shared_ptr<Mock_Mux> mock_mux;
    shared_ptr<Mock_Cond_Var> mock_cv;
    shared_ptr<Mailbox> mailbox;
    NiceMock<Mock_Factory> factory;

    void SetUp(void)
    {
        using ::testing::_;
        this->tid = IPC_GTEST_1_WORKER_TID;
        this->mock_mux = make_shared<NiceMock<Mock_Mux>>();
        this->mock_cv = make_shared<NiceMock<Mock_Cond_Var>>();
        EXPECT_CALL(factory, create_mutex()).WillOnce(Return(this->mock_mux));
        EXPECT_CALL(factory, create_cond_var()).WillOnce(Return(this->mock_cv));
        EXPECT_CALL(*this->mock_cv, with_mutex(_)).WillOnce(Return(true));

        this->mailbox = make_shared<Mailbox>(this->tid, factory);
    }
};

TEST(Mailbox, constructor)
{
    using ::testing::_;
    shared_ptr<Mock_Mux> mock_mux = make_shared<NiceMock<Mock_Mux>>();
    shared_ptr<Mock_Cond_Var> mock_cv = make_shared<NiceMock<Mock_Cond_Var>>();

    EXPECT_CALL(*mock_cv, with_mutex(_)).WillOnce(Return(true));

    shared_ptr<Mailbox> mailbox = make_shared<Mailbox>(IPC_GTEST_1_WORKER_TID, mock_mux, mock_cv);
    ASSERT_EQ(mailbox->tid, IPC_GTEST_1_WORKER_TID);
}

TEST_F(Gtest_Mailbox, push_and_tail)
{
    using ::testing::Return;
    Mail mail(WORKER_INT_SHUTDOWN_MID, this->tid);
    EXPECT_CALL(*this->mock_mux, lock(200)).WillOnce(Return(true));
    EXPECT_CALL(*this->mock_cv, signal());
    EXPECT_CALL(*this->mock_mux, unlock());
    this->mailbox->push(mail);


    EXPECT_CALL(*this->mock_mux, lock(1000)).WillOnce(Return(true));
    EXPECT_CALL(*this->mock_mux, unlock());

    shared_ptr<Mail> rcv_mail = this->mailbox->tail(1000);
    ASSERT_TRUE(rcv_mail);
}

TEST_F(Gtest_Mailbox, tail_with_mid)
{

}
