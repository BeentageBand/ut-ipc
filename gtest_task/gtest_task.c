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

/*=====================================================================================* 
 * Local Define Macros
 *=====================================================================================*/

/*=====================================================================================* 
 * Local Type Definitions
 *=====================================================================================*/

/*=====================================================================================* 
 * Local Function Prototypes
 *=====================================================================================*/

/*=====================================================================================* 
 * Local Object Definitions
 *=====================================================================================*/
CLASS_DEF(Gtest_Task)
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
void Gtest_Task_Init(void)
{
   Gtest_Task_Class.run = Gtest_Task_run;
}


void Gtest_Task_Dtor(Object_T * const obj)
{}
/*=====================================================================================* 
 * Exported Function Definitions
 *=====================================================================================*/
union Gtest_Task Gtest_Task_Main(IPC_Task_Id_T const tid, int argc, char ** argv)
{
	union Gtest_Task this = Gtest_Task_Default();
	Object_Update_Info(&this.Object, & Task_Tid(tid).Object, sizeof(this.Task));
   this.argc = argc;
   this.argv = argv;
   return this;
}
union Gtest_Task * Gtest_Task_Main_New(IPC_Task_Id_T const tid, int argc, char ** argv)
{
	Constructor_New_Impl(Gtest_Task, Main, tid, argc, argv);
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
