/*
* File:    APP4.c
* Author:  Yasmin Amr
* Created: 14/3/2024
* Target:  STM32F401cc
*/

/**
 * Note: Adjust Runnable Periodicity to 150ms to avoid high Sensitivity
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

void Switch_Led_Runnable (void);

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
    u8 switch_state;
    static u8 led_state=LED_OFF;
    SWITCH_GetStatus(SWITCH_ONE,&switch_state);
    if(switch_state==SWITCH_PRESSED)
    {
      //Toggle Led State
      led_state^=1;
      LED_SetStatus(LED_RED,led_state);
    }  
    else
    {
      //Do Nothing
    }
}

#endif
#endif