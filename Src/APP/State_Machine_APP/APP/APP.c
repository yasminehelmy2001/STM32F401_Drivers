/*
* File:    APP.c
* Author:  Yasmin Amr
* Created: 14/3/2024
* Target:  STM32F401cc
*/

#include "ClockControl.h"
#include "SCHED.h"
#include "SYSTICK.h"
#include "LED.h"
#include "APP.h"

extern Runnables_t System_Runnables[];

int main(void)
{
  Enable_HAL_ClockControl();
  LED_Init();
  SCHED_Init();
  SCHED_Start();
}

void Traffic_Lights(void)
{
  /*Current State*/
  static  TrafficLightState_t state=green;
  /*Previous State*/
  static  TrafficLightState_t previous=yellow;
  /*Increments by Periodicity*/
  static  u32 CounterSeconds=0;
  /*Increment 'counter' by runnables periodicity*/
  CounterSeconds+=((System_Runnables[Traffic_Lights_Runnble].PeriodicityMs)/(u32)MS_TO_S);

  switch(state)
  {
    case green:
    {
      LED_SetStatus(LED_GREEN,LED_ON);
      LED_SetStatus(LED_YELLOW,LED_OFF);
      LED_SetStatus(LED_RED,LED_OFF);
      switch(previous)
      {
        case yellow:
        {
          if(CounterSeconds==GREEN_LED_SECONDS)
          {
            CounterSeconds=0;
            state=yellow;
            previous=green;
          }
        }
        break;
      }
    }
    break;
    case yellow:
    {
      LED_SetStatus(LED_GREEN,LED_OFF);
      LED_SetStatus(LED_YELLOW,LED_ON);
      LED_SetStatus(LED_RED,LED_OFF);      
      switch(previous)
      {
        case green:
        {
          if(CounterSeconds==YELLOW_LED_SECONDS)
          {
            CounterSeconds=0;
            state=red;
            previous=yellow;
          }
        }
        break;
        case red:
        {
          if(CounterSeconds==YELLOW_LED_SECONDS)
          {
            CounterSeconds=0;
            state=green;
            previous=yellow;
          }
        }
        break;
      }
    }
    break;
    case red:
    {
      LED_SetStatus(LED_GREEN,LED_OFF);
      LED_SetStatus(LED_YELLOW,LED_OFF);
      LED_SetStatus(LED_RED,LED_ON);  
      switch(previous)
      {
        case yellow:
        {
          if(CounterSeconds==RED_LED_SECONDS)
          {
            CounterSeconds=0;
            state=yellow;
            previous=red;
          }
        }
        break;
      }
    }
    break;
  }

}