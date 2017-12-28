#define COBJECT_IMPLEMENTATION
#undef Dbg_FID
#define Dbg_FID DBG_FID_DEF(GTEST_FID, 1)
 
#include "dbg_log.h"
#include "ipc.h"
#include "gtest_task_ext.h"
#include "gtest_task.h"
 
#include <unistd.h>
 
static void gtest_thread_delete(struct Object * const obj);
static void gtest_worker_on_start(union Worker * const super);
static void gtest_worker_on_mail(union Worker * const super, union Mail * const mail);
static void gtest_worker_on_loop(union Worker * const super);
static void gtest_worker_on_stop(union Worker * const super);

Gtest_worker_Class_T Gtest_Worker_Class =
{
	{gtest_worker_delete, NULL},
	gtest_worker_on_start,
	gtest_worker_on_mail,
	gtest_worker_on_loop,
	gtest_worker_on_stop
};

static union Gtest_Worker Gtest_Worker = {NULL};
static union Mail Gtest_Worker_Mailbox[64];

void gtest_thread_delete(struct Object * const obj)
{}

void gtest_thread_on_start(union Worker * const super)
{
   Dbg_Info("Gtest_Thread_run");
   Gtest_Thread_T * const this = _cast(Gtest_Thread, super);

   IPC_Thread_Ready();

   Gtest_Thread_Cbk(this->argc, this->argv);
}

int main(int argc, char ** argv)
{
	Gtest_Thread_T gtest;
	Populate_Gtest_Worker(&gtest, GTEST_FWK_WORKER, argc, argv);

	IPC_Run(GTEST_FWK_WORKER);
	IPC_Wait(GTEST_FWK_WORKER);
}
 
Populate_Gtest_Worker(union Gtest_Worker * const this, IPC_Task_Id_T const tid, int argc, char ** argv)
{
	if(NULL == Gtest_Thread.vtbl)
	{
		Populate_Worker(&Gtest_Worker.Worker, tid, Gtest_Mailbox, Num_Elems(Gtest_Mailbox));
		Object_Init(&Gtest_Thread.Object, &Gtest_Thread_Class.Class, sizeof(Gtest_Thread_Class.Thread));
		Gtest_Thread_Class.runnable = gtest_thread_runnable;
	}

	memcpy(this, &Gtest_Thread, sizeof(Gtest_Thread));
	this.argc = argc;
	this.argv = argv;

	return this;
}

