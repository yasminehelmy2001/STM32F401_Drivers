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

/**
 * Function to Initialize Scheduler (Initializes SysTick Timer)
*/
void SCHED_Init(void)
{
    STK_SetTimeMS(TICK_TIME_MS);
    STK_SetCallBack(SCHED_TickCallBack);
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
    static u32 TickTimeCounter=0;
    for(u32 i=0;i<SYSTEM_RUNNABLES_COUNT;i++)
    {
        /*Check if Periodicity Time is Reached, Check if CallBack Fn is not NULL*/
        if(((TickTimeCounter%System_Runnables[i].PeriodicityMs)==0)&&(System_Runnables[i].CallBackFn))
        {
            System_Runnables[i].CallBackFn();
        }
    }
    TickTimeCounter+=TICK_TIME_MS;
}

/**
 * Function to Increment 'PendingTicks' variable every SystTick/Scheduler Interrupt
*/
static void SCHED_TickCallBack(void)
{
    PendingTicks++;
}