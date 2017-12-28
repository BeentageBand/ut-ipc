#define COBJECT_IMPLEMENTATION
#undef Dbg_FID
#define Dbg_FID DBG_FID_DEF(GTEST_FID, 1)
 
#include "dbg_log.h"
#include "ipc.h"
#include "gtest_task_ext.h"
#include "gtest_task.h"
 
#include <unistd.h>
 
static void gtest_thread_delete(struct Object * const obj);

Gtest_Thread_Class_T Gtest_Thread_Class = 
{
	{gtest_thread_delete, NULL},

static Gtest_Thread_T test;
 
int main(int argc, char ** argv)
{
   test = Gtest_Thread();

   test.vtbl->ctor(&test, GTEST_FWK_WORKER, argc, argv);

   IPC_Run(GTEST_FWK_WORKER);

   IPC_Wait(GTEST_FWK_WORKER);
}
 
void gtest_thread_delete(struct Object * const obj)
{}
 
Populate_Gtest_Task(union Gtest_Thread * const this, IPC_Task_Id_T const tid, int argc, char ** argv)
{
	if(NULL == Gtest_Thread.vtbl)
	{
		Populate_Thread(&Gtest_Thread.Thread, tid);
		Object_Init(&Gtest_Thread.Object, &Gtest_Thread_Class.Class, sizeof(Gtest_Thread_Class.Thread));
		Gtest_Thread_Class.runnable = gtest_thread_runnable;
	}

	memcpy(this, &Gtest_Thread, sizeof(Gtest_Thread));
	this.argc = argc;
	this.argv = argv;

	return this;
}

void gtest_thread_runnable(union Thread * const super)
{
   Dbg_Info("Gtest_Thread_run");
   IPC_Create_Mailbox(64, 80);
   IPC_Thread_Ready();

   Gtest_Thread_T * const this = _cast(Gtest_Thread, super);

   Isnt_Nullptr(this, );
   Gtest_Thread_Cbk(this->argc, this->argv);

   IPC_Destroy_Mailbox();
}
