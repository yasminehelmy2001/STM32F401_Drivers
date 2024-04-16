#include "RCC.h"
#include "LED.h"
#include "scheduler.h"

int main(void)
{
	RCC_enuEnableDisablePeripheral(RCC_AHB1,GPIOAEN,Periph_enuON);
	RCC_enuEnableDisablePeripheral(RCC_AHB1,GPIOBEN,Periph_enuON);
	LED_Init();
	SWITCH_Init();
	scheduler_init();
	scheduler_start();
    /* Loop forever */
	while(1);
	return 0;
}
