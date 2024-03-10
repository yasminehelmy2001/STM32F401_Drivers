/*
* File:    SYSTICK.h
* Author:  Yasmin Amr
* Created: 9/3/2024
* Brief:   SYSTICK Driver
* Target:  STM32F401cc
*/
#include "std_types.h"
#include "SYSTICK_private.h"
#include "SYSTICK_cfg.h"

typedef void (*stkcbf_t) (void); 


/**************************************************************************/
/*						SYSTICK Registers Struct			 			  */
/**************************************************************************/
typedef struct
{
    volatile u32 CTRL;
    volatile u32 LOAD;
    volatile u32 VAL;
    volatile u32 CALIB;
}STK_Peri_t;


/**************************************************************************/
/*						SYSTICK Error Status Enum   	 			 	  */
/**************************************************************************/
typedef enum
{
    STK_Ok,
    STK_Nok
}STK_ErrorStatus_t;

/**
 * @brief   Function to Start SysTick Timer
 */
void STK_Start(void);

/**
 * @brief   Function to Stop SysTick Timer
 */
void STK_Stop(void);

/**
 * @brief   Function to Set Time in MilliSeconds in SysTick Timer
 *
 * @param   - Time in MS
 *
 * @return  Error Status (Checks if time exceeds time in 'STK_MAX_COUNT_MS' variable)
 */
STK_ErrorStatus_t STK_SetTimeMS(u32 Time);

/**
 * @brief   Function to Set CallBack Function from Application Layer
 *
 * @param   - cbf (Function Name)
 * 
 * @constr  - cbf must be a funcation that takes void and returns void
 *
 * @return  Error Status (Checks if cbf is Null)
 */
STK_ErrorStatus_t STK_SetCallBack(stkcbf_t cbf);

/**
 * @brief   SysTick Handler Function Implementation
 */
void SysTick_Handler(void);
