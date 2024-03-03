#ifdef TEST

#include "unity.h"
#include "mock_GPIO.h"
#include "SWITCH.h"
#include "SWITCH_cfg.h"

#define NOT_NULL_VALUE	3

extern const SwitchCfg_t Switches[_Switch_Num];

void setUp(void)
{
}

void tearDown(void)
{
}

void test_SWITCH_Init_ValidParameters(void)
{
	//To enter for loop
	if(_Switch_Num!=0)
	{
		GPIO_InitPin_IgnoreAndReturn(GPIO_Ok);
		TEST_ASSERT_EQUAL(SWITCH_Ok,SWITCH_Init());
	}
}

void test_SWITCH_Init_InvalidParameters(void)
{
	//To enter for loop
	if(_Switch_Num!=0)
	{
		GPIO_InitPin_IgnoreAndReturn(GPIO_InvalidParameter);
		TEST_ASSERT_EQUAL(SWITCH_Nok,SWITCH_Init());
	}
}

void test_SWITCH_ReadStatus_NullPointer(void)
{
	//To enter for loop
	if(_Switch_Num!=0)
	{
		u8*InvalidState=NULL;
		TEST_ASSERT_EQUAL(SWITCH_NullPointer,SWITCH_ReadStatus((_Switch_Num-1),InvalidState));
	}
}

void test_SWITCH_ReadStatus_InvalidSwitchName(void)
{
	//To enter for loop
	if(_Switch_Num!=0)
	{
		u8 ValidState= NOT_NULL_VALUE;
		TEST_ASSERT_EQUAL(SWITCH_InvalidParameter,SWITCH_ReadStatus((_Switch_Num),&ValidState));
	}
}

void test_SWITCH_ReadStatus_InvalidParameters(void)
{
	//To enter for loop
	if(_Switch_Num!=0)
	{
		u8 ValidState= NOT_NULL_VALUE;
		GPIO_GetPinValue_IgnoreAndReturn(GPIO_InvalidParameter);
		TEST_ASSERT_EQUAL(SWITCH_Nok,SWITCH_ReadStatus((_Switch_Num-1),&ValidState));
	}
}

void test_SWITCH_ReadStatus_ValidParameters(void)
{
	//To enter for loop
	if(_Switch_Num!=0)
	{
		u8 ValidState= NOT_NULL_VALUE;
		GPIO_GetPinValue_IgnoreAndReturn(GPIO_Ok);
		TEST_ASSERT_EQUAL(SWITCH_Ok,SWITCH_ReadStatus((_Switch_Num-1),&ValidState));
	}
}

#endif // TEST
