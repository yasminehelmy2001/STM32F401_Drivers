/*
* File:    USART.h
* Author:  Yasmin Amr
* Created: 28/3/2024
* Brief:   USART Driver
* Target:  STM32F401cc
*/

#ifndef USART_H_
#define USART_H_

#include "USART_cfg.h"

#define USART_CH1         (0U)
#define USART_CH2         (1U)
#define USART_CH6         (2U)

#define USART_ENABLE                         0x00002000
#define USART_DISABLE                        0x00000000

#define USART_OVERSAMPLING_16                0x00000000
#define USART_OVERSAMPLING_8                 0x00008000

#define USART_DATA_BITS_8                    0x00000000
#define USART_DATA_BITS_9                    0x00001000

#define USART_PARITY_NONE                    0x00000000  
#define USART_PARITY_ODD                     0x00000200
#define USART_PARITY_EVEN                    0x00000000

#define USART_TXE_INTERRUPT_ENABLE           0x00000080
#define USART_TXE_INTERRUPT_DISABLE          0x00000000

#define USART_TX_COMPLETE_INT_ENABLE         0x00000040
#define USART_TX_COMPLETE_INT_DISABLE        0x00000000

#define USART_RXNE_INT_ENABLE                0x00000020   
#define USART_RXNE_INT_DISABLE               0x00000000

#define USART_STOP_BITS_HALF                 0x00001000
#define USART_STOP_BITS_ONE                  0x00000000
#define USART_STOP_BITS_ONE_AND_HALF         0x00003000
#define USART_STOP_BITS_TWO                  0x00002000

typedef void (*fnpointer)(void);

typedef struct
{
    volatile u8*data;                 /*Bytes to be Sent/Received Asynchronously*/
    volatile u16 len;                 /*Number of Bytes to Be Sent/Received Asynchronously*/
    volatile fnpointer cbf;           /*CallBack Function After End of Operation*/
    volatile u16 pos;                  /*Tracker for Bytes*/
    volatile u8 state;                /*State for User Request*/
}USART_Buffer_t;

typedef struct
{
    u8 Channel;
    u8 OverSampling;
    u8 WordLength;
    u8 ParitySelect;
    u8 StopBits;
    f32 BaudRate;
}USART_PostCompileCfg_t;

typedef enum
{
    USART_Ok,
    USART_NullPtr,
    USART_Nok
}USART_ErrorStatus_t;


USART_ErrorStatus_t USART_Init(USART_PostCompileCfg_t* cfg);
USART_ErrorStatus_t USART_TxBufferAsyncZeroCopy(u8 USART_Num,u8*buffer, u16 len, fnpointer cbf );
USART_ErrorStatus_t USART_RxBufferAsyncZeroCopy(u8 USART_Num,u8*buffer, u16 len, fnpointer cbf);

USART_ErrorStatus_t USART_SendByte(u8 USART_Num,u8 byte);
USART_ErrorStatus_t USART_GetByte(u8 USART_Num,u8 byte);

//u8 USART_TxDone(void);
//u8 USART_IsRx(void);


#endif