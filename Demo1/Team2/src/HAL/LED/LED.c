/*
 * File Name: LED.c
 * Layer	: HAL
 * Module	: LED
 * Version  : V 0.0
 * Created	:  Feb 19, 2024
 * Target   : Stm32F401CC (BlackBill)
 * Author	: Anas Khamees
 */

#include "MCAL/GPIO/GPIO.h"
#include "MCAL/RCC/RCC.h"
#include"LED.h"

extern LedCFG_t LEDs[_Led_Number];

ErrorStatus_t LED_Init(void)
{
    ErrorStatus_t ReturnError;
    GPIO_CFG_t Led;
    Led.GPIO_Mode=GPIO_OUT_PP_NO_PUPD;
    Led.GPIO_Speed=GPIO_LOW_SPEED;
    Led.GPIO_AF=GPIO_AF_DISABLED;
    uint8_t LedNum;
    for(LedNum=0;LedNum<_Led_Number;LedNum++)
    {
        Led.GPIO_Pin=LEDs[LedNum].Led_Pin;
        Led.GPIO_Port=LEDs[LedNum].Led_Port;
        ReturnError=GPIO_InitPin(&Led);
        ReturnError=GPIO_SetPinValue(LEDs[LedNum].Led_Port,LEDs[LedNum].Led_Pin,(LEDs[LedNum].Led_InitialState)^(LEDs[LedNum].Led_Connection));
    }

    return ReturnError;
}

ErrorStatus_t LED_SetState(uint32_t LedNum,uint32_t LedState)
{
    ErrorStatus_t ReturnState;
    if(((LedNum<(uint32_t)0) || (LedNum>_Led_Number))||((LedState !=LED_ON) && (LedState!=LED_OFF)))
    {
        ReturnState=WRONG_PARAMETER;
    }
    else
    {
        ReturnState=GPIO_SetPinValue(LEDs[LedNum].Led_Port,LEDs[LedNum].Led_Pin,LedState^(LEDs[LedNum].Led_Connection));
    }
    return ReturnState;
}
/* Need Enhancement to be Generic*/
ErrorStatus_t LED_Toggle(uint32_t LedNum)
{
    uint32_t PinState;
    ErrorStatus_t ReturnState;
    if(LedNum>_Led_Number)
    {
        ReturnState=WRONG_PARAMETER;
    }
    else
    {
        ReturnState=GPIO_GetPinValue(LEDs[LedNum].Led_Port,LEDs[LedNum].Led_Pin,&PinState);
        ReturnState=GPIO_SetPinValue(LEDs[LedNum].Led_Port,LEDs[LedNum].Led_Pin,(1^PinState)); /*PinState^(LedState^(LEDs[LedNum].Led_Connection))*/
        ReturnState=OK;
    }
    return ReturnState;
}
   