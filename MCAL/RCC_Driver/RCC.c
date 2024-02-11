/***************************************/
/*			Masks			  		   */
/***************************************/
#define MASK_HSIRDY					0x00000002
#define MASK_HSERDY					0x00020000
#define MASK_PLLRDY					0x02000000

#define MASK_SET_PLL_M				0x0000003F
#define MASK_SET_PLL_N				0x00007FC0
#define MASK_SET_PLL_P				0x00030000
#define MASK_SET_PLL_Q				0x0F000000

#define SHIFT_PLL_M					0
#define SHIFT_PLL_N					6
#define SHIFT_PLL_P					16
#define SHIFT_PLL_Q					22

#define MASK_GET_SYSCLK				0x0000000C
