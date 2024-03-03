/* AUTOGENERATED FILE. DO NOT EDIT. */
#ifndef _MOCK_RCC_H
#define _MOCK_RCC_H

#include "unity.h"
#include "RCC.h"

/* Ignore the following warnings, since we are copying code */
#if defined(__GNUC__) && !defined(__ICC) && !defined(__TMS470__)
#if __GNUC__ > 4 || (__GNUC__ == 4 && (__GNUC_MINOR__ > 6 || (__GNUC_MINOR__ == 6 && __GNUC_PATCHLEVEL__ > 0)))
#pragma GCC diagnostic push
#endif
#if !defined(__clang__)
#pragma GCC diagnostic ignored "-Wpragmas"
#endif
#pragma GCC diagnostic ignored "-Wunknown-pragmas"
#pragma GCC diagnostic ignored "-Wduplicate-decl-specifier"
#endif

void mock_RCC_Init(void);
void mock_RCC_Destroy(void);
void mock_RCC_Verify(void);




#define RCC_EnableClock_IgnoreAndReturn(cmock_retval) RCC_EnableClock_CMockIgnoreAndReturn(__LINE__, cmock_retval)
void RCC_EnableClock_CMockIgnoreAndReturn(UNITY_LINE_TYPE cmock_line, RCC_ErrorStatus_t cmock_to_return);
#define RCC_EnableClock_StopIgnore() RCC_EnableClock_CMockStopIgnore()
void RCC_EnableClock_CMockStopIgnore(void);
#define RCC_EnableClock_ExpectAndReturn(ClockRegisterAddress, Clock, cmock_retval) RCC_EnableClock_CMockExpectAndReturn(__LINE__, ClockRegisterAddress, Clock, cmock_retval)
void RCC_EnableClock_CMockExpectAndReturn(UNITY_LINE_TYPE cmock_line, u32* ClockRegisterAddress, u32 Clock, RCC_ErrorStatus_t cmock_to_return);
typedef RCC_ErrorStatus_t (* CMOCK_RCC_EnableClock_CALLBACK)(u32* ClockRegisterAddress, u32 Clock, int cmock_num_calls);
void RCC_EnableClock_AddCallback(CMOCK_RCC_EnableClock_CALLBACK Callback);
void RCC_EnableClock_Stub(CMOCK_RCC_EnableClock_CALLBACK Callback);
#define RCC_EnableClock_StubWithCallback RCC_EnableClock_Stub
#define RCC_DisableClock_IgnoreAndReturn(cmock_retval) RCC_DisableClock_CMockIgnoreAndReturn(__LINE__, cmock_retval)
void RCC_DisableClock_CMockIgnoreAndReturn(UNITY_LINE_TYPE cmock_line, RCC_ErrorStatus_t cmock_to_return);
#define RCC_DisableClock_StopIgnore() RCC_DisableClock_CMockStopIgnore()
void RCC_DisableClock_CMockStopIgnore(void);
#define RCC_DisableClock_ExpectAndReturn(ClockRegisterAddress, Clock, cmock_retval) RCC_DisableClock_CMockExpectAndReturn(__LINE__, ClockRegisterAddress, Clock, cmock_retval)
void RCC_DisableClock_CMockExpectAndReturn(UNITY_LINE_TYPE cmock_line, u32* ClockRegisterAddress, u32 Clock, RCC_ErrorStatus_t cmock_to_return);
typedef RCC_ErrorStatus_t (* CMOCK_RCC_DisableClock_CALLBACK)(u32* ClockRegisterAddress, u32 Clock, int cmock_num_calls);
void RCC_DisableClock_AddCallback(CMOCK_RCC_DisableClock_CALLBACK Callback);
void RCC_DisableClock_Stub(CMOCK_RCC_DisableClock_CALLBACK Callback);
#define RCC_DisableClock_StubWithCallback RCC_DisableClock_Stub
#define RCC_SelectSystemClock_IgnoreAndReturn(cmock_retval) RCC_SelectSystemClock_CMockIgnoreAndReturn(__LINE__, cmock_retval)
void RCC_SelectSystemClock_CMockIgnoreAndReturn(UNITY_LINE_TYPE cmock_line, RCC_ErrorStatus_t cmock_to_return);
#define RCC_SelectSystemClock_StopIgnore() RCC_SelectSystemClock_CMockStopIgnore()
void RCC_SelectSystemClock_CMockStopIgnore(void);
#define RCC_SelectSystemClock_ExpectAndReturn(Sysclk, cmock_retval) RCC_SelectSystemClock_CMockExpectAndReturn(__LINE__, Sysclk, cmock_retval)
void RCC_SelectSystemClock_CMockExpectAndReturn(UNITY_LINE_TYPE cmock_line, u32 Sysclk, RCC_ErrorStatus_t cmock_to_return);
typedef RCC_ErrorStatus_t (* CMOCK_RCC_SelectSystemClock_CALLBACK)(u32 Sysclk, int cmock_num_calls);
void RCC_SelectSystemClock_AddCallback(CMOCK_RCC_SelectSystemClock_CALLBACK Callback);
void RCC_SelectSystemClock_Stub(CMOCK_RCC_SelectSystemClock_CALLBACK Callback);
#define RCC_SelectSystemClock_StubWithCallback RCC_SelectSystemClock_Stub
#define RCC_EnablePeriphral_IgnoreAndReturn(cmock_retval) RCC_EnablePeriphral_CMockIgnoreAndReturn(__LINE__, cmock_retval)
void RCC_EnablePeriphral_CMockIgnoreAndReturn(UNITY_LINE_TYPE cmock_line, RCC_ErrorStatus_t cmock_to_return);
#define RCC_EnablePeriphral_StopIgnore() RCC_EnablePeriphral_CMockStopIgnore()
void RCC_EnablePeriphral_CMockStopIgnore(void);
#define RCC_EnablePeriphral_ExpectAndReturn(PeriphralBus, Periphral, cmock_retval) RCC_EnablePeriphral_CMockExpectAndReturn(__LINE__, PeriphralBus, Periphral, cmock_retval)
void RCC_EnablePeriphral_CMockExpectAndReturn(UNITY_LINE_TYPE cmock_line, u32* PeriphralBus, u32 Periphral, RCC_ErrorStatus_t cmock_to_return);
typedef RCC_ErrorStatus_t (* CMOCK_RCC_EnablePeriphral_CALLBACK)(u32* PeriphralBus, u32 Periphral, int cmock_num_calls);
void RCC_EnablePeriphral_AddCallback(CMOCK_RCC_EnablePeriphral_CALLBACK Callback);
void RCC_EnablePeriphral_Stub(CMOCK_RCC_EnablePeriphral_CALLBACK Callback);
#define RCC_EnablePeriphral_StubWithCallback RCC_EnablePeriphral_Stub
#define RCC_DisablePeriphral_IgnoreAndReturn(cmock_retval) RCC_DisablePeriphral_CMockIgnoreAndReturn(__LINE__, cmock_retval)
void RCC_DisablePeriphral_CMockIgnoreAndReturn(UNITY_LINE_TYPE cmock_line, RCC_ErrorStatus_t cmock_to_return);
#define RCC_DisablePeriphral_StopIgnore() RCC_DisablePeriphral_CMockStopIgnore()
void RCC_DisablePeriphral_CMockStopIgnore(void);
#define RCC_DisablePeriphral_ExpectAndReturn(PeriphralBus, Periphral, cmock_retval) RCC_DisablePeriphral_CMockExpectAndReturn(__LINE__, PeriphralBus, Periphral, cmock_retval)
void RCC_DisablePeriphral_CMockExpectAndReturn(UNITY_LINE_TYPE cmock_line, u32* PeriphralBus, u32 Periphral, RCC_ErrorStatus_t cmock_to_return);
typedef RCC_ErrorStatus_t (* CMOCK_RCC_DisablePeriphral_CALLBACK)(u32* PeriphralBus, u32 Periphral, int cmock_num_calls);
void RCC_DisablePeriphral_AddCallback(CMOCK_RCC_DisablePeriphral_CALLBACK Callback);
void RCC_DisablePeriphral_Stub(CMOCK_RCC_DisablePeriphral_CALLBACK Callback);
#define RCC_DisablePeriphral_StubWithCallback RCC_DisablePeriphral_Stub
#define RCC_SelectAHBPerscaler_IgnoreAndReturn(cmock_retval) RCC_SelectAHBPerscaler_CMockIgnoreAndReturn(__LINE__, cmock_retval)
void RCC_SelectAHBPerscaler_CMockIgnoreAndReturn(UNITY_LINE_TYPE cmock_line, RCC_ErrorStatus_t cmock_to_return);
#define RCC_SelectAHBPerscaler_StopIgnore() RCC_SelectAHBPerscaler_CMockStopIgnore()
void RCC_SelectAHBPerscaler_CMockStopIgnore(void);
#define RCC_SelectAHBPerscaler_ExpectAndReturn(AHBPrescaler, cmock_retval) RCC_SelectAHBPerscaler_CMockExpectAndReturn(__LINE__, AHBPrescaler, cmock_retval)
void RCC_SelectAHBPerscaler_CMockExpectAndReturn(UNITY_LINE_TYPE cmock_line, u32 AHBPrescaler, RCC_ErrorStatus_t cmock_to_return);
typedef RCC_ErrorStatus_t (* CMOCK_RCC_SelectAHBPerscaler_CALLBACK)(u32 AHBPrescaler, int cmock_num_calls);
void RCC_SelectAHBPerscaler_AddCallback(CMOCK_RCC_SelectAHBPerscaler_CALLBACK Callback);
void RCC_SelectAHBPerscaler_Stub(CMOCK_RCC_SelectAHBPerscaler_CALLBACK Callback);
#define RCC_SelectAHBPerscaler_StubWithCallback RCC_SelectAHBPerscaler_Stub
#define RCC_SelectAPB1Perscaler_IgnoreAndReturn(cmock_retval) RCC_SelectAPB1Perscaler_CMockIgnoreAndReturn(__LINE__, cmock_retval)
void RCC_SelectAPB1Perscaler_CMockIgnoreAndReturn(UNITY_LINE_TYPE cmock_line, RCC_ErrorStatus_t cmock_to_return);
#define RCC_SelectAPB1Perscaler_StopIgnore() RCC_SelectAPB1Perscaler_CMockStopIgnore()
void RCC_SelectAPB1Perscaler_CMockStopIgnore(void);
#define RCC_SelectAPB1Perscaler_ExpectAndReturn(APB1Prescaler, cmock_retval) RCC_SelectAPB1Perscaler_CMockExpectAndReturn(__LINE__, APB1Prescaler, cmock_retval)
void RCC_SelectAPB1Perscaler_CMockExpectAndReturn(UNITY_LINE_TYPE cmock_line, u32 APB1Prescaler, RCC_ErrorStatus_t cmock_to_return);
typedef RCC_ErrorStatus_t (* CMOCK_RCC_SelectAPB1Perscaler_CALLBACK)(u32 APB1Prescaler, int cmock_num_calls);
void RCC_SelectAPB1Perscaler_AddCallback(CMOCK_RCC_SelectAPB1Perscaler_CALLBACK Callback);
void RCC_SelectAPB1Perscaler_Stub(CMOCK_RCC_SelectAPB1Perscaler_CALLBACK Callback);
#define RCC_SelectAPB1Perscaler_StubWithCallback RCC_SelectAPB1Perscaler_Stub
#define RCC_SelectAPB2Perscaler_IgnoreAndReturn(cmock_retval) RCC_SelectAPB2Perscaler_CMockIgnoreAndReturn(__LINE__, cmock_retval)
void RCC_SelectAPB2Perscaler_CMockIgnoreAndReturn(UNITY_LINE_TYPE cmock_line, RCC_ErrorStatus_t cmock_to_return);
#define RCC_SelectAPB2Perscaler_StopIgnore() RCC_SelectAPB2Perscaler_CMockStopIgnore()
void RCC_SelectAPB2Perscaler_CMockStopIgnore(void);
#define RCC_SelectAPB2Perscaler_ExpectAndReturn(APB2Prescaler, cmock_retval) RCC_SelectAPB2Perscaler_CMockExpectAndReturn(__LINE__, APB2Prescaler, cmock_retval)
void RCC_SelectAPB2Perscaler_CMockExpectAndReturn(UNITY_LINE_TYPE cmock_line, u32 APB2Prescaler, RCC_ErrorStatus_t cmock_to_return);
typedef RCC_ErrorStatus_t (* CMOCK_RCC_SelectAPB2Perscaler_CALLBACK)(u32 APB2Prescaler, int cmock_num_calls);
void RCC_SelectAPB2Perscaler_AddCallback(CMOCK_RCC_SelectAPB2Perscaler_CALLBACK Callback);
void RCC_SelectAPB2Perscaler_Stub(CMOCK_RCC_SelectAPB2Perscaler_CALLBACK Callback);
#define RCC_SelectAPB2Perscaler_StubWithCallback RCC_SelectAPB2Perscaler_Stub
#define RCC_ConfigurePLL_IgnoreAndReturn(cmock_retval) RCC_ConfigurePLL_CMockIgnoreAndReturn(__LINE__, cmock_retval)
void RCC_ConfigurePLL_CMockIgnoreAndReturn(UNITY_LINE_TYPE cmock_line, RCC_ErrorStatus_t cmock_to_return);
#define RCC_ConfigurePLL_StopIgnore() RCC_ConfigurePLL_CMockStopIgnore()
void RCC_ConfigurePLL_CMockStopIgnore(void);
#define RCC_ConfigurePLL_ExpectAndReturn(PLLCfg, cmock_retval) RCC_ConfigurePLL_CMockExpectAndReturn(__LINE__, PLLCfg, cmock_retval)
void RCC_ConfigurePLL_CMockExpectAndReturn(UNITY_LINE_TYPE cmock_line, PLLCfgOptions_t* PLLCfg, RCC_ErrorStatus_t cmock_to_return);
typedef RCC_ErrorStatus_t (* CMOCK_RCC_ConfigurePLL_CALLBACK)(PLLCfgOptions_t* PLLCfg, int cmock_num_calls);
void RCC_ConfigurePLL_AddCallback(CMOCK_RCC_ConfigurePLL_CALLBACK Callback);
void RCC_ConfigurePLL_Stub(CMOCK_RCC_ConfigurePLL_CALLBACK Callback);
#define RCC_ConfigurePLL_StubWithCallback RCC_ConfigurePLL_Stub
#define RCC_CheckReadyClk_IgnoreAndReturn(cmock_retval) RCC_CheckReadyClk_CMockIgnoreAndReturn(__LINE__, cmock_retval)
void RCC_CheckReadyClk_CMockIgnoreAndReturn(UNITY_LINE_TYPE cmock_line, RCC_ErrorStatus_t cmock_to_return);
#define RCC_CheckReadyClk_StopIgnore() RCC_CheckReadyClk_CMockStopIgnore()
void RCC_CheckReadyClk_CMockStopIgnore(void);
#define RCC_CheckReadyClk_ExpectAndReturn(ClockRegisterAddress, ReadyMask, cmock_retval) RCC_CheckReadyClk_CMockExpectAndReturn(__LINE__, ClockRegisterAddress, ReadyMask, cmock_retval)
void RCC_CheckReadyClk_CMockExpectAndReturn(UNITY_LINE_TYPE cmock_line, u32* ClockRegisterAddress, u32 ReadyMask, RCC_ErrorStatus_t cmock_to_return);
typedef RCC_ErrorStatus_t (* CMOCK_RCC_CheckReadyClk_CALLBACK)(u32* ClockRegisterAddress, u32 ReadyMask, int cmock_num_calls);
void RCC_CheckReadyClk_AddCallback(CMOCK_RCC_CheckReadyClk_CALLBACK Callback);
void RCC_CheckReadyClk_Stub(CMOCK_RCC_CheckReadyClk_CALLBACK Callback);
#define RCC_CheckReadyClk_StubWithCallback RCC_CheckReadyClk_Stub

#if defined(__GNUC__) && !defined(__ICC) && !defined(__TMS470__)
#if __GNUC__ > 4 || (__GNUC__ == 4 && (__GNUC_MINOR__ > 6 || (__GNUC_MINOR__ == 6 && __GNUC_PATCHLEVEL__ > 0)))
#pragma GCC diagnostic pop
#endif
#endif

#endif