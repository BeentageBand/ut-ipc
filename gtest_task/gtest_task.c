/*=====================================================================================*/
/**
 * gtest_task.cpp
 * author : puch
 * date : Oct 22 2015
 *
 * description : Any comments
 *
 */
/*=====================================================================================*/
#define CLASS_IMPLEMENTATION
/*=====================================================================================*
 * Project Includes
 *=====================================================================================*/
#include "ipc.h"
#include "gtest_task_ext.h"
#include "gtest_task.h"
/*=====================================================================================* 
 * Standard Includes
 *=====================================================================================*/

/*=====================================================================================* 
 * Local X-Macros
 *=====================================================================================*/
#undef CLASS_VIRTUAL_METHODS
#define CLASS_VIRTUAL_METHODS(_ovr) \
   _ovr(Worker,on_start) \
   _ovr(Worker,on_loop) \
   _ovr(Worker,on_stop) \
/*=====================================================================================* 
 * Local Define Macros
 *=====================================================================================*/

/*=====================================================================================* 
 * Local Type Definitions
 *=====================================================================================*/

/*=====================================================================================* 
 * Local Function Prototypes
 *=====================================================================================*/
static void Gtest_Task_ctor(Gtest_Task_T * const this, IPC_Task_Id_T const tid, uint32_t const mailbox_size);
static void Gtest_Task_on_start(Worker_T * const super);
static void Gtest_Task_on_loop(Worker_T * const super);
static void Gtest_Task_on_stop(Worker_T * const super);
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
int main(void)
{
   test = Gtest_Task();

   test.vtbl->ctor(&test, GTEST_FWK_WORKER,64);
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
void Gtest_Task_ctor(Gtest_Task_T * const this, IPC_Task_Id_T const tid, uint32_t const mailbox_size)
{
   this->Worker.vtbl->ctor(&this->Worker, tid, mailbox_size);
}

void Gtest_Task_on_start(Worker_T * const super)
{}

void Gtest_Task_on_loop(Worker_T * const super)
{
   Gtest_Task_T * const this = _dynamic_cast(Gtest_Task, super);
   Isnt_Nullptr(this, );
   Gtest_Task_Cbk();
   IPC_Send(GTEST_FWK_WORKER, WORKER_SHUTDOWN, NULL, 0);
}

void Gtest_Task_on_stop(Worker_T * const super)
{}
/*=====================================================================================* 
 * gtest_task.c
 *=====================================================================================*
 * Log History
 *
 *=====================================================================================*/
