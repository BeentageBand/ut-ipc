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
    public:
    NiceMock<Mock_Factory> mock_factory;
    shared_ptr<Mock_Mux> mock_mux;
    shared_ptr<Mock_Publisher_Cbk> mock_cbk;

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
    vector<IPC_MID_T> mid_list {WORKER_INT_SHUTDOWN_MID};

    EXPECT_CALL(*this->mock_mux, lock(200)).WillOnce(Return(true));
    EXPECT_CALL(*this->mock_mux, unlock());
    bool rc = pub.subscribe(mid_list.begin(), mid_list.end(), IPC_MAIN_TID);
    ASSERT_TRUE(rc);

    auto subscription = pub.find_subscription(WORKER_INT_SHUTDOWN_MID);
    ASSERT_FALSE(subscription.empty());

    EXPECT_CALL(*this->mock_mux, lock(200)).WillRepeatedly(Return(true));
    EXPECT_CALL(*this->mock_mux, unlock());
    auto found = subscription.find(IPC_MAIN_TID);
    ASSERT_FALSE(found == subscription.end());
    ASSERT_EQ(*found, IPC_MAIN_TID);
}

TEST_F(Publisher_Gtest, publish)
{
    Publisher & pub = Publisher::get();
    EXPECT_CALL(*this->mock_cbk, send(_));
    pub.publish(WORKER_INT_SHUTDOWN_MID, IPC_MAIN_TID, IPC_MAIN_TID);
}

TEST_F(Publisher_Gtest, unsubscribe)
{
    Publisher & pub = Publisher::get();
    vector<IPC_MID_T> mid_list {WORKER_INT_SHUTDOWN_MID};

    EXPECT_CALL(*this->mock_mux, lock(200)).WillRepeatedly(Return(true));
    EXPECT_CALL(*this->mock_mux, unlock());

    bool rc = pub.unsubscribe(mid_list.begin(), mid_list.end(), IPC_MAIN_TID);
    ASSERT_TRUE(rc);

    EXPECT_CALL(*this->mock_mux, lock(200)).WillRepeatedly(Return(true));
    EXPECT_CALL(*this->mock_mux, unlock());
    auto subscription = pub.find_subscription(WORKER_INT_SHUTDOWN_MID);
    ASSERT_TRUE(subscription.empty());

    EXPECT_CALL(*this->mock_mux, lock(200)).WillRepeatedly(Return(true));
    EXPECT_CALL(*this->mock_mux, unlock());
    auto found = subscription.find(IPC_MAIN_TID);
    ASSERT_TRUE(found == subscription.end());
}
