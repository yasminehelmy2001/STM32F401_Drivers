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
 *             .CallBackFn=Toggle_LED,
 *             .FirstDelay=5000
 *            }
 *          };
 * 
 * Add Your Runnable in order of PRIORITY
 */


Runnables_t System_Runnables[]=
{
    [0]={
        .name="LCD_Task",
        .PeriodicityMs=2,
        .CallBackFn=LCD_Task,
        .FirstDelay=0
    },
    [1]={
    .name="LCD_APP_Runnable",
    .PeriodicityMs=20,
    .CallBackFn=LCD_APP_Runnable,
    .FirstDelay=0
    }
};