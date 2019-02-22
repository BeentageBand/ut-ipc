#ifndef GWORKER_H_
#define GWORKER_H_
#include "ccworker.h"

class GWorker : public cc::Worker
{
    public:
    explicit GWorker(IPC_TID_T const tid, cc::Factory & factory);
    virtual ~GWorker(void);
};
#endif /*GWORKER_H_*/
