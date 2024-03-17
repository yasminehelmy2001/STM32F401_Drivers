/*
* File:    APP1.c
* Author:  Yasmin Amr
* Created: 14/3/2024
* Target:  STM32F401cc
*/

/**
 * Note: For Handler Debugging: Add a breakpoint inside the Handler & use Step Over.
*/

#include "APP.h"

#ifdef APP  
#if (APP==APP1_NVIC)

#include "NVIC.h"
#include "ClockControl.h"
#include "LED.h"

void EXTI0_IRQHandler(void)
{
  LED_SetStatus(LED_RED, LED_OFF);
  LED_SetStatus(LED_YELLOW, LED_OFF);

}

void EXTI1_IRQHandler(void)
{
  LED_SetStatus(LED_RED, LED_ON);
  NVIC_SetPending(NVIC_EXT0_INTERRRUPT);
  LED_SetStatus(LED_YELLOW, LED_ON);
}

int main(void)
{
  Enable_HAL_ClockControl();
  LED_Init();
  
  NVIC_EnableInterrupt(NVIC_EXT0_INTERRRUPT);
  NVIC_EnableInterrupt(NVIC_EXT1_INTERRRUPT);

  /*Testing Nesting Priorities*/
  NVIC_SetPriority(NVIC_EXT0_INTERRRUPT,0,0,SUBPRIORITY_BITS_TWO);
  NVIC_SetPriority(NVIC_EXT1_INTERRRUPT,3,0,SUBPRIORITY_BITS_TWO);

  /** 
   * Testing Non Nesting Priorities
   * Problem: Returns to main after 1st ISR then goes back to 2nd ISR??
   */

  // NVIC_SetPriority(NVIC_EXT0_INTERRRUPT,3,0,SUBPRIORITY_BITS_TWO);
  // NVIC_SetPriority(NVIC_EXT1_INTERRRUPT,0,0,SUBPRIORITY_BITS_TWO);

  /*Testing Pending Register*/
  //NVIC_SetPending(NVIC_EXT1_INTERRRUPT);

  /*Testing STIR Register*/
  //NVIC_GenerateSoftwareInterrupt(NVIC_EXT0_INTERRRUPT);


  while(1)
  {

  }
}

#endif
#endif
