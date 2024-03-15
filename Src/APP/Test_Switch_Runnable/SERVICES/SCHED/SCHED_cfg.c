/*
* File:    SCHED_cfg.c
* Author:  Yasmin Amr
* Created: 14/3/2024
* Brief:   SCHED Driver
* Target:  STM32F401cc
*/

#include "APP.h"
#include "SCHED.h"
#include "SWITCH.h"

extern void SW_Runnable(void);

/**
 * Add Your Runnables Information Here
 * Example: 
 * Runnables_t System_Runnables[]=
 *   {
 *      [0]={
 *       .name="FirstRunnable",
 *       .PeriodicityMs=100,
 *       .CallBackFn=Toggle_LED
 *        }
 *   };
 * 
 * Add Your Runnable in order of PRIORITY
 */
Runnables_t System_Runnables[]=
{
    [0]={
        .name="Switch_Runnable",
        .PeriodicityMs=5,
        .CallBackFn=SW_Runnable
    },
    [1]={
        .name="Switch_LED_APP_Runnable",
        .PeriodicityMs=25,
        .CallBackFn=Switch_Led_Runnable
    }

};