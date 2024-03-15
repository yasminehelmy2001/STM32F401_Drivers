/*
* File:    SWITCH.c
* Author:  Yasmin Amr
* Created: 19/2/2024
* Brief:   SWITCH Driver
* Target:  STM32F401cc
*/

#include "GPIO.h"
#include "SWITCH.h"

extern const SwitchCfg_t Switches[_Switch_Num];

static u8 Switch_State[_Switch_Num];

/**
 * @brief	Initializes all Switches Pre-configured in SWITCH_cfg.c
 * @param	None
 * @error	Error Status(SWITCH_Ok/SWITCH/Nok)
 */
SWITCH_ErrorStatus_t SWITCH_Init (void)
{
	GPIO_Pin_t SwitchPinCfg;
	SWITCH_ErrorStatus_t RET_ErrorStatus=SWITCH_Ok;
	for(int i=0;i<_Switch_Num;i++)
	{
		SwitchPinCfg.Port=Switches[i].Port;
		SwitchPinCfg.Pin=Switches[i].Pin;
		SwitchPinCfg.Speed=SPEED_HIGH;
		SwitchPinCfg.AF_Choice=AF_DEACTIVATED;
		if(Switches[i].Connection==SWITCH_PULLUP)
		{
			SwitchPinCfg.Mode=MODE_INPUT_PU;
		}
		else
		{
			SwitchPinCfg.Mode=MODE_INPUT_PD;
		}
		GPIO_ErrorStatus_t GPIO_ErrorStatus= GPIO_InitPin(&SwitchPinCfg);
		if (GPIO_ErrorStatus!=GPIO_Ok)
		{
			RET_ErrorStatus=SWITCH_Nok;
		}
	}
	return RET_ErrorStatus;
}

// /**
//  * @brief	Reads a Switch State (HIGH/LOW)
//  *
//  * @param	- Switch (Takes the SWITCH name written in the Switches_t enum type in SWITCH_cfg.h)
//  * 			- Pointer to State (SWITCH_PRESSED/ SWITCH_NOTPRESSED)
//  *
//  * @error	Error Status (SWITCH_Ok / SWITCH_InvalidParameter)
//  */
// SWITCH_ErrorStatus_t SWITCH_ReadStatus(u32 Switch, u8*State)
// {
// 	u8 SwitchState;

// 	SWITCH_ErrorStatus_t RET_ErrorStatus=SWITCH_Ok;
// 	GPIO_ErrorStatus_t GPIO_ErrorStatus=GPIO_Ok;

// 	if(State==NULL)
// 	{
// 		RET_ErrorStatus=SWITCH_NullPointer;
// 	}
// 	else if(Switch>=_Switch_Num)
// 	{
// 		RET_ErrorStatus=SWITCH_InvalidParameter;
// 	}
// 	else
// 	{
// 		GPIO_ErrorStatus=GPIO_GetPinValue(Switches[Switch].Port,Switches[Switch].Pin,&SwitchState);
// 		if(GPIO_ErrorStatus!=GPIO_Ok)
// 		{
// 			RET_ErrorStatus=SWITCH_Nok;
// 		}
// 		else if(((SwitchState==GPIO_HIGH)&&(Switches[Switch].Connection==SWITCH_PULLUP)) ||
// 			((SwitchState==GPIO_LOW)&&(Switches[Switch].Connection==SWITCH_PULLDOWN)))
// 		{
// 			*State=SWITCH_NOTPRESSED;
// 		}
// 		else
// 		{
// 			*State=SWITCH_PRESSED;
// 		}
// 	}
// 	return RET_ErrorStatus;
// }

SWITCH_ErrorStatus_t SW_GetState(u32 Switch, u8*State)
{
	SWITCH_ErrorStatus_t RET_ErrorStatus=SWITCH_Ok;
	if(State==NULL)
	{
		RET_ErrorStatus=SWITCH_NullPointer;
	}
	else if(Switch>=_Switch_Num)
	{
		RET_ErrorStatus=SWITCH_InvalidParameter;
	}
	else
	{
		*State=Switch_State[Switch];
	}
	return RET_ErrorStatus;
}

void SW_Runnable(void)
{
	static u8 prev[_Switch_Num];
	static u8 curr;
	static u8 counts[_Switch_Num];
	for(int i=0;i<_Switch_Num;i++)
	{
		GPIO_GetPinValue(Switches[i].Port,Switches[i].Pin,&curr);
		if(curr==prev[i])
		{
			counts[i]++;
		}
		else
		{
			counts[i]=0;
		}
		if(counts[i]==5)
		{
			Switch_State[i]=curr;
			counts[i]=0;
		}
		prev[i]=curr;
	}

}
