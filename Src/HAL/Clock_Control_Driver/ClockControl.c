#include "RCC.h"
#include "GPIO.h"
#include "LED.h"
#include "ClockControl.h"

extern const LedCfg_t Leds[_Led_Num];

void Enable_HAL_ClockControl(void)
{
    for(int i=0;i<_Led_Num;i++)
    {
            if(Leds[i].Port==GPIO_PORTA)
                RCC_EnablePeriphral(AHB1,GPIOA_RCC);
            else if(Leds[i].Port==GPIO_PORTB)
                RCC_EnablePeriphral(AHB1,GPIOB_RCC);
            else if(Leds[i].Port==GPIO_PORTC)
                RCC_EnablePeriphral(AHB1,GPIOC_RCC);
            else if(Leds[i].Port==GPIO_PORTD)
                RCC_EnablePeriphral(AHB1,GPIOD_RCC);
            else if(Leds[i].Port==GPIO_PORTE)
                RCC_EnablePeriphral(AHB1,GPIOE_RCC);
            else if(Leds[i].Port==GPIO_PORTH)
                RCC_EnablePeriphral(AHB1,GPIOH_RCC);
            else
            {
                
            }

        
    }
}