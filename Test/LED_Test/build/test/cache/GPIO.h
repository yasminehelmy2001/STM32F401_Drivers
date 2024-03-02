#include "std_types.h"
typedef struct

{

 volatile u32 MODER;

 volatile u32 OTYPER;

 volatile u32 OSPEEDR;

 volatile u32 PUPDR;

 volatile u32 IDR;

 volatile u32 ODR;

 volatile u32 BSRR;

 volatile u32 LCKR;

 volatile u32 AFRL;

 volatile u32 AFRH;

} GPIO_Registers_t;

typedef struct

{

 void* Port;

 u32 Pin;



 u32 Speed;



 u32 Mode;











 u32 AF_Choice;











} GPIO_Pin_t;









typedef enum

{

 GPIO_Ok,

 GPIO_Nok,

 GPIO_InvalidParameter,

 GPIO_NullPointer

}GPIO_ErrorStatus_t;

GPIO_ErrorStatus_t GPIO_InitPin(GPIO_Pin_t*PinCfg);

GPIO_ErrorStatus_t GPIO_SetPinValue(void*Port, u32 Pin,u8 Value );

GPIO_ErrorStatus_t GPIO_GetPinValue(void*Port, u32 Pin, u8*Value);
