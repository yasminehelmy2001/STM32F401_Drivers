/*
* File:    USART.c
* Author:  Yasmin Amr
* Created: 28/3/2024
* Brief:   USART Driver
* Target:  STM32F401cc
*/

/**
 * Notes for Implementing
 * 1) Falling Edge of idle state is what determines the USART to start listening to the frame
 * 2) Stop bits are essential in order to bring the signal to idle state again
 * 3) If theres a frame error, such as mistaking a data bit as a start bit or so on.. the frame error flag will be set
 * 4) Each USART has only one handler, so you must check on all the flags inside this handler
 * 5) We clear RXNE Interrupt Enable at the beginning of the RxAsync Function in order not to receive any interrupts while configuring a new buffer
 * 6) In a driver, you must give the user all the configurable options in the datasheet, any mistake would be the users fault
*/

/**
 * Defs:
 * 1) RXNE: Receiver Buffer Not Empty (Ready to Read Data)
 * 2) TXE: Transmitter Buffer Empty: No Data in Buffer (Data Shifted to Shift Register), Ready to Transmit Data 
 * 3) TC: Transmit Complete: When All Data in Buffer is Transmitted
*/

#include "USART.h"

#define busy     (0U)
#define ready    (1U)

#define USART_COUNT  (3U)

#define USART_TC_FLAG_MASK                  0x00000040
#define USART_TXE_FLAG_MASK                 0x00000080
#define USART_RXNE_FLAG_MASK                0x00000020

#define USART_ENABLE_MASK                   0x00002000
#define USART_TXE_INT_ENABLE_MASK           0X00000080
#define USART_RXNE_INT_ENABLE_MASK          0X00000020 
#define USART_TX_ENABLE_MASK                0X00000008
#define USART_RX_ENABLE_MASK                0X00000004
#define USART_WORD_LENGTH_MASK              0x00001000
#define USART_OVERSAMPLING_MASK             0x00008000
#define USART_PARITY_SELECT_MASK            0x00000200
#define USART_PARITY_CONTROL_MASK           0x00000400
#define USART_STOP_BIT_MASK                 0x00003000
#define USART_PARITY_ON                     0x00000400

#define USART_TX_ENABLE                     0x00000008
#define USART_RX_ENABLE                     0x00000004

#define USART_DIV_MANTISSA_MASK              0x0000FFF0
#define USART_DIV_FRACTION_MASK              0x0000000F

#define SHIFT_FOUR                           (4U)

#define IS_USART_OVERSAMPLING(USART_OVERSAMPLING)       ((USART_OVERSAMPLING==USART_OVERSAMPLING_16)    ||\
                                                        (USART_OVERSAMPLING==USART_OVERSAMPLING_8))


#define IS_USART_WORD_LENGTH(USART_WORD_LENGTH)         ((USART_WORD_LENGTH==USART_DATA_BITS_8)         ||\
                                                        (USART_WORD_LENGTH==USART_DATA_BITS_9))

#define IS_USART_PARITY_SELECT(USART_PARITY_SELECT)     ((USART_PARITY_SELECT==USART_PARITY_NONE)       ||\
                                                        (USART_PARITY_SELECT==USART_PARITY_EVEN)        ||\
                                                        (USART_PARITY_SELECT==USART_PARITY_ODD))


#define IS_USART_STOP_BITS(USART_STOP_BITS)             ((USART_STOP_BITS==USART_STOP_BITS_HALF)                ||\
                                                        (USART_STOP_BITS==USART_STOP_BITS_ONE)                  ||\
                                                        (USART_STOP_BITS==USART_STOP_BITS_ONE_AND_HALF)     ||\
                                                        (USART_STOP_BITS==USART_STOP_BITS_TWO))


typedef struct
{
   u32 SR;
   u32 DR;
   u32 BRR;
   u32 CR1;
   u32 CR2;
   u32 CR3;
   u32 GTPR;
}USART_Reg_t;

#define USART1        ((volatile USART_Reg_t*const)0x40011000)
#define USART2        ((volatile USART_Reg_t*const)0x40004400)
#define USART6        ((volatile USART_Reg_t*const)0x40011400)

USART_Buffer_t volatile USART_TxBuffer[3]={{.state=ready},{.state=ready},{.state=ready}};
USART_Buffer_t volatile USART_RxBuffer[3]={{.state=ready},{.state=ready},{.state=ready}};

u32 USART_Peri_Add[3]={0x40011000,0x40004400,0x40011400};

USART_ErrorStatus_t USART_Init(USART_PostCompileCfg_t *cfg)
{
    USART_ErrorStatus_t RET_ErrorStatus=USART_Ok;
    if(!cfg)
    {
        RET_ErrorStatus=USART_NullPtr; 
    }
    else if(cfg->Channel>USART_CH6)
    {
        RET_ErrorStatus=USART_Nok; 
    }
    else if(!(IS_USART_OVERSAMPLING(cfg->OverSampling)))
    {
        RET_ErrorStatus=USART_Nok; 
    }
    else if(!(IS_USART_WORD_LENGTH(cfg->WordLength)))
    {
        RET_ErrorStatus=USART_Nok; 
    }
    else if(!(IS_USART_PARITY_SELECT(cfg->ParitySelect)))
    {
        RET_ErrorStatus=USART_Nok; 
    }
    else if(!(IS_USART_STOP_BITS(cfg->StopBits)))
    {
        RET_ErrorStatus=USART_Nok; 
    }
    else
    {
        /*Check for Max Baud Rate*/
        f32 OVER8= (cfg->OverSampling==USART_OVERSAMPLING_16)?0:1;
        u32 MaxBaudRate= F_USART/(2-OVER8);
        if(cfg->BaudRate>MaxBaudRate)
        {
            RET_ErrorStatus=USART_Nok; 
        }
        else
        {
            volatile USART_Reg_t *const USART=( volatile USART_Reg_t *)USART_Peri_Add[cfg->Channel];
            /*Enable USART*/
            u32 Loc_Reg=USART->CR1;
            Loc_Reg|=(USART_ENABLE);
            
            /*Program Word Length*/
            Loc_Reg&=~(USART_WORD_LENGTH_MASK);
            Loc_Reg|=(cfg->WordLength);
            USART->CR1=Loc_Reg;

            /*Program Number of Stop Bits*/
            Loc_Reg=USART->CR2;
            Loc_Reg&=~USART_STOP_BIT_MASK;
            Loc_Reg|=(cfg->StopBits);
            USART->CR2=Loc_Reg;

            /*Program Parity Bits*/
            Loc_Reg=USART->CR1;
            Loc_Reg&=~USART_PARITY_CONTROL_MASK;
            if(cfg->ParitySelect==USART_PARITY_NONE)
            {
               Loc_Reg|=USART_PARITY_NONE;
            }
            else
            {
                Loc_Reg|=USART_PARITY_ON;
                Loc_Reg&=~USART_PARITY_SELECT_MASK;
                Loc_Reg|=cfg->ParitySelect;
            }
            USART->CR1=Loc_Reg;

            /*Select Baud Rate*/
            f32 USARTDIV=((f32)(F_USART)/((cfg->BaudRate)*8*(2-OVER8)));
            f32 FracionBoundary=(cfg->OverSampling==USART_OVERSAMPLING_16)?16:8;
            u32 DIV_Fraction=(u32)(FracionBoundary*(f32)((f32)USARTDIV-(u32)USARTDIV));
            u32 MAXVALUE=(cfg->OverSampling==USART_OVERSAMPLING_16)?15:7;
            u32 DIV_Mantissa=0;
            if(DIV_Fraction>MAXVALUE)
            {
                DIV_Fraction=0;
                DIV_Mantissa=(u32)USARTDIV+1;
            }
            else
            {
                DIV_Mantissa= (u32)USARTDIV;
            }

            Loc_Reg=USART->BRR;
            Loc_Reg&=~USART_DIV_MANTISSA_MASK;
            Loc_Reg|=DIV_Mantissa<<SHIFT_FOUR;

            Loc_Reg&=~USART_DIV_FRACTION_MASK;
            Loc_Reg|=DIV_Fraction;

            USART->BRR=Loc_Reg;

            /*Enable Transmitter to Begin Idle State*/
            Loc_Reg=USART->CR1;
            Loc_Reg|=USART_TX_ENABLE;

            /*Enable Receiver to Start Searching for Start Bit*/
            Loc_Reg|=USART_RX_ENABLE;
            USART->CR1=Loc_Reg;
        } 
    }
    return RET_ErrorStatus;
}

USART_ErrorStatus_t USART_TxBufferAsyncZeroCopy(u8 USART_Num,u8*buffer, u16 len, fnpointer cbf )
{
    USART_ErrorStatus_t RetErrorStatus=USART_Ok;
    if(!buffer)
    {
        RetErrorStatus=USART_NullPtr;
    }
    else if(!(USART_Num==USART_CH1)||(USART_Num==USART_CH2)||(USART_Num==USART_CH6))
    {
        RetErrorStatus=USART_Nok;
    }
    else
    {        
        if((USART_TxBuffer[USART_Num].state)==ready)
        {
            volatile USART_Reg_t *const USART=( volatile USART_Reg_t *)USART_Peri_Add[USART_Num];
            /*Enable Transmit Interrupt*/
            u32 Loc_Reg=USART->CR1;
            Loc_Reg&=~USART_TXE_INT_ENABLE_MASK;
            Loc_Reg|=USART_TXE_INTERRUPT_ENABLE;
            USART->CR1=Loc_Reg;
            /*Copy User Request Data*/
            USART_TxBuffer[USART_Num].data=buffer;
            USART_TxBuffer[USART_Num].len=len;
            USART_TxBuffer[USART_Num].cbf=cbf;
            /*Reset Byte Position Index*/
            USART_TxBuffer[USART_Num].pos=0;
            USART_TxBuffer[USART_Num].state=busy;
            /*Send First Byte to Trigger Interrupt*/
            USART->DR|=(USART_TxBuffer[USART_Num].data[USART_TxBuffer[USART_Num].pos++]);
        }
        else
        {
            RetErrorStatus=USART_Nok;
        }
    }    
    
    return RetErrorStatus;
}

USART_ErrorStatus_t USART_RxBufferAsyncZeroCopy(u8 USART_Num,u8*buffer, u16 len, fnpointer cbf)
{
    USART_ErrorStatus_t RetErrorStatus=USART_Ok;
    if(!buffer)
    {
        RetErrorStatus=USART_NullPtr;
    }
    else if(!(USART_Num==USART_CH1)||(USART_Num==USART_CH2)||(USART_Num==USART_CH6))
    {
        RetErrorStatus=USART_Nok;
    }
    else
    {
        volatile USART_Reg_t *const USART=( volatile USART_Reg_t *)USART_Peri_Add[USART_Num];
        /*Disable Receive Interrupt*/
        u32 Loc_Reg=USART->CR1;
        Loc_Reg&=~USART_RXNE_INT_ENABLE_MASK;
        Loc_Reg|=USART_RXNE_INT_DISABLE;
        USART->CR1=Loc_Reg;

        if((USART_RxBuffer[USART_Num].state==ready))
        {
            /*Copy User Request Data*/
            USART_RxBuffer[USART_Num].data=buffer;
            USART_RxBuffer[USART_Num].len=len;
            USART_RxBuffer[USART_Num].cbf=cbf;
            /*Reset Byte Position Index*/
            USART_RxBuffer[USART_Num].pos=0;
            USART_RxBuffer[USART_Num].state=busy;
        }
        else
        {
            RetErrorStatus=USART_Nok;
        } 

        /*Enable Receive Interrupt*/
        Loc_Reg=USART->CR1;
        Loc_Reg&=~USART_RXNE_INT_ENABLE_MASK;
        Loc_Reg|=USART_RXNE_INT_ENABLE;
        USART->CR1=Loc_Reg;
    }
    return RetErrorStatus;

}

void USART1_IRQHandler(void)
{
    /*If Data is Transferred to the Shift Register*/
    if((USART1->SR&USART_TXE_FLAG_MASK))
    {
        /*Check on Length( If More Bytes to Send)*/
        if(USART_TxBuffer[USART_CH1].pos<USART_TxBuffer[USART_CH1].len)
        {
             USART1->DR= (u8)(USART_TxBuffer[USART_CH1].data[USART_TxBuffer->pos++]);
        }
        /*All Bytes Sent*/
        else
        {
            USART_TxBuffer[USART_CH1].state=ready;
            USART_TxBuffer[USART_CH1].pos=0;
            /*Check on NULL*/
            if(USART_TxBuffer[USART_CH1].cbf)
            {
                USART_TxBuffer[USART_CH1].cbf();
            }
        }
    }

    /*Unread Data in Receive Buffer*/
    if(USART1->SR&USART_RXNE_FLAG_MASK)
    {
        /*Check on Length*/
        if(USART_RxBuffer[USART_CH1].pos<USART_RxBuffer[USART_CH1].len)
        {
            /*Read data from Buffer ... Flag is automatically cleared*/
            USART_RxBuffer[USART_CH1].data[USART_RxBuffer->pos++]=USART1->DR;
        }
        else
        {
            USART_RxBuffer[USART_CH1].state=ready;
            USART_RxBuffer[USART_CH1].pos=0;
            /*Check on NULL*/
            if(USART_RxBuffer[USART_CH1].cbf)
            {
                USART_RxBuffer[USART_CH1].cbf();
            }
        }

    }

}

void USART2_IRQHandler(void)
{
    /*If Data is Transferred to the Shift Register*/
    if((USART2->SR & USART_TXE_FLAG_MASK))
    {
        /*Check on Length( If More Bytes to Send)*/
        if(USART_TxBuffer[USART_CH2].pos < USART_TxBuffer[USART_CH2].len)
        {
            USART2->DR = (u8)(USART_TxBuffer[USART_CH2].data[USART_TxBuffer[USART_CH2].pos++]);
        }
        /*All Bytes Sent*/
        else
        {
            USART_TxBuffer[USART_CH2].state = ready;
            USART_TxBuffer[USART_CH2].pos = 0;
            /*Check on NULL*/
            if(USART_TxBuffer[USART_CH2].cbf)
            {
                USART_TxBuffer[USART_CH2].cbf();
            }
        }
    }

    /*Unread Data in Receive Buffer*/
    if(USART2->SR & USART_RXNE_FLAG_MASK)
    {
        /*Check on Length*/
        if(USART_RxBuffer[USART_CH2].pos < USART_RxBuffer[USART_CH2].len)
        {
            /*Read data from Buffer ... Flag is automatically cleared*/
            USART_RxBuffer[USART_CH2].data[USART_RxBuffer[USART_CH2].pos++] = USART2->DR;
        }
        else
        {
            USART_RxBuffer[USART_CH2].state = ready;
            USART_RxBuffer[USART_CH2].pos = 0;
            /*Check on NULL*/
            if(USART_RxBuffer[USART_CH2].cbf)
            {
                USART_RxBuffer[USART_CH2].cbf();
            }
        }
    }

}

void USART6_IRQHandler(void)
{
    /*If Data is Transferred to the Shift Register*/
    if((USART6->SR & USART_TXE_FLAG_MASK))
    {
        /*Check on Length( If More Bytes to Send)*/
        if(USART_TxBuffer[USART_CH6].pos < USART_TxBuffer[USART_CH6].len)
        {
            USART6->DR = (u8)(USART_TxBuffer[USART_CH6].data[USART_TxBuffer[USART_CH6].pos++]);
        }
        /*All Bytes Sent*/
        else
        {
            USART_TxBuffer[USART_CH6].state = ready;
            USART_TxBuffer[USART_CH6].pos = 0;
            /*Check on NULL*/
            if(USART_TxBuffer[USART_CH6].cbf)
            {
                USART_TxBuffer[USART_CH6].cbf();
            }
        }
    }

    /*Unread Data in Receive Buffer*/
    if(USART6->SR & USART_RXNE_FLAG_MASK)
    {
        /*Check on Length*/
        if(USART_RxBuffer[USART_CH6].pos < USART_RxBuffer[USART_CH6].len)
        {
            /*Read data from Buffer ... Flag is automatically cleared*/
            USART_RxBuffer[USART_CH6].data[USART_RxBuffer[USART_CH6].pos++] = USART6->DR;
        }
        else
        {
            USART_RxBuffer[USART_CH6].state = ready;
            USART_RxBuffer[USART_CH6].pos = 0;
            /*Check on NULL*/
            if(USART_RxBuffer[USART_CH6].cbf)
            {
                USART_RxBuffer[USART_CH6].cbf();
            }
        }
    }

}
