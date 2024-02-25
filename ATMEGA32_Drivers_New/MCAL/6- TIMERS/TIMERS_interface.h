
/********************************************************************/
/********************************************************************/
/******************** Author: Ziyad Mohammed      *******************/
/******************** File  : TIMERS_Interface.h  *******************/
/******************** Version: 1.00               *******************/
/********************************************************************/
/********************************************************************/

#ifndef TIMERS_INTERFACE_H_
#define TIMERS_INTERFACE_H_

#include "TIMERS_prv.h"

#define TIMER_u8_TIMER_0	0u
#define TIMER_u8_TIMER_1	1u
#define TIMER_u8_TIMER_2	2u

/*				TIMER0					*/
#define TIMER0_u8_NORMAL				0u
#define TIMER0_u8_PWM_PHASE_CORRECT		1u
#define TIMER0_u8_CTC					2u
#define TIMER0_u8_FAST_PWM				3u


#define TIMER0_u8_OC0_DISCONNECTED		0u
#define TIMER0_u8_OC0_TOGGLE			1u
#define TIMER0_u8_OC0_CLEAR				2u
#define TIMER0_u8_OC0_SET				3u

#define	TIMER0_u8_STOP					0u
#define	TIMER0_u8_DIV_BY_1				1u
#define TIMER0_u8_DIV_BY_8				2u
#define TIMER0_u8_DIV_BY_64				3u
#define TIMER0_u8_DIV_BY_256			4u
#define TIMER0_u8_DIV_BY_1024			5u

#define	TIMER0_u8_DISABLE_INTERRUPT		0u
#define	TIMER0_u8_ENABLE_INTERRUPT		1u

/*				TIMER1					*/
#define TIMER1_u8_NORMAL								0u
#define TIMER1_u8_PWM_PHASE_CORRECT_8BIT				1u
#define TIMER1_u8_PWM_PHASE_CORRECT_9BIT				2u
#define TIMER1_u8_PWM_PHASE_CORRECT_10BIT				3u
#define TIMER1_u8_CTC_OCR1A								4u
#define TIMER1_u8_FAST_PWM_8BIT							5u
#define TIMER1_u8_FAST_PWM_9BIT							6u
#define TIMER1_u8_FAST_PWM_10BIT						7u
#define TIMER1_u8_PWM_PHASE_FREQUANCY_CORRECT_ICR1		8u
#define TIMER1_u8_PWM_PHASE_FREQUANCY_CORRECT_OCR1A		9u
#define TIMER1_u8_PWM_PHASE_CORRECT_ICR1				10u
#define TIMER1_u8_PWM_PHASE_CORRECT_OCR1A				11u
#define TIMER1_u8_CTC_ICR1								12u
#define TIMER1_u8_FAST_PWM_ICR1							13u
#define TIMER1_u8_FAST_PWM_OCR1A						14u

#define TIMER1_u8_OC1_DISCONNECTED			0u
#define TIMER1_u8_OC1_TOGGLE				1u
#define TIMER1_u8_OC1_CLEAR					2u
#define TIMER1_u8_OC1_SET					3u

#define	TIMER1_u8_STOP						0u
#define	TIMER1_u8_DIV_BY_1					1u
#define TIMER1_u8_DIV_BY_8					2u
#define TIMER1_u8_DIV_BY_64					3u
#define TIMER1_u8_DIV_BY_256				4u
#define TIMER1_u8_DIV_BY_1024				5u

/*				TIMER2					*/
#define TIMER2_u8_NORMAL				0u
#define TIMER2_u8_PWM_PHASE_CORRECT		1u
#define TIMER2_u8_CTC					2u
#define TIMER2_u8_FAST_PWM				3u

#define TIMER2_u8_OC2_DISCONNECTED		0u
#define TIMER2_u8_OC2_TOGGLE			1u
#define TIMER2_u8_OC2_CLEAR				2u
#define TIMER2_u8_OC2_SET				3u

#define	TIMER2_u8_STOP					0u
#define	TIMER2_u8_DIV_BY_1				1u
#define TIMER2_u8_DIV_BY_8				2u
#define TIMER2_u8_DIV_BY_32				3u
#define TIMER2_u8_DIV_BY_64				4u
#define TIMER2_u8_DIV_BY_128			5u
#define TIMER2_u8_DIV_BY_256			6u
#define TIMER2_u8_DIV_BY_1024			7u


#define	TIMER2_u8_DISABLE_INTERRUPT		0u
#define	TIMER2_u8_ENABLE_INTERRUPT		1u

/*            	TIMER FUNCTIONS	PART				*/

typedef enum
{
	Timer_Interrupt_Enable,
	Timer_Interrupt_Disable
}Timer_Interrupt;


typedef enum
{
	NO_CLK_SRC,
	NO_PRESCALAR,
	PRESCALAR_CLK8,
	PRESCALAR_CLK64,
	PRESCALAR_CLK256,
	PRESCALAR_CLK1024,
	EXT_CLK_FALLING=6,
	EXT_CLK_RISING
}Timer_PRESCALAR;

typedef enum
{
 TIMER0_OVF_CALLBACK_INDEX				=0u,
 TIMER0_CTC_CALLBACK_INDEX				=1u,
 TIMER1_OVF_CALLBACK_INDEX				=2u,
 TIMER1_CTC_CHANNEL_A_CALLBACK_INDEX	=3u,
 TIMER1_CTC_CHANNEL_B_CALLBACK_INDEX	=4u,
 TIMER1_INPUT_CAPTURE_CALLBACK_INDEX	=5u,
 TIMER2_OVF_CALLBACK_INDEX				=6u,
 TIMER2_CTC_CALLBACK_INDEX				=7u,
}TIMERS_Int_SRC_t;

/*Input Capture Unit Macros.*/
#define	TIMER1_u8_FALLING_INPUT_CAPTURE		1u
#define	TIMER1_u8_RISING_INPUT_CAPTURE		2u


void TIMER_voidInit(void);
//void TIMER_voidPostInit(const Timer_Configration *  Cpy_Configuration);

uint8 TIMERS_u8SetCallBack(TIMERS_Int_SRC_t Copy_u8TmrIntSource, void (*Copy_pvCallBackFunc)(void));

/*										TIMER0											*/

void TIMER0_voidSetOVFRegister(uint8 Copy_u8Value);
void TIMER0_voidSetCTCRegister(uint8 Copy_u8Value);

void TIMER0_voidEnableOVFINT(void);
void TIMER0_voidDisableOVFINT(void);
void TIMER0_voidClearOVFFlag(void);


void TIMER0_voidEnableCTCINT(void);
void TIMER0_voidDisableCTCINT(void);
void TIMER0_voidClearCTCFlag(void);

void TIMER0_voidForceOutputCompare(void);


/*										TIMER1											*/
void TIMER1_voidSetOVFRegister(uint16 Copy_u16Value);
void TIMER1_voidChannelASetCTCRegister(uint16 Copy_u16Value);
void TIMER1_voidChannelBSetCTCRegister(uint16 Copy_u16Value);
uint16	 TIMER1_u16InputCaptureValue(void);


void TIMER1_voidEnableOVFINT(void);
void TIMER1_voidDisableOVFINT(void);
void TIMER1_voidClearOVFFlag(void);

void TIMER1_voidChannelAEnableCTCINT(void);
void TIMER1_voidChannelADisableCTCINT(void);
void TIMER1_voidChannelAClearCTCFlag(void);

void TIMER1_voidChannelBEnableCTCINT(void);
void TIMER1_voidChannelBDisableCTCINT(void);
void TIMER1_voidChannelBClearCTCFlag(void);

void TIMER1_voidEnableInputCaptureINT(void);
void TIMER1_voidDisableInputCaptureINT(void);
void TIMER1_voidClearInputCaptureFlag(void);

void TIMER1_voidChannelAForceOutputCompare(void);
void TIMER1_voidChannelBForceOutputCompare(void);

Timers_ErrorState_t ICU_u8Timer1SetTriggerSrc(uint8 Copy_u8TriggerSrc);

/*										TIMER2											*/

void TIMER2_voidSetOVFRegister(uint8 Copy_u8Value);
void TIMER2_voidSetCTCRegister(uint8 Copy_u8Value);

void TIMER2_voidEnableOVFINT(void);
void TIMER2_voidDisableOVFINT(void);
void TIMER2_voidClearOVFFlag(void);

void TIMER2_voidEnableCTCINT(void);
void TIMER2_voidDisableCTCINT(void);
void TIMER2_voidClearCTCFlag(void);

void TIMER2_voidForceOutputCompare(void);

#endif
