/*
* File:    NVIC.h
* Author:  Yasmin Amr
* Created: 4/3/2024
* Brief:   NVIC Driver
* Target:  STM32F401cc
*/

#include "STM32F401xx.h"

#define NVIC_BASE_ADDRESS       0xE000E100
#define SCB_BASE_ADDRESS        0xE000ED00 

#define NOT_ACTIVE              (0U)
#define ACTIVE                  (1U)

#define SUBPRIORITY_BITS_NONE   0x00000300
#define SUBPRIORITY_BITS_ONE    0x00000400
#define SUBPRIRITY_BITS_TWO     0x00000500
#define SUBPRIRITY_BITS_THREE   0x00000600
#define SUBPRIRITY_BITS_FOUR    0x00000700


typedef struct 
{
    volatile u32 ISER[8];
    volatile u32 Reserved[24];
    volatile u32 ICER[8];
    volatile u32 Reserved1[24];
    volatile u32 ISPR[8];
    volatile u32 Reserved2[24];
    volatile u32 ICPR[8];
    volatile u32 Reserved3[24];
    volatile u32 IABR[8];
    volatile u32 Reserved4[56];
    volatile u32 IPR[60];
    volatile u32 Reserved5[580];
    volatile u32 STIR;
}NVIC_Peri_t;

typedef struct
{
    volatile u32 CPUID;
    volatile u32 ICSR;
    volatile u32 VTOR;
    volatile u32 AIRCR;
    volatile u32 SCR;
    volatile u32 CCR;
    volatile u32 SHPR[3];
    volatile u32 SHCSR;
    volatile u32 CFSR;
    volatile u32 HFSR;
    volatile u32 Reserved2;
    volatile u32 MMAR;
    volatile u32 BFAR;
    volatile u32 AFSR;
}SCB_Peri_t;

typedef enum
{
    NVIC_Ok,
    NVIC_NOk

}NVIC_ErrorStatus_t;

NVIC_ErrorStatus_t NVIC_EnableInterrupt(u8 IRQn);
NVIC_ErrorStatus_t NVIC_DisableInterrupt(u8 IRQn);
NVIC_ErrorStatus_t NVIC_SetPending(u8 IRQn);
NVIC_ErrorStatus_t NVIC_ClearPending(u8 IRQn);
NVIC_ErrorStatus_t NVIC_GetActiveStatus(u8 IRQn, u8*ActiveStatus);
NVIC_ErrorStatus_t NVIC_GenerateSoftwareInterrupt(u8 ID);
NVIC_ErrorStatus_t NVIC_SetPriority(u8 IRQn, u8 PreemptLevel, u8 SubGroupLevel, u32 SubGroupBitsMask);


