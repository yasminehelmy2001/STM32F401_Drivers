#include "APP.h"

#ifdef APPCURR
#if (APP==APP3_BLINKING_LED_TASK)

/*
* File:    APP.c
* Author:  Yasmin Amr
* Created: 14/3/2024
* Target:  STM32F401cc
*/

#include "ClockControl.h"
#include "SYSTICK.h"
#include "LED.h"

static void Toggle_LED(void);

int main(void)
{
  Enable_HAL_ClockControl();
  LED_Init();
  SCHED_Init();
  SCHED_Start();

}

void Toggle_LED(void) {
  static u32 status = LED_ON ;
	status ^= (LED_ON|LED_OFF); /*Toggle LED*/
  LED_SetStatus(LED_ONE, status);
}

#endif
#endif