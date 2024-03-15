#include "ClockControl.h"
#include "SCHED.h"
#include "SYSTICK.h"
#include "LED.h"
#include "SWITCH.h"
#include "APP.h"


int main(void)
{
   Enable_HAL_ClockControl();
   LED_Init();
   SWITCH_Init();
   SCHED_Init();
   SCHED_Start();
}
