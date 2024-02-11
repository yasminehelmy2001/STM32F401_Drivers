#include "../LIB/std_types.h"

/**********************************************/
/*				Clock Types				      */
/**********************************************/
#define CLOCK_HSI					0x00000001
#define CLOCK_HSE					0x00010000
#define CLOCK_PLL					0x01000000

/*********************************************/
/*				System Clock Types			 */
/*********************************************/
#define SYSCLK_HSI					0x00000000
#define SYSCLK_HSE					0x00000001
#define SYSCLK_PLL					0x00000002

/*********************************************/
/*				APB2 Peripherals		 	 */
/*********************************************/
#define TIM1_RCC					0x00000001
#define USART1_RCC					0x00000010
#define USART6_RCC					0x00000020
#define ADC1_RCC					0x00000100
#define	SDIO_RCC					0x00000800
#define SPI1_RCC					0x00001000
#define SPI4_RCC					0x00002000
#define	SYSCFGEN_RCC				0x00004000
#define TIM9_RCC					0x00010000
#define TIM10_RCC					0x00020000
#define TIM11_RCC					0x00040000

/*********************************************/
/*				APB1 Peripherals		  	 */
/*********************************************/
#define TIM2_RCC					0x00000001
#define TIM3_RCC					0x00000002
#define TIM4_RCC					0x00000004
#define TIM5_RCC					0x00000008
#define WWDG_RCC					0x00000400
#define SPI2_RCC					0x00004000
#define SPI3_RCC					0x00008000
#define USART2_RCC					0x00020000
#define I2C1_RCC					0x00200000
#define	I2C2_RCC					0x00400000
#define	I2C3_RCC					0x00800000
#define PWR_RCC						0x10000000

/*********************************************/
/*				AHB2 Peripherals		 	 */
/*********************************************/
#define	OTGFS						0x00000080

/*********************************************/
/*				AHB1 Peripherals			 */
/*********************************************/
#define GPIOA_RCC					0x00000001
#define GPIOB_RCC					0x00000002
#define GPIOC_RCC					0x00000004
#define GPIOD_RCC					0x00000008
#define GPIOE_RCC					0x00000010
#define GPIOH_RCC					0x00000080
#define CRC_RCC						0x00000800
#define DMA1_RCC					0x00200000
#define DMA2_RCC					0x00400000

/********************************************/
/*				AHB Prescaler			    */
/********************************************/
#define AHB_CLOCK_NOT_DIVIDED		0b0000
#define AHB_CLOCK_DIVIDED_BY_2		0b1000
#define AHB_CLOCK_DIVIDED_BY_4		0b1001
#define AHB_CLOCK_DIVIDED_BY_8		0b1010
#define AHB_CLOCK_DIVIDED_BY_16		0b1011
#define AHB_CLOCK_DIVIDED_BY_64		0b1100
#define AHB_CLOCK_DIVIDED_BY_128	0b1101
#define AHB_CLOCK_DIVIDED_BY_256	0b1110
#define AHB_CLOCK_DIVIDED_BY_256	0b1111

/*******************************************/
/*				APBx Prescaler			   */
/*******************************************/
#define APBx_CLOCK_NOT_DIVIDED		0b000
#define APBx_CLOCK_DIVIDED_BY_2		0b100
#define APBx_CLOCK_DIVIDED_BY_4		0b101
#define APBx_CLOCK_DIVIDED_BY_8		0b110
#define APBx_CLOCK_DIVIDED_BY_16	0b111

/*******************************************/
/*				PLL CFG Struct			   */
/*******************************************/
typedef struct
{
	u8 M;
	u32 N;
	u8 P;
	u8 Q;
}RCC_strPLLCfgOptions_t;

/********************************************/
/*				Peripheral Buses		    */
/********************************************/

typedef enum
{
	AHB1,
	AHB2,
	APB1,
	APB2
}RCC_PeripheralBuses;


void RCC_ControlClock (u8 ClockStatus, u8 ClockName);
void RCC_ConfigurePLL(RCC_strPLLCfgOptions_t*PLLCfg);
void RCC_SelectSystemClock(u8 Sysclk);
void RCC_EnablePeriphral(RCC_PeripheralBuses PeriphralBus, u8 Periphral);
void RCC_DisablePeriphral(RCC_PeripheralBuses PeriphralBus,u8 Periphral);
void RCC_SelectAHBPerscaler(u8 AHBPrescaler);
void RCC_SelectAPB1Perscaler(u8 APB1Prescaler);
void RCC_SelectAPB2Perscaler(u8 APB2Prescaler);

