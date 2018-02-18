#define COBJECT_IMPLEMENTATION
#undef Dbg_FID
#define Dbg_FID DBG_FID_DEF(GTEST_FID, 1)
 
#include "dbg_log.h"
#include "ipc.h"
#include "gtest_worker_ext.h"
#include "gtest_worker.h"
#include "ipc_posix.h"
 
#include <unistd.h>
 
static void gtest_worker_delete(struct Object * const obj);
static void gtest_worker_on_start(union Worker * const super);
static void gtest_worker_on_mail(union Worker * const super, union Mail * const mail);
static void gtest_worker_on_loop(union Worker * const super);
static void gtest_worker_on_stop(union Worker * const super);

Gtest_Worker_Class_T Gtest_Worker_Class =
{{
	{
	        {gtest_worker_delete, NULL},
	        NULL,
	        NULL
	},
	gtest_worker_on_mail,
	gtest_worker_on_start,
	gtest_worker_on_loop,
	gtest_worker_on_stop
}};

static union Gtest_Worker Gtest_Worker = {NULL};
static union Mail Gtest_Worker_Mailbox[64] = {0};

void gtest_worker_delete(struct Object * const obj)
{}

void gtest_worker_on_start(union Worker * const super)
{
   Gtest_Worker_T * const this = _cast(Gtest_Worker, super);
   Isnt_Nullptr(this,)
   Dbg_Info("Gtest_Worker_run argc = %d, argv = %ld", this->argc, (size_t)this->argv);

   IPC_Ready();

   Gtest_Worker_Cbk(this->argc, this->argv);
}

static void gtest_worker_on_mail(union Worker * const super, union Mail * const mail)
{
}

void gtest_worker_on_loop(union Worker * const super)
{
	IPC_Sleep(500);
}

void gtest_worker_on_stop(union Worker * const super)
{
}

int main(int argc, char ** argv)
{
	Dbg_Info("Init with %d args", argc);
	static IPC_POSIX_T posix_helper = {NULL};
	Populate_IPC_POSIX(&posix_helper);
	IPC_Helper_Append(&posix_helper.IPC_Helper);

	union Thread thrd = {NULL};

	Init_Gtest_Worker(argc, argv);
	Populate_Thread(&thrd, IPC_GTEST_2_WORKER_TID);

	IPC_Run(GTEST_FWK_WORKER_TID);
	IPC_Wait(GTEST_FWK_WORKER_TID, 15000);

	Dbg_Info("main end");
	while(1){}
}
 
void Init_Gtest_Worker(int argc, char ** argv)
{
	if(NULL == Gtest_Worker.vtbl)
	{
	    Populate_Worker(&Gtest_Worker.Worker, GTEST_FWK_WORKER_TID, Gtest_Worker_Mailbox, Num_Elems(Gtest_Worker_Mailbox));
		Object_Init(&Gtest_Worker.Object, &Gtest_Worker_Class.Class, sizeof(Gtest_Worker_Class.Thread));
		Gtest_Worker.argc = argc;
		Gtest_Worker.argv = argv;
	}
	Dbg_Info("%s, argc = %d", __func__, argc);
}
