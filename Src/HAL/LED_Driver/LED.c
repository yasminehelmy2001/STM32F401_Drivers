/*
* File:    LED.c
* Author:  Yasmin Amr
* Created: 17/2/2024
* Brief:   LED Driver
* Target:  STM32F401cc
*/

#include "GPIO.h"
#include "LED.h"

extern const LedCfg_t Leds[_Led_Num];

/**
 * @brief	Initializes all LEDS Pre-configured in LED_cfg.c
 * @param	None
 * @error	Error Status (LED_Ok / LED_Nok)
 */
LED_ErrorStatus_t LED_Init (void)
{
	GPIO_Pin_t LedPinCfg;
	GPIO_ErrorStatus_t GPIO_ErrorStatus=GPIO_Ok;
	LED_ErrorStatus_t RET_ErrorStatus= LED_Ok;
	for(int i=0;i<_Led_Num;i++)
	{
		LedPinCfg.Port=Leds[i].Port;
		LedPinCfg.Pin=Leds[i].Pin;
		LedPinCfg.Mode=MODE_OUTPUT_PP;
		LedPinCfg.Speed=SPEED_HIGH;
		LedPinCfg.AF_Choice=AF_DEACTIVATED;

		GPIO_ErrorStatus=GPIO_InitPin(&LedPinCfg);

		if(GPIO_ErrorStatus!=GPIO_Ok)
		{
			RET_ErrorStatus=LED_Nok;
		}
		else
		{
			u32 GPIO_State;
			if(((Leds[i].Connection)^(Leds[i].InitialState))==0)
			{
				GPIO_State=GPIO_RESET_PIN;
			}
			else
			{
				GPIO_State=GPIO_SET_PIN;
			}
			GPIO_ErrorStatus=GPIO_SetPinValue(Leds[i].Port,Leds[i].Pin,GPIO_State);
			if(GPIO_ErrorStatus!=GPIO_Ok)
			{
				RET_ErrorStatus=LED_Nok;

			}
			else
			{
				//Empty
			}
		}

	}
	return RET_ErrorStatus;
}

/**
 * @brief	Sets a LED State to either HIGH or LOW
 *
 * @param	- Led	(Takes the LED name written in the Leds_t enum type in LED_cfg.h)
 * 			- State (LED_ON/ LED_OFF)
 *
 * @error	Error Status (LED_Ok / LED_InvalidParameter)
 */
LED_ErrorStatus_t LED_SetStatus(u32 Led, u8 State)
{
	LED_ErrorStatus_t RET_ErrorStatus= LED_Ok;
	GPIO_ErrorStatus_t GPIO_ErrorStatus=GPIO_Ok;

	if(Led>=_Led_Num)
	{
		RET_ErrorStatus=LED_InvalidParameter;
	}
	else if(State>LED_ON)
	{
		RET_ErrorStatus=LED_InvalidParameter;
	}
	else
	{
		u32 GPIO_State;
		if(Leds[Led].Connection^Leds[Led].InitialState==0)
		{
			GPIO_State=GPIO_RESET_PIN;
		}
		else
		{
			GPIO_State=GPIO_SET_PIN;
		}
		GPIO_ErrorStatus=GPIO_SetPinValue(Leds[Led].Port,Leds[Led].Pin,GPIO_State);
		if(GPIO_ErrorStatus!=GPIO_Ok)
		{
			RET_ErrorStatus=LED_Nok;
		}
	}
	return RET_ErrorStatus;
}
