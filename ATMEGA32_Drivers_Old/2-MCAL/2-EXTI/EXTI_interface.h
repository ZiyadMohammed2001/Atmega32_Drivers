/************************************************/
/*                     Name: Ziyad Mohammed     */
/*                     Date: 9/10/2021          */
/*                     SWC: EXTI                */
/*                     Version: 1.0             */
/************************************************/
#ifndef EXTI_INTERFACE_H
#define EXTI_INTERFACE_H

/*#define  EXTI_u8_INT0_PININTERRUPT               0
#define  EXTI_u8_INT1_PININTERRUPT               1
#define  EXTI_u8_INT2_PININTERRUPT               2

#define  EXTI_u8_LOWLEVEL_INTERRUPT              0
#define  EXTI_u8_ANYLOGICALCHANGE_INTERRUPT      1
#define  EXTI_u8_FALLINGEDGE_INTERRUPT           2
#define  EXTI_u8_RISINGEDGE_INTERRUPT            3
*/

/* External Interrupt Numbers Macros. */
typedef enum
{
	EXTI_u8_EXTI0=0,
	EXTI_u8_EXTI1,
	EXTI_u8_EXTI2
}EXTINum_Type;

typedef enum
{
	EXTI_u8_FALLINGEDGE=0,
	EXTI_u8_RAISINGEDGE,
	EXTI_u8_ANY_LOGIGAL_CHANGE,
	EXTI_u8_LOWLEVEL
}EXTITrigSrc_t;// Trigger Source

void EXTI_voidEXTIEnable(void);

u8 EXTI_u8Init(EXTINum_Type Copy_ENUEXTINumber,EXTITrigSrc_t Copy_EnuEXTITrigSrc); // Copy_ENUEXTINumber size of int depend on compiler.
u8 EXTI_u8Enable(EXTINum_Type Copy_ENUEXTINumber);
u8 EXTI_u8Disable(EXTINum_Type Copy_ENUEXTINumber);

u8 EXTI_u8SetCallBack(EXTINum_Type Copy_ENUEXTINumber,void(*Copy_pf)(void));

#endif

