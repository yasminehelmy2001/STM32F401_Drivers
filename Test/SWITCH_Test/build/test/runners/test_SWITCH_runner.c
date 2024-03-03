/* AUTOGENERATED FILE. DO NOT EDIT. */

/*=======Automagically Detected Files To Include=====*/
#include "unity.h"
#include "cmock.h"
#include "mock_GPIO.h"

int GlobalExpectCount;
int GlobalVerifyOrder;
char* GlobalOrderError;

/*=======External Functions This Runner Calls=====*/
extern void setUp(void);
extern void tearDown(void);
extern void test_SWITCH_Init_ValidParameters(void);
extern void test_SWITCH_Init_InvalidParameters(void);
extern void test_SWITCH_ReadStatus_NullPointer(void);
extern void test_SWITCH_ReadStatus_InvalidSwitchName(void);
extern void test_SWITCH_ReadStatus_InvalidParameters(void);
extern void test_SWITCH_ReadStatus_ValidParameters(void);


/*=======Mock Management=====*/
static void CMock_Init(void)
{
  GlobalExpectCount = 0;
  GlobalVerifyOrder = 0;
  GlobalOrderError = NULL;
  mock_GPIO_Init();
}
static void CMock_Verify(void)
{
  mock_GPIO_Verify();
}
static void CMock_Destroy(void)
{
  mock_GPIO_Destroy();
}

/*=======Test Reset Options=====*/
void resetTest(void);
void resetTest(void)
{
  tearDown();
  CMock_Verify();
  CMock_Destroy();
  CMock_Init();
  setUp();
}
void verifyTest(void);
void verifyTest(void)
{
  CMock_Verify();
}

/*=======Test Runner Used To Run Each Test=====*/
static void run_test(UnityTestFunction func, const char* name, UNITY_LINE_TYPE line_num)
{
    Unity.CurrentTestName = name;
    Unity.CurrentTestLineNumber = line_num;
#ifdef UNITY_USE_COMMAND_LINE_ARGS
    if (!UnityTestMatches())
        return;
#endif
    Unity.NumberOfTests++;
    UNITY_CLR_DETAILS();
    UNITY_EXEC_TIME_START();
    CMock_Init();
    if (TEST_PROTECT())
    {
        setUp();
        func();
    }
    if (TEST_PROTECT())
    {
        tearDown();
        CMock_Verify();
    }
    CMock_Destroy();
    UNITY_EXEC_TIME_STOP();
    UnityConcludeTest();
}

/*=======MAIN=====*/
int main(void)
{
  UnityBegin("test_SWITCH.c");
  run_test(test_SWITCH_Init_ValidParameters, "test_SWITCH_Init_ValidParameters", 20);
  run_test(test_SWITCH_Init_InvalidParameters, "test_SWITCH_Init_InvalidParameters", 30);
  run_test(test_SWITCH_ReadStatus_NullPointer, "test_SWITCH_ReadStatus_NullPointer", 40);
  run_test(test_SWITCH_ReadStatus_InvalidSwitchName, "test_SWITCH_ReadStatus_InvalidSwitchName", 50);
  run_test(test_SWITCH_ReadStatus_InvalidParameters, "test_SWITCH_ReadStatus_InvalidParameters", 60);
  run_test(test_SWITCH_ReadStatus_ValidParameters, "test_SWITCH_ReadStatus_ValidParameters", 71);

  CMock_Guts_MemFreeFinal();
  return UnityEnd();
}
