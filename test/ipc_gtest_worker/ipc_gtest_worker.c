#define COBJECT_IMPLEMENTATION
#undef Dbg_FID
#define Dbg_FID DBG_FID_DEF(IPC_FID,0)
 
#include "dbg_log.h"
#include "ipc.h"
#include "ipc_gtest_worker.h"
 
#include <unistd.h>
 
static void ipc_gtest_worker_delete(struct Object * const obj);
static void ipc_gtest_worker_on_mail(Worker_T * const super, union Mail * const mail);
static void ipc_gtest_worker_on_start(Worker_T * const super);
static void ipc_gtest_worker_on_loop(Worker_T * const super);
static void ipc_gtest_worker_on_stop(Worker_T * const super);
 
IPC_Gtest_Worker_Class_T IPC_Gtest_Worker_Class =
{{
	{
	        {ipc_gtest_worker_delete, NULL},
	        NULL
	},
	ipc_gtest_worker_on_mail,
	ipc_gtest_worker_on_start,
	ipc_gtest_worker_on_loop,
	ipc_gtest_worker_on_stop
}};

static IPC_Gtest_Worker_T IPC_Gtest_Worker = {NULL};

void ipc_gtest_worker_delete(struct Object * const obj)
{
}
 
void Populate_IPC_Gtest_Worker(IPC_Gtest_Worker_T * const this, IPC_TID_T const tid, union Mail * const mail_buff,
		size_t const mail_size)
{
	if(NULL == IPC_Gtest_Worker.vtbl)
	{
		Populate_Worker(&IPC_Gtest_Worker, IPC_MAX_TID, NULL, 0);
		Object_Init(&IPC_Gtest_Worker.Object, &IPC_Gtest_Worker_Class.Class, sizeof(IPC_Gtest_Worker_Class));

		IPC_Gtest_Worker_Class.on_mail = ipc_gtest_worker_on_mail;
		IPC_Gtest_Worker_Class.on_start = ipc_gtest_worker_on_start;
		IPC_Gtest_Worker_Class.on_loop = ipc_gtest_worker_on_loop;
		IPC_Gtest_Worker_Class.on_stop = ipc_gtest_worker_on_stop;
	}
	Populate_Worker(this, tid, mail_buff, mail_size);
	this->vtbl = &IPC_Gtest_Worker_Class;

}

void ipc_gtest_worker_on_start(Worker_T * const super)
{
   IPC_Gtest_Worker_T * const this = (IPC_Gtest_Worker_T *) _cast(IPC_Gtest_Worker, super);
   Isnt_Nullptr(this, );
   Dbg_Info("IPC_Gtest_Worker_on_start %d", this->Thread.tid);
}

void ipc_gtest_worker_on_mail(Worker_T * const super, union Mail * const mail)
{
	Dbg_Info("Worker %d: mail not null mid %d", super->Thread.tid, mail->mid);

	switch(mail->mid)
	{
	case IPC_GTEST_INT_MID:
	   Dbg_Info("Gtest Worker  Handles mid IPC_GTEST_EV_MID");
	   IPC_Send(GTEST_FWK_WORKER_TID, IPC_GTEST_INT_MID, NULL, 0);
	   break;
	default: break;
	}
}

void ipc_gtest_worker_on_loop(Worker_T * const super)
{
    IPC_Sleep(1000);
}

void ipc_gtest_worker_on_stop(Worker_T * const super)
{
   IPC_Gtest_Worker_T * const this = _cast(IPC_Gtest_Worker, super);
   Isnt_Nullptr(this, );
   Dbg_Info("IPC_Gtest_Worker_on_stop %d", this->Thread.tid);
}
