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
#define MASK_SET_PLL_PLLSRC				0X00400000

#define SHIFT_PLL_M           		   	(0U)
#define SHIFT_PLL_N           		  	(6U)
#define SHIFT_PLL_P            		  	(16U)
#define SHIFT_PLL_Q             		(24U)

#define MASK_SET_SYSCLK					0x00000003
#define MASK_GET_SYSCLK					0x0000000C

#define PLL_SELECTED_AS_SYSCLK			0x00000008
#define HSE_SELECTED_AS_SYSCLK			0x00000004
#define HSI_SELECTED_AS_SYSCLK			0x00000000

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
volatile RCC_Peri_t *RCC=(volatile RCC_Peri_t*)RCC_BA;

/**
*@brief : Function to Control HSI,HSE,PLL -> On/Off
*
*@param : # Clock Status(CLOCK_STATUS_ON / CLOCK_STATUS_OFF)
*		  # Clock(CLOCK_HSI, CLOCK_HSE,CLOCK_PLL)
*
*@return: Error Status
*
*       --Note--
*       # If Input Parameters are out of range -> ***Input Parameter Error***
*       # If clock fails to be ready after a predefined amount of time -> ***Timeout Error***
*/
RCC_ErrorStatus_t RCC_ControlClock (u8 ClockStatus, u32 Clock)
{
	RCC_ErrorStatus_t RET_ErrorStatus=RCC_Ok;
	u16 Timeout=600;

	if(!(Clock==CLOCK_HSI||Clock==CLOCK_HSE||Clock==CLOCK_PLL))
	{
		RET_ErrorStatus=RCC_InvalidParameter;
	}
	else if(!(ClockStatus==CLOCK_STATUS_OFF||ClockStatus==CLOCK_STATUS_ON))
	{
		RET_ErrorStatus=RCC_InvalidParameter;
	}
	else
	{
		RET_ErrorStatus=RCC_Ok;
		switch(ClockStatus)
		{
			case CLOCK_STATUS_ON:
			{
				u32 Loc_Mask_Ready=(Clock<<1);

				(RCC->CR)|=Clock;
				while(!(RCC->CR&Loc_Mask_Ready)&&(Timeout))
				{
					Timeout--;
				}
				if(!(RCC->CR&Loc_Mask_Ready))
				{
					RET_ErrorStatus=RCC_TimeoutError;
				}
			}
			break;

			case CLOCK_STATUS_OFF:
			{
					switch(Clock)
					{
						case CLOCK_HSI:
						{
							if((RCC->CFGR&MASK_GET_SYSCLK)==HSI_SELECTED_AS_SYSCLK)
							{
								RET_ErrorStatus=RCC_InvalidParameter;
							}

							else
							{
								RCC->CR&=~Clock;

							}
						}
						break;

						case CLOCK_HSE:
						{
							if((RCC->CFGR&MASK_GET_SYSCLK)==HSE_SELECTED_AS_SYSCLK)
							{
								RET_ErrorStatus=RCC_InvalidParameter;
							}
							else
							{
								RCC->CR&=~Clock;

							}
						}
						break;

						case CLOCK_PLL:
						{
							if((RCC->CFGR&MASK_GET_SYSCLK)==PLL_SELECTED_AS_SYSCLK)
							{
								RET_ErrorStatus=RCC_InvalidParameter;
							}

							else
							{
								RCC->CR&=~Clock;

							}
						}
						break;

					}
				}
			break;
			}
	}
	return RET_ErrorStatus;
}

/**
*@brief : Function to Select a System Clock
*
*@param : # Sysclk (SYSCLK_HSI, SYSCLK_HSE, SYSCLK_PLL)
*
*@return: Error Status
*
*       --Note--
*       # If Input Parameters are out of range -> ***Input Parameter Error***
*       # If Clock isn't On/Ready -> ***Input Parameter Error***
*       # If clock fails to be ready after a predefined amount of time -> ***Timeout Error***
*
*       --Constraint--
*       # Make sure Clock is On&Ready before selecting it as system clock!!
*/
RCC_ErrorStatus_t RCC_SelectSystemClock(u32 Sysclk)
{
	RCC_ErrorStatus_t RET_ErrorStatus=RCC_Ok;
	u8 SelectSysClkFlag=0;
	u16 Timeout=600;
	switch(Sysclk)
	{
		case SYSCLK_HSI:
		{
			if(!((RCC->CR&MASK_HSION) && (RCC->CR&MASK_HSIRDY)))
			{
				RET_ErrorStatus=RCC_InvalidParameter;
			}
			else
			{
				SelectSysClkFlag=1;
			}
		}
		break;

		case SYSCLK_HSE:
		{
			if(!((RCC->CR&MASK_HSEON) && (RCC->CR&MASK_HSERDY)))
			{
				RET_ErrorStatus=RCC_InvalidParameter;
			}
			else
			{
				SelectSysClkFlag=1;
			}
		}
		break;

		case SYSCLK_PLL:
		{
			if(!((RCC->CR&MASK_PLLON) && (RCC->CR&MASK_PLLRDY)))
			{
				RET_ErrorStatus=RCC_InvalidParameter;
			}
			else
			{
				SelectSysClkFlag=1;
			}
		}
		break;
		default:
		{
				RET_ErrorStatus=RCC_InvalidParameter;
		}
		break;
	}

	if(SelectSysClkFlag==1)
	{
		u8 Temp_CFGR= RCC->CFGR;

		/*Create a SWS Mask Corresponding to your current Clock*/
		u8 MASK_SWS=(Sysclk<<2);

		Temp_CFGR&=~(MASK_SET_SYSCLK);
		Temp_CFGR|=Sysclk;
		RCC->CFGR=Temp_CFGR;

		/*Decrease Timeout if System Clock is not Selected*/
		while(((RCC->CFGR&MASK_GET_SYSCLK) != MASK_SWS )&& Timeout)
		{
			Timeout--;
		}

		/*Return Error if System Clock is not Selected*/
		if((RCC->CFGR&MASK_GET_SYSCLK)!= MASK_SWS)
		{
			RET_ErrorStatus=RCC_TimeoutError;
		}
	}

	return RET_ErrorStatus;
}

/**
*@brief : Function to Enable a Peripheral
*
*@param : # Peripheral Bus (AHB1, AHB2, APB1, APB2)
*		  # Peripheral
*
*@return: Error Status
*
*       --Note--
*       # If Input Parameters are out of range -> ***Input Parameter Error***
*/
RCC_ErrorStatus_t RCC_EnablePeriphral(PeripheralBuses_t PeriphralBus, u32 Periphral)
{
	RCC_ErrorStatus_t RET_ErrorStatus= RCC_Ok;
	switch(PeriphralBus)
	{
		case APB1:
		{
			RCC->APB1ENR|=Periphral;
		}
		break;
		case APB2:
		{
			RCC->APB2ENR|=Periphral;
		}
		break;
		case AHB1:
		{
			RCC->AHB1ENR|=Periphral;
		}
		break;
		case AHB2:
		{
			RCC->AHB2ENR|=Periphral;
		}
		break;
		default:
		{
			RET_ErrorStatus=RCC_InvalidParameter;
		}
	}

	return RET_ErrorStatus;
}

/**
*@brief : Function to Disable a Peripheral
*@param : # Peripheral Bus (AHB1, AHB2, APB1, APB2)
*		  # Peripheral
*
*@return: Error Status
*
*       --Note--
*       # If Input Parameters are out of range -> ***Input Parameter Error***
*/
RCC_ErrorStatus_t RCC_DisablePeriphral(PeripheralBuses_t PeriphralBus,u32 Periphral)
{
	RCC_ErrorStatus_t RET_ErrorStatus= RCC_Ok;
	switch(PeriphralBus)
	{
		case APB1:
		{
			RCC->APB1ENR&=~Periphral;
		}
		break;
		case APB2:
		{
			RCC->APB2ENR&=~Periphral;
		}
		break;
		case AHB1:
		{
			RCC->AHB1ENR&=~Periphral;
		}
		break;
		case AHB2:
		{
			RCC->AHB2ENR&=~Periphral;
		}
		break;
		default:
		{
			RET_ErrorStatus=RCC_InvalidParameter;
		}
	}
	return RET_ErrorStatus;
}

/**
*@brief : Function to Set AHB Prescaler
*
*@param : # AHB Prescaler (Macro starts with AHB_CLOCK_)
*
*@return: Error Status
*
*       --Note--
*       # If Input Parameters are out of range -> ***Input Parameter Error***
*/
RCC_ErrorStatus_t RCC_SelectAHBPerscaler(u32 AHBPrescaler)
{
	RCC_ErrorStatus_t RET_ErrorStatus=RCC_Ok;

	/*Get AHB Bits in CFGR Register & Check on its Range*/
	u8 AHB_Bits=RCC_get_AHB_Bits(AHBPrescaler);

	if (!(AHB_Bits>= 0x08 && AHB_Bits <=0x0F))
	{
		RET_ErrorStatus=RCC_InvalidParameter;
	}
	else
	{
		u8 Temp_CFGR=RCC->CFGR;
		Temp_CFGR&=~MASK_AHB_PRESCALER;
		Temp_CFGR|=AHBPrescaler;
		RCC->CFGR=Temp_CFGR;
	}
	return RET_ErrorStatus;
}

/**
*@brief : Function to Set APB1 Prescaler
*
*@param : # APB1 Prescaler (Macro starts with APB1_CLOCK_)
*
*@return: Error Status
*
*       --Note--
*       # If Input Parameters are out of range -> ***Input Parameter Error***
*/
RCC_ErrorStatus_t RCC_SelectAPB1Perscaler(u32 APB1Prescaler)
{
	RCC_ErrorStatus_t RET_ErrorStatus=RCC_Ok;
	if(!(APB1Prescaler==APB1_CLOCK_DIVIDED_BY_2||APB1Prescaler==APB1_CLOCK_DIVIDED_BY_4||APB1Prescaler==APB1_CLOCK_DIVIDED_BY_8||APB1Prescaler==APB1_CLOCK_DIVIDED_BY_16))
	{
		RET_ErrorStatus=RCC_InvalidParameter;
	}
	else
	{
		u8 Temp_CFGR=RCC->CFGR;
		Temp_CFGR&=~MASK_APB1_PRESCALER;
		Temp_CFGR|=APB1Prescaler;
		RCC->CFGR=Temp_CFGR;
	}
	return RET_ErrorStatus;
}

/**
*@brief : Function to Set APB2 Prescaler
*
*@param : # APB2 Prescaler (Macro starts with APB2_CLOCK_)
*
*@return: Error Status
*
*       --Note--
*       # If Input Parameters are out of range -> ***Input Parameter Error***
*/
RCC_ErrorStatus_t RCC_SelectAPB2Perscaler(u32 APB2Prescaler)
{
	RCC_ErrorStatus_t RET_ErrorStatus=RCC_Ok;
	if(!(APB2Prescaler==APB2_CLOCK_DIVIDED_BY_2||APB2Prescaler==APB2_CLOCK_DIVIDED_BY_4||APB2Prescaler==APB2_CLOCK_DIVIDED_BY_8||APB2Prescaler==APB2_CLOCK_DIVIDED_BY_16))
	{
		RET_ErrorStatus=RCC_InvalidParameter;
	}
	else
	{
		u8 Temp_CFGR=RCC->CFGR;
		Temp_CFGR&=~MASK_APB1_PRESCALER;
		Temp_CFGR|=APB2Prescaler;
		RCC->CFGR=Temp_CFGR;
	}
	return RET_ErrorStatus;
}

/**
*@brief : Function to Configure PLL
*
*@param : Struct of type "PLLCfgOptions_t", Takes:
*		 	# M:  		2:63
*		 	# N:  		2:511
*		 	# P:		2,4,6,8
*		 	# Q: 	 	2:15
*		 	# PLLSRC:  (PLL_CLK_HSI, PLL_CLK_HSE)
*
*@return: Error Status
*
*       --Constraints--
*       1) PLL must be OFF before configuring!
*       2) PLL must not be selected as system clock before configuring!
*       3) M,N,P,Q,PLLSRC values must be selected from the range above!
*       --> Failing to do so will result in an ***Invalid Parameter Error***
*
*/
RCC_ErrorStatus_t RCC_ConfigurePLL(PLLCfgOptions_t*PLLCfg)
{
	RCC_ErrorStatus_t RET_ErrorStatus=RCC_Ok;

	u32 M=PLLCfg->M;
	u32 N=PLLCfg->N;
	u32 P=PLLCfg->P;
	u32 Q=PLLCfg->Q;
	u32 PLLSRC=PLLCfg->PLLSRC;

	if((RCC->CR&MASK_PLLON))
	{
		RET_ErrorStatus=RCC_InvalidParameter;
	}
	else if((RCC->CFGR&MASK_GET_SYSCLK)==PLL_SELECTED_AS_SYSCLK)
	{
		RET_ErrorStatus=RCC_InvalidParameter;
	}
	else if((M==0 || M==1 || M>63))
	{
		RET_ErrorStatus=RCC_InvalidParameter;
	}
	else if((N==0||N==1||N==433||N==511||N>511))
	{
		RET_ErrorStatus=RCC_InvalidParameter;
	}
	else if((P==2||P==4||P==6||P==8))
	{
		RET_ErrorStatus=RCC_InvalidParameter;
	}
	else if((Q==0||Q==1||Q>15))
	{
		RET_ErrorStatus=RCC_InvalidParameter;
	}
	else if(!(PLLSRC==PLL_CLK_HSI || PLLSRC==PLL_CLK_HSE))
	{
		RET_ErrorStatus=RCC_InvalidParameter;
	}
	else
	{
		u32 Local_CFGR=RCC->PLLCFGR;

		Local_CFGR&=~MASK_SET_PLL_M;
		Local_CFGR|=(M<<SHIFT_PLL_M);

		Local_CFGR&=~MASK_SET_PLL_N;
		Local_CFGR|=(N<<SHIFT_PLL_N);

		Local_CFGR&=~MASK_SET_PLL_P;
		Local_CFGR|=(P<<SHIFT_PLL_P);

		Local_CFGR&=~MASK_SET_PLL_Q;
		Local_CFGR|=(Q<<SHIFT_PLL_Q);

		Local_CFGR&=~MASK_SET_PLL_PLLSRC;
		Local_CFGR|=(PLLSRC);

		RCC->PLLCFGR=Local_CFGR;
	}
	return RET_ErrorStatus;
}
