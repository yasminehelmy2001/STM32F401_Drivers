/*
* File:    ClockControl.c
* Author:  Yasmin Amr
* Created: 2/3/2024
* Brief:   Clock Control Driver
* Target:  STM32F401cc
*/

#include "RCC.h"
#include "GPIO.h"
#include "LED.h"
#include "ClockControl.h"

extern const LedCfg_t Leds[_Led_Num];

/**
 * @brief	Enables RCC Clock for all HAL Layers
 */
void Enable_HAL_ClockControl(void)
{
    for(int i=0;i<_Led_Num;i++)
    {
            if(Leds[i].Port==GPIO_PORTA)
            {
                RCC_EnablePeriphral(AHB1,RCC_GPIOA);
            }
            else if(Leds[i].Port==GPIO_PORTB)
            {
                RCC_EnablePeriphral(AHB1,RCC_GPIOB);
            }
            else if(Leds[i].Port==GPIO_PORTC)
            {
                RCC_EnablePeriphral(AHB1,RCC_GPIOC);
            }
            else if(Leds[i].Port==GPIO_PORTD)
            {
                RCC_EnablePeriphral(AHB1,RCC_GPIOD);
            }
            else if(Leds[i].Port==GPIO_PORTE)
            {
                RCC_EnablePeriphral(AHB1,RCC_GPIOE);
            }
            else if(Leds[i].Port==GPIO_PORTH)
            {
                RCC_EnablePeriphral(AHB1,RCC_GPIOH);
            }
            else
            {
                //Empty for MISRA
            }
    }
}