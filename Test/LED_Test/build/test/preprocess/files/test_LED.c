#include "src/LED_cfg.h"
#include "src/LED.h"
#include "build/test/mocks/mock_GPIO.h"
#include "C:/Users/yasmi/.local/share/gem/ruby/3.0.0/gems/ceedling-0.31.1/vendor/unity/src/unity.h"






extern const LedCfg_t Leds[_Led_Num];



void setUp(void)

{



}



void tearDown(void)

{

}





void test_LED_Init_ValidParameters(void)

{

 GPIO_InitPin_CMockIgnoreAndReturn(22, GPIO_Ok);

 GPIO_SetPinValue_CMockIgnoreAndReturn(23, GPIO_Ok);

 UnityAssertEqualNumber((UNITY_INT)((LED_Ok)), (UNITY_INT)((LED_Init())), (((void*)0)), (UNITY_UINT)(24), UNITY_DISPLAY_STYLE_INT);

}



void test_LED_Init_InvalidParameters(void)

{

 GPIO_InitPin_CMockIgnoreAndReturn(29, GPIO_Nok);

 GPIO_SetPinValue_CMockIgnoreAndReturn(30, GPIO_Ok);

 UnityAssertEqualNumber((UNITY_INT)((LED_Nok)), (UNITY_INT)((LED_Init())), (((void*)0)), (UNITY_UINT)(31), UNITY_DISPLAY_STYLE_INT);

}



void test_LED_SetStatus_InvalidLedName(void)

{



 u32 Led=_Led_Num+1;

 UnityAssertEqualNumber((UNITY_INT)((LED_InvalidParameter)), (UNITY_INT)((LED_SetStatus(Led,(1U)))), (((void*)0)), (UNITY_UINT)(38), UNITY_DISPLAY_STYLE_INT);

}



void test_LED_SetStatus_ValidLedName(void)

{



 if(_Led_Num!=0)

 {



  u32 Led=_Led_Num-1;

  GPIO_SetPinValue_CMockIgnoreAndReturn(48, GPIO_Ok);

  UnityAssertEqualNumber((UNITY_INT)((LED_Ok)), (UNITY_INT)((LED_SetStatus(Led,(1U)))), (((void*)0)), (UNITY_UINT)(49), UNITY_DISPLAY_STYLE_INT);

 }

}



void test_LED_SetStatus_InvalidState(void)

{



 if(_Led_Num!=0)

 {



  u32 Led=_Led_Num-1;

  GPIO_SetPinValue_CMockIgnoreAndReturn(60, GPIO_Ok);

  u8 InvalidState=5;

  UnityAssertEqualNumber((UNITY_INT)((LED_InvalidParameter)), (UNITY_INT)((LED_SetStatus(Led,InvalidState))), (((void*)0)), (UNITY_UINT)(62), UNITY_DISPLAY_STYLE_INT);

 }



}



void test_LED_SetStatus_ValidState(void)

{



 if(_Led_Num!=0)

 {



  u32 Led=_Led_Num-1;

  GPIO_SetPinValue_CMockIgnoreAndReturn(74, GPIO_Ok);

  UnityAssertEqualNumber((UNITY_INT)((LED_Ok)), (UNITY_INT)((LED_SetStatus(Led,(1U)))), (((void*)0)), (UNITY_UINT)(75), UNITY_DISPLAY_STYLE_INT);

 }

}
