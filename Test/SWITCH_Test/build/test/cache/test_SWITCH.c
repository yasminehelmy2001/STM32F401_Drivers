#include "src/SWITCH_cfg.h"
#include "src/SWITCH.h"
#include "build/test/mocks/mock_GPIO.h"
#include "C:/Users/yasmi/.local/share/gem/ruby/3.0.0/gems/ceedling-0.31.1/vendor/unity/src/unity.h"










extern const SwitchCfg_t Switches[_Switch_Num];



void setUp(void)

{

}



void tearDown(void)

{

}



void test_SWITCH_Init_ValidParameters(void)

{



 if(_Switch_Num!=0)

 {

  GPIO_InitPin_CMockIgnoreAndReturn(25, GPIO_Ok);

  UnityAssertEqualNumber((UNITY_INT)((SWITCH_Ok)), (UNITY_INT)((SWITCH_Init())), (((void*)0)), (UNITY_UINT)(26), UNITY_DISPLAY_STYLE_INT);

 }

}



void test_SWITCH_Init_InvalidParameters(void)

{



 if(_Switch_Num!=0)

 {

  GPIO_InitPin_CMockIgnoreAndReturn(35, GPIO_InvalidParameter);

  UnityAssertEqualNumber((UNITY_INT)((SWITCH_Nok)), (UNITY_INT)((SWITCH_Init())), (((void*)0)), (UNITY_UINT)(36), UNITY_DISPLAY_STYLE_INT);

 }

}



void test_SWITCH_ReadStatus_NullPointer(void)

{



 if(_Switch_Num!=0)

 {

  u8*InvalidState=((void*)0);

  UnityAssertEqualNumber((UNITY_INT)((SWITCH_NullPointer)), (UNITY_INT)((SWITCH_ReadStatus((_Switch_Num-1),InvalidState))), (((void*)0)), (UNITY_UINT)(46), UNITY_DISPLAY_STYLE_INT);

 }

}



void test_SWITCH_ReadStatus_InvalidSwitchName(void)

{



 if(_Switch_Num!=0)

 {

  u8 ValidState= 3;

  UnityAssertEqualNumber((UNITY_INT)((SWITCH_InvalidParameter)), (UNITY_INT)((SWITCH_ReadStatus((_Switch_Num),&ValidState))), (((void*)0)), (UNITY_UINT)(56), UNITY_DISPLAY_STYLE_INT);

 }

}



void test_SWITCH_ReadStatus_InvalidParameters(void)

{



 if(_Switch_Num!=0)

 {

  u8 ValidState= 3;

  GPIO_GetPinValue_CMockIgnoreAndReturn(66, GPIO_InvalidParameter);

  UnityAssertEqualNumber((UNITY_INT)((SWITCH_Nok)), (UNITY_INT)((SWITCH_ReadStatus((_Switch_Num-1),&ValidState))), (((void*)0)), (UNITY_UINT)(67), UNITY_DISPLAY_STYLE_INT);

 }

}



void test_SWITCH_ReadStatus_ValidParameters(void)

{



 if(_Switch_Num!=0)

 {

  u8 ValidState= 3;

  GPIO_GetPinValue_CMockIgnoreAndReturn(77, GPIO_Ok);

  UnityAssertEqualNumber((UNITY_INT)((SWITCH_Ok)), (UNITY_INT)((SWITCH_ReadStatus((_Switch_Num-1),&ValidState))), (((void*)0)), (UNITY_UINT)(78), UNITY_DISPLAY_STYLE_INT);

 }

}
