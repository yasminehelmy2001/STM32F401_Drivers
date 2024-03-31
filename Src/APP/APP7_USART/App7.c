
#include "APP.h"

#ifdef APP 
#if(APP==APP7_USART_TEST)

#include "RCC.h"
#include "GPIO.h"
#include "USART.h"
#include "NVIC.h"
#include "ClockControl.h"
#include "LED.h"

u8 buffer[3]={0};

/*Test CBF*/
void CBF(void)
{
    if(buffer[0]=='y'&&buffer[1]=='e'&&buffer[2]=='s')
    {
         LED_SetStatus(LED_RED,LED_ON);
         USART_TxBufferAsyncZeroCopy(USART_CH1,buffer,3,CBF);
    }
    else
    {
         LED_SetStatus(LED_RED,LED_OFF);
    }
}

int main (void)
{
    u8 ch=0;
    Enable_HAL_ClockControl();
    LED_Init();
    NVIC_EnableInterrupt(NVIC_USART1_INTERRUPT);
    //NVIC_SetPending(NVIC_USART1_INTERRUPT);

    /*Set GPIO Pins as AF .. See Datasheet*/
    GPIO_Pin_t GpioTX={GPIO_PORTA,GPIO_PIN9,SPEED_HIGH,MODE_AF_PP_PD,AF7}; 
    GPIO_Pin_t GpioRX={GPIO_PORTA,GPIO_PIN10,SPEED_HIGH,MODE_AF_PP_PD,AF7};
    GPIO_InitPin(&GpioTX);
    GPIO_InitPin(&GpioRX);  

    USART_PostCompileCfg_t USART1_cfg={USART_CH1,USART_OVERSAMPLING_16,USART_DATA_BITS_8,USART_PARITY_NONE,USART_STOP_BITS_ONE,9600};
    USART_Init(&USART1_cfg);

    //USART_RxBufferAsyncZeroCopy(USART_CH1,buffer,3,CBF);

    while(1)
    {

        // USART_GetByte(USART_CH1,&ch);
        // if(ch=='Y')
        // {
        //     LED_SetStatus(LED_RED,LED_ON);
        // }
        // else
        // {
        //     LED_SetStatus(LED_RED,LED_OFF);
        // }
        // USART_SendByte(USART_CH1,ch);
    }
}

#endif
#endif