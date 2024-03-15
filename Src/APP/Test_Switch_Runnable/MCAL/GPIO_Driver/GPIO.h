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
#define GPIO_PIN0						(0UL)
#define GPIO_PIN1						(1UL)
#define GPIO_PIN2						(2UL)
#define GPIO_PIN3						(3UL)
#define GPIO_PIN4						(4UL)
#define GPIO_PIN5						(5UL)
#define GPIO_PIN6						(6UL)
#define GPIO_PIN7						(7UL)
#define GPIO_PIN8						(8UL)
#define GPIO_PIN9						(9UL)
#define GPIO_PIN10						(10UL)
#define GPIO_PIN11						(11UL)
#define GPIO_PIN12						(12UL)
#define GPIO_PIN13						(13UL)
#define GPIO_PIN14						(14UL)
#define GPIO_PIN15						(15UL)

/**************************************************************************/
/*						ALTERNATING FUNCTION OPTION  MACROS	 		 	  */
/**************************************************************************/
#define AF0								(0UL)
#define AF1								(1UL)
#define AF2								(2UL)
#define AF3								(3UL)
#define AF4								(4UL)
#define AF5								(5UL)
#define AF6								(6UL)
#define AF7								(7UL)
#define AF8								(8UL)
#define AF9								(9UL)
#define AF10							(10UL)
#define AF11							(11UL)
#define AF12							(12UL)
#define AF13							(13UL)
#define AF14							(14UL)
#define AF15							(15UL)
#define AF_DEACTIVATED					(16UL)

/**************************************************************************/
/*						MODES MACROS								 	  */
/**************************************************************************/
#define MODE_OUTPUT_PP					0x00000001
#define MODE_OUTPUT_PP_PU				0x00000005
#define MODE_OUTPUT_PP_PD				0x00000009
#define MODE_OUTPUT_OD					0x00000011
#define MODE_OUTPUT_OD_PU				0x00000015
#define MODE_OUTPUT_OD_PD				0x00000019
#define MODE_AF_PP						0x00000002
#define MODE_AF_PP_PU					0x00000006
#define MODE_AF_PP_PD					0x0000000A
#define MODE_AF_OD						0x0000000C
#define MODE_AF_OD_PU					0x00000016
#define MODE_AF_OD_PD					0x0000001A
#define MODE_INPUT_FLOATING				0x00000000
#define MODE_INPUT_PU					0x00000004
#define MODE_INPUT_PD					0x00000008
#define MODE_ANALOG						0x00000003

/**************************************************************************/
/*						SPEED MACROS			 					 	  */
/**************************************************************************/
#define SPEED_LOW						(0UL)
#define SPEED_MEDIUM					(1UL)
#define SPEED_HIGH						(2UL)
#define SPEED_VERY_HIGH					(3UL)

/**************************************************************************/
/*						GPIO BIT SET/RESET MACRO					 	  */
/**************************************************************************/
#define GPIO_RESET_PIN					0x00010000
#define GPIO_SET_PIN					0x00000001

/**************************************************************************/
/*						GPIO LOW/HIGH MACRO		 					 	  */
/**************************************************************************/
#define GPIO_LOW						(0U)
#define GPIO_HIGH						(1U)


/**************************************************************************/
/*						GPIO Pin Configuration Struct	 			 	  */
/**************************************************************************/

/**
 * @note    Use 32-bit variables to avoid implicit casting
 * 
 * @param   1) Port
 * 			2) Pin
 * 			3) Speed
 * 			4) Mode
 * 			5) AF_Choice
 */
typedef struct
{
	void* Port; 		 /* GPIO_PORTA, GPIO_PORTB, GPIO_PORTC, GPIO_PORTD, GPIO_PORTE, GPIO_PORTH */
	u32 Pin;  			 /* GPIO_PIN0 -> GPIO_PIN15 */

	u32 Speed;			 /* SPEED_LOW, SPEED_MEDIUM, SPEED_HIGH, SPEED_VERY_HIGH */

	u32 Mode;   		 /* # MACRO Starts with MODE_
						    # Selects mode from Input/Output/Alternating Function/Analog
						    # If Mode is Output -> Select whether Output Type is PP(Push Pull) or OD(Open Drain)
						    # Select if circuit is PU(Pull Up), PD(Pull Down), or Deactivated */


	u32 AF_Choice; 		 /* # Macro begins with AF
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
GPIO_ErrorStatus_t GPIO_SetPinValue(void*Port, u32 Pin,u32 Value );

/**
 * @brief	Function that Gets a GPIO Pin Value
 *
 * @param	-Port			(GPIO_PORTA, GPIO_PORTB, GPIO_PORTC, GPIO_PORTD, GPIO_PORTE, GPIO_PORTH)
 * 			-Pin			(GPIO_PIN0->GPIO_PIN15)
 * 			-*Value			(GPIO_LOW/GPIO_HIGH)
 *
 * @error	Error Status    GPIO_InvalidParameter/ GPIO_Ok / GPIO_NullPointer
 */
GPIO_ErrorStatus_t GPIO_GetPinValue(void*Port, u32 Pin, u8*Value);
#endif
