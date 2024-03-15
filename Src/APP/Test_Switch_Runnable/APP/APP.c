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
#include "SWITCH.h"
#include "APP.h"

//extern Runnables_t System_Runnables[];

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

// void Traffic_Lights(void)
// {
//   /*Current State*/
//   static TrafficLightState_t state=green;
//   /*Previous State*/
//   static TrafficLightState_t previous=yellow;
//   /*Increments by Periodicity*/
//   static u32 Counter_Seconds=0;
//   /*Increment 'counter' by runnables periodicity*/
//   Counter_Seconds+=((System_Runnables[Traffic_Lights_Runnble].PeriodicityMs)/(u32)MS_TO_S);

//   switch(state)
//   {
//     case green:
//     {
//       LED_SetStatus(LED_GREEN,LED_ON);
//       LED_SetStatus(LED_YELLOW,LED_OFF);
//       LED_SetStatus(LED_RED,LED_OFF);
//       switch(previous)
//       {
//         case yellow:
//         {
//           if(Counter_Seconds==GREEN_LED_SECONDS)
//           {
//             Counter_Seconds=RESET_COUNTER;
//             state=yellow;
//             previous=green;
//           }
//         }
//         break;
//       }
//     }
//     break;
//     case yellow:
//     {
//       LED_SetStatus(LED_GREEN,LED_OFF);
//       LED_SetStatus(LED_YELLOW,LED_ON);
//       LED_SetStatus(LED_RED,LED_OFF);      
//       switch(previous)
//       {
//         case green:
//         {
//           if(Counter_Seconds==YELLOW_LED_SECONDS)
//           {
//             Counter_Seconds=RESET_COUNTER;
//             state=red;
//             previous=yellow;
//           }
//         }
//         break;
//         case red:
//         {
//           if(Counter_Seconds==YELLOW_LED_SECONDS)
//           {
//             Counter_Seconds=RESET_COUNTER;
//             state=green;
//             previous=yellow;
//           }
//         }
//         break;
//       }
//     }
//     break;
//     case red:
//     {
//       LED_SetStatus(LED_GREEN,LED_OFF);
//       LED_SetStatus(LED_YELLOW,LED_OFF);
//       LED_SetStatus(LED_RED,LED_ON);  
//       switch(previous)
//       {
//         case yellow:
//         {
//           if(Counter_Seconds==RED_LED_SECONDS)
//           {
//             Counter_Seconds=RESET_COUNTER;
//             state=yellow;
//             previous=red;
//           }
//         }
//         break;
//       }
//     }
//     break;
//   }

// }