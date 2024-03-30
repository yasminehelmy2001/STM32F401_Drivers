
#include "APP.h"

#ifdef APP 
#if(APP==APP7_USART_TEST)

#include "RCC.h"
#include "GPIO.h"
#include "USART.h"
#include "NVIC.h"
#include "ClockControl.h"
#include "LED.h"

u8 buffer[1]={0};

/*Test CBF*/
void CBF(void)
{
    //USART_TxBufferAsyncZeroCopy(USART_CH1,buffer,1,NULL);
}

int main (void)
{
    Enable_HAL_ClockControl();
    LED_Init();
    NVIC_EnableInterrupt(NVIC_USART1_INTERRUPT);
    //NVIC_SetPending(NVIC_USART1_INTERRUPT);

    /*Set GPIO Pins as AF .. See Datasheet*/
    GPIO_Pin_t GpioTX={GPIO_PORTA,GPIO_PIN9,SPEED_HIGH,MODE_AF_PP_PD,AF7}; 
    GPIO_Pin_t GpioRX={GPIO_PORTA,GPIO_PIN10,SPEED_HIGH,MODE_AF_PP_PD,AF7};
    GPIO_InitPin(&GpioTX);
    GPIO_InitPin(&GpioRX);  

    USART_PostCompileCfg_t USART1_cfg={USART_CH1,USART_OVERSAMPLING_16,USART_DATA_BITS_8,USART_PARITY_EVEN,USART_STOP_BITS_TWO,9600};
    USART_Init(&USART1_cfg);
    LED_SetStatus(LED_RED,LED_ON);

    //USART_TxBufferAsyncZeroCopy(USART_CH1,(u8*)"Yasmin",6,CBF);
    while(1)
    {
        USART_RxBufferAsyncZeroCopy(USART_CH1,buffer,1,CBF);
        if(buffer[0]=='Y')
        {
            LED_SetStatus(LED_RED,LED_ON);
        }
        else
        {
            LED_SetStatus(LED_RED,LED_OFF);

        }
    }
}

#endif
#endif