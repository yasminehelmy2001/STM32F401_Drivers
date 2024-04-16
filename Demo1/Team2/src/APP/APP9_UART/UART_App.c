/*
 * File Name: App7.h
 * Layer	: App
 * Version  : V 0.0
 * Created	:  Mar 16, 2024
 * Author	: Anas Khamees
 */
#include "APP/APP.h"
#ifdef APP
#if (APP==APP9_UART_TEST)
/******************************************************************************************/
/*                                       Includes                                         */
/******************************************************************************************/
#include "HAL/PeripheralCLK_Control/CLK_Control.h"
#include "MCAL/GPIO/GPIO.h"
#include "MCAL/NVIC/NVIC.h"
#include "MCAL/NVIC/STM32F401xx.h"
//#include "MCAL/UART/USART.h"
#include "HAL/IPC/IPC.h"
#include "HAL/LED/LED.h"
/******************************************************************************************/
/*                                        Defines                                         */
/******************************************************************************************/


/******************************************************************************************/
/*                                Variables                                               */
/******************************************************************************************/

/**
 * GPIO Configurations As Alternative Function
 *      - USART1 ---> Tx Pin PA9  ,, Rx Pin PA10 ,, AF07 .
 *      - USART2 ---> Tx Pin PA2  ,, Rx Pin PA3  ,, AF07 .
 *      - USART6 ---> Tx Pin PA11 ,, Rx Pin PA12 ,, AF08 .
 */

/*------------------- Configure PA9 As TX pin ------------------*/
GPIO_CFG_t UART_TX_PIN=
{
    .GPIO_AF   = GPIO_AF07,
    .GPIO_Mode = GPIO_AF_PP_NO_PUPD,
    .GPIO_Pin  = GPIO_PIN2,
    .GPIO_Port = GPIO_PORTA,
    .GPIO_Speed= GPIO_HIGH_SPEED   
};

/*------------------ Configure PA10 As RX pin ------------------*/
GPIO_CFG_t UART_RX_PIN=
{
    .GPIO_AF   = GPIO_AF07,
    .GPIO_Mode = GPIO_AF_PP_NO_PUPD,
    .GPIO_Pin  = GPIO_PIN3,
    .GPIO_Port = GPIO_PORTA,
    .GPIO_Speed= GPIO_HIGH_SPEED   
};

/*--------------- Configure USART1 Peripheral ------------------*/
// USART_CFG_t UART1_CFG=
// {
//     .BaudRate=9600,
//     .BitSampleMethod=USART_SAMPLE_BIT3,
//     .DataBits=USART_DATA_BITS_8,
//     .OverSample=USART_OVERSAMPLING_16,
//     .Parity=USART_PARITY_NONE,
//     .StopBits=UART_STOP_BITS_ONE,
//     .USART_ID=USART1
// };

// USART_CFG_t UART2_CFG=
// {
//     .BaudRate=9600,
//     .BitSampleMethod=USART_SAMPLE_BIT3,
//     .DataBits=USART_DATA_BITS_8,
//     .OverSample=USART_OVERSAMPLING_16,
//     .Parity=USART_PARITY_NONE,
//     .StopBits=UART_STOP_BITS_ONE,
//     .USART_ID=USART2
// };

IPC_USART_CFG_t IPC_UART2_CFG =
{
    .IPC_USART_BaudRate        = 9600,
    .IPC_USART_BitSampleMethod = USART_SAMPLE_BIT3,
    .IPC_USART_DataBits        = USART_DATA_BITS_8,
    .IPC_USART_ID              = USART2,
    .IPC_USART_OverSample      = USART_OVERSAMPLING_16,
    .IPC_USART_Parity          = USART_PARITY_NONE,
    .IPC_USART_StopBits        = UART_STOP_BITS_ONE
};

uint8_t Buffer[5]={'A','B','C','D','E'};
uint8_t ReciverBuffer[3]={0};

/*------------------- USART1 CallBack Fun --------------------*/
void TurnLedON(void)
{
    ErrorStatus_t ReturnError;
    // if((ReciverBuffer[0]==0x0A)&&(ReciverBuffer[1]==0x0B)&&(ReciverBuffer[2]==0x0C))
    // {
    //     //ErrorStatus_t RetError=LED_SetState(RED_LED,LED_ON);
    //     ReturnError=USART_SendBufferAsynchZeroCopy(USART1,ReciverBuffer,3,NULL);
    // }

  if((ReciverBuffer[0]=='A')&&(ReciverBuffer[1]=='B')&&(ReciverBuffer[2]=='C'))
    {
        ErrorStatus_t RetError=LED_SetState(RED_LED,LED_ON);
        IPC_USART_SendBufferAsynchZeroCopy(USART2,ReciverBuffer,3,NULL);
    }  
}

int main(int argc, char* argv[])
{
	ErrorStatus_t ReturnError;
    uint8_t byte=0;
    ReturnError=HAL_PeripheralEnableCLK(HAL_GPIOA);
    ReturnError=HAL_PeripheralEnableCLK(HAL_GPIOB);
    ReturnError=HAL_PeripheralEnableCLK(HAL_USART2);
    ReturnError=GPIO_InitPin(&UART_TX_PIN);
    ReturnError=GPIO_InitPin(&UART_RX_PIN);
    ReturnError=NVIC_EnableIRQ(NVIC_USART2_INTERRUPT);
    ReturnError=LED_Init();
    // ReturnError=USART_Init(&UART2_CFG);
    // ReturnError=USART_ReceiveBufferAsynchZeroCopy(USART2,ReciverBuffer,3,TurnLedON);
    //ReturnError=USART_SendBufferAsynchZeroCopy(USART1,Buffer,5,TurnLedON);
    // ReturnError=USART_SendByte(USART1,'A');
    // ReturnError=USART_SendByte(USART1,'B');
    // ReturnError=USART_SendByte(USART1,'C');
       
       IPC_USART_Init(&IPC_UART2_CFG);
       IPC_USART_ReceiveBufferAsynchZeroCopy(USART2,ReciverBuffer,3,TurnLedON);

    while (1)
    {
        // ReturnError=USART_SendByte(USART1,'A');
        // ReturnError=USART_SendByte(USART1,'N');
        // ReturnError=USART_SendByte(USART1,'A');
        // ReturnError=USART_SendByte(USART1,'S');
        // ReturnError=USART_SendByte(USART1,'\n');
        // ReturnError=USART_ReceiveByte(USART1,&byte);
        // if(byte==0x0A)
        // {
        //     ErrorStatus_t RetError=LED_SetState(RED_LED,LED_ON);
        // }
        // else if(byte==0x0B)
        // {
        //     ErrorStatus_t RetError=LED_SetState(RED_LED,LED_OFF);
        // }
        // else
        // {
        //     /* Nothing to Do but for MISRA */
        // }
    }
     
    return 0;
}
#endif
#endif
