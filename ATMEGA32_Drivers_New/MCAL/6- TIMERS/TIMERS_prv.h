
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

/*			TIMER1 Mode					*/
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

/*Input Capture Unit Interrupt State. */
#define ICU_TIMER1_U8_INT_DISABLE		2u
#define ICU_TIMER1_U8_INT_ENABLE		3u

#define TIMER1_u8_OC1_DISCONNECTED		1u			/*(Normal port operation, OC1A/OC1B disconnected)             */
#define TIMER1_u8_OC1_TOGGLE			2u			/*(Toggle OC1A/OC1B on compare match)                         */
#define TIMER1_u8_OC1_CLEAR				3u			/*(Clear OC1A/OC1B on compare match (Set output to low level))*/
#define TIMER1_u8_OC1_SET				4u			/*(Set OC1A/OC1B on compare match (Set output to high level)) */


#define TIMER2_ENABLE					1u
#define TIMER2_DISABLE					0u

typedef enum
{
	TIMER1_ICU_TRIGGER_SOURCE_OK=0u,
	TIMER1_ICU_TRIGGER_SOURCE_ERROR=1u,
	TIMER1_ICU_TRIGGER_SOURCE_INTERRUPT_TRIGGER_ERROR = 2u,
}Timers_ErrorState_t;

#endif
