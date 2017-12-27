#define CLASS_IMPLEMENTATION
#undef Dbg_FID
#define Dbg_FID Dbg_FID_Def(IPC_FID,0)
 
#include "dbg_log.h"
#include "ipc.h"
#include "ipc_gtest_worker.h"
 
#include <unistd.h>
 
static void ipc_gtest_worker_delete(struct Object * const obj);
static void ipc_gtest_worker_on_start(Worker_T * const super);
static void ipc_gtest_worker_on_loop(Worker_T * const super);
static void ipc_gtest_worker_on_stop(Worker_T * const super);
 
IPC_Gtest_Worker_Class_T IPC_Gtest_Worker_Class =
{
	{ipc_gtest_worker_delete, NULL},
	ipc_gtest_worker_on_start,
	ipc_gtest_worker_on_loop,
	ipc_gtest_worker_on_stop
};

static IPC_Gtest_Worker_T IPC_Gtest_Worker = {NULL};

void ipc_gtest_worker_delete(struct Object * const obj)
{
}
 
void Populate_IPC_Gtest_Worker(IPC_Gtest_Worker_T * const this, IPC_TID_T const tid, union Mail * const mail_buff,
		size_t const mail_size)
{
	if(NULL == IPC_Gtest_Worker.vtbl)
	{
		Populate_Worker(&IPC_Gtest_Worker, tid, mail_buff, mail_size);
		Object_Init(&IPC_Gtest_Worker.Object, IPC_Gtest_Worker_Class.Class, sizeof(IPC_Gtest_Worker_Class));
	}
	memcpy(this, &IPC_Gtest_Worker, sizeof(IPC_Gtest_Worker));
}

void ipc_gtest_worker_on_start(Worker_T * const super)
{
   IPC_Gtest_Worker_T * const this = _dynamic_cast(IPC_Gtest_Worker, super);
   Isnt_Nullptr(this, );
   Dbg_Info("IPC_Gtest_Worker_on_start %d", this->Worker.Task.tid);
}

void ipc_gtest_worker_on_loop(Worker_T * const super, union Mail * const mail)
{
	Dbg_Info("mail not null mid %d", mail->mid);

	switch(mail->mid)
	{
	case IPC_GTEST_EV_MID:
	   Dbg_Info("Gtest Worker  Handles mid IPC_GTEST_EV_MID");
	   IPC_Send(GTEST_FWK_WORKER, IPC_GTEST_EV_MID, NULL, 0);
	   break;
	default: break;
	}
}

void ipc_gtest_worker_on_loop(Worker_T * const super)
{
   sleep(0.1);
}

void ipc_gtest_worker_on_stop(Worker_T * const super)
{
   IPC_Gtest_Worker_T * const this = _cast(IPC_Gtest_Worker, super);
   Isnt_Nullptr(this, );
   Dbg_Info("IPC_Gtest_Worker_on_stop %d", this->Worker.Task.tid);
}
