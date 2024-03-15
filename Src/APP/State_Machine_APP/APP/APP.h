/*
* File:    APP.h
* Author:  Yasmin Amr
* Created: 14/3/2024
* Target:  STM32F401cc
*/

#define MS_TO_SECS  1000

typedef enum
{
    red,
    yellow,
    green
}TrafficLightState_t;


/**
 * Function to Toggle a LED
*/
void Toggle_LED(void);

/**
 * Traffic Lights Runnable
*/
void Traffic_Lights(void);

