/*=====================================================================================*/
/**
 * gtest_task.c
 * author : puch
 * date : Oct 22 2015
 *
 * description : Any comments
 *
 */
/*=====================================================================================*/
#define CLASS_IMPLEMENTATION
#undef Dbg_FID
#define Dbg_FID Dbg_FID_Def(GTEST_FID, 1)
/*=====================================================================================*
 * Project Includes
 *=====================================================================================*/
#include "dbg_log.h"
#include "ipc.h"
#include "gtest_task_ext.h"
#include "gtest_task.h"
/*=====================================================================================* 
 * Standard Includes
 *=====================================================================================*/
#include <unistd.h>
/*=====================================================================================* 
 * Local X-Macros
 *=====================================================================================*/
#undef CLASS_VIRTUAL_METHODS
#define CLASS_VIRTUAL_METHODS(_ovr) \
   _ovr(Task,run) \
/*=====================================================================================* 
 * Local Define Macros
 *=====================================================================================*/

/*=====================================================================================* 
 * Local Type Definitions
 *=====================================================================================*/

/*=====================================================================================* 
 * Local Function Prototypes
 *=====================================================================================*/
static void Gtest_Task_ctor(Gtest_Task_T * const this, IPC_Task_Id_T const tid, int argc, char ** argv);
static void Gtest_Task_run(Task_T * const super);
/*=====================================================================================* 
 * Local Object Definitions
 *=====================================================================================*/
CLASS_DEFINITION
static Gtest_Task_T test;
/*=====================================================================================* 
 * Exported Object Definitions
 *=====================================================================================*/

/*=====================================================================================* 
 * Local Inline-Function Like Macros
 *=====================================================================================*/
int main(int argc, char ** argv)
{
   test = Gtest_Task();

   test.vtbl->ctor(&test, GTEST_FWK_WORKER, argc, argv);

   IPC_Run(GTEST_FWK_WORKER);

   IPC_Wait(GTEST_FWK_WORKER);
}
/*=====================================================================================* 
 * Local Function Definitions
 *=====================================================================================*/
void Gtest_Task_init(void)
{
   CHILD_CLASS_INITIALIZATION
   Gtest_Task_Vtbl.ctor = Gtest_Task_ctor;
}

void Gtest_Task_shut(void) {}

void Gtest_Task_Dtor(Object_T * const obj)
{}
/*=====================================================================================* 
 * Exported Function Definitions
 *=====================================================================================*/
void Gtest_Task_ctor(Gtest_Task_T * const this, IPC_Task_Id_T const tid, int argc, char ** argv)
{
   this->Task.vtbl->ctor(&this->Task, tid);
   this->argc = argc;
   this->argv = argv;
}

void Gtest_Task_run(Task_T * const super)
{
   Dbg_Info("Gtest_Task_run");
   IPC_Create_Mailbox(64, 80);
   IPC_Task_Ready();

   Gtest_Task_T * const this = _dynamic_cast(Gtest_Task, super);

   Isnt_Nullptr(this, );
   Gtest_Task_Cbk(this->argc, this->argv);

   IPC_Destroy_Mailbox();
}
/*=====================================================================================* 
 * gtest_task.c
 *=====================================================================================*
 * Log History
 *
 *=====================================================================================*/
