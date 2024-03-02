#include "src/std_types.h"
typedef struct

{

 u32 M;

 u32 N;

 u32 P;

 u32 Q;

 u32 PLLSRC;

}PLLCfgOptions_t;











typedef struct

{

 volatile u32 CR;

 volatile u32 PLLCFGR;

 volatile u32 CFGR;

 volatile u32 CIR;

 volatile u32 AHB1RSTR;

 volatile u32 AHB2RSTR;

 volatile u32 Reserved[2];

 volatile u32 APB1RSTR;

 volatile u32 APB2RSTR;

 volatile u32 Reserved2[2];

 volatile u32 AHB1ENR;

 volatile u32 AHB2ENR;

 volatile u32 Reserved3[2];

 volatile u32 APB1ENR;

 volatile u32 APB2ENR;

 volatile u32 Reserved4[2];

 volatile u32 AHB1LPENR;

 volatile u32 AHB2LPENR;

 volatile u32 Reserved5[2];

 volatile u32 APB1LPENR;

 volatile u32 APB2LPENR;

 volatile u32 Reserved6[2];

 volatile u32 BDCR;

 volatile u32 CSR;

 volatile u32 Reserved7[2];

 volatile u32 SSCGR;

 volatile u32 PLLI2SCFGR;

 volatile u32 DCKCFGR;

}RCC_Peri_t;









typedef enum

{

 RCC_Ok,

 RCC_Nok,

 RCC_NotReady,

 RCC_NullPointer,

 RCC_InvalidParameter



}RCC_ErrorStatus_t;

RCC_ErrorStatus_t RCC_EnableClock (u32*ClockRegisterAddress,u32 Clock);

RCC_ErrorStatus_t RCC_DisableClock (u32*ClockRegisterAddress,u32 Clock);

RCC_ErrorStatus_t RCC_SelectSystemClock(u32 Sysclk);

RCC_ErrorStatus_t RCC_EnablePeriphral(u32*PeriphralBus, u32 Periphral);

RCC_ErrorStatus_t RCC_DisablePeriphral(u32*PeriphralBus,u32 Periphral);

RCC_ErrorStatus_t RCC_SelectAHBPerscaler(u32 AHBPrescaler);

RCC_ErrorStatus_t RCC_SelectAPB1Perscaler(u32 APB1Prescaler);

RCC_ErrorStatus_t RCC_SelectAPB2Perscaler(u32 APB2Prescaler);

RCC_ErrorStatus_t RCC_ConfigurePLL(PLLCfgOptions_t*PLLCfg);

RCC_ErrorStatus_t RCC_CheckReadyClk(u32*ClockRegisterAddress,u32 ReadyMask);
