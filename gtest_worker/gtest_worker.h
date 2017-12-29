#ifndef GTEST_TASK_H_
#define GTEST_TASK_H_
 
#include "worker.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef union Worker_Class Gtest_Worker_Class_T;

typedef union Gtest_Worker
{
	Gtest_Worker_Class_T _private * _private vtbl;
	union Thread Thread;
	struct Object Object;
	struct
	{
		union Worker Worker;
		int _private argc;
		char _private ** _private argv;
	};
}Gtest_Worker_T;
	
 
extern Gtest_Worker_Class_T _private Gtest_Worker_Class;

extern Populate_Gtest_Worker(union Gtest_Worker * const gtest_thread, IPC_TID_T const tid, int argc, char ** argv);

#ifdef __cplusplus
}
#endif
#endif /*GTEST_TASK_H_*/
