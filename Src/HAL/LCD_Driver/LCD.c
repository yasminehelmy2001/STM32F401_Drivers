/*
* File:    LCD.c
* Author:  Yasmin Amr
* Created: 23/3/2024
* Brief:   LCD Driver - Using Scheduler
* Target:  STM32F401cc
*/

#include "LCD_.h"
#include "SCHED.h"

/**
 * @brief:  LCD implemented using scheduler to decrease CPU load by not halting it during delays.
 *          Circular double buffer data structure was used to buffer asynchronous user requests.
*/

/************************************************************************/
/*					           LCD COMMANDS		                        */
/************************************************************************/
#define LCD_CLEAR								                0x01
#define LCD_RETURN_HOME							                0x02
#define LCD_ENTRY_MODE_SET_DEC_SHIFT_OFF		                0x04
#define LCD_ENTRY_MODE_SET_INC_SHIFT_OFF		                0x06
#define LCD_ENTRY_MODE_SET_DEC_SHIFT_ON			                0x05
#define LCD_ENTRY_MODE_SET_DEC_SHIFT_ON			                0x05
#define LCD_ENTRY_MODE_SET_INC_SHIFT_ON			                0x07
#define LCD_DISPLAY_OFF_CURSOR_OFF_BLINK_OFF	                0x08
#define LCD_DISPLAY_ON_CURSOR_OFF_BLINK_OFF		                0x0C
#define LCD_DISPLAY_ON_CURSOR_ON_BLINK_OFF		                0x0E
#define LCD_DISPLAY_ON_CURSOR_ON_BLINK_ON		                0x0F
#define LCD_DISPLAY_ON_CURSOR_OFF_BLINK_ON		                0x0D
#define LCD_SHIFT_CURSOR_LEFT					                0x10
#define LCD_SHIFT_CURSOR_RIGHT					                0x14
#define LCD_SHIFT_DISPLAY_LEFT					                0x18
#define LCD_SHIFT_DISPLAY_RIGHT					                0x1C
#define LCD_FUNCTION_SET_8BIT_2LINES_5x7						0x38	
#define LCD_FUNCTION_SET_4BIT_2LINES_5x8						0x28	
#define LCD_CGRAM_ADDRESS						                0x40						
#define LCD_DDRAM_ADDRESS						                0x80	

/************************************************************************/
/*					         LCD States		                            */
/************************************************************************/
#define init_state          (0U)
#define operational_state   (1U)
#define inactive_state      (2U)

/************************************************************************/
/*					         LCD Init States		                    */
/************************************************************************/
#define PowerOn             (0U)
#define FunctionSet         (1U)
#define DisplayOnOff        (2U)
#define DisplayClear        (3U)
#define EntryModeSet        (4U)

/************************************************************************/
/*					    LCD User Request Types	                        */
/************************************************************************/
#define write               (0U)
#define clear               (1U)
#define setpos              (2U)

/************************************************************************/
/*					         LCD States		                            */
/************************************************************************/
#define ready               (0U)
#define busy                (1U)

/************************************************************************/
/*					    Writing Command States		                    */
/************************************************************************/
#define enable_high             (1U)
#define enable_low              (2U)

/************************************************************************/
/*					         Other Imp. Macros                          */
/************************************************************************/
#define LCD_DATA_BITS_COUNT     (8U)
#define LCD_DATA_BITS_SHIFT     (3U)


/*LCD Functions that Need Delays*/
static void LcdInitProc(void);
static void LcdWriteProc(void);
static void LcdClearProc(void);
static void LcdSetPosProc(void);

/*LCD Helper Functions*/
static void LCD_WriteCommand(u8 Command);
static u8 GET_BIT(u8 Register,u8 BitNum);
static void LCD_WriteData(u8 Data);

/*Extern Runnables Array*/
extern Runnables_t System_Runnables[];

/*LCD Cfg Array*/
extern LCD_Pins_t LcdCfgArray[LCD_BITS];

/*LCD State*/
u8 lcdstate=inactive_state;

/**
 * Global User Request Struct to Share User Info with Task.
 * Global Array of User Request Struct to Buffer User Requests 
 */
LCD_Request_t User_Req[10];
/*Pointer that increments with each user request*/
u8 UserReqPtr=0;
/*Pointer that increments after request is done*/
u8 RunnablePtr=0;
/*Buffer size of user requests*/
u8 BufferSize=10;

/*Enable Tracker*/
static u8 enable_state=enable_high;

/*Global Pointer to Functions*/
func LCD_ClearScreenCbf=NULL;
func LCD_SetCursorCbf=NULL;
func LCD_WriteStringCbf=NULL;
func LCD_InitCbf=NULL;


/************************************************************************/
/*					 User Function Implementations		                */
/************************************************************************/

/**
 * @brief	Initializes Pins used with the LCD Module
 */
void LCD_InitPins(void)
{
        GPIO_Pin_t GpioPinCfg;
        for(u8 i=0; i<LCD_BITS;i++)
        {
            GpioPinCfg.Port=LcdCfgArray[i].Port;
            GpioPinCfg.Pin=LcdCfgArray[i].Pin;
            GpioPinCfg.Mode=MODE_OUTPUT_PP;
            GpioPinCfg.Speed=SPEED_HIGH;
            GpioPinCfg.AF_Choice=AF_DEACTIVATED;
            GPIO_InitPin(&GpioPinCfg);
        }
}

/**
 * @brief	Registers User Request for Initializing an LCD Module
 *
 * @param	- CallBack Function
 *
 * @return  void
 */
void LCD_InitAsync(func callback)
{
    /*Initialize State to Be Ready*/
    for(int i=0;i<BufferSize;i++)
    {
        User_Req[i].state=ready;
    }
    LCD_InitCbf=callback;
    if(User_Req[UserReqPtr].state==ready)
    {
        lcdstate=init_state;
        User_Req[UserReqPtr].state=busy;
        /*If index reached maximum buffer size*/
        if(UserReqPtr==(BufferSize-1))
        {
            /*Circulate Buffer*/
            UserReqPtr=0;
        }
        else
        {
            UserReqPtr++;
        }
    }
}

/**
 * @brief	Registers User Request for Clear Screan
 *
 * @param	- (callback) CallBack Function
 * 
 * @return  void
 */
void LCD_ClearScreenAsync(func callback)
{
    LCD_ClearScreenCbf=callback;
    if(User_Req[UserReqPtr].state==ready)
    {
        User_Req[UserReqPtr].type=clear;
        User_Req[UserReqPtr].state=busy;
        /*If index reached maximum buffer size*/
        if(UserReqPtr==(BufferSize-1))
        {
            /*Circulate Buffer*/
            UserReqPtr=0;
        }
        else
        {
            UserReqPtr++;
        }
    }
}

/**
 * @brief	Registers User Request for Wriiting String + Saves "string" & "length" Information
 *
 * @param	- (string) Pointer to the String
 *          - (length) Length of the String
 *          - (callback) CallBack Function 
 * 
 * @return	Error Status 
 */
LCD_ErrorStatus_t LCD_WriteStringAsync(const char*string, u8 length, func callback)
{
    LCD_ErrorStatus_t RET_ErrorStatus=LCD_Ok;
    if(string==NULL)
    {
        RET_ErrorStatus=LCD_Nok;
    }
    else if(length>16)
    {
        RET_ErrorStatus=LCD_Nok;
    }
    else
    {
        LCD_WriteStringCbf=callback;
        if(User_Req[UserReqPtr].state==ready)
        {
            User_Req[UserReqPtr].string=string;
            User_Req[UserReqPtr].length=length;
            User_Req[UserReqPtr].type=write;
            User_Req[UserReqPtr].state=busy;  
            /*If index reached maximum buffer size*/
            if(UserReqPtr==(BufferSize-1))
            {
                /*Circulate Buffer*/
                UserReqPtr=0;
            }
            else
            {
                UserReqPtr++;
            }
        }
    }
    return RET_ErrorStatus;
}

/**
 * @brief	Registers User Request for Setting Cursor Position and Saves "posX" & "posY" Information.
 *
 * @param	- (posX) Row Number (0/1)
 *          - (posY) Column Number (0->16)
 *          - (callback) CallBack Function 
 * 
 * @return	Error Status 
 */
LCD_ErrorStatus_t LCD_SetCursorPosAsync(u8 posX, u8 posY, func callback)
{
    LCD_ErrorStatus_t RET_ErrorStatus=LCD_Ok;
    if(posX>1)
    {
        RET_ErrorStatus=LCD_Nok;
    }
    else if(posY>16)
    {
        RET_ErrorStatus=LCD_Nok;
    }
    else
    {
        LCD_SetCursorCbf=callback;
        if(User_Req[UserReqPtr].state==ready)
        {
            User_Req[UserReqPtr].posX=posX;
            User_Req[UserReqPtr].posY=posY;
            User_Req[UserReqPtr].type=setpos;
            User_Req[UserReqPtr].state=busy;
            /*If index reached maximum buffer size*/
            if(UserReqPtr==(BufferSize-1))
            {
                /*Circulate Buffer*/
                UserReqPtr=0;
            }
            else
            {
                UserReqPtr++;
            }
        }
    }
    return RET_ErrorStatus;
}

/************************************************************************/
/*					         LCD Task              		                */
/************************************************************************/

//Comes every 2ms
void LCD_Task(void)
{
    if(lcdstate==init_state)
    {
        LcdInitProc();
    }
    else if(lcdstate==operational_state)
    {
        /*Check if User Needs Request*/
        if(User_Req[RunnablePtr].state==busy)
        {
            switch(User_Req[RunnablePtr].type)
            {
                case write:
                    LcdWriteProc();
                break;
                case clear:
                    LcdClearProc();
                break;
                case setpos:
                    LcdSetPosProc();
                break;
            }
        }
    }
}

/************************************************************************/
/*					         LCD Task Threads   		                */
/************************************************************************/

/*Thread for Initializing LCD*/
static void LcdInitProc(void)
{
    static u8 state=PowerOn;
    static u32 counter=0;
    counter+=System_Runnables[LCD_Runnable].PeriodicityMs;
    switch(state)
    {
        case PowerOn:
            if((counter/30)>0) /*If 30ms Have Passed*/
            {
                switch(enable_state)
                {
                    case enable_high:
                        /*Send Command*/
                        LCD_WriteCommand(LCD_FUNCTION_SET_8BIT_2LINES_5x7);
                        /*Set Enable Pin->High*/
                        GPIO_SetPinValue(LcdCfgArray[E_PIN].Port,LcdCfgArray[E_PIN].Pin,GPIO_SET_PIN);
                        /*Set Enable State->Low*/
                        enable_state=enable_low;
                    break;
                    case enable_low: 
                        /*Will Reset Enable Pin After 2ms*/
                        GPIO_SetPinValue(LcdCfgArray[E_PIN].Port,LcdCfgArray[E_PIN].Pin,GPIO_RESET_PIN);
                        /*Change State to Function Set*/
                        state=FunctionSet;
                        /*Reset Enable State to High*/
                        enable_state=enable_high;
                    break;
                }
            }
        break;
        case FunctionSet:
        /*After 2ms*/
                switch(enable_state)
                {
                    case enable_high:
                        /*Send Command*/
                        LCD_WriteCommand(LCD_DISPLAY_ON_CURSOR_ON_BLINK_ON);
                        /*Set Enable Pin->High*/
                        GPIO_SetPinValue(LcdCfgArray[E_PIN].Port,LcdCfgArray[E_PIN].Pin,GPIO_SET_PIN);
                        /*Set Enable State->Low*/
                        enable_state=enable_low;
                    break;
                    case enable_low:
                        /*Will Reset Enable Pin After 2ms*/
                        GPIO_SetPinValue(LcdCfgArray[E_PIN].Port,LcdCfgArray[E_PIN].Pin,GPIO_RESET_PIN);
                        /*Change State to Function Set*/
                        state=DisplayOnOff;
                        /*Reset Enable State to High*/
                        enable_state=enable_high;
                    break;
                }
        break;
        case DisplayOnOff:
                switch(enable_state)
                {
                    case enable_high:
                        /*Send Command*/
                        LCD_WriteCommand(LCD_CLEAR);
                        /*Set Enable Pin->High*/
                        GPIO_SetPinValue(LcdCfgArray[E_PIN].Port,LcdCfgArray[E_PIN].Pin,GPIO_SET_PIN);
                        /*Set Enable State->Low*/
                        enable_state=enable_low;
                    break;
                    case enable_low:
                        /*Will Reset Enable Pin After 2ms*/
                        GPIO_SetPinValue(LcdCfgArray[E_PIN].Port,LcdCfgArray[E_PIN].Pin,GPIO_RESET_PIN);
                        /*Change State to Function Set*/
                        state=DisplayClear;
                        /*Reset Enable State to High*/
                        enable_state=enable_high;
                    break;
                }
            
        break;
        case DisplayClear:
                switch(enable_state)
                {
                    case enable_high:
                        LCD_WriteCommand(LCD_ENTRY_MODE_SET_INC_SHIFT_OFF);
                        /*Set Enable Pin->High*/
                        GPIO_SetPinValue(LcdCfgArray[E_PIN].Port,LcdCfgArray[E_PIN].Pin,GPIO_SET_PIN);
                        /*Set Enable State->Low*/
                        enable_state=enable_low;
                    break;
                    case enable_low:
                        /*Will Reset Enable Pin After 2ms*/
                        GPIO_SetPinValue(LcdCfgArray[E_PIN].Port,LcdCfgArray[E_PIN].Pin,GPIO_RESET_PIN);
                        /*Change State to Function Set*/
                        state=EntryModeSet;
                        /*Reset Enable State to High*/
                        enable_state=enable_high;
                    break;
                }
        break;
        case EntryModeSet:
            lcdstate=operational_state;
            User_Req[RunnablePtr].state=ready;
            /*If index reached maximum buffer size*/
            if(RunnablePtr==(BufferSize-1))
            {
                /*Circulate Buffer*/
                RunnablePtr=0;
            }
            else
            {
                RunnablePtr++;
            }
            /*Call CallBack Function AFTER Seeting User State to Ready*/
            if(LCD_InitCbf)
            {
                LCD_InitCbf();
            }
        break;
    }
}

/*Thread for Writing String to the LCD*/
static void LcdWriteProc(void)
{
    static u8 currpos=0;
    if(currpos==User_Req[RunnablePtr].length)
    {
        /*Clear cursor position*/
        currpos=0;
        /*Set User State to Ready*/
        User_Req[RunnablePtr].state=ready;
        /*If index reached maximum buffer size*/
        if(RunnablePtr==(BufferSize-1))
        {
            /*Circulate Buffer*/
            RunnablePtr=0;
        }
        else
        {
            RunnablePtr++;
        }
        /*Call CallBack Function AFTER Seeting User State to Ready*/
        if(LCD_WriteStringCbf)
        {
            LCD_WriteStringCbf();
        }

    }
    else
    {
        switch(enable_state)
        {
            case enable_high:
                /*Send Data (1 byte)*/
                LCD_WriteData(User_Req[RunnablePtr].string[currpos]);
                /*Set Enable Pin->High*/
                GPIO_SetPinValue(LcdCfgArray[E_PIN].Port,LcdCfgArray[E_PIN].Pin,GPIO_SET_PIN);
                /*Set Enable State->Low*/
                enable_state=enable_low;
            break;
            case enable_low:
                /*Will Reset Enable Pin After 2ms*/
                GPIO_SetPinValue(LcdCfgArray[E_PIN].Port,LcdCfgArray[E_PIN].Pin,GPIO_RESET_PIN);
                /*Reset Enable State to High*/
                enable_state=enable_high;
                /*Increment Current Position to String*/
                currpos++;
            break;
        }
    }
}

/*Thread for Clearing LCD*/
static void LcdClearProc(void)
{
    switch(enable_state)
    {
        case enable_high:
            LCD_WriteCommand(LCD_CLEAR);
            /*Set Enable Pin->High*/
            GPIO_SetPinValue(LcdCfgArray[E_PIN].Port,LcdCfgArray[E_PIN].Pin,GPIO_SET_PIN);
            /*Set Enable State->Low*/
            enable_state=enable_low;
        break;
        case enable_low:
            /*Will Reset Enable Pin After 2ms*/
            GPIO_SetPinValue(LcdCfgArray[E_PIN].Port,LcdCfgArray[E_PIN].Pin,GPIO_RESET_PIN);
            /*Reset Enable State to High*/
            enable_state=enable_high;
            /*Set User State to Ready*/
            User_Req[RunnablePtr].state=ready;
            /*If index reached maximum buffer size*/
            if(RunnablePtr==(BufferSize-1))
            {
                /*Circulate Buffer*/
                RunnablePtr=0;
            }
            else
            {
                RunnablePtr++;
            }
            /*Call CallBack Function AFTER Seeting User State to Ready*/
            if(LCD_ClearScreenCbf)
            {
                LCD_ClearScreenCbf();
            }
        break;
    }
}

/*Thread for Setting Curson Position on the LCD*/
static void LcdSetPosProc(void)
{
    u8 static Cursor_Position=0;
    if(User_Req[RunnablePtr].posX==0)
    {
        //Cursor_Position=(LCD_DDRAM_ADDRESS+User_Req[RunnablePtr].posY);
        Cursor_Position=User_Req[RunnablePtr].posY;
    }
    else
    {
        //Cursor_Position=(LCD_DDRAM_ADDRESS+0x40+User_Req[RunnablePtr].posY);
        Cursor_Position=(0x40+User_Req[RunnablePtr].posY);
    }
    switch(enable_state)
    {
        case enable_high:
            /*Send Command*/
            LCD_WriteCommand(LCD_DDRAM_ADDRESS+Cursor_Position);
            /*Set Enable Pin->High*/
            GPIO_SetPinValue(LcdCfgArray[E_PIN].Port,LcdCfgArray[E_PIN].Pin,GPIO_SET_PIN);
            /*Set Enable State->Low*/
            enable_state=enable_low;
        break;
        case enable_low:
            /*Will Reset Enable Pin After 2ms*/
            GPIO_SetPinValue(LcdCfgArray[E_PIN].Port,LcdCfgArray[E_PIN].Pin,GPIO_RESET_PIN);
            /*Reset Enable State to High*/
            enable_state=enable_high;
            /*Set User State to Ready*/
            User_Req[RunnablePtr].state=ready;
            /*If index reached maximum buffer size*/
            if(RunnablePtr==(BufferSize-1))
            {
                /*Circulate Buffer*/
                RunnablePtr=0;
            }
            else
            {
                RunnablePtr++;
            }
            /*Call CallBack Function AFTER Seeting User State to Ready*/
            if(LCD_SetCursorCbf)
            {
                LCD_SetCursorCbf();
            }
        break;
    }
}

/************************************************************************/
/*					         Helper Functions      		                */
/************************************************************************/

/*Gets Bit from an 8-bit Variable*/
static u8 GET_BIT(u8 Register,u8 BitNum)
{
    return (Register&(1<<BitNum));
}

/*Writes Command on LCD*/
static void LCD_WriteCommand(u8 Command)
{
    u8 bit_tracker=0;
    /*RS=0 -> Command*/
    GPIO_SetPinValue(LcdCfgArray[RS_PIN].Port,LcdCfgArray[RS_PIN].Pin,GPIO_RESET_PIN);
    /*RW=0 -> Write*/
    GPIO_SetPinValue(LcdCfgArray[RW_PIN].Port,LcdCfgArray[RW_PIN].Pin,GPIO_RESET_PIN);
    u32 GPIO_State=0;
    /*Extract Command and Send it*/
    for(u8 i=D0_PIN;i<=D7_PIN;i++)
    {
        if(GET_BIT(Command,bit_tracker++))
        {
            GPIO_State=GPIO_SET_PIN;
        }
        else
        {
            GPIO_State=GPIO_RESET_PIN;
        }
        GPIO_SetPinValue(LcdCfgArray[i].Port,LcdCfgArray[i].Pin,GPIO_State);
    }
}

/*Writes Data to LCD*/ 
static void LCD_WriteData(u8 Data)
{
    u8 bit_tracker=0;
    /*RS=1 -> Data*/
    GPIO_SetPinValue(LcdCfgArray[RS_PIN].Port,LcdCfgArray[RS_PIN].Pin,GPIO_SET_PIN);
    /*RW=0 -> Write*/
    GPIO_SetPinValue(LcdCfgArray[RW_PIN].Port,LcdCfgArray[RW_PIN].Pin,GPIO_RESET_PIN);
    u32 GPIO_State=0;
    /*Extract Data and Send it*/
    for(u8 i=D0_PIN;i<=D7_PIN;i++)
    {
        if(GET_BIT(Data,bit_tracker++))
        {
            GPIO_State=GPIO_SET_PIN;
        }
        else
        {
            GPIO_State=GPIO_RESET_PIN;
        }
        GPIO_SetPinValue(LcdCfgArray[i].Port,LcdCfgArray[i].Pin,GPIO_State);
    }
}
