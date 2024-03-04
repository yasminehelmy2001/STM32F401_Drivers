/*
* File:    GPIO.c
* Author:  Yasmin Amr
* Created: 17/2/2024
* Brief:   GPIO Driver
* Target:  STM32F401cc
*/

#include "GPIO.h"

#define ONE_BIT_MASK						0x00000001
#define TWO_BIT_MASK						0x00000003
#define FOUR_BIT_MASK						0x0000000F

#define MODE_MASK							0x00000003
#define OUTPUT_TYPE_MASK					0x00000010
#define PUPD_MASK							0x0000000C

#define SHIFT_2								(2U)
#define SHIFT_4								(4U)

#define IS_GPIO_MODE(MODE)					(((MODE) == MODE_OUTPUT_PP)          ||\
											((MODE) == MODE_OUTPUT_PP_PU)        ||\
											((MODE) == MODE_OUTPUT_PP_PD)        ||\
											((MODE) == MODE_OUTPUT_OD)           ||\
											((MODE) == MODE_OUTPUT_OD_PU)        ||\
											((MODE) == MODE_OUTPUT_OD_PD)        ||\
											((MODE) == MODE_AF_PP)               ||\
											((MODE) == MODE_AF_PP_PU)            ||\
											((MODE) == MODE_AF_PP_PD)            ||\
											((MODE) == MODE_AF_OD)               ||\
											((MODE) == MODE_AF_OD_PU)            ||\
											((MODE) == MODE_AF_OD_PD)            ||\
											((MODE) == MODE_INPUT_FLOATING)      ||\
											((MODE) == MODE_INPUT_PU)            ||\
											((MODE) == MODE_INPUT_PD)            ||\
											((MODE) == MODE_ANALOG))

#define	IS_GPIO_SPEED(SPEED)				(((SPEED) == SPEED_LOW)         	||\
                              	  			((SPEED) == SPEED_MEDIUM)      		||\
											((SPEED) == SPEED_HIGH)        		||\
											((SPEED) == SPEED_VERY_HIGH))

#define IS_GPIO_PORT(PORT)					(((PORT) == GPIO_PORTA)				||\
											((PORT) == GPIO_PORTB)				||\
											((PORT) == GPIO_PORTC)				||\
											((PORT) == GPIO_PORTD)				||\
											((PORT) == GPIO_PORTE)				||\
											((PORT) == GPIO_PORTH))

#define IS_GPIO_PIN(PIN) 		  			(((PIN) == GPIO_PIN0) 				||\
								  			((PIN) == GPIO_PIN1)  				||\
											((PIN) == GPIO_PIN2)  				||\
											((PIN) == GPIO_PIN3)  				||\
											((PIN) == GPIO_PIN4)  				||\
											((PIN) == GPIO_PIN5)  				||\
											((PIN) == GPIO_PIN6)  				||\
											((PIN) == GPIO_PIN7)  				||\
											((PIN) == GPIO_PIN8)  				||\
											((PIN) == GPIO_PIN9)  				||\
											((PIN) == GPIO_PIN10) 				||\
											((PIN) == GPIO_PIN11) 				||\
											((PIN) == GPIO_PIN12) 				||\
											((PIN) == GPIO_PIN13) 				||\
											((PIN) == GPIO_PIN14) 				||\
											((PIN) == GPIO_PIN15))

#define IS_GPIO_AF(AF) 						(((AF) == AF0)           			||\
											((AF) == AF1)           			||\
											((AF) == AF2)           			||\
											((AF) == AF3)           			||\
											((AF) == AF4)           			||\
											((AF) == AF5)           			||\
											((AF) == AF6)           			||\
											((AF) == AF7)           			||\
											((AF) == AF8)           			||\
											((AF) == AF9)           			||\
											((AF) == AF10)          			||\
											((AF) == AF11)          			||\
											((AF) == AF12)          			||\
											((AF) == AF13)          			||\
											((AF) == AF14)          			||\
											((AF) == AF15)          			||\
											((AF) == AF_DEACTIVATED))

#define IS_GPIO_CORRECT_AF_CFG(MODE,AF)		(((((MODE) == MODE_AF_PP)             ||\
											((MODE) == MODE_AF_PP_PU)            ||\
											((MODE) == MODE_AF_PP_PD)            ||\
											((MODE) == MODE_AF_OD)               ||\
											((MODE) == MODE_AF_OD_PU)            ||\
											((MODE) == MODE_AF_OD_PD))			 &&\
											((AF)!=AF_DEACTIVATED))				   \
																				 ||\
																				   \
											((!(((MODE) == MODE_AF_PP)           ||\
											((MODE) == MODE_AF_PP_PU)            ||\
											((MODE) == MODE_AF_PP_PD)            ||\
											((MODE) == MODE_AF_OD)               ||\
											((MODE) == MODE_AF_OD_PU)            ||\
											((MODE) == MODE_AF_OD_PD)))			 &&\
											((AF)==AF_DEACTIVATED)))


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
GPIO_ErrorStatus_t GPIO_InitPin(GPIO_Pin_t*PinCfg)
{
	GPIO_ErrorStatus_t RET_ErrorStatus=GPIO_Ok;

	if(PinCfg==NULL)
	{
		RET_ErrorStatus=GPIO_NullPointer;
	}
	else if(((GPIO_Registers_t volatile *) (PinCfg->Port))==NULL)
	{
		RET_ErrorStatus=GPIO_NullPointer;
	}
	else if(!(IS_GPIO_PORT(PinCfg->Port)))
	{
		RET_ErrorStatus=GPIO_InvalidParameter;
	}
	else if(!(IS_GPIO_PIN(PinCfg->Pin)))
	{
		RET_ErrorStatus=GPIO_InvalidParameter;
	}
	else if(!(IS_GPIO_MODE(PinCfg->Mode)))
	{
		RET_ErrorStatus=GPIO_InvalidParameter;
	}
	else if(!(IS_GPIO_SPEED(PinCfg->Speed)))
	{
		RET_ErrorStatus=GPIO_InvalidParameter;
	}
	else if(!(IS_GPIO_AF(PinCfg->AF_Choice)))
	{
		RET_ErrorStatus=GPIO_InvalidParameter;
	}
	else if(!(IS_GPIO_CORRECT_AF_CFG(PinCfg->Mode,PinCfg->AF_Choice)))
	{
		RET_ErrorStatus=GPIO_InvalidParameter;
	}
	else
	{
		GPIO_Registers_t volatile *Port= (GPIO_Registers_t volatile *) (PinCfg->Port);
		u32 Pin= PinCfg->Pin;
		u32 Speed= PinCfg->Speed;
		u32 Direction_Mode= (PinCfg->Mode & MODE_MASK);
		u32 OutputType=(PinCfg->Mode & OUTPUT_TYPE_MASK)>>SHIFT_4;
		u32 PUPD= (PinCfg->Mode & PUPD_MASK)>>SHIFT_2;
		u32 AF_Choice= PinCfg->AF_Choice;

		u32 Loc_Register= Port->OSPEEDR;
		Loc_Register&=~(TWO_BIT_MASK<<Pin*SHIFT_2);
		Loc_Register|=(Speed<<Pin*SHIFT_2);
		Port->OSPEEDR= Loc_Register;

		Loc_Register= Port->MODER;
		Loc_Register&=~(TWO_BIT_MASK<<Pin*SHIFT_2);
		Loc_Register|=(Direction_Mode<<Pin*SHIFT_2);
		Port->MODER= Loc_Register;

		Loc_Register= Port->PUPDR;
		Loc_Register&=~(TWO_BIT_MASK<<Pin*SHIFT_2);
		Loc_Register|=(PUPD<<Pin*SHIFT_2);
		Port->PUPDR=Loc_Register;

		Loc_Register=Port->OTYPER;
		Loc_Register&=~(ONE_BIT_MASK<<Pin);
		Loc_Register|=(OutputType<<Pin);
		Port->OTYPER=Loc_Register;

		if(AF_Choice!=AF_DEACTIVATED)
		{
			u8 RegisterPinState=Pin%8;
			(Pin>GPIO_PIN7)?(Loc_Register=Port->AFRH):(Loc_Register=Port->AFRL);
			Loc_Register&=~(FOUR_BIT_MASK<<RegisterPinState*SHIFT_4);
			Loc_Register|=(AF_Choice<<RegisterPinState*SHIFT_4);
			(Pin>GPIO_PIN7)?(Port->AFRH=Loc_Register):(Port->AFRL=Loc_Register);
		}
		else
		{
			//Do Nothing
		}

	}
	return RET_ErrorStatus;
}

/**
 * @brief	Function that Sets a GPIO Pin to either HIGH/LOW
 *
 * @param	-Port			(GPIO_PORTA, GPIO_PORTB, GPIO_PORTC, GPIO_PORTD, GPIO_PORTE, GPIO_PORTH)
 * 			-Pin			(GPIO_PIN0->GPIO_PIN15)
 * 			-Value			(GPIO_SET_PIN/GPIO_RESET_PIN)
 *
 * @error	Error Status    GPIO_InvalidParameter/ GPIO_Ok / GPIO_NullPointer
 */
GPIO_ErrorStatus_t GPIO_SetPinValue(void*Port, u32 Pin,u32 Value)
{
	GPIO_ErrorStatus_t RET_ErrorStatus=GPIO_Ok;

	if(Port==NULL)
	{
    	RET_ErrorStatus=GPIO_NullPointer;
	}
	else if(!(IS_GPIO_PORT(Port)))
	{
		RET_ErrorStatus=GPIO_InvalidParameter;
	}
	else if(!(IS_GPIO_PIN(Pin)))
	{
		RET_ErrorStatus=GPIO_InvalidParameter;
	}
    else if(!((Value==GPIO_SET_PIN)||(Value==GPIO_RESET_PIN)))
	{
		RET_ErrorStatus=GPIO_InvalidParameter;
	}
    else
    {
        GPIO_Registers_t* Loc_Port = (GPIO_Registers_t*)Port;
        Loc_Port->BSRR = (Value<<Pin);
    }
	return RET_ErrorStatus;
}

/**
 * @brief	Function that Gets a GPIO Pin Value
 *
 * @param	-Port			(GPIO_PORTA, GPIO_PORTB, GPIO_PORTC, GPIO_PORTD, GPIO_PORTE, GPIO_PORTH)
 * 			-Pin			(GPIO_PIN0->GPIO_PIN15)
 * 			-*Value			(GPIO_LOW/GPIO_HIGH)
 *
 * @error	Error Status    GPIO_InvalidParameter/ GPIO_Ok / GPIO_NullPointer
 */
GPIO_ErrorStatus_t GPIO_GetPinValue(void*Port, u32 Pin,u8*Value)
{
	GPIO_ErrorStatus_t RET_ErrorStatus=GPIO_Ok;
    GPIO_Registers_t* Loc_Port = (GPIO_Registers_t*)Port;

	if((Port==NULL)||(Value==NULL))
	{
		RET_ErrorStatus=GPIO_NullPointer;
	}
	else if(!(IS_GPIO_PORT(Port)))
	{
		RET_ErrorStatus=GPIO_InvalidParameter;
	}
	else if(!(IS_GPIO_PIN(Pin)))
	{
		RET_ErrorStatus=GPIO_InvalidParameter;
	}
	else
	{
		*Value=Loc_Port->IDR&(1<<Pin);
	}
	return RET_ErrorStatus;
}

