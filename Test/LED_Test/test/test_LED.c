#ifdef TEST

#include "unity.h"
#include "mock_GPIO.h"
#include "LED.h"
#include "LED_cfg.h"

extern const LedCfg_t Leds[_Led_Num];
	
void setUp(void) 
{
	
}

void tearDown(void) 
{
}


void test_LED_Init_ValidParameters(void)
{
	GPIO_InitPin_IgnoreAndReturn(GPIO_Ok);
	GPIO_SetPinValue_IgnoreAndReturn(GPIO_Ok);
	TEST_ASSERT_EQUAL(LED_Ok,LED_Init());
}

void test_LED_Init_InvalidParameters(void)
{
	GPIO_InitPin_IgnoreAndReturn(GPIO_Nok);
	GPIO_SetPinValue_IgnoreAndReturn(GPIO_Ok);
	TEST_ASSERT_EQUAL(LED_Nok,LED_Init());
}

void test_LED_SetStatus_InvalidLedName(void)
{
	//Invalid Led Name
	u32 Led=_Led_Num+1;
	TEST_ASSERT_EQUAL(LED_InvalidParameter,LED_SetStatus(Led,LED_ON));
}

void test_LED_SetStatus_ValidLedName(void)
{
	//If Leds exist ... Test 
	if(_Led_Num!=0)
	{
		//Valid Led Name
		u32 Led=_Led_Num-1;
		GPIO_SetPinValue_IgnoreAndReturn(GPIO_Ok);
		TEST_ASSERT_EQUAL(LED_Ok,LED_SetStatus(Led,LED_ON));
	}
}

void test_LED_SetStatus_InvalidState(void)
{
	//If Leds exist ... Test 
	if(_Led_Num!=0)
	{
		//Valid Led Name
		u32 Led=_Led_Num-1;
		GPIO_SetPinValue_IgnoreAndReturn(GPIO_Ok);
		u8 InvalidState=5;
		TEST_ASSERT_EQUAL(LED_InvalidParameter,LED_SetStatus(Led,InvalidState));
	}

}

void test_LED_SetStatus_ValidState(void)
{
	//If Leds exist ... Test 
	if(_Led_Num!=0)
	{
		//Valid Led Name
		u32 Led=_Led_Num-1;
		GPIO_SetPinValue_IgnoreAndReturn(GPIO_Ok);
		TEST_ASSERT_EQUAL(LED_Ok,LED_SetStatus(Led,LED_ON));
	}
}

#endif