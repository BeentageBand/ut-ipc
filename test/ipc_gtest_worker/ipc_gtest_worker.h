#ifndef IPC_GTEST_WORKER_H_
#define IPC_GTEST_WORKER_H_
 
#include "worker.h"
 
#ifdef __cplusplus
extern "C" {
#endif
 
typedef union Worker IPC_Gtest_Worker_T;
typedef union Worker_Class IPC_Gtest_Worker_Class_T;

extern IPC_Gtest_Worker_Class_T _private IPC_Gtest_Worker_Class; 

extern void Populate_IPC_Gtest_Worker(IPC_Gtest_Worker_T * const ipc_gtest_wrkr,
		IPC_TID_T const tid, union Mail * const mail_buff, size_t const mail_size);
 
#ifdef __cplusplus
}
#endif
 
#endif /*IPC_GTEST_WORKER_H_*/
