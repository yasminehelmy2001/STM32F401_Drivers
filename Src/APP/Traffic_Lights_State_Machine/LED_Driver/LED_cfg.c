/*
* File:    LED_cfg.c
* Author:  Yasmin Amr
* Created: 17/2/2024
* Brief:   LED Driver
* Target:  STM32F401cc
*/

#include "GPIO.h"
#include "LED.h"

/**
 * In this array, you will create an array of structs, each struct represents a LED
 *
 * You will use your LED Name as the array index: [Led_Alarm]
 *
 * You will specify these parameters for each pin:
 *
 * 		-Port			 // (GPIO_PORTA,GPIO_PORTB, GPIO_PORTC,GPIO_PORTD,GPIO_PORTE,GPIO_PORTH)
 * 		-Pin  			 // (GPIO_PIN0 -> GPIO_PIN15)
 * 		-Connection		 // (LED_CONN_FOR / LED_CONN_REV)
 * 		-Initial State	 // (LED_ON / LED_OFF)
 *
 * An Example of the array is shown below:
 *
 * const LedCfg_t Leds[_Led_Num]={
 *
 *     [LED_ONE]={
 *       .Port=GPIO_PORTA,
 *       .Pin=GPIO_PIN0,
 *       .Connection=LED_CONN_FOR,
 *       .InitialState=LED_ON
 *   	},
 *
 *   	[LED_TWO]={
 *       .Port=GPIO_PORTA,
 *       .Pin=GPIO_PIN1,
 *       .Connection=LED_CONN_REV,
 *       .InitialState=LED_OFF
 *   	}
 *
 * 	};
 */

const LedCfg_t Leds[_Led_Num]={

 [LED_RED]={
        .Port=GPIO_PORTA,
        .Pin=GPIO_PIN0,
        .Connection=LED_CONN_FOR,
        .InitialState=LED_OFF
    	},
 [LED_YELLOW]={
        .Port=GPIO_PORTA,
        .Pin=GPIO_PIN1,
        .Connection=LED_CONN_FOR,
        .InitialState=LED_OFF
 },
 [LED_GREEN]={
        .Port=GPIO_PORTA,
        .Pin=GPIO_PIN2,
        .Connection=LED_CONN_FOR,
        .InitialState=LED_OFF
 }


};


