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
 */
void LED_Init (void)
{
	GPIO_Pin_t LedPinCfg;
	for(int i=0;i<_Led_Num;i++)
	{
		LedPinCfg.Port=Leds[i].Port;
		LedPinCfg.Pin=Leds[i].Pin;
		LedPinCfg.Mode=MODE_OUTPUT_PP;
		LedPinCfg.Speed=SPEED_HIGH;
		LedPinCfg.AF_Choice=AF_DEACTIVATED;
		GPIO_InitPin(&LedPinCfg);

		if(Leds[i].InitialState==LED_ON)
		{
			GPIO_SetPinValue(Leds[i].Port,Leds[i].Pin,Leds[i].Connection^Leds[i].InitialState);
		}
		else
		{
			GPIO_SetPinValue(Leds[i].Port,Leds[i].Pin,Leds[i].Connection^Leds[i].InitialState);
		}

	}
}

/**
 * @brief	Sets a LED State to either HIGH or LOW
 *
 * @param	- Led	(Takes the LED name written in the Leds_t enum type in LED_cfg.h)
 * 			- State (LED_ON/ LED_OFF)
 *
 * @error	Error Status (LED_Ok / LED_InvalidParameter)
 */
void LED_SetStatus(u32 Led, u8 State)
{
	GPIO_SetPinValue(Leds[Led].Port, Leds[Led].Pin, Leds[Led].Connection^State);
}
