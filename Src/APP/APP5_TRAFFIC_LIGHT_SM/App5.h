/*
* File:    APP.h
* Author:  Yasmin Amr
* Created: 14/3/2024
* Target:  STM32F401cc
*/

#define MS_TO_S                 1000
#define RED_LED_SECONDS         20
#define YELLOW_LED_SECONDS      2
#define GREEN_LED_SECONDS       6
#define RESET_COUNTER           0

typedef enum
{
    red,
    yellow,
    green
}TrafficLightState_t;
