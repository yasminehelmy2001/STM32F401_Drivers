/*
* File:    SCHED.c
* Author:  Yasmin Amr
* Created: 14/3/2024
* Brief:   SCHED Driver
* Target:  STM32F401cc
*/

#include "SYSTICK.h" /*Scheduler only depends on systick*/
#include "SCHED.h"

/**************************************************************************/
/*						Implementation Defs               	 			  */
/**************************************************************************/
#define ACTIVATED   0
#define DEACTIVATED 1

/**************************************************************************/
/*						Static Function Prototypes      	 			  */
/**************************************************************************/

/**
 * Function to Execute Runnable CallBack Function After Periodicity Time is Reached
*/
static void SCHED_App(void);

/**
 * Function to Increment 'PendingTicks' variable every SystTick/Scheduler Interrupt
*/
static void SCHED_TickCallBack(void);

/*Extern Runnables Array*/
extern Runnables_t System_Runnables[SYSTEM_RUNNABLES_COUNT];

/**
 * Variable to Track Scheduler Interrupt
 * Note: Variable must be declared as volatile, to prevent compiler optimization as variable is modified in ISR
 */
static volatile u32 PendingTicks=0;
static u32 RemainTimeMs[SYSTEM_RUNNABLES_COUNT]={0};

/**
 * Function to Initialize Scheduler (Initializes SysTick Timer)
*/
void SCHED_Init(void)
{
    STK_SetTimeMS(TICK_TIME_MS);
    STK_SetCallBack(SCHED_TickCallBack);
    for(u32 Runnable_Index=0;i<SYSTEM_RUNNABLES_COUNT;Runnable_Index++)
    {
        RemainTimeMs[Runnable_Index]=System_Runnables[Runnable_Index].FirstDelay;
    }
}

/**
 * Function to Start Scheduler (Starts SysTick Timer)
*/
void SCHED_Start(void)
{
    STK_Start(STK_PERIODICITY_INFINITE); 
    while(1)
    { 
        if(PendingTicks)
        {
            PendingTicks--;
            SCHED_App();
        }
    }
}

/**
 * Function to Execute Runnable CallBack Function After Periodicity Time is Reached
*/
static void SCHED_App(void)
{
    for(u32 Runnable_Index=0;i<SYSTEM_RUNNABLES_COUNT;Runnable_Index++)
    {
        /*Check if Periodicity Time is Reached*/
        if(((RemainTimeMs[Runnable_Index])==0)&&(System_Runnables[Runnable_Index].CallBackFn))
        {
            System_Runnables[Runnable_Index].CallBackFn();
            RemainTimeMs[Runnable_Index]=System_Runnables[i].PeriodicityMs;
        }
        else
        {
            //Empty for MISRA
        }
        RemainTimeMs[i]-=TICK_TIME_MS;
    }
}

/**
 * Function to Increment 'PendingTicks' variable every SystTick/Scheduler Interrupt
*/
static void SCHED_TickCallBack(void)
{
    PendingTicks++;
}