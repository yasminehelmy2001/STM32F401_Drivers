/*
* File:    NVIC.h
* Author:  Yasmin Amr
* Created: 4/3/2024
* Brief:   NVIC Driver
* Target:  STM32F401cc
*/

#include "STM32F401xx.h"

/**************************************************************************/
/*						NVIC-SCB BASE ADDRESSES     				 	  */
/**************************************************************************/
#define NVIC_BASE_ADDRESS       0xE000E100
#define SCB_BASE_ADDRESS        0xE000ED00

/**************************************************************************/
/*						INTERRUPT ACTIVE STATES     				 	  */
/**************************************************************************/
#define INTERRUPT_NOT_ACTIVE              (0U)
#define INTERRUPT_ACTIVE                  (1U)

/**************************************************************************/
/*						NVIC SUBPRIORITY BIT OPTIONS				 	  */
/**************************************************************************/
#define SUBPRIORITY_BITS_NONE   0x00000300
#define SUBPRIORITY_BITS_ONE    0x00000400
#define SUBPRIRITY_BITS_TWO     0x00000500
#define SUBPRIRITY_BITS_THREE   0x00000600
#define SUBPRIRITY_BITS_FOUR    0x00000700

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
    volatile u32 Reserved5[580];
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
/*						NVIC ERROR STATUS ENUM	 					 	  */
/**************************************************************************/
typedef enum
{
    NVIC_Ok,
    NVIC_NOk

}NVIC_ErrorStatus_t;

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
NVIC_ErrorStatus_t NVIC_EnableInterrupt(u8 IRQn);

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
NVIC_ErrorStatus_t NVIC_DisableInterrupt(u8 IRQn);

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
NVIC_ErrorStatus_t NVIC_SetPending(u8 IRQn);

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
NVIC_ErrorStatus_t NVIC_ClearPending(u8 IRQn);

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
NVIC_ErrorStatus_t NVIC_GetActiveStatus(u8 IRQn, u8*ActiveStatus);

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
NVIC_ErrorStatus_t NVIC_GenerateSoftwareInterrupt(u8 ID);

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
NVIC_ErrorStatus_t NVIC_SetPriority(u8 IRQn, u8 PreemptLevel, u8 SubGroupLevel, u32 SubGroupBitsMask);


