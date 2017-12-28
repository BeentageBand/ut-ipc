#ifndef GTEST_TASK_H_
#define GTEST_TASK_H_
 
#include "thread.h"
 
#define Gtest_Task_INHERITS Task
#define Gtest_Task_MEMBERS(_member, _class) \
_member(int _private, argc) \
_member(char ** _private, argv) \

#define Gtest_Task_METHODS(_method, _class)

#ifdef __cplusplus
extern "C" {
#endif

typedef union Thread Gtest_Thread_Class_T;
typedef union Gtest_Thread
{
	Gtest_Thread_Class_T _private * _private vtbl;
	struct Object Object;
	struct
	{
		union Thread Thread;
		int _private args;
		char _private ** _private argv;
	};
}Gtest_Thread_T;
	
 
extern Gtest_Thread_Class_T _private Gtest_Thread_Class;

extern Populate_Gtest_Task(union Gtest_Thread * const gtest_thread, IPC_Task_Id_T const, int argc, char ** argv);

#ifdef __cplusplus
}
#endif
#endif /*GTEST_TASK_H_*/
