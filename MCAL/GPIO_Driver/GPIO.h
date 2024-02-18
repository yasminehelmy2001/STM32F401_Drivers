#ifndef GPIO_H_
#define GPIO_H_

#include "std_types.h"

/**************************************************************************/
/*						PORT MACROS				 					 	  */
/**************************************************************************/
#define GPIOA						(void*)(0x40020000)
#define GPIOB						(void*)(0x40020400)
#define GPIOC						(void*)(0x40020800)
#define GPIOD						(void*)(0x40020C00)
#define GPIOE						(void*)(0x40021000)
#define GPIOH						(void*)(0x40021C00)

/**************************************************************************/
/*						PIN MACROS				 					 	  */
/**************************************************************************/
#define PIN0						0
#define PIN1						1
#define PIN2						2
#define PIN3						3
#define PIN4						4
#define PIN5						5
#define PIN6						6
#define PIN7						7
#define PIN8						8
#define PIN9						9
#define PIN10						10
#define PIN11						11
#define PIN12						12
#define PIN13						13
#define PIN14						14
#define PIN15						15

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
	void* Port; 		 /* GPIOA, GPIOB, GPIOC, GPIOD, GPIOE, GPIOH */
	u8 Pin;  			 /* PIN0 -> PIN15 */

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
 * 			- Port 			(GPIOA, GPIOB, GPIOC, GPIOD, GPIOE, GPIOH)
 *
 * 			- Pin  			(PIN0->PIN15)
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
 * @param	-Port			(GPIOA, GPIOB, GPIOC, GPIOD, GPIOE, GPIOH)
 * 			-Pin			(PIN0->PIN15)
 * 			-Value			(GPIO_LOW/GPIO_HIGH)
 *
 * @error	Error Status    GPIO_InvalidParameter/ GPIO_Ok / GPIO_NullPointer
 */
GPIO_ErrorStatus_t GPIO_SetPinValue(void*Port, u8 Pin,u8 Value );

/**
 * @brief	Function that Gets a GPIO Pin Value
 *
 * @param	-Port			(GPIOA, GPIOB, GPIOC, GPIOD, GPIOE, GPIOH)
 * 			-Pin			(PIN0->PIN15)
 * 			-*Value			(GPIO_LOW/GPIO_HIGH)
 *
 * @error	Error Status    GPIO_InvalidParameter/ GPIO_Ok / GPIO_NullPointer
 */
GPIO_ErrorStatus_t GPIO_GetPinValue(void*Port, u8 Pin, u8*Value);
#endif
