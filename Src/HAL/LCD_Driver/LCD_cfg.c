/*
* File:    LCD_cfg.c
* Author:  Yasmin Amr
* Created: 23/3/2024
* Brief:   LCD Driver - Using Scheduler
* Target:  STM32F401cc
*/

#include "LCD_.h"

/* For 8-BIT Mode, Select Port,Pin, and Pin Configuration for RS PIN, RW PIN, E PIN, AND D0-D7 PINS
 * For 4-BIT Mode, Select Port,Pin, and Pin Configuration for RS PIN, RW PIN, E PIN, AND D4-D7 PINS
 *
 * For each PIN, select .Port from options:
 *		1) GPIO_PORTA
 *		2) GPIO_PORTB
 *		3) GPIO_PORTC
 *		4) GPIO_PORTD
 *
 * For each PIN, select .Pin from options:
 *		1) GPIO_PIN0
 *		2) GPIO_PIN1
 *		3) GPIO_PIN2
 *		4) GPIO_PIN3
 *		5) GPIO_PIN4
 *		6) GPIO_PIN5
 *		7) GPIO_PIN6
 *		8) GPIO_PIN7
 *
 * Example of Configuration for Four Bit Mode:
 * LCD_Pins_t LCD_CfgArray[LCD_MODE]=
 *   {
 *       [RS_PIN]=
 *       {
 *           .Port=GPIO_PORTA,
 *           .Pin=GPIO_PIN0
 *       },
 *       [RW_PIN]
 *       {
 *           .Port=GPIO_PORTA,
 *           .Pin=GPIO_PIN1
 *       },
 *       [E_PIN]
 *       {
 *           .Port=GPIO_PORTA,
 *           .Pin=GPIO_PIN2
 *       },
 *       [D4_PIN]
 *       {
 *           .Port=GPIO_PORTC,
 *           .Pin=GPIO_PIN4 
 *       },
 *       [D5_PIN]
 *       {
 *           .Port=GPIO_PORTC,
 *           .Pin=GPIO_PIN5 
 *       },
 *       [D6_PIN]
 *       {
 *           .Port=GPIO_PORTC,
 *           .Pin=GPIO_PIN6 
 *       },
 *       [D7_PIN]
 *       {
 *           .Port=GPIO_PORTC,
 *           .Pin=GPIO_PIN7 
 *       }
 *   }
 *
 */
LCD_Pins_t volatile LcdCfgArray[LCD_BITS]=
{
    [RS_PIN]=
    {
        .Port=GPIO_PORTA,
        .Pin=GPIO_PIN0
    },
    [RW_PIN]
    {
        .Port=GPIO_PORTA,
        .Pin=GPIO_PIN1
    },
    [E_PIN]
    {
        .Port=GPIO_PORTA,
        .Pin=GPIO_PIN2
    },
    [D0_PIN]
    {
        .Port=GPIO_PORTA,
        .Pin=GPIO_PIN3 
    },
    [D1_PIN]
    {
        .Port=GPIO_PORTA,
        .Pin=GPIO_PIN4 
    },
    [D2_PIN]
    {
        .Port=GPIO_PORTA,
        .Pin=GPIO_PIN5 
    },
    [D3_PIN]
    {
        .Port=GPIO_PORTA,
        .Pin=GPIO_PIN6 
    },
    [D4_PIN]
    {
        .Port=GPIO_PORTA,
        .Pin=GPIO_PIN7 
    },
    [D5_PIN]
    {
        .Port=GPIO_PORTA,
        .Pin=GPIO_PIN8 
    },
    [D6_PIN]
    {
        .Port=GPIO_PORTA,
        .Pin=GPIO_PIN9 
    },
    [D7_PIN]
    {
        .Port=GPIO_PORTA,
        .Pin=GPIO_PIN10 
    }
};