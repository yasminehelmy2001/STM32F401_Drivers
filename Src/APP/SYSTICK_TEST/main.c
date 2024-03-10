#include "RCC.h"
#include "SYSTICK.h"
#include "LED.h"

void Toggle_LED(void) {
  static u32 status = LED_ON ;
	status ^= (LED_ON | LED_OFF);
  LED_SetStatus(LED_ONE, status);
}

int main(void)
{
  RCC_EnablePeriphral(AHB1,RCC_GPIOA);
  LED_Init();
  STK_SetTimeMS(1000);
  STK_SetCallBack(Toggle_LED);
  STK_Start();

  while (1)
    {

    }

}

