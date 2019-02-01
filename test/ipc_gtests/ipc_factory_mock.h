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
};

#endif /*IPC_FACTORY_MOCK_H_*/
