/*
* File:    LCD_cfg.h
* Author:  Yasmin Amr
* Created: 23/3/2024
* Brief:   LCD Driver - Using Scheduler
* Target:  STM32F401cc
*/

#ifndef LCD_CFG_H_
#define LCD_CFG_H_

#include "GPIO.h"
#include "LCD_.h"

/**
 * Select Your LCD Mode from:
 *      1) LCD_EIGHT_BIT_MODE
 *      2) LCD_FOUR_BIT_MODE
*/
#define LCD_BITS    LCD_EIGHT_BIT_MODE        

#endif