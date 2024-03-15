/*
* File:    LED.h
* Author:  Yasmin Amr
* Created: 17/2/2024
* Brief:   LED Driver
* Target:  STM32F401cc
*/

#ifndef LED_H_
#define LED_H_

#include "GPIO.h"
#include "LED_cfg.h"
#include "ClockControl.h"


#define LED_OFF					(0U)
#define LED_ON					(1U)

#define LED_CONN_FOR			(0U)
#define LED_CONN_REV			(1U) 

typedef struct
{
	void* Port;			/*(GPIO_PORTA,GPIO_PORTB, GPIO_PORTC,GPIO_PORTD,GPIO_PORTE,GPIO_PORTH)*/

	u8 Pin;				/*(GPIO_PIN0 -> GPIO_PIN15)*/

	u8 Connection; 		/**
	 	 	 	 	 	 * -LED_CONN_FOR: LED Connected to GND
						 * -LED_CONN_REV: LED Connected to VCC
	 	 	 	 	 	 */

	u32 InitialState;	/*(LED_ON/LED_OFF)*/

}LedCfg_t;

typedef enum
{
	LED_Ok,
	LED_Nok,
	LED_InvalidParameter
}LED_ErrorStatus_t;

/**
 * @brief	Initializes all LEDS Pre-configured in LED_cfg.c
 * @param	None
 * @error	Error Status (LED_Ok / LED_Nok)
 */
LED_ErrorStatus_t LED_Init(void);

/**
 * @brief	Sets a LED State to either HIGH or LOW
 *
 * @param	- Led	(Takes the LED name written in the Leds_t enum type in LED_cfg.h)
 * 			- State (LED_ON/ LED_OFF)
 *
 * @error	Error Status (LED_Ok / LED_InvalidParameter)
 */
LED_ErrorStatus_t LED_SetStatus(u32 Led, u8 State);

#endif
