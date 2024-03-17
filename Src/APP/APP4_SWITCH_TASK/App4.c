/*
* File:    APP4.c
* Author:  Yasmin Amr
* Created: 14/3/2024
* Target:  STM32F401cc
*/

#include "APP.h"

#ifdef APP
#if (APP==APP4_SWITCH_TASK)

#include "ClockControl.h"
#include "SCHED.h"
#include "SYSTICK.h"
#include "LED.h"
#include "SWITCH.h"
#include "APP.h"

static void Switch_Led_Runnable (void);

int main(void)
{
   Enable_HAL_ClockControl();
   LED_Init();
   SWITCH_Init();
   SCHED_Init();
   SCHED_Start();
}

void Switch_Led_Runnable (void)
{
    u8 state;
    SWITCH_GetStatus(SWITCH_ONE,&state);
    if(state==SWITCH_PRESSED)
    {
      LED_SetStatus(LED_RED,LED_ON);
    }  
    else
    {
      LED_SetStatus(LED_RED,LED_OFF);
    }
}

#endif
#endif