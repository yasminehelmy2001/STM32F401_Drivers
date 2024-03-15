/*
* File:    SWITCH.h
* Author:  Yasmin Amr
* Created: 19/2/2024
* Brief:   SWITCH Driver
* Target:  STM32F401cc
*/

#ifndef SWITCH_H_
#define SWITCH_H_

#include "SWITCH_cfg.h"

#define SWITCH_NOTPRESSED					(0U)
#define SWITCH_PRESSED						(1U)

#define SWITCH_PULLUP						(0U)
#define SWITCH_PULLDOWN						(1U)

typedef struct
{
	void* Port;			/*(GPIO_PORTA,GPIO_PORTB, GPIO_PORTC,GPIO_PORTD,GPIO_PORTE,GPIO_PORTH)*/

	u8 Pin;				/*(GPIO_PIN0 -> GPIO_PIN15)*/

	u8 Connection; 		/*(SWITCH_PULLUP / SWITCH_PULLDOWN)*/
}SwitchCfg_t;

typedef enum
{
	SWITCH_Ok,
	SWITCH_Nok,
	SWITCH_InvalidParameter,
	SWITCH_NullPointer
}SWITCH_ErrorStatus_t;

/**
 * @brief	Initializes all Switches Pre-configured in SWITCH_cfg.c
 * @param	None
 * @error	Error Status(SWITCH_Ok/SWITCH/Nok)
 */
SWITCH_ErrorStatus_t SWITCH_Init(void);

// /**
//  * @brief	Reads a Switch State (HIGH/LOW)
//  *
//  * @param	- Switch (Takes the SWITCH name written in the Switches_t enum type in SWITCH_cfg.h)
//  * 			- Pointer to State (SWITCH_PRESSED/ SWITCH_NOTPRESSED)
//  *
//  * @error	Error Status (SWITCH_Ok / SWITCH_InvalidParameter)
//  */
// SWITCH_ErrorStatus_t SWITCH_ReadStatus(u32 Switch, u8*State);

/**
 * @brief	Reads a Switch State (HIGH/LOW)
 *
 * @param	- Switch (Takes the SWITCH name written in the Switches_t enum type in SWITCH_cfg.h)
 * 			- Pointer to State (SWITCH_PRESSED/ SWITCH_NOTPRESSED)
 *
 * @error	Error Status (SWITCH_Ok / SWITCH_InvalidParameter)
 */
SWITCH_ErrorStatus_t SW_GetState(u32 Switch, u8*State);


#endif /* SWITCH_H_ */
