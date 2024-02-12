#include "RCC.h"

/********************************************/
/*			Masks				  	   		*/
/********************************************/
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

/********************************************/
/*			Function Implementations 		*/
/********************************************/
RCC_ErrorStatus_t RCC_ControlClock (u8 ClockStatus, u8 Clock)
{
	RCC_ErrorStatus_t RET_ErrorStatus=RCC_OK;

	if(!(Clock==CLOCK_HSI||Clock==CLOCK_HSE||Clock==CLOCK_PLL))
	{
		RET_ErrorStatus=RCC_InvalidClock;
	}
	else if(!(ClockStatus==CLOCK_STATUS_OFF||ClockStatus==CLOCK_STATUS_ON))
	{
		RET_ErrorStatus=RCC_InvalidClockStatus;
	}
	else
	{
		RET_ErrorStatus=RCC_OK;
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
