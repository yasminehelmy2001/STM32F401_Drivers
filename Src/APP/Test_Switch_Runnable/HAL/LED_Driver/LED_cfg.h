/*
* File:    LED_cfg.h
* Author:  Yasmin Amr
* Created: 17/2/2024
* Brief:   LED Driver
* Target:  STM32F401cc
*/

#ifndef LED_CFG_H_
#define LED_CFG_H_

/**
 * Enter your LED Names above the "_Led_Num" integer like the following:
 * 		typedef enum
 * 		{
 *			LED_ONE,
 *			LED_TWO,
 *			LED_THREE
 *
 *			_Led_Num
 * 		}Leds_t;
 *
 */
typedef enum
{
	LED_RED,
	_Led_Num
}Leds_t;

#endif /* LED_CFG_H_ */
