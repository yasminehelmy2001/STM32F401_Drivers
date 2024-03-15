/*
* File:    RCC.h
* Author:  Yasmin Amr
* Created: 10/2/2024
* Brief:   RCC Driver
* Target:  STM32F401cc
*/

#ifndef RCC_H_
#define RCC_H_

#include "../LIB/std_types.h"

/**************************************************************************/
/*						RCC REGISTER ADDRESSES	 					 	  */
/**************************************************************************/
#define RCC_BA							0x40023800

/**************************************************************************/
/*						Clock Status			 					 	  */
/**************************************************************************/
#define CLOCK_STATUS_ON					1
#define CLOCK_STATUS_OFF				0

/**************************************************************************/
/*						Clock Types	 					 				  */
/**************************************************************************/
#define CLOCK_HSI						0x00000001
#define CLOCK_HSE						0x00010000
#define CLOCK_PLL						0x01000000
#define CLOCK_LSI						0x00000001
#define CLOCK_LSE						0x00000001
#define CLOCK_PLLI2S					0x04000000

/**************************************************************************/
/*						Ready Clock Mask				 				  */
/**************************************************************************/
#define MASK_HSIRDY						0x00000002
#define MASK_HSERDY						0x00020000
#define MASK_PLLRDY						0x02000000
#define MASK_PLLI2SRDY					0x08000000
#define MASK_LSIRDY						0x00000002
#define MASK_LSERDY						0x00000002
/**************************************************************************/
/*						PLL Clock Options	 			 				  */
/**************************************************************************/
#define PLL_CLK_HSI						0X00000000
#define PLL_CLK_HSE						0X00400000

/**************************************************************************/
/*						System Clock Types		 					 	  */
/**************************************************************************/
#define SYSCLK_HSI						0x00000000
#define SYSCLK_HSE						0x00000001
#define SYSCLK_PLL						0x00000002

/**************************************************************************/
/*						APB2 Peripherals		 					 	  */
/**************************************************************************/
#define RCC_TIM1						0x00000001
#define RCC_USART1						0x00000010
#define RCC_USART6						0x00000020
#define RCC_ADC1						0x00000100
#define	RCC_SDIO						0x00000800
#define RCC_SPI1						0x00001000
#define RCC_SPI4						0x00002000
#define	RCC_SYSCFGEN					0x00004000
#define RCC_TIM9						0x00010000
#define RCC_TIM10						0x00020000
#define RCC_TIM11						0x00040000

/**************************************************************************/
/*						APB1 Peripherals		 					 	  */
/**************************************************************************/
#define RCC_TIM2						0x00000001
#define RCC_TIM3						0x00000002
#define RCC_TIM4						0x00000004
#define RCC_TIM5						0x00000008
#define RCC_WWDG						0x00000400
#define RCC_SPI2						0x00004000
#define RCC_SPI3						0x00008000
#define RCC_USART2						0x00020000
#define RCC_I2C1						0x00200000
#define	RCC_I2C2						0x00400000
#define	RCC_I2C3						0x00800000
#define RCC_PWR							0x10000000

/**************************************************************************/
/*						AHB2 Peripherals		 					 	  */
/**************************************************************************/
#define	RCC_OTGFS						0x00000080

/**************************************************************************/
/*						AHB1 Peripherals		 					 	  */
/**************************************************************************/
#define RCC_GPIOA						0x00000001
#define RCC_GPIOB						0x00000002
#define RCC_GPIOC						0x00000004
#define RCC_GPIOD						0x00000008
#define RCC_GPIOE						0x00000010
#define RCC_GPIOH						0x00000080
#define RCC_CRC							0x00000800
#define RCC_DMA1						0x00200000
#define RCC_DMA2						0x00400000

/**************************************************************************/
/*						AHB Prescaler			 					 	  */
/**************************************************************************/
#define AHB_CLOCK_NOT_DIVIDED			0x00000000
#define AHB_CLOCK_DIVIDED_BY_2			0x00000080
#define AHB_CLOCK_DIVIDED_BY_4			0x00000090
#define AHB_CLOCK_DIVIDED_BY_8			0x000000A0
#define AHB_CLOCK_DIVIDED_BY_16			0x000000B0
#define AHB_CLOCK_DIVIDED_BY_64			0x000000C0
#define AHB_CLOCK_DIVIDED_BY_128		0x000000D0
#define AHB_CLOCK_DIVIDED_BY_256		0x000000E0
#define AHB_CLOCK_DIVIDED_BY_512		0x000000F0

/**************************************************************************/
/*						APB1 Prescaler			 					 	  */
/**************************************************************************/
#define APB1_CLOCK_NOT_DIVIDED			0x00000000
#define APB1_CLOCK_DIVIDED_BY_2			0x00001000
#define APB1_CLOCK_DIVIDED_BY_4			0x00001400
#define APB1_CLOCK_DIVIDED_BY_8			0x00001800
#define APB1_CLOCK_DIVIDED_BY_16		0x00001C00

/**************************************************************************/
/*						APB2 Prescaler			 					 	  */
/**************************************************************************/
#define APB2_CLOCK_NOT_DIVIDED			0x00000000
#define APB2_CLOCK_DIVIDED_BY_2			0x00008000
#define APB2_CLOCK_DIVIDED_BY_4			0x0000A000
#define APB2_CLOCK_DIVIDED_BY_8			0x0000C000
#define APB2_CLOCK_DIVIDED_BY_16		0x0000E000

/**************************************************************************/
/*						PERIPHERAL BUS ADDRESSES					 	  */
/**************************************************************************/
#define AHB1							((volatile u32*)0x40023830)
#define AHB2							((volatile u32*)0x40023834)
#define APB1							((volatile u32*)0x40023840)
#define APB2							((volatile u32*)0x40023844)

/**************************************************************************/
/*						CLOCK ENABLE BUS ADDRESSES					 	  */
/**************************************************************************/
#define RCC_HSI_HSE_PLL_PLLI2S_REG          ((volatile u32*)0x40023800)
#define RCC_LSE_REG              		  	((volatile u32*)0x40023870)
#define RCC_LSI_REG                 		((volatile u32*)0x40023874)

/**************************************************************************/
/*						PLL CFG Struct			 					 	  */
/**************************************************************************/
typedef struct
{
	u32 M; 			// M values-> 2:63
	u32 N; 			// N values -> 192:432
	u32 P; 			// P values -> 2, 4, 6, 8
	u32 Q; 			// Q values -> 2:15
	u32 PLLSRC;	 	// PLLSRC values -> (PLL_CLK_HSI, PLL_CLK_HSE)
}PLLCfgOptions_t;

/**************************************************************************/
/*						RCC Error Status		 					 	  */
/**************************************************************************/
typedef enum
{
	RCC_Ok,
	RCC_Nok,
	RCC_NotReady,
	RCC_NullPointer,
	RCC_InvalidParameter

}RCC_ErrorStatus_t;

/**************************************************************************/
/*						Function Prototypes		 					 	  */
/**************************************************************************/

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
RCC_ErrorStatus_t RCC_EnableClock  (volatile u32*ClockRegisterAddress,u32 Clock);

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
RCC_ErrorStatus_t RCC_DisableClock  (volatile u32*ClockRegisterAddress,u32 Clock);

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
RCC_ErrorStatus_t RCC_SelectSystemClock(u32 Sysclk);

/**
 * @brief   Function to Enable a Peripheral
 *
 * @param   - Peripheral Bus (AHB1, AHB2, APB1, APB2)
 *          - Peripheral (Macro begins with RCC_)
 *
 * @return  Error Status
 *          - If Input Parameters are out of range -> ***Input Parameter Error***
 */
RCC_ErrorStatus_t RCC_EnablePeriphral(volatile u32*PeriphralBus, u32 Periphral);

/**
 * @brief   Function to Disable a Peripheral
 *
 * @param   - Peripheral Bus (AHB1, AHB2, APB1, APB2)
 *          - Peripheral (Macro begins with RCC_)
 *
 * @return  Error Status
 *          - If Input Parameters are out of range -> ***Input Parameter Error***
 */
RCC_ErrorStatus_t RCC_DisablePeriphral(volatile u32*PeriphralBus,u32 Periphral);

/**
 * @brief   Function to Set AHB Prescaler
 *
 * @param   - AHB Prescaler (Macro starts with AHB_CLOCK_)
 *
 * @return  Error Status
 *          - If Input Parameters are out of range -> ***Input Parameter Error***
 */
RCC_ErrorStatus_t RCC_SelectAHBPerscaler(u32 AHBPrescaler);

/**
 * @brief   Function to Set APB1 Prescaler
 *
 * @param   - APB1 Prescaler (Macro starts with APB1_CLOCK_)
 *
 * @return  Error Status
 *          - If Input Parameters are out of range -> ***Input Parameter Error***
 *
 * @note	The software has to set these bits correctly not to exceed 42MHz on this domain.
 */
RCC_ErrorStatus_t RCC_SelectAPB1Perscaler(u32 APB1Prescaler);

/**
 * @brief   Function to Set APB2 Prescaler
 *
 * @param   - APB2 Prescaler (Macro starts with APB2_CLOCK_)
 *
 * @return  Error Status
 *          - If Input Parameters are out of range -> ***Input Parameter Error***
 *
 * @note	The software has to set these bits correctly not to exceed 84MHz on this domain.
 */
RCC_ErrorStatus_t RCC_SelectAPB2Perscaler(u32 APB2Prescaler);

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
 */
RCC_ErrorStatus_t RCC_ConfigurePLL(PLLCfgOptions_t*PLLCfg);

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
RCC_ErrorStatus_t RCC_CheckReadyClk(volatile u32*ClockRegisterAddress,u32 ReadyMask);


#endif
