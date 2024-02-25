
/********************************************************************/
/********************************************************************/
/*********************** Author: Ziyad Mohammed   *******************/
/*********************** File  : TIMERS_PRV.h     *******************/
/*********************** Version: 1.00            *******************/
/********************************************************************/
/********************************************************************/

#ifndef TIMERS_PRV_H_
#define TIMERS_PRV_H_


typedef enum
{
	TMR_OK = 0,
	TMR_NOK = 1,
	TMR_PTR_ERROR=2,
}Timer_Error_t;

#define TIMER0_ENABLE					1u
#define TIMER0_DISABLE					0u

#define TIMER1_ENABLE					1u
#define TIMER1_DISABLE					2u
#define TIMER1_CHANNEL_A_ENABLE			3u
#define TIMER1_CHANNEL_A_DISABLE		4u
#define TIMER1_CHANNEL_B_ENABLE			5u
#define TIMER1_CHANNEL_B_DISABLE		6u

/*Input Capture Unit Interrupt State. */
#define ICU_TIMER1_U8_INT_DISABLE		2u
#define ICU_TIMER1_U8_INT_ENABLE		3u

#define TIMER2_ENABLE					1u
#define TIMER2_DISABLE					0u

typedef enum
{
	TIMER1_ICU_TRIGGER_SOURCE_OK=0u,
	TIMER1_ICU_TRIGGER_SOURCE_ERROR=1u,
	TIMER1_ICU_TRIGGER_SOURCE_INTERRUPT_TRIGGER_ERROR = 2u,
}Timers_ErrorState_t;

void __vector_4(void) __attribute__((signal));
void __vector_5(void) __attribute__((signal));
void __vector_6(void) __attribute__((signal));
void __vector_7(void) __attribute__((signal));
void __vector_8(void) __attribute__((signal));
void __vector_9(void) __attribute__((signal));
void __vector_10(void) __attribute__((signal));
void __vector_11(void) __attribute__((signal));

#endif
