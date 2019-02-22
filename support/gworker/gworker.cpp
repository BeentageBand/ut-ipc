#undef Dbg_FID
#define Dbg_FID DBG_FID_DEF(GTEST_FID,4)
#include "ccfactory.h"
#include "gworker.h"
#include "dbg_log.h"

using namespace cc;
using namespace std;

class GBundle : public Bundle
{
    void on_start(void)
    {
        Dbg_Info("GBundle:%s ", __func__);
    }

    void on_mail(Mail const & mail)
    {
        Dbg_Info("GBundle:%s ", __func__);
    }

    void on_loop(void)
    {
        Dbg_Info("GBundle:%s ", __func__);
    }

    void on_stop(void)
    {
        Dbg_Info("GBundle:%s ", __func__);
    }
};

GWorker::GWorker(IPC_TID_T const tid, Factory & factory)
: cc::Worker(tid, 0, factory, make_shared<GBundle>(), IPC::get(factory))
{
    Dbg_Info("GWorker::%s with tid %d", __func__, tid);
}

GWorker::~GWorker(void){}
