/*
* File:    SWITCH_cfg.h
* Author:  Yasmin Amr
* Created: 19/2/2024
* Brief:   SWITCH Driver
* Target:  STM32F401cc
*/

#ifndef SWITCH_CFG_H_
#define SWITCH_CFG_H_

/**
 * Enter your SWITCH Names above the "_Switch_Num" integer like the following:
 * 		typedef enum
 * 		{
 *			SWITCH_ONE,
 *			SWITCH_TWO,
 *			SWITCH_THREE
 *
 *			_Switch_Num
 * 		}Switches_t;
 *
 */
typedef enum
{


	SWITCH_ONE,
	_Switch_Num
}Switches_t;


#endif /* SWITCH_CFG_H_ */
