#ifndef IPC_MAIL_LIST_H_
#define IPC_MAIL_LIST_H_
 
#include "ipc_gtest_worker_evs.h"
#include "worker_mailist.h"

#define IPC_INTERNAL_MAILIST(X) \
   IPC_GTEST_INT_MAILIST(X) \
   WORKER_INT_MAILIST(X)  \

#define IPC_PUBLIC_MAILIST(X) \
   IPC_GTEST_PBC_MAILIST(X) \
   WORKER_PBC_MAILIST(X)  \

#define IPC_RETRIEVE_TOUT_MS (500U)

#endif /*IPC_MAIL_LIST_H_*/
