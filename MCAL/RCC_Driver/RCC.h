#include "../LIB/std_types.h"

/**********************************************/
/*				RCC REGISTER ADDRESSES	      */
/**********************************************/
#define RCC_CR                  *((volatile u32*)0x40023800)
#define RCC_PLLCFGR             *((volatile u32*)0x40023804)
#define RCC_CFGR                *((volatile u32*)0x40023808)
#define RCC_CIR                 *((volatile u32*)0x4002380C)
#define RCC_AHB1RSTR            *((volatile u32*)0x40023810)
#define RCC_AHB2RSTR            *((volatile u32*)0x40023814)
#define RCC_APB1RSTR            *((volatile u32*)0x40023820)
#define RCC_APB2RSTR            *((volatile u32*)0x40023824)
#define RCC_AHB1ENR             *((volatile u32*)0x40023830)
#define RCC_AHB2ENR             *((volatile u32*)0x40023834)
#define RCC_APB1ENR             *((volatile u32*)0x40023840)
#define RCC_APB2ENR             *((volatile u32*)0x40023844)
#define RCC_AHB1LPENR           *((volatile u32*)0x40023850)
#define RCC_AHB2LPENR           *((volatile u32*)0x40023854)
#define RCC_APB1LPENR           *((volatile u32*)0x40023860)
#define RCC_APB2LPENR           *((volatile u32*)0x40023864)
#define RCC_BDCR                *((volatile u32*)0x40023870)
#define RCC_CSR                 *((volatile u32*)0x40023874)
#define RCC_SSCGR               *((volatile u32*)0x40023880)
#define RCC_PLLI2SCFGR          *((volatile u32*)0x40023884)
#define RCC_DCKCFGR             *((volatile u32*)0x4002388C)

/**********************************************/
/*				Clock Status			      */
/**********************************************/
#define CLOCK_STATUS_ON				1
#define CLOCK_STATUS_OFF			0

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
#define AHB_CLOCK_DIVIDED_BY_512	0b1111

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
}PLLCfgOptions_t;

/********************************************/
/*				Peripheral Buses		    */
/********************************************/

typedef enum
{
	AHB1,
	AHB2,
	APB1,
	APB2
}PeripheralBuses_t;

/********************************************/
/*				Error Status			    */
/********************************************/
typedef enum
{
	RCC_InvalidClock,
	RCC_InvalidClockStatus,
	RCC_OK,
	RCC_NOK
}RCC_ErrorStatus_t;

/********************************************/
/*				Function Prototypes		    */
/********************************************/
void RCC_ControlClock (u8 ClockStatus, u8 Clock);
void RCC_SelectSystemClock(u8 Sysclk);
void RCC_EnablePeriphral(PeripheralBuses_t PeriphralBus, u8 Periphral);
void RCC_DisablePeriphral(PeripheralBuses_t PeriphralBus,u8 Periphral);
void RCC_SelectAHBPerscaler(u8 AHBPrescaler);
void RCC_SelectAPB1Perscaler(u8 APB1Prescaler);
void RCC_SelectAPB2Perscaler(u8 APB2Prescaler);

