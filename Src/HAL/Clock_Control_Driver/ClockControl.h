/*
* File:    ClockControl.h
* Author:  Yasmin Amr
* Created: 2/3/2024
* Brief:   Clock Control Driver
* Target:  STM32F401cc
*/

#define ON      (1U)
#define OFF     (0U)

#define CLOCK_CONTROL_GPIOA     ON
#define CLOCK_CONTROL_GPIOB     ON
#define CLOCK_CONTROL_GPIOC     ON
#define CLOCK_CONTROL_GPIOD     ON
#define CLOCK_CONTROL_GPIOE     ON
#define CLOCK_CONTROL_GPIOF     ON
#define CLOCK_CONTROL_GPIOG     ON
#define CLOCK_CONTROL_GPIOH     ON

#define CLOCK_CONTROL_UART1      ON
#define CLOCK_CONTROL_UART2      ON
#define CLOCK_CONTROL_UART6      ON

/**
 * @brief	Enables RCC Clock for all HAL Layers
 */
void Enable_HAL_ClockControl(void);

