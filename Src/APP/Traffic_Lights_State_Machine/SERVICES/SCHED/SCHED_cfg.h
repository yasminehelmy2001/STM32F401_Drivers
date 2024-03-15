/*
* File:    SCHED_cfg.h
* Author:  Yasmin Amr
* Created: 14/3/2024
* Brief:   SCHED Driver
* Target:  STM32F401cc
*/

#ifndef SCHED_CFG_H_
#define SCHED_CFG_H_

#include "std_types.h"

/*Modify Tick Time of Scheduler - Done by ARCHITECT */
#define TICK_TIME_MS                1
/*Modify your Runnables Count*/
#define SYSTEM_RUNNABLES_COUNT      1
/*Define Your Runnable Name According to Array Index*/
#define Traffic_Lights_Runnble      0

#endif