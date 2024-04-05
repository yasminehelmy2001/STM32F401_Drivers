/*
* File:    SCHED_cfg.c
* Author:  Yasmin Amr
* Created: 14/3/2024
* Brief:   SCHED Driver
* Target:  STM32F401cc
*/

#include "SCHED.h"

extern void Traffic_Lights (void);
extern void Toggle_LED (void);
extern void SW_Runnable (void);
extern void Switch_Led_Runnable (void);
extern void LCD_Task(void);
extern void LCD_APP_Runnable(void);

/**
 * 1) Extern Your Runnable Here
 * 2) Add Your Runnables Information Here
 *      Example: 
 *          Runnables_t System_Runnables[]=
 *            {
 *             [0]={
 *             .name="FirstRunnable",
 *             .PeriodicityMs=100,
 *             .CallBackFn=Toggle_LED
 *            }
 *          };
 * 
 * Add Your Runnable in order of PRIORITY
 */


Runnables_t System_Runnables[]=
{
    [0]={
        .name="Toggle_LED",
        .PeriodicityMs=1000,
        .CallBackFn=Toggle_LED,
        .FirstDelay=5000
    }
};