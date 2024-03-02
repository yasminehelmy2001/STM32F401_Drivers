/*
* File:    SWITCH_cfg.c
* Author:  Yasmin Amr
* Created: 19/2/2024
* Brief:   SWITCH Driver
* Target:  STM32F401cc
*/

#include "GPIO.h"
#include "SWITCH.h"

/**
 * In this array, you will create an array of structs, each struct represents a SWITCH
 *
 * You will use your SWITCH Name as the array index: [SWITCH_ONE]
 *
 * You will specify these parameters for each pin:
 *
 * 		-Port			 // (GPIO_PORTA,GPIO_PORTB, GPIO_PORTC,GPIO_PORTD,GPIO_PORTE,GPIO_PORTH)
 * 		-Pin  			 // (GPIO_PIN0 -> GPIO_PIN15)
 * 		-Connection		 // (SWITCH_PULLUP / SWITCH_PULLDOWN)
 *
 * An Example of the array is shown below:
 *
 * const SwitchCfg_t Switches[_Switch_Num]={
 *
 *      [SWITCH_ONE]={
 *       .Port=GPIO_PORTA,
 *       .Pin=GPIO_PIN0,
 *       .Connection=SWITCH_PULLUP
 *   	},
 *
 *      [SWITCH_TWO]={
 *       .Port=GPIO_PORTA,
 *       .Pin=GPIO_PIN1,
 *       .Connection=SWITCH_PULLDOWN
 *   	}
 * 	};
 */

const SwitchCfg_t Switches[_Switch_Num]={



};



