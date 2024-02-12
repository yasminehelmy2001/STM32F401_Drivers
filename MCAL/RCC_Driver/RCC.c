#include "RCC.h"

/**************************************************************************/
/*						Masks & Shifts					 				  */
/**************************************************************************/
#define MASK_HSION						0x00000001
#define MASK_HSEON						0x00010000
#define MASK_PLLON						0x01000000

#define MASK_HSIRDY						0x00000002
#define MASK_HSERDY						0x00020000
#define MASK_PLLRDY						0x02000000

#define MASK_SET_PLL_M					0x0000003F
#define MASK_SET_PLL_N					0x00007FC0
#define MASK_SET_PLL_P					0x00030000
#define MASK_SET_PLL_Q					0x0F000000
#define MASK_SET_PLL_PLLSRC				0X00200000

#define SHIFT_PLL_M           		   	(0U)
#define SHIFT_PLL_N           		  	(6U)
#define SHIFT_PLL_P            		  	(16U)
#define SHIFT_PLL_Q             		(24U)
#define SHIFT_PLL_SRC           		(22U)

#define MASK_SET_SYSCLK					0x00000003
#define MASK_GET_SYSCLK					0x0000000C
#define PLL_SELECTED_AS_SYSCLK			0x00000008

#define MASK_AHB_PRESCALER				0x000000F0
#define MASK_APB1_PRESCALER				0x00001C00
#define MASK_APB2_PRESCALER				0x0000E000


/**************************************************************************/
/*						Static Functions		 					 	  */
/**************************************************************************/
static u8 RCC_get_AHB_Bits(u32 Copy_CFGR)
{
	return ((Copy_CFGR >> 4) & 0x0F);
}

/**************************************************************************/
/*						Function Implementations 					 	  */
/**************************************************************************/

RCC_ErrorStatus_t RCC_ControlClock (u8 ClockStatus, u32 Clock)
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

RCC_ErrorStatus_t RCC_SelectSystemClock(u32 Sysclk)
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

RCC_ErrorStatus_t RCC_EnablePeriphral(PeripheralBuses_t PeriphralBus, u32 Periphral)
{
	RCC_ErrorStatus_t RET_ErrorStatus= RCC_Error_Ok;
	switch(PeriphralBus)
	{
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
		default:
		{
			RET_ErrorStatus=RCC_Error_InvalidPeriphralBus;
		}
	}

	return RET_ErrorStatus;
}

RCC_ErrorStatus_t RCC_DisablePeriphral(PeripheralBuses_t PeriphralBus,u32 Periphral)
{
	RCC_ErrorStatus_t RET_ErrorStatus= RCC_Error_Ok;
	switch(PeriphralBus)
	{
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
		default:
		{
			RET_ErrorStatus=RCC_Error_InvalidPeriphralBus;
		}
	}
	return RET_ErrorStatus;
}

RCC_ErrorStatus_t RCC_SelectAHBPerscaler(u32 AHBPrescaler)
{
	RCC_ErrorStatus_t RET_ErrorStatus=RCC_Error_Ok;

	u8 AHB_Bits=RCC_get_AHB_Bits(AHBPrescaler);

	if (!(AHB_Bits>= 0x08 && AHB_Bits <=0x0F))
	{
		RET_ErrorStatus=RCC_Error_InvalidAHBClock;
	}
	else
	{
		u8 Temp_CFGR=RCC_CFGR;
		Temp_CFGR&=~MASK_AHB_PRESCALER;
		Temp_CFGR|=AHBPrescaler;
		RCC_CFGR=Temp_CFGR;
	}
	return RET_ErrorStatus;
}

RCC_ErrorStatus_t RCC_SelectAPB1Perscaler(u32 APB1Prescaler)
{
	RCC_ErrorStatus_t RET_ErrorStatus=RCC_Error_Ok;
	if(!(APB1Prescaler==APB1_CLOCK_DIVIDED_BY_2||APB1Prescaler==APB1_CLOCK_DIVIDED_BY_4||APB1Prescaler==APB1_CLOCK_DIVIDED_BY_8||APB1Prescaler==APB1_CLOCK_DIVIDED_BY_16))
	{
		RET_ErrorStatus=RCC_Error_InvalidAPB2Clock;
	}
	else
	{
		u8 Temp_CFGR=RCC_CFGR;
		Temp_CFGR&=~MASK_APB1_PRESCALER;
		Temp_CFGR|=APB1Prescaler;
		RCC_CFGR=Temp_CFGR;
	}
	return RET_ErrorStatus;
}

RCC_ErrorStatus_t RCC_SelectAPB2Perscaler(u32 APB2Prescaler)
{
	RCC_ErrorStatus_t RET_ErrorStatus=RCC_Error_Ok;
	if(!(APB2Prescaler==APB2_CLOCK_DIVIDED_BY_2||APB2Prescaler==APB2_CLOCK_DIVIDED_BY_4||APB2Prescaler==APB2_CLOCK_DIVIDED_BY_8||APB2Prescaler==APB2_CLOCK_DIVIDED_BY_16))
	{
		RET_ErrorStatus=RCC_Error_InvalidAPB2Clock;
	}
	else
	{
		u8 Temp_CFGR=RCC_CFGR;
		Temp_CFGR&=~MASK_APB1_PRESCALER;
		Temp_CFGR|=APB2Prescaler;
		RCC_CFGR=Temp_CFGR;
	}
	return RET_ErrorStatus;
}

RCC_ErrorStatus_t RCC_ConfigurePLL(PLLCfgOptions_t*PLLCfg)
{
	RCC_ErrorStatus_t RET_ErrorStatus=RCC_Error_Ok;

	u8 M=PLLCfg->M;
	u16 N=PLLCfg->N;
	u8 P=PLLCfg->P;
	u8 Q=PLLCfg->Q;
	u32 PLLSRC=PLLCfg->PLLSRC;

	if(!((RCC_CR&MASK_PLLON) && (RCC_CR&MASK_PLLRDY)))
	{
		RET_ErrorStatus=RCC_Error_ClockNotOnOrReady;
	}
	else if((RCC_CFGR&MASK_GET_SYSCLK)==PLL_SELECTED_AS_SYSCLK)
	{
		RET_ErrorStatus=RCC_Error_PLLSelectedAsSysClk;
	}
	else if(!(M==0 || M==1 || M>63))
	{
		RET_ErrorStatus=RCC_Error_Invalid_M_Configuration;
	}
	else if(!(N==0||N==1||N==433||N==511||N>511))
	{
		RET_ErrorStatus=RCC_Error_Invalid_N_Configuration;
	}
	else if(!(P==2||P==4||P==6||P==8))
	{
		RET_ErrorStatus=RCC_Error_Invalid_P_Configuration;
	}
	else if(!(Q==0||Q==1||Q>15))
	{
		RET_ErrorStatus=RCC_Error_Invalid_Q_Configuration;
	}
	else if(!(PLLSRC==PLL_CLK_HSI || PLLSRC==PLL_CLK_HSE))
	{
		RET_ErrorStatus=RCC_Error_Invalid_PLL_Clock_Source;
	}
	else
	{
		u8 Local_CFGR=RCC_PLLCFGR;

		Local_CFGR&=~MASK_SET_PLL_M;
		Local_CFGR|=(M<<SHIFT_PLL_M);

		Local_CFGR&=~MASK_SET_PLL_N;
		Local_CFGR|=(N<<SHIFT_PLL_N);

		Local_CFGR&=~MASK_SET_PLL_P;
		Local_CFGR|=(P<<SHIFT_PLL_P);

		Local_CFGR&=~MASK_SET_PLL_Q;
		Local_CFGR|=(Q<<SHIFT_PLL_Q);

		Local_CFGR&=~MASK_SET_PLL_PLLSRC;
		Local_CFGR|=(PLLSRC<<SHIFT_PLL_SRC);

		RCC_PLLCFGR=Local_CFGR;
	}
	return RET_ErrorStatus;
}
