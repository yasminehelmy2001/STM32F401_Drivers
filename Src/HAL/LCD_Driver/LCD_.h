/*
* File:    LCD.h
* Author:  Yasmin Amr
* Created: 23/3/2024
* Brief:   LCD Driver - Using Scheduler
* Target:  STM32F401cc
*/

#ifndef LCD_H_
#define LCD_H_

#include "std_types.h"
#include "GPIO.h"
#include "LCD_cfg.h"

typedef void (*func)(void);

/************************************************************************/
/*					           LCD PINS			                        */
/************************************************************************/
#define RS_PIN		(0U)
#define RW_PIN		(1U)
#define E_PIN		(2U)
#define D0_PIN		(3U)
#define D1_PIN		(4U)
#define D2_PIN		(5U)
#define D3_PIN		(6U)
#define D4_PIN		(7U)
#define D5_PIN		(8U)
#define D6_PIN		(9U)
#define D7_PIN		(10U)

/**************************************************************************/
/*						LCD Configuration Macros					 	  */
/**************************************************************************/
#define LCD_EIGHT_BIT_MODE      (11U)  
#define LCD_FOUR_BIT_MODE       (7U)

/**
 * Struct to Store Port and Pin States of Each LCD Pin
*/
typedef struct 
{
   void *Port;          /*GPIO Port Number of LCD Pin*/
   u32 Pin;             /*GPIO Pin Number of LCD Pin*/
}LCD_Pins_t;

/**
 * Struct to Store State of User Request to Use in Scheduler
*/
typedef struct
{
    const char*string;  /*String to Write on the LCD*/
    u8 length;          /*Length of String*/
    u8 state;           /*User Request State (Ready/Busy)*/
    u8 type;            /*Type of Request (Write/Clear/SetCursorPosition)*/
    u8 posX;            /*Stores Position of Row on LCD*/
    u8 posY;            /*Stores Position of Column on LCD*/
    func callback;      /*Callback function to call after end of a single operation*/

}LCD_Request_t;


void LCD_InitAsync(func callback);
void LCD_ClearScreenAsync(func callback);
void LCD_WriteStringAsync(const char*string, u8 length,func callback);
void LCD_SetCursorPosAsync(u8 posX, u8 posY, func callback);
void LCD_InitPins(void);

//void LCD_getState(void);
#endif