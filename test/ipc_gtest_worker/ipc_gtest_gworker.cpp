#include "gmock/gmock.h"
#include "ccipc.h"
#include "ccposix_factory.h"
#include "ccpublisher.h"
#include "gworker.h"

using namespace cc;
using namespace std;
using namespace ::testing;


class GWorker_Gtest : public Test
{
    public:
    ccposix::Factory factory;
    GWorker gworker;

    GWorker_Gtest(void)
    : factory(), gworker(IPC_GTEST_1_WORKER_TID, this->factory)
    {}

    void SetUp(void)
    {
        IPC::get(this->factory);
        Publisher::get(this->factory, IPC::get());
    }
};

TEST_F(GWorker_Gtest, run)
{

    this->gworker.run();

    shared_ptr<IPC::Sender> sender = IPC::get().get_sender(IPC_MAIN_TID);
    Mail::Builder builder;
    builder.with_mid(WORKER_INT_SHUTDOWN_MID);
    builder.with_sender(IPC_MAIN_TID);
    builder.with_receiver(IPC_GTEST_1_WORKER_TID);

    if(sender)
        sender->send(builder.build());
}

TEST_F(GWorker_Gtest, join)
{
    gworker.join();
}
