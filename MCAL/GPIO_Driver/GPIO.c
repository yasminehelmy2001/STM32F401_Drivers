/*
* File:    GPIO.c
* Author:  Yasmin Amr
* Created: 17/2/2024
* Brief:   GPIO Driver
* Target:  STM32F401cc
*/

#include "GPIO.h"

#define ONE_BIT_MASK					0x00000001
#define TWO_BIT_MASK					0x00000003
#define FOUR_BIT_MASK					0x0000000F

#define MODE_MASK						0x03
#define OUTPUT_TYPE_MASK				0x10
#define PUPD_MASK						0x0C

#define SHIFT_2							(2U)
#define SHIFT_4							(4U)

#define INPUT_MODE						(0U)
#define OUTPUT_MODE						(1U)
#define AF_MODE							(2U)
#define ANALOG_MODE						(3U)

#define PUPD_DEACTIVATED				(0U)
#define PUPD_PULL_UP					(1U)
#define PUPD_PULL_DOWN					(2U)

#define OUTPUT_TYPE_PP					(0U)
#define OUTPUT_TYPE_OD					(1U)
#define OUTPUT_TYPE_DEACTIVATED			(2U)

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
	else
	{
		GPIO_Registers_t volatile *Port= (GPIO_Registers_t volatile *) (PinCfg->Port);

		u32 Pin= PinCfg->Pin;
		u32 Speed= PinCfg->Speed;
		u32 Direction_Mode= (PinCfg->Mode & MODE_MASK);
		u32 OutputType=(PinCfg->Mode & OUTPUT_TYPE_MASK)>>SHIFT_4;
		u32 PUPD= (PinCfg->Mode & PUPD_MASK)>>SHIFT_2;
		u32 AF_Choice= PinCfg->AF_Choice;

		if(!((Direction_Mode<=ANALOG_MODE)&&(OutputType<=OUTPUT_TYPE_DEACTIVATED) &&
		  ((PUPD==PUPD_PULL_UP)||(PUPD==PUPD_PULL_DOWN)||(PUPD==PUPD_DEACTIVATED)) &&
		  ((Port==GPIO_PORTA)||(Port==GPIO_PORTB)||(Port==GPIO_PORTC)|| (Port==GPIO_PORTD)||
		  (Port==GPIO_PORTE)||(Port==GPIO_PORTH)) && (Pin<=GPIO_PIN15)))
		{
			RET_ErrorStatus=GPIO_InvalidParameter;
		}
		else if((Direction_Mode==AF_MODE)&&(AF_Choice==AF_DEACTIVATED))
		{
			RET_ErrorStatus=GPIO_InvalidParameter;
		}
		else
		{
			u32 Loc_OSPEEDR= Port->OSPEEDR;
			Loc_OSPEEDR&=~(TWO_BIT_MASK<<Pin*SHIFT_2);
			Loc_OSPEEDR|=(Speed<<Pin*SHIFT_2);
			Port->OSPEEDR= Loc_OSPEEDR;

			u32 Loc_MODER= Port->MODER;
			Loc_MODER&=~(TWO_BIT_MASK<<Pin*SHIFT_2);
			Loc_MODER|=(Direction_Mode<<Pin*SHIFT_2);
			Port->MODER= Loc_MODER;

			u32 Loc_PUPDR= Port->PUPDR;
			Loc_PUPDR&=~(TWO_BIT_MASK<<Pin*SHIFT_2);
			Loc_PUPDR|=(PUPD<<Pin*SHIFT_2);
			Port->PUPDR=Loc_PUPDR;

			u32 Loc_OTYPER=Port->OTYPER;
			Loc_OTYPER&=~(ONE_BIT_MASK<<Pin);
			Loc_OTYPER|=(OutputType<<Pin);
			Port->OTYPER=Loc_OTYPER;

			if(AF_Choice!=AF_DEACTIVATED)
			{
				u32 Loc_AFRx;
				(Pin>GPIO_PIN8)?(Loc_AFRx=Port->AFRH):(Loc_AFRx=Port->AFRL);
				Loc_AFRx&=~(FOUR_BIT_MASK<<Pin*SHIFT_4);
				Loc_AFRx|=(AF_Choice<<Pin*SHIFT_4);
				(Pin>GPIO_PIN8)?(Port->AFRH=Loc_AFRx):(Port->AFRL=Loc_AFRx);
			}
			else
			{
				//Do Nothing
			}

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
GPIO_ErrorStatus_t GPIO_SetPinValue(void*Port, u8 Pin,u32 Value)
{
	GPIO_ErrorStatus_t RET_ErrorStatus=GPIO_Ok;
    GPIO_Registers_t* Loc_Port = (GPIO_Registers_t*)Port;
    if(!(((Value==GPIO_SET_PIN)||(Value==GPIO_RESET_PIN))&&
      ((Port==GPIO_PORTA)||(Port==GPIO_PORTB)||(Port==GPIO_PORTC)
      ||(Port==GPIO_PORTD)||(Port==GPIO_PORTE)||(Port==GPIO_PORTH))))
	{
		RET_ErrorStatus=GPIO_InvalidParameter;
	}
    else if(Port==NULL)
    {
    	RET_ErrorStatus=GPIO_NullPointer;
    }
    else
    {
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
GPIO_ErrorStatus_t GPIO_GetPinValue(void*Port, u8 Pin,u32*Value)
{
	GPIO_ErrorStatus_t RET_ErrorStatus=GPIO_Ok;
    GPIO_Registers_t* Loc_Port = (GPIO_Registers_t*)Port;

	if((Port==NULL)||(Value==NULL))
	{
		RET_ErrorStatus=GPIO_NullPointer;
	}

	else
	{
		*Value=Loc_Port->IDR&(1<<Pin);
	}
	return RET_ErrorStatus;
}

