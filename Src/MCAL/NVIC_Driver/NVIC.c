#include "NVIC.h"

/**
 * Note 1: For Handler Debugging: Add a breakpoint inside the Handler & use Step Over.
 * 
 * Note 2: Use "SetPriority" Function to Set Priorities as all ISRs have the same SW Priority after Reset
*/

/**************************************************************************/
/*						NVIC-SCB Implementation Macros 				 	  */
/**************************************************************************/
#define SCB_PRIGROUP_MASK       0x00000700
#define EIGHT_BIT_MASK          0x000000FF
#define SCB_VECTKEY_MASK        0xFFFF0000
#define SCR_AIRCR_WRITE         0x05FA0000
#define FOUR_BIT_SHIFT          0x00000004
#define BYTE                    (8U)

/**************************************************************************/
/*						NVIC-SCB BASE ADDRESSES     				 	  */
/**************************************************************************/
#define NVIC_BASE_ADDRESS       0xE000E100
#define SCB_BASE_ADDRESS        0xE000ED00

/**************************************************************************/
/*						NVIC Registers Struct	 					 	  */
/**************************************************************************/
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
    volatile u32 Reserved5[644];
    volatile u32 STIR;
}NVIC_Peri_t;

/**************************************************************************/
/*						SCB Registers Struct	 					 	  */
/**************************************************************************/
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

/**************************************************************************/
/*						NVIC-SCB Pointer to Registers  				 	  */
/**************************************************************************/
volatile NVIC_Peri_t* const NVIC=( volatile NVIC_Peri_t*)NVIC_BASE_ADDRESS;
volatile SCB_Peri_t* const SCB=( volatile SCB_Peri_t*)SCB_BASE_ADDRESS;

/**
 * @brief  		 Function to get Two power input number
 *
 * @param   	 num
 *
 * @return		 Result: Two power num
 */
u8 two_power (u8 num)
{
    u8 result=1;
    for (u8 i=0;i<num;i++)
    {
        result*=2;
    }
    return result;
}

/**
 * @brief  		 Function to Enable Any Interrupt in the System
 *
 * @param   	 IRQn(Interrupt Number)
 *               - MACRO Begins with NVIC_
 *               - Options listed in STM32F401xx.h
 *
 * @return		 Error Status
 *         		 - Returns Error if Interrupt Number is out of range 
 * 
 * @constraint   Must Disable Pending Bit before Enabling to avoid Handling Interrupts from Disabled Time!
 */
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

/**
 * @brief  		 Function to Disable Any Interrupt in the System
 *
 * @param   	 IRQn(Interrupt Number)
 *               - MACRO Begins with NVIC_
 *               - Options listed in STM32F401xx.h
 *
 * @return		  Error Status
 *         		 - Returns Error if Interrupt Number is out of range 
 */
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
        NVIC->ICER[Reg_Num]=(1<<Bit_Num);
    }
    return RET_ErrorStatus;  
}

/**
 * @brief  		 Function to Set Pending Bit for Any Interrupt in the System
 *
 * @param   	 IRQn(Interrupt Number)
 *               - MACRO Begins with NVIC_
 *               - Options listed in STM32F401xx.h
 *
 * @return		  Error Status
 *         		 - Returns Error if Interrupt Number is out of range 
 */
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

/**
 * @brief  		 Function to Clear Pending Bit for Any Interrupt in the System
 *
 * @param   	 IRQn(Interrupt Number)
 *               - MACRO Begins with NVIC_
 *               - Options listed in STM32F401xx.h
 *
 * @return		  Error Status
 *         		 - Returns Error if Interrupt Number is out of range 
 */
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
        NVIC->ICPR[Reg_Num]=(1<<Bit_Num);
    }
    return RET_ErrorStatus;
}

/**
 * @brief  		 Function to Check if Any Interrupt in the System is Active/Not Active
 *
 * @param   	 1) IRQn(Interrupt Number)
 *                  - MACRO Begins with NVIC_
 *                  - Options listed in STM32F401xx.h
 * 
 *               2) Pointer to ActiveStatus Variable
 *                  - Returns (INTERRUPT_NOT_ACTIVE/INTERRUPT_ACTIVE) through pointer
 * 
 * @return		 Error Status
 *         		 - Returns Error if:
 *                  * Interrupt Number is out of range 
 *                  * Pointer is NULL
 */
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

/**
 * @brief  		 Function to Generate Software Interrupt for Any Interrupt in the System
 *
 * @param   	 ID(Interrupt Number)
 *               - MACRO Begins with NVIC_
 *               - Options listed in STM32F401xx.h
 *
 * @return		  Error Status
 *         		 - Returns Error if Interrupt Number is out of range 
 */
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


/**
 * @brief  		 Function to Set Priority Bit for Any Interrupt in the System
 *
 * @param   	 1) IRQn(Interrupt Number)
 *                  - MACRO Begins with NVIC_
 *                  - Options listed in STM32F401xx.h
 *              
 *               2) PreemptLevel
 *                  - Takes preemtion level, number must less than 2^(preemption bits)
 *                  - Preemtion bits is (Priority bits - Subgroup Bits)
 * 
 *               3) SubGroupLevel
 *                  - Takes Subgroup level, number must less than 2^(subgroup bits)
 * 
 *               4) SubGroupBitsMask
 *                  - Takes Number of Subgroup bits configuration, choose options from:
 *                          * SUBPRIORITY_BITS_NONE
 *                          * SUBPRIORITY_BITS_ONE
 *                          * SUBPRIORITY_BITS_TWO
 *                          * SUBPRIORITY_BITS_THREE
 *                          * SUBPRIORITY_BITS_FOUR
 *
 * @return		  Error Status
 *         		 - Returns Error if:
 *                          * Interrupt Number is out of range 
 *                          * Preemtion bits >= 2^(preemption bits)
 *                          * SubGroupLevel >= 2^(subgroup bits)
 *                          * Subgroup Bits + Preemption Bits > PRIORITY_BITS
 */
NVIC_ErrorStatus_t NVIC_SetPriority(u8 IRQn, u8 PreemptLevel, u8 SubGroupLevel, u32 SubGroupBitsMask)
{
    NVIC_ErrorStatus_t RET_ErrorStatus= NVIC_Ok;

    /*Extract Subgroup Bits from Subgroup Mask*/
    u8 SubGroupBitsNum=(u8)(((SubGroupBitsMask>>8)&0x07)-0x03);

    /*Extract Preemtion Bits from Data*/
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
        /**************************************************/
        /*	    SubGroup Configuration - SCB Peripheral   */
        /**************************************************/
        u32 Local_AIRCR=SCB->AIRCR;
        /*Apply Write Mask to Register*/
        Local_AIRCR&=~SCB_VECTKEY_MASK;
        /*Apply Priority Mask to Register*/
        Local_AIRCR&=~SCB_PRIGROUP_MASK;
        /*Apply Write Value + Priority Value to Register*/
        Local_AIRCR|=(SCR_AIRCR_WRITE | SubGroupBitsMask);
        SCB->AIRCR=Local_AIRCR;

        /***************************************************/
        /*	    Priority Configuration - NVIC Peripheral   */
        /***************************************************/
        u8 Priority_Reg_Num= IRQn/4;
        u8 Priority_Byte_Offset= IRQn%4;

        u32 Local_IPR=NVIC->IPR[Priority_Reg_Num];
        Local_IPR&=~(EIGHT_BIT_MASK<<Priority_Byte_Offset);
        Local_IPR|=((((PreemptLevel<<SubGroupBitsNum)|(SubGroupLevel))<<FOUR_BIT_SHIFT)<<(Priority_Byte_Offset*BYTE));
        NVIC->IPR[Priority_Reg_Num]|=Local_IPR;

    }
    return RET_ErrorStatus;
    
}

