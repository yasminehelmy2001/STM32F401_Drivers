
#include "APP.h"

#ifdef APP 
#if(APP==APP6_LCD_TASK)

#include "RCC.h"
#include "SYSTICK.h"
#include "SCHED.h"
#include "LED.h"
#include "ClockControl.h"
#include "LCD_.h"

void LCD_APP_Runnable(void);

extern Runnables_t System_Runnables[SYSTEM_RUNNABLES_COUNT];

int main (void)
{
    RCC_EnablePeriphral(AHB1,RCC_GPIOA);
    LED_Init();
    LCD_InitPins();
    SCHED_Init();
    SCHED_Start();
}

void ClearScreen (void)
{
    //LCD_ClearScreenAsync(NULL);

}
void WriteString (void)
{
    LCD_WriteStringAsync("Yasmin",6,ClearScreen);
}

void SetCursor (void)
{
    LCD_SetCursorPosAsync(0,0,WriteString);
}

void LCD_APP_Runnable(void)
{
    static u8 counter=0;
    counter++;
    if(counter==1)
    {
        LCD_InitAsync(SetCursor);   
    }
}

#endif
#endif