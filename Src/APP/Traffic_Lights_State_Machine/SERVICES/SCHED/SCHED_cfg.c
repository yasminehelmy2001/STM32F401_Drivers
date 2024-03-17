/*
* File:    SCHED_cfg.c
* Author:  Yasmin Amr
* Created: 14/3/2024
* Brief:   SCHED Driver
* Target:  STM32F401cc
*/

#include "SCHED.h"

extern void Traffic_Lights (void);

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
    [Traffic_Lights_Runnble]={
        .name="Traffic_Lights_Runnble",
        .PeriodicityMs=2000,
        .CallBackFn=Traffic_Lights
    }
};