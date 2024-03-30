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
#include "SWITCH.h"
#include "ClockControl.h"
#include "LCD.h"

/**
 * @brief	Enables RCC Clock for all HAL Layers
 */
void Enable_HAL_ClockControl(void)
{
    #if (CLOCK_CONTROL_GPIOA==ON)
        RCC_EnablePeriphral(AHB1,RCC_GPIOA);
    #endif

    #if(CLOCK_CONTROL_GPIOB==ON)
        RCC_EnablePeriphral(AHB1,RCC_GPIOB);
    #endif

    #if(CLOCK_CONTROL_GPIOC==ON)
        RCC_EnablePeriphral(AHB1,RCC_GPIOC);
    #endif

    #if(CLOCK_CONTROL_GPIOD==ON)
        RCC_EnablePeriphral(AHB1,RCC_GPIOD);
    #endif
    
    #if(CLOCK_CONTROL_GPIOE==ON)
        RCC_EnablePeriphral(AHB1,RCC_GPIOE);
    #endif

    #if(CLOCK_CONTROL_GPIOH==ON)
        RCC_EnablePeriphral(AHB1,RCC_GPIOH);
    #endif

    #if(CLOCK_CONTROL_UART1==ON)
        RCC_EnablePeriphral(APB2,RCC_USART1);
    #endif

    #if(CLOCK_CONTROL_UART2==ON)
        RCC_EnablePeriphral(APB1,RCC_USART2);
    #endif

    #if(CLOCK_CONTROL_UART6==ON)
        RCC_EnablePeriphral(APB2,RCC_USART6);
    #endif
}