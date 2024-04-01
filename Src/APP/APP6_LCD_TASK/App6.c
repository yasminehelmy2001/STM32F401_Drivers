
#include "APP.h"

#ifdef APP 
#if(APP==APP6_LCD_TASK)

#include "RCC.h"
#include "SYSTICK.h"
#include "SCHED.h"
#include "LED.h"
#include "ClockControl.h"
#include "LCD_.h"

extern Runnables_t System_Runnables[SYSTEM_RUNNABLES_COUNT];

/**
 * Scheduler Double Buffer Constraint: LCD_Task comes every 2ms, LCD_APP_Runnable comes every 10ms
 */

int main (void)
{
    RCC_EnablePeriphral(AHB1,RCC_GPIOA);
    LED_Init();
    LCD_InitPins();
    LCD_InitAsync(NULL);   
    SCHED_Init();
    SCHED_Start();
}

/**
 * @brief:  APP Runnable that comes every 10ms to store user requests. Storing them all at once before starting the scheduler would 
 *          limit the requests to max buffer size.
*/
void LCD_APP_Runnable(void)
{
    u32 static counter=0;
    counter++;
    if(counter==1)
    {
        LCD_SetCursorPosAsync(0,0,NULL);
    }
    else if(counter==2)
    {
        LCD_WriteStringAsync("Yasmin",6,NULL);
    }
    else if(counter==3)
    {
        LCD_ClearScreenAsync(NULL);
    }
    else if(counter==4)
    {
        LCD_WriteStringAsync("ITI",3,NULL);
    }
    else if(counter==5)
    {
        LCD_SetCursorPosAsync(1,0,NULL);
    }
    else if(counter==6)
    {
        LCD_WriteStringAsync("44",2,NULL);
    }
    else if(counter==7)
    {
        LCD_ClearScreenAsync(NULL);
    }
    else if(counter==8)
    {
        LCD_SetCursorPosAsync(0,0,NULL);
    }
    else if(counter==9)
    {
       LCD_WriteStringAsync("DOUBLE",6,NULL);
    }
    else if(counter==10)
    {
        LCD_SetCursorPosAsync(1,0,NULL);
    }
    else if(counter==11)
    {
       LCD_WriteStringAsync("BUFFER",6,NULL);
    }

}

#endif
#endif