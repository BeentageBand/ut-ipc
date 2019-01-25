#include "gmock/gmock.h"
#include "ccmutex.h"

using namespace std;
using namespace cc;

class Mock_Mutex_Cbk : public Mutex::Cbk
{
    public:
    MOCK_METHOD1(lock, bool (IPC_Clock_T const wait_ms));
    MOCK_METHOD0(unlock, void ());
};

class Gtest_Mutex : public Test
{
    public:
        shared_ptr<Mock_Mutex_Cbk> mock_cbk;
        shared_ptr<Mutex> mutex;

    void SetUp(void)
    {
        this->mock_sem = make_shared<NiceMock<Mock_Mutex_Cbk>>();
        this->mutex = make_shared<Mutex>(this->mock_cbk);
    }

    void TearDown(void)
    {
    }
};

TEST(Mutex, constructor)
{
    using ::testing::_;

    shared_ptr<NiceMock<Mock_Mutex_Cbk>> mock_cbk = make_shared<NiceMock<Mock_Mutex_Cbk>>();
    
    EXPECT_CALL(*mock_cbk, register_mutex(_));
    shared_ptr<Mutex> mutex =  make_shared<Mutex>(IPC_GTEST_1_WORKER_TID, make_shared<NiceMock<Mock_Mutex_Cbk>>(), mock_cbk);

    ASSERT_TRUE(mutex);
    ASSERT_EQ(mutex->tid, );
}
