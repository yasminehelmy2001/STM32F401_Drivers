#include "NVIC.h"

#define SCB_PRIGROUP_MASK       0x00000700
#define EIGHT_BIT_MASK          0x000000FF
#define SCB_VECTKEY_MASK        0xFFFF0000
#define SCR_AIRCR_WRITE         0x05FA0000
#define FOUR_BIT_SHIFT          0x00000004

volatile NVIC_Peri_t* const NVIC=( volatile NVIC_Peri_t*)NVIC_BASE_ADDRESS;
volatile SCB_Peri_t* const SCB=( volatile SCB_Peri_t*)SCB_BASE_ADDRESS;

u8 two_power (u8 num)
{
    u8 result=1;
    for (u8 i=0;i<num;i++)
    {
        result*=2;
    }
    return result;
}

NVIC_ErrorStatus_t NVIC_EnableInterrupt(u8 IRQn)
{
    NVIC_ErrorStatus_t RET_ErrorStatus= NVIC_Ok;
    u8 Reg_Num;
    u8 Bit_Num;
    if(IRQn>=IRQn_MAX)
    {
        RET_ErrorStatus= NVIC_NOk;
    }
    else
    {
        Reg_Num=IRQn/32;
        Bit_Num=IRQn%32;
        NVIC->ISER[Reg_Num]|=(1<<Bit_Num);
    }
    return RET_ErrorStatus;
}

NVIC_ErrorStatus_t NVIC_DisableInterrupt(u8 IRQn)
{
    NVIC_ErrorStatus_t RET_ErrorStatus= NVIC_Ok;
    u8 Reg_Num;
    u8 Bit_Num;
    if(IRQn>=IRQn_MAX)
    {
        RET_ErrorStatus= NVIC_NOk;
    }
    else
    {
        Reg_Num=IRQn/32;
        Bit_Num=IRQn%32;
        NVIC->ICER[Reg_Num]|=(1<<Bit_Num);
    }
    return RET_ErrorStatus;  
}

NVIC_ErrorStatus_t NVIC_SetPending(u8 IRQn)
{
    NVIC_ErrorStatus_t RET_ErrorStatus= NVIC_Ok;
    u8 Reg_Num;
    u8 Bit_Num;
    if(IRQn>=IRQn_MAX)
    {
        RET_ErrorStatus= NVIC_NOk;
    }
    else
    {
        Reg_Num=IRQn/32;
        Bit_Num=IRQn%32;
        NVIC->ISPR[Reg_Num]|=(1<<Bit_Num);
    }
    return RET_ErrorStatus;
}

NVIC_ErrorStatus_t NVIC_ClearPending(u8 IRQn)
{
    NVIC_ErrorStatus_t RET_ErrorStatus= NVIC_Ok;
    u8 Reg_Num;
    u8 Bit_Num;
    if(IRQn>=IRQn_MAX)
    {
        RET_ErrorStatus= NVIC_NOk;
    }
    else
    {
        Reg_Num=IRQn/32;
        Bit_Num=IRQn%32;
        NVIC->ICPR[Reg_Num]|=(1<<Bit_Num);
    }
    return RET_ErrorStatus;
}

NVIC_ErrorStatus_t NVIC_GetActiveStatus(u8 IRQn, u8*ActiveStatus)
{
    NVIC_ErrorStatus_t RET_ErrorStatus= NVIC_Ok;
    u8 Reg_Num;
    u8 Bit_Num;
    if(IRQn>=IRQn_MAX)
    {
        RET_ErrorStatus= NVIC_NOk;
    }
    else
    {
        Reg_Num=IRQn/32;
        Bit_Num=IRQn%32;
        *ActiveStatus=((NVIC->IABR[Reg_Num]>>Bit_Num)&0x01);
    }
    return RET_ErrorStatus;
}

NVIC_ErrorStatus_t NVIC_GenerateSoftwareInterrupt(u8 ID)
{
    NVIC_ErrorStatus_t RET_ErrorStatus= NVIC_Ok;
    if(ID>=IRQn_MAX)
    {
        RET_ErrorStatus= NVIC_NOk;
    }
    else
    {
        NVIC->STIR=ID;
    }
    return RET_ErrorStatus;
}

NVIC_ErrorStatus_t NVIC_SetPriority(u8 IRQn, u8 PreemptLevel, u8 SubGroupLevel, u32 SubGroupBitsMask)
{
    NVIC_ErrorStatus_t RET_ErrorStatus= NVIC_Ok;

    u8 SubGroupBitsNum=(u8)(((SubGroupBitsMask>>8)&0x07)-0x03);
    u8 PreemptionBitsNum=PRIORITY_BITS-SubGroupBitsNum;
    u8 MaxPreemptLevel=(two_power(PreemptionBitsNum)-1);
    u8 MaxSubGroupLevel=(two_power(SubGroupBitsNum)-1);

    if(IRQn>=IRQn_MAX)
    {
        RET_ErrorStatus= NVIC_NOk;
    }
    else if(SubGroupBitsNum+PreemptionBitsNum>PRIORITY_BITS)
    {
        RET_ErrorStatus= NVIC_NOk;
    }
    else if(SubGroupLevel>MaxSubGroupLevel)
    {
       RET_ErrorStatus= NVIC_NOk;
    }
    else if(PreemptLevel> MaxPreemptLevel )
    {
        RET_ErrorStatus= NVIC_NOk;
    }
    else
    {
        u32 Local_AIRCR=SCB->AIRCR;
        Local_AIRCR&=~SCB_VECTKEY_MASK;
        Local_AIRCR&=~SCB_PRIGROUP_MASK;
        Local_AIRCR|=(SCR_AIRCR_WRITE | SubGroupBitsMask);
        SCB->AIRCR=Local_AIRCR;

        u8 Priority_Reg_Num= IRQn/4;
        u8 Priority_Byte_Offset= IRQn%4;

        u32 Local_IPR=NVIC->IPR[Priority_Reg_Num];
        Local_IPR&=~(EIGHT_BIT_MASK<<Priority_Byte_Offset);
        Local_IPR|=(((PreemptLevel<<PreemptionBitsNum)|(SubGroupLevel))<<FOUR_BIT_SHIFT);
        NVIC->IPR[Priority_Reg_Num]|=Local_IPR;

    }
    return RET_ErrorStatus;
    
}

