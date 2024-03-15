/*
* File:    RCC.c
* Author:  Yasmin Amr
* Created: 10/2/2024
* Brief:   RCC Driver
* Target:  STM32F401cc
*/

#include "RCC.h"

/**************************************************************************/
/*						Masks & Shifts					 				  */
/**************************************************************************/
#define MASK_HSION						0x00000001
#define MASK_HSEON						0x00010000
#define MASK_PLLON						0x01000000

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
/*						RCC Registers Struct			 			 	  */
/**************************************************************************/
typedef struct
{
	volatile u32 CR;
	volatile u32 PLLCFGR;
	volatile u32 CFGR;
	volatile u32 CIR;
	volatile u32 AHB1RSTR;
	volatile u32 AHB2RSTR;
	volatile u32 Reserved[2];
	volatile u32 APB1RSTR;
	volatile u32 APB2RSTR;
	volatile u32 Reserved2[2];
	volatile u32 AHB1ENR;
	volatile u32 AHB2ENR;
	volatile u32 Reserved3[2];
	volatile u32 APB1ENR;
	volatile u32 APB2ENR;
	volatile u32 Reserved4[2];
	volatile u32 AHB1LPENR;
	volatile u32 AHB2LPENR;
	volatile u32 Reserved5[2];
	volatile u32 APB1LPENR;
	volatile u32 APB2LPENR;
	volatile u32 Reserved6[2];
	volatile u32 BDCR;
	volatile u32 CSR;
	volatile u32 Reserved7[2];
	volatile u32 SSCGR;
	volatile u32 PLLI2SCFGR;
	volatile u32 DCKCFGR;
}RCC_Peri_t;

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
volatile RCC_Peri_t *RCC=(volatile RCC_Peri_t *)RCC_BA;

/**
 * @brief  		 Function to Enable HSI, HSE, PLL -> On/Off
 *
 * @param   	 - ClockRegisterAddress (RCC_HSI_HSE_PLL_PLLI2S_REG,RCC_LSE_REG,RCC_LSI_REG)
 * 				 - Clock (CLOCK_HSI, CLOCK_HSE, CLOCK_PLL, CLOCK_PLLI2S, CLOCK_LSI, CLOCK_LSE)
 *
 * @return		  Error Status
 *         		 - If Input Parameters are out of range -> ***Input Parameter Error***
 *
 * @constraint	 - Make sure that clock is ready after enabling it using the
 * 				   "RCC_CheckReadyClk()" Function
 *
 */
RCC_ErrorStatus_t RCC_EnableClock  (volatile u32*ClockRegisterAddress,u32 Clock)
{
	RCC_ErrorStatus_t RET_ErrorStatus=RCC_Ok;
	if(!(Clock==CLOCK_HSI||Clock==CLOCK_HSE||Clock==CLOCK_PLL||Clock==CLOCK_LSI
	  || Clock==CLOCK_LSE||Clock==CLOCK_PLLI2S))
	{
		RET_ErrorStatus=RCC_InvalidParameter;
	}
	else
	{
		RET_ErrorStatus=RCC_Ok;
		*(ClockRegisterAddress)|=Clock;
	}
	return RET_ErrorStatus;
}

/**
 * @brief   	 Function to Disable HSI, HSE, PLL -> On/Off
 *
 * @param   	 - ClockRegisterAddress (RCC_HSI_HSE_PLL_PLLI2S_REG,RCC_LSE_REG,RCC_LSI_REG)
 * 				 - Clock (CLOCK_HSI, CLOCK_HSE, CLOCK_PLL, CLOCK_PLLI2S, CLOCK_LSI, CLOCK_LSE)
 *
 * @return  	 Error Status
 *          	 - If Input Parameters are out of range -> ***Input Parameter Error***
 *
 * @constraint	 - You can't disable a clock if it is selected as a System Clock!
 * 				   Use the function "" to check if the clock is selected as a System Clock.
 *
 */
RCC_ErrorStatus_t RCC_DisableClock (volatile u32*ClockRegisterAddress,u32 Clock)
{
	RCC_ErrorStatus_t RET_ErrorStatus=RCC_Ok;
	if(!(Clock==CLOCK_HSI||Clock==CLOCK_HSE||Clock==CLOCK_PLL||Clock==CLOCK_LSI
	  || Clock==CLOCK_LSE||Clock==CLOCK_PLLI2S))
	{
		RET_ErrorStatus=RCC_InvalidParameter;
	}
	else
	{
		RET_ErrorStatus=RCC_Ok;
		*(ClockRegisterAddress)&=~Clock;
	}
	return RET_ErrorStatus;
}

/**
 * @brief   	  Function to Select a System Clock
 *
 * @param   	  - Sysclk (SYSCLK_HSI, SYSCLK_HSE, SYSCLK_PLL)
 *
 * @return	      Error Status
 *          	  - If Input Parameters are out of range -> ***Input Parameter Error****
 *
 * @constraint    - Make sure Clock is On & Ready before selecting it as system clock!! Use the
 * 				    "RCC_CheckReadyClk()" Function
 *
 */
RCC_ErrorStatus_t RCC_SelectSystemClock(u32 Sysclk)
{
	RCC_ErrorStatus_t RET_ErrorStatus=RCC_Ok;

	if(!((Sysclk==SYSCLK_HSE)||(Sysclk==SYSCLK_HSE)||(Sysclk==SYSCLK_PLL)))
	{
		RET_ErrorStatus=RCC_InvalidParameter;
	}
	else
	{
		u32 Temp_CFGR= RCC->CFGR;
		Temp_CFGR&=~(MASK_SET_SYSCLK);
		Temp_CFGR|=Sysclk;
		RCC->CFGR=Temp_CFGR;
	}
	return RET_ErrorStatus;
}

/**
 * @brief   Function to Enable a Peripheral
 *
 * @param   - Peripheral Bus (AHB1, AHB2, APB1, APB2)
 *          - Peripheral (Macro begins with RCC_)
 *
 * @return  Error Status
 *          - If Input Parameters are out of range -> ***Input Parameter Error***
 *
 */
RCC_ErrorStatus_t RCC_EnablePeriphral(volatile u32*PeriphralBus, u32 Periphral)
{
	RCC_ErrorStatus_t RET_ErrorStatus= RCC_Ok;
	if(!((PeriphralBus==APB1)||(PeriphralBus==APB2)||(PeriphralBus==AHB1)||(PeriphralBus==AHB2)))
	{
		RET_ErrorStatus=RCC_InvalidParameter;
	}
	else
	{
		*PeriphralBus|=Periphral;
	}
	return RET_ErrorStatus;
}

/**
 * @brief   Function to Disable a Peripheral
 *
 * @param   - Peripheral Bus (AHB1, AHB2, APB1, APB2)
 *          - Peripheral (Macro begins with RCC_)
 *
 * @return  Error Status
 *          - If Input Parameters are out of range -> ***Input Parameter Error***
 *
 */
RCC_ErrorStatus_t RCC_DisablePeriphral(volatile u32*PeriphralBus,u32 Periphral)
{
	RCC_ErrorStatus_t RET_ErrorStatus= RCC_Ok;
	if(!((PeriphralBus==APB1)||(PeriphralBus==APB2)||(PeriphralBus==AHB1)||(PeriphralBus==AHB2)))
	{
		RET_ErrorStatus=RCC_InvalidParameter;
	}
	else
	{
		*PeriphralBus&=~Periphral;
	}
	return RET_ErrorStatus;
}

/**
 * @brief   Function to Set AHB Prescaler
 *
 * @param   - AHB Prescaler (Macro starts with AHB_CLOCK_)
 *
 * @return  Error Status
 *          - If Input Parameters are out of range -> ***Input Parameter Error***
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
 * @brief   Function to Set APB1 Prescaler
 *
 * @param   - APB1 Prescaler (Macro starts with APB1_CLOCK_)
 *
 * @return  Error Status
 *          - If Input Parameters are out of range -> ***Input Parameter Error***
 *
 * @note	The software has to set these bits correctly not to exceed 42MHz on this domain.
 *
 */
RCC_ErrorStatus_t RCC_SelectAPB1Perscaler(u32 APB1Prescaler)
{
	RCC_ErrorStatus_t RET_ErrorStatus=RCC_Ok;
	if(!(APB1Prescaler==APB1_CLOCK_DIVIDED_BY_2||APB1Prescaler==APB1_CLOCK_DIVIDED_BY_4||
	APB1Prescaler==APB1_CLOCK_DIVIDED_BY_8||APB1Prescaler==APB1_CLOCK_DIVIDED_BY_16))
	{
		RET_ErrorStatus=RCC_InvalidParameter;
	}
	else
	{
		u32 Temp_CFGR=RCC->CFGR;
		Temp_CFGR&=~MASK_APB1_PRESCALER;
		Temp_CFGR|=APB1Prescaler;
		RCC->CFGR=Temp_CFGR;
	}
	return RET_ErrorStatus;
}

/**
 * @brief   Function to Set APB2 Prescaler
 *
 * @param   - APB2 Prescaler (Macro starts with APB2_CLOCK_)
 *
 * @return  Error Status
 *          - If Input Parameters are out of range -> ***Input Parameter Error***
 *
 * @note	The software has to set these bits correctly not to exceed 84MHz on this domain.
 *
 */
RCC_ErrorStatus_t RCC_SelectAPB2Perscaler(u32 APB2Prescaler)
{
	RCC_ErrorStatus_t RET_ErrorStatus=RCC_Ok;
	if(!(APB2Prescaler==APB2_CLOCK_DIVIDED_BY_2||APB2Prescaler==APB2_CLOCK_DIVIDED_BY_4||
	APB2Prescaler==APB2_CLOCK_DIVIDED_BY_8||APB2Prescaler==APB2_CLOCK_DIVIDED_BY_16))
	{
		RET_ErrorStatus=RCC_InvalidParameter;
	}
	else
	{
		u32 Temp_CFGR=RCC->CFGR;
		Temp_CFGR&=~MASK_APB2_PRESCALER;
		Temp_CFGR|=APB2Prescaler;
		RCC->CFGR=Temp_CFGR;
	}
	return RET_ErrorStatus;
}

/**
 * @brief   Function to Configure PLL
 *
 * @param   Struct of type "PLLCfgOptions_t", Takes:
 *          - M:      2:63
 *          - N:      192:432
 *          - P:      2, 4, 6, 8
 *          - Q:      2:15
 *          - PLLSRC: (PLL_CLK_HSI, PLL_CLK_HSE)
 *
 * @return  Error Status
 *          - Failing to comply with constraints will result in an ***Invalid Parameter Error***
 *
 * @constraints
 *          1) PLL must be OFF before configuring!
 *          2) PLL must not be selected as the system clock before configuring!
 *          3) M, N, P, Q, PLLSRC values must be selected from the specified ranges!
 *
 * @note:  - The USB OTG FS requires a 48 MHz clock to work correctly.
 *         - The SDIO and the random number generator need a frequency lower than or equal to 48 MHz to work
 *		   	 correctly.
 *		   - Ensure that the VCO output frequency (FreqInput/M*N) is between 192 and 432MHz.
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
	else if((N<192)||(N>432))
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

/**
 * @brief   Function to Check if Clock is Ready
 *
 * @param   - ClockRegisterAddress (RCC_HSI_HSE_PLL_PLLI2S_REG,RCC_LSE_REG,RCC_LSI_REG)
 * 			- Ready Mask for Clock (MASK_HSIRDY, MASK_HSERDY, MASK_PLLRDY, MASK_LSIRDY, MASKLSERDY,MASKPLLI2SRDY)
 *
 * @return  Error Status
 *          - If Input Parameters are out of range -> ***Input Parameter Error***
 *          - If Clock is not ready -> ***Not Ready Error***
 */
RCC_ErrorStatus_t RCC_CheckReadyClk(volatile u32*ClockRegisterAddress,u32 ReadyMask)
{
	RCC_ErrorStatus_t RET_ErrorStatus=RCC_Ok;
	if(!((ReadyMask==MASK_HSIRDY)||(ReadyMask==MASK_HSERDY)||(ReadyMask==MASK_PLLRDY)||
		(ReadyMask==MASK_HSIRDY)||(ReadyMask==MASK_HSIRDY)||(ReadyMask==MASK_HSIRDY)))
	{
		RET_ErrorStatus=RCC_InvalidParameter;
	}
	else
	{
		if(!(*(ClockRegisterAddress)&ReadyMask))
		{
			RET_ErrorStatus=RCC_NotReady;
		}
	}
	return RET_ErrorStatus;
}
