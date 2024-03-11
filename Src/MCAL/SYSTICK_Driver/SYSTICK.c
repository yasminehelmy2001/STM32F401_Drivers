/*
* File:    SYSTICK.c
* Author:  Yasmin Amr
* Created: 9/3/2024
* Brief:   SYSTICK Driver
* Target:  STM32F401cc
*/


#include "SYSTICK.h"

/**************************************************************************/
/*						Peripheral Base Addresses 		 				  */
/**************************************************************************/
#define STK_BASE_ADDRESS                0xE000E010   

/**************************************************************************/
/*						Implementation Masks/Values			 			  */
/**************************************************************************/
#define STK_LOAD_MASK                   0x00FFFFFF
#define STK_MAX_COUNT_MS                0x00FFFFFF
#define STK_ENABLE_MASK                 0x00000001
#define STK_TICK_MASK                   0x00000002
#define STK_CLKSOURCE_MASK              0X00000004
#define STK_COUNTFLAG_MASK              0x00010000

/*Pointer to STK  Registers*/
volatile STK_Peri_t * const STK= (volatile STK_Peri_t*) STK_BASE_ADDRESS;
/*Static SysTick CallBack Function*/
static stkcbf_t APP_cbf= NULL;
/*Static SysTick Periodicity Variable*/
static u8 Periodicity= STK_PERIODICITY_ONE_TIME;
/*Static Counter To Track Handler Activation in One Time Mode*/
static u8 Counter=STK_ACTIVATE_HANDLER;

/**
 * @brief   Function to Start SysTick Timer
 * 
 * @param   Periodicity:   
 *                 - STK_PERIODICITY_ONE_TIME
 *                 - STK_PERIODICITY_INFINITE
 * 
 * @return  Error Status (If Periodicity Option is Invalid)
 */
STK_ErrorStatus_t STK_Start(u8 Copy_Periodicity)
{
        STK_ErrorStatus_t RET_ErrorStatus=STK_Ok;
        if(Copy_Periodicity>STK_PERIODICITY_INFINITE)
        {
            RET_ErrorStatus=STK_Nok;
        }
        else
        {
            /*Enable Interrupts*/
            STK->CTRL|=STK_TICK_MASK;
            /*Set Systick Clock Source*/
            u32 temp_STK_CTRL=STK->CTRL;
            temp_STK_CTRL&=~STK_CLKSOURCE_MASK;
            temp_STK_CTRL|=STK_CLOCK_CHOICE;
            STK->CTRL=temp_STK_CTRL;
            /*Reset Timer*/
            STK->VAL=0;
            /*Check on Peridicity*/
            Periodicity=Copy_Periodicity;      
            /*Activate Handler*/
            Counter=STK_ACTIVATE_HANDLER;  
            /*Enable Timer*/
            STK->CTRL|=STK_ENABLE_MASK;
 
        }
        return RET_ErrorStatus;
}

/**
 * @brief   Function to Stop SysTick Timer
 */
void STK_Stop(void)
{
    STK->CTRL&=~STK_ENABLE_MASK;
}

/**
 * @brief   Function to Set Time in MilliSeconds in SysTick Timer
 *
 * @param   - Time in MS
 *
 * @return  Error Status (Checks if time exceeds time in 'STK_MAX_COUNT_MS' variable)
 */

STK_ErrorStatus_t STK_SetTimeMS(u32 Time_MS)
{
    STK_ErrorStatus_t RET_ErrorStatus= STK_Ok;
    u32 Loc_StkClock = ((STK_CLOCK_CHOICE ==STK_AHB_CLOCK) ? STK_AHB_FREQUENCY : (STK_AHB_FREQUENCY /8));
    /*Cast to u64 to Prevent Overflow*/
    u32 Loc_Counts=((((u64)Loc_StkClock*(u64)Time_MS)/(u64)1000)-1);
    if(Loc_Counts>STK_MAX_COUNT_MS)
    {
        RET_ErrorStatus=STK_Nok;
    }
    else
    {  
        /*Clear Counter Value*/
        STK->VAL=0;
        /*Load Counter Value*/
        u32 Loc_STK_LOAD=STK->LOAD;
        Loc_STK_LOAD&=~STK_LOAD_MASK;
        Loc_STK_LOAD|= Loc_Counts;
        STK->LOAD=Loc_STK_LOAD;
    }
    /*Load temp value to register*/
    return RET_ErrorStatus;
}

/**
 * @brief   Function to Set CallBack Function from Application Layer
 *
 * @param   - cbf (Function Name)
 * 
 * @constr  - cbf must be a funcation that takes void and returns void
 *
 * @return  Error Status (Checks if cbf is Null)
 */
STK_ErrorStatus_t STK_SetCallBack(stkcbf_t cbf)
{
    STK_ErrorStatus_t RET_ErrorStatus= STK_Ok;
    if(cbf)
    {
        APP_cbf=cbf;
    }
    else
    {
        RET_ErrorStatus= STK_Nok;
    }
    return RET_ErrorStatus;
}

/**
 * @brief   SysTick Handler Function Implementation
 */
void SysTick_Handler(void)
{   
    if(APP_cbf && (Counter==STK_ACTIVATE_HANDLER))
    {
        APP_cbf();
    }   
    if(Periodicity==STK_PERIODICITY_ONE_TIME)
    {
        STK_Stop();
        Counter=STK_DONT_ACTIVATE_HANDLER;
    } 
}

