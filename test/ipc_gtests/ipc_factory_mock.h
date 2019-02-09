#ifndef IPC_FACTORY_MOCK_H_
#define IPC_FACTORY_MOCK_H_
#include "gmock/gmock.h"
#include "ccfactory.h"

class Mock_Factory : public cc::Factory
{
    public:
    MOCK_METHOD0(create_mutex, std::shared_ptr<cc::Mutex> ());
    MOCK_METHOD1(create_semaphore, std::shared_ptr<cc::Semaphore> (uint32_t const resources));
    MOCK_METHOD0(create_cond_var, std::shared_ptr<cc::Cond_Var> ());
    MOCK_METHOD0(create_thread_cbk, std::shared_ptr<cc::Thread::Cbk> ());
    MOCK_METHOD1(create_barrier, std::shared_ptr<cc::Barrier> (uint32_t const resources));
    MOCK_METHOD0(create_rw_lock, std::shared_ptr<cc::RW_Lock> ());
    MOCK_METHOD2(create_ipc_retriever, std::shared_ptr<cc::IPC::Retriever> (IPC_TID_T const tid, cc::IPC & ipc));
    MOCK_METHOD2(create_ipc_sender, std::shared_ptr<cc::IPC::Sender> (IPC_TID_T const tid, cc::IPC & ipc));
};

class Mock_Mux : public cc::Mutex
{
    public:
    MOCK_METHOD1(lock, bool (uint32_t const tout_ms));
    MOCK_METHOD0(unlock, void ());
};

class Mock_RW : public cc::RW_Lock
{
    public:
    MOCK_METHOD1(rlock, bool (IPC_Clock_T const wait_ms));
    MOCK_METHOD1(wlock, bool (IPC_Clock_T const wait_ms));
    MOCK_METHOD0(unlock, void ());
};

class Mock_Sender : public cc::IPC::Sender
{
    public:
    explicit Mock_Sender(IPC_TID_T const tid)
    : cc::IPC::Sender(tid)
    {}

    MOCK_METHOD1(send, void (cc::Mail const & mail));
};

#endif /*IPC_FACTORY_MOCK_H_*/
