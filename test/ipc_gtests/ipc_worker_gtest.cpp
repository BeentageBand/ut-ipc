#include "ipc_factory_mock.h"
#include "ccworker.h"

using namespace ::testing;
using namespace std;
using namespace cc;

class Worker_Gtest : public Test
{
    public:
    shared_ptr<Worker> worker;
    shared_ptr<Mock_Bundle> mock_bundle;
    shared_ptr<Mock_Barrier> mock_barrier;
    shared_ptr<Mock_Thread_Cbk> mock_cbk;
    shared_ptr<Mock_RW> mock_rw;
    public:
    void SetUp(void)
    {
        this->mock_cbk = make_shared<NiceMock<Mock_Thread_Cbk>>();
        this->mock_bundle = make_shared<NiceMock<Mock_Bundle>>();
        this->mock_barrier = make_shared<NiceMock<Mock_Barrier>>();

        EXPECT_CALL(*Mock_IPC::get().mock_factory, create_thread_cbk()).WillRepeatedly(Return(this->mock_cbk));
        EXPECT_CALL(*Mock_IPC::get().mock_factory, create_barrier(_)).WillRepeatedly(Return(this->mock_barrier));
        EXPECT_CALL(*this->mock_cbk, register_thread(_)).WillOnce(Return(0));

        this->worker = make_shared<Worker>(IPC_MAIN_TID, 1, *Mock_IPC::get().mock_factory, this->mock_bundle, IPC::get());
    }
};

TEST_F(Worker_Gtest, runnable)
{
    EXPECT_CALL(*this->mock_cbk, create_thread(_));
    EXPECT_CALL(*this->mock_bundle, on_start());
    this->worker->run();
}
