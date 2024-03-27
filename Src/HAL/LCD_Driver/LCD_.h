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

typedef enum
{
    LCD_Ok,
    LCD_Nok
}LCD_ErrorStatus_t;

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

/**
 * @brief	Initializes Pins used with the LCD Module
 */
void LCD_InitPins(void);

/**
 * @brief	Registers User Request for Initializing an LCD Module
 *
 * @param	- CallBack Function
 *
 * @return  void
 */
void LCD_InitAsync(func callback);

/**
 * @brief	Registers User Request for Clear Screan
 *
 * @param	- (callback) CallBack Function
 * 
 * @return  void
 */
void LCD_ClearScreenAsync(func callback);

/**
 * @brief	Registers User Request for Wriiting String + Saves "string" & "length" Information
 *
 * @param	- (string) Pointer to the String
 *          - (length) Length of the String
 *          - (callback) CallBack Function 
 * 
 * @return	Error Status 
 */
LCD_ErrorStatus_t LCD_WriteStringAsync(const char*string, u8 length,func callback);

/**
 * @brief	Registers User Request for Setting Cursor Position and Saves "posX" & "posY" Information.
 *
 * @param	- (posX) Row Number (0/1)
 *          - (posY) Column Number (0->16)
 *          - (callback) CallBack Function 
 * 
 * @return	Error Status 
 */
LCD_ErrorStatus_t LCD_SetCursorPosAsync(u8 posX, u8 posY, func callback);

//void LCD_getState(void);
#endif