/*
* File:    GPIO.h
* Author:  Yasmin Amr
* Created: 17/2/2024
* Brief:   GPIO Driver
* Target:  STM32F401cc
*/

#ifndef GPIO_H_
#define GPIO_H_

#include "std_types.h"

/**************************************************************************/
/*						PORT MACROS				 					 	  */
/**************************************************************************/
#define GPIO_PORTA						(void*)(0x40020000)
#define GPIO_PORTB						(void*)(0x40020400)
#define GPIO_PORTC						(void*)(0x40020800)
#define GPIO_PORTD						(void*)(0x40020C00)
#define GPIO_PORTE						(void*)(0x40021000)
#define GPIO_PORTH						(void*)(0x40021C00)

/**************************************************************************/
/*						PIN MACROS				 					 	  */
/**************************************************************************/
#define GPIO_PIN0						0
#define GPIO_PIN1						1
#define GPIO_PIN2						2
#define GPIO_PIN3						3
#define GPIO_PIN4						4
#define GPIO_PIN5						5
#define GPIO_PIN6						6
#define GPIO_PIN7						7
#define GPIO_PIN8						8
#define GPIO_PIN9						9
#define GPIO_PIN10						10
#define GPIO_PIN11						11
#define GPIO_PIN12						12
#define GPIO_PIN13						13
#define GPIO_PIN14						14
#define GPIO_PIN15						15

/**************************************************************************/
/*						ALTERNATING FUNCTION OPTION  MACROS	 		 	  */
/**************************************************************************/
#define AF0							(0U)
#define AF1							(1U)
#define AF2							(2U)
#define AF3							(3U)
#define AF4							(4U)
#define AF5							(5U)
#define AF6							(6U)
#define AF7							(7U)
#define AF8							(8U)
#define AF9							(9U)
#define AF10						(10U)
#define AF11						(11U)
#define AF12						(12U)
#define AF13						(13U)
#define AF14						(14U)
#define AF15						(15U)
#define AF_DEACTIVATED				(16U)

/**************************************************************************/
/*						MODES MACROS								 	  */
/**************************************************************************/
#define MODE_OUTPUT_PP				0x01
#define MODE_OUTPUT_PP_PU			0x05
#define MODE_OUTPUT_PP_PD			0x09
#define MODE_OUTPUT_OD				0x11
#define MODE_OUTPUT_OD_PU			0x15
#define MODE_OUTPUT_OD_PD			0x19
#define MODE_AF_PP					0x02
#define MODE_AF_PP_PU				0x06
#define MODE_AF_PP_PD				0x0A
#define MODE_AF_OD					0x0C
#define MODE_AF_OD_PU				0x16
#define MODE_AF_OD_PD				0x1A
#define MODE_INPUT_FLOATING			0x00
#define MODE_INPUT_PU				0x04
#define MODE_INPUT_PD				0x08
#define MODE_ANALOG					0x03

/**************************************************************************/
/*						SPEED MACROS			 					 	  */
/**************************************************************************/
#define SPEED_LOW					(0U)
#define SPEED_MEDIUM				(1U)
#define SPEED_HIGH					(2U)
#define SPEED_VERY_HIGH				(3U)

/**************************************************************************/
/*						GPIO BIT SET/RESET MACRO					 	  */
/**************************************************************************/
#define GPIO_RESET_PIN				0x00010000
#define GPIO_SET_PIN				0x00000001

/**************************************************************************/
/*						GPIO LOW/HIGH MACRO		 					 	  */
/**************************************************************************/
#define GPIO_LOW					(0U)
#define GPIO_HIGH					(1U)

/**************************************************************************/
/*						GPIO Registers Struct			 			 	  */
/**************************************************************************/
typedef struct
{
	volatile u32 MODER;
	volatile u32 OTYPER;
	volatile u32 OSPEEDR;
	volatile u32 PUPDR;
	volatile u32 IDR;
	volatile u32 ODR;
	volatile u32 BSRR;
	volatile u32 LCKR;
	volatile u32 AFRL;
	volatile u32 AFRH;
} GPIO_Registers_t;


/**************************************************************************/
/*						GPIO Pin Configuration Struct	 			 	  */
/**************************************************************************/
typedef struct
{
	void* Port; 		 /* GPIO_PORTA, GPIO_PORTB, GPIO_PORTC, GPIO_PORTD, GPIO_PORTE, GPIO_PORTH */
	u8 Pin;  			 /* GPIO_PIN0 -> GPIO_PIN15 */

	u8 Speed;			 /* SPEED_LOW, SPEED_MEDIUM, SPEED_HIGH, SPEED_VERY_HIGH */

	u8 Mode;   		 	 /* # MACRO Starts with MODE_
  							# Selects mode from Input/Output/Alternating Function/Analog
 							# If Mode is Output -> Select whether Output Type is PP(Push Pull) or OD(Open Drain)
  							# Select if circuit is PU(Pull Up), PD(Pull Down), or Deactivated */


	u8 AF_Choice; 		 /* # Macro begins with AF
							# Selects Alternating Function from 16 choices
							# Choices: AF0->AF_15 or AF_DEACTIVATED
							# You should enable your selected peripheral from RCC! */


} GPIO_Pin_t;

/**************************************************************************/
/*						GPIO ERROR STATUS		 					 	  */
/**************************************************************************/
typedef enum
{
	GPIO_Ok,
	GPIO_Nok,
	GPIO_InvalidParameter,
	GPIO_NullPointer
}GPIO_ErrorStatus_t;

/**************************************************************************/
/*						FUNCTION PROTOTYPES		 					 	  */
/**************************************************************************/

/**
 * @brief	Function that Initializes a GPIO PIN
 *
 * @param	Pointer to GPIO_Pin_t Struct, contains:
 *
 * 			- Port 			(GPIO_PORTA, GPIO_PORTB, GPIO_PORTC, GPIO_PORTD, GPIO_PORTE, GPIO_PORTH)
 *
 * 			- Pin  			(GPIO_PIN0->GPIO_PIN15)
 *
 * 			- Speed			(Macro begins with SPEED_)
 *
 * 			- Mode			# (Macro begins with MODE_)
 * 							# Selects mode from Input/Output/Alternating Function/Analog
 * 							# If Mode is Output -> Select whether Output Type is PP(Push Pull) or OD(Open Drain)
 * 							# Select if circuit is PU(Pull Up), PD(Pull Down), or Deactivated
 *
 *
 * 			- AF_CHOICE		# Selects Alternating Function from 16 choices
 * 							# (Macro begins with AF)
 * 							# Choices: AF0->AF_15 or AF_DEACTIVATED
 * 							# You should enable your selected peripheral from RCC!
 *
 * @error	Error Status    GPIO_InvalidParameter/ GPIO_Ok / GPIO_NullPointer
 *
 * @note: You should enable the GPIO Peripheral using RCC before Initialization!
 */
GPIO_ErrorStatus_t GPIO_InitPin(GPIO_Pin_t*PinCfg);

/**
 * @brief	Function that Sets a GPIO Pin to either HIGH/LOW (OUTPUT MODE)
 *
 * @param	-Port			(GPIO_PORTA, GPIO_PORTB, GPIO_PORTC, GPIO_PORTD, GPIO_PORTE, GPIO_PORTH)
 * 			-Pin			(GPIO_PIN0->GPIO_PIN15)
 * 			-Value			(GPIO_SET_PIN/GPIO_RESET_PIN)
 *
 * @error	Error Status    GPIO_InvalidParameter/ GPIO_Ok / GPIO_NullPointer
 */
GPIO_ErrorStatus_t GPIO_SetPinValue(void*Port, u8 Pin,u32 Value );

/**
 * @brief	Function that Gets a GPIO Pin Value
 *
 * @param	-Port			(GPIO_PORTA, GPIO_PORTB, GPIO_PORTC, GPIO_PORTD, GPIO_PORTE, GPIO_PORTH)
 * 			-Pin			(GPIO_PIN0->GPIO_PIN15)
 * 			-*Value			(GPIO_LOW/GPIO_HIGH)
 *
 * @error	Error Status    GPIO_InvalidParameter/ GPIO_Ok / GPIO_NullPointer
 */
GPIO_ErrorStatus_t GPIO_GetPinValue(void*Port, u8 Pin, u32*Value);
#endif
