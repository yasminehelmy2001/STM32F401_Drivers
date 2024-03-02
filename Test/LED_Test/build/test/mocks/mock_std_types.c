#include <string.h>
#include <stdlib.h>
#include <setjmp.h>
#include "cmock.h"
#include "mock_std_types.h"


static struct mock_std_typesInstance
{
  unsigned char placeHolder;
} Mock;

extern jmp_buf AbortFrame;
extern int GlobalExpectCount;
extern int GlobalVerifyOrder;

void mock_std_types_Verify(void)
{
}

void mock_std_types_Init(void)
{
  mock_std_types_Destroy();
}

void mock_std_types_Destroy(void)
{
  CMock_Guts_MemFreeAll();
  memset(&Mock, 0, sizeof(Mock));
  GlobalExpectCount = 0;
  GlobalVerifyOrder = 0;
}

