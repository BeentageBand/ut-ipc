#include "gmock/gmock.h"
#include "ccthread.h"

using namespace ::testing;
using namespace cc;
using namespace std;

class Mock_Thread_Sem : public Thread::Sem 
{
    public:
    MOCK_METHOD0(wait, void ());
    MOCK_METHOD1(wait, void (uint32_t wait_ms));
    MOCK_METHOD0(ready, void ());
};

class Mock_Thread_Cbk : public Thread::Cbk
{
    public:
    MOCK_METHOD1(register_thread, int (Thread & thread));
    MOCK_METHOD1(create_thread, int (Thread & thread));
    MOCK_METHOD1(cancel_thread, int (void *& exit ));
    MOCK_METHOD0(join_thread, int());
};

class Gtest_Thread : public Test
{
    public:
        IPC_TID_T tid;
        shared_ptr<Mock_Thread_Cbk> mock_cbk;
        shared_ptr<Mock_Thread_Sem> mock_sem;
        shared_ptr<Thread> thread;

    void SetUp(void)
    {
        this->tid = IPC_GTEST_1_WORKER_TID;
        this->mock_cbk = make_shared<NiceMock<Mock_Thread_Cbk>>();
        this->mock_sem = make_shared<NiceMock<Mock_Thread_Sem>>();
        this->thread = make_shared<Thread>(this->tid, this->mock_sem, this->mock_cbk);
    }

    void TearDown(void)
    {
    }

};

TEST(Thread, constructor)
{
    using ::testing::_;

    shared_ptr<NiceMock<Mock_Thread_Cbk>> mock_cbk = make_shared<NiceMock<Mock_Thread_Cbk>>();
    
    EXPECT_CALL(*mock_cbk, register_thread(_));
    shared_ptr<Thread> thread =  make_shared<Thread>(IPC_GTEST_1_WORKER_TID, make_shared<NiceMock<Mock_Thread_Sem>>(), mock_cbk);

    ASSERT_TRUE(thread);
    ASSERT_EQ(thread->tid, IPC_GTEST_1_WORKER_TID);
}

TEST_F(Gtest_Thread, ready)
{
    ASSERT_TRUE(this->thread);
    EXPECT_CALL(*this->mock_sem, ready());
    this->thread->ready();
}

TEST_F(Gtest_Thread, run)
{
    using ::testing::_;
    EXPECT_CALL(*this->mock_cbk, create_thread(_));
    this->thread->run();
}

TEST_F(Gtest_Thread, wait)
{
    using ::testing::_;
    EXPECT_CALL(*this->mock_sem, wait());
    this->thread->wait();
    EXPECT_CALL(*this->mock_sem, wait(1000));
    this->thread->wait(1000);
}

TEST_F(Gtest_Thread, delete)
{
    using ::testing::_;
    EXPECT_CALL(*this->mock_cbk, cancel_thread(_));
    this->thread.reset();
}
