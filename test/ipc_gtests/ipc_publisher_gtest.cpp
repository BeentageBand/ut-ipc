#include "ipc_factory_mock.h"
#include "ccpublisher.h"
#include <vector>

using namespace ::testing;
using namespace std;
using namespace cc;


class Mock_Publisher_Cbk : public Publisher::Cbk
{
    public:
    MOCK_METHOD1(send, bool (Mail & mail));
};

class Publisher_Gtest : public Test
{
    private:
    NiceMock<Mock_Factory> mock_factory;
    shared_ptr<Mutex> mock_mux;
    shared_ptr<Publisher::Cbk> mock_cbk;
    public:
    void SetUp(void)
    {
        this->mock_mux = make_shared<NiceMock<Mock_Mux>>();
        this->mock_cbk = make_shared<NiceMock<Mock_Publisher_Cbk>>();

        EXPECT_CALL(this->mock_factory, create_mutex()).WillOnce(Return(this->mock_mux));
        EXPECT_CALL(this->mock_factory, create_publisher_cbk()).WillOnce(Return(this->mock_cbk));

        Publisher::get(this->mock_factory);
        Publisher::get(this->mock_mux, this->mock_cbk);
    }

};

TEST(Publisher, init)
{
    NiceMock<Mock_Factory> mock_factory;
    shared_ptr<Mutex> mock_mux;
    shared_ptr<Publisher::Cbk> mock_cbk;
    
    mock_mux = make_shared<NiceMock<Mock_Mux>>();
    mock_cbk = make_shared<NiceMock<Mock_Publisher_Cbk>>();

    EXPECT_CALL(mock_factory, create_mutex()).WillOnce(Return(mock_mux));
    EXPECT_CALL(mock_factory, create_publisher_cbk()).WillOnce(Return(mock_cbk));

    Publisher::get(mock_factory);
    Publisher::get(mock_mux, mock_cbk);
}

TEST_F(Publisher_Gtest, subscribe)
{
    Publisher & pub = Publisher::get();
    vector<IPC_MID_T> mid_list {IPC_MAIN_TID};
    bool rc = pub.subscribe(mid_list.begin(), mid_list.end(), WORKER_INT_SHUTDOWN_MID);
    ASSERT_TRUE(rc);

    auto subscription = pub.find_subscription(WORKER_INT_SHUTDOWN_MID);
    ASSERT_FALSE(subscription.empty());

    auto found = subscription.find(IPC_MAIN_TID);
    ASSERT_FALSE(found == subscription.end());
    ASSERT_EQ(*found, IPC_MAIN_TID);
}

TEST_F(Publisher_Gtest, publish)
{
    Publisher & pub = Publisher::get();
    pub.publish(WORKER_INT_SHUTDOWN_MID, IPC_MAIN_TID, IPC_MAIN_TID);
}

TEST_F(Publisher_Gtest, unsubscribe)
{
    Publisher & pub = Publisher::get();
    vector<IPC_MID_T> mid_list {IPC_MAIN_TID};
    bool rc = pub.unsubscribe(mid_list.begin(), mid_list.end(), WORKER_INT_SHUTDOWN_MID);
    ASSERT_TRUE(rc);

    auto subscription = pub.find_subscription(WORKER_INT_SHUTDOWN_MID);
    ASSERT_TRUE(subscription.empty());

    auto found = subscription.find(IPC_MAIN_TID);
    ASSERT_TRUE(found == subscription.end());
}
