#include "RCC.h"

/********************************************/
/*			Masks				  	   		*/
/********************************************/
#define MASK_HSION					0x00000001
#define MASK_HSEON					0x00010000
#define MASK_PLLON					0x01000000

#define MASK_HSIRDY					0x00000002
#define MASK_HSERDY					0x00020000
#define MASK_PLLRDY					0x02000000

#define MASK_SET_PLL_M				0x0000003F
#define MASK_SET_PLL_N				0x00007FC0
#define MASK_SET_PLL_P				0x00030000
#define MASK_SET_PLL_Q				0x0F000000

#define SHIFT_PLL_M					0
#define SHIFT_PLL_N					6
#define SHIFT_PLL_P					16
#define SHIFT_PLL_Q					22

#define MASK_GET_SYSCLK				0x0000000C
#define MASK_SET_SYSCLK				0x00000003

/********************************************/
/*			Function Implementations 		*/
/********************************************/
RCC_ErrorStatus_t RCC_ControlClock (u8 ClockStatus, u8 Clock)
{
	RCC_ErrorStatus_t RET_ErrorStatus=RCC_Error_Ok;

	if(!(Clock==CLOCK_HSI||Clock==CLOCK_HSE||Clock==CLOCK_PLL))
	{
		RET_ErrorStatus=RCC_Error_InvalidClock;
	}
	else if(!(ClockStatus==CLOCK_STATUS_OFF||ClockStatus==CLOCK_STATUS_ON))
	{
		RET_ErrorStatus=RCC_Error_InvalidClockStatus;
	}
	else
	{
		RET_ErrorStatus=RCC_Error_Ok;
		switch(ClockStatus)
		{
		case CLOCK_STATUS_ON:
			RCC_CR|=Clock;
		break;
		case CLOCK_STATUS_OFF:
			RCC_CR&=~Clock;
		break;
		}
	}
	return RET_ErrorStatus;
}

RCC_ErrorStatus_t RCC_SelectSystemClock(u8 Sysclk)
{
	RCC_ErrorStatus_t RET_ErrorStatus=RCC_Error_Ok;
	u8 Temp_CFGR;
	switch(Sysclk)
	{
		case SYSCLK_HSI:
		{
			if((RCC_CR&MASK_HSION) && (RCC_CR&MASK_HSIRDY))
			{
				Temp_CFGR= RCC_CFGR;
				Temp_CFGR&=~(MASK_SET_SYSCLK);
				Temp_CFGR|=SYSCLK_HSI;
				RCC_CFGR=Temp_CFGR;
			}
			else
			{
				RET_ErrorStatus=RCC_Error_ClockNotOnOrReady;
			}
		}
		break;
		case SYSCLK_HSE:
		{
			if((RCC_CR&MASK_HSEON) && (RCC_CR&MASK_HSERDY))
			{
				Temp_CFGR= RCC_CFGR;
				Temp_CFGR&=~(MASK_SET_SYSCLK);
				Temp_CFGR|=SYSCLK_HSE;
				RCC_CFGR=Temp_CFGR;
			}
			else
			{
				RET_ErrorStatus=RCC_Error_ClockNotOnOrReady;
			}
		}
		break;
		case SYSCLK_PLL:
		{
			if((RCC_CR&MASK_PLLON) && (RCC_CR&MASK_PLLRDY))
			{
				Temp_CFGR= RCC_CFGR;
				Temp_CFGR&=~(MASK_SET_SYSCLK);
				Temp_CFGR|=SYSCLK_PLL;
				RCC_CFGR=Temp_CFGR;
			}
			else
			{
				RET_ErrorStatus=RCC_Error_ClockNotOnOrReady;
			}
		}
		break;
		default:
		{
				RET_ErrorStatus=RCC_Error_InvalidSysClk;
		}
		break;
	}
	return RET_ErrorStatus;
}

RCC_ErrorStatus_t RCC_EnablePeriphral(PeripheralBuses_t PeriphralBus, u8 Periphral)
{
	RCC_ErrorStatus_t RET_ErrorStatus= RCC_Error_Ok;

	switch (PeriphralBus)
	{
		case AHB1:
		{
			RCC_AHB1ENR|=Periphral;
		}
		break;
		case AHB2:
		{
			RCC_AHB2ENR|=Periphral;
		}
		break;
		case APB1:
		{
			RCC_APB1ENR|=Periphral;
		}
		break;
		case APB2:
		{
			RCC_APB2ENR|=Periphral;

		}
		break;
		default:
		{
			RET_ErrorStatus=RCC_Error_InvalidPeriphralBus;
		}
		break;
	}
}

RCC_ErrorStatus_t RCC_DisablePeriphral(PeripheralBuses_t PeriphralBus,u8 Periphral)
{
	RCC_ErrorStatus_t RET_ErrorStatus= RCC_Error_Ok;

	switch (PeriphralBus)
	{
		case AHB1:
		{
			RCC_AHB1ENR&=~Periphral;
		}
		break;
		case AHB2:
		{
			RCC_AHB2ENR&=~Periphral;
		}
		break;
		case APB1:
		{
			RCC_APB1ENR&=~Periphral;
		}
		break;
		case APB2:
		{
			RCC_APB2ENR&=~Periphral;

		}
		break;
		default:
		{
			RET_ErrorStatus=RCC_Error_InvalidPeriphralBus;
		}
		break;
	}
}

RCC_ErrorStatus_t RCC_SelectAHBPerscaler(u8 AHBPrescaler)
{

}

RCC_ErrorStatus_t RCC_SelectAPB1Perscaler(u8 APB1Prescaler)
{

}

RCC_ErrorStatus_t RCC_SelectAPB2Perscaler(u8 APB2Prescaler)
{

}

RCC_ErrorStatus_t RCC_ConfigurePLL(PLLCfgOptions_t*PLLCfg)
{

}
