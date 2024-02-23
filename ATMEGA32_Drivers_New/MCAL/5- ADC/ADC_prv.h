
/********************************************************************/
/********************************************************************/
/*********************** Author: Ziyad Mohammed   *******************/
/*********************** File  : ADC_PRV.h        *******************/
/*********************** Version: 1.00            *******************/
/********************************************************************/
/********************************************************************/

#ifndef ADC_PRV_H_
#define ADC_PRV_H_

/*Macros for reference voltage*/
#define AREF_REF					1u
#define AVCC_REF					2u
#define INTERNAL_2560mV_REF			3u

/*Macros for Resolution*/
#define EIGHT_BITS					1u
#define TEN_BITS					2u

/*Macros for prescaler*/
#define DIVISION_BY_2 				1u
#define DIVISION_BY_4 				2u
#define DIVISION_BY_8 				3u
#define DIVISION_BY_16 				4u
#define DIVISION_BY_32 				5u
#define DIVISION_BY_64 				6u
#define DIVISION_BY_128 			7u

#define ADC_ADCSRA_PRESCALLER_MASKING	0b11111000u

/*Macros For Trigger Source.*/
#define	ADC_FREE_RUNNING_MODE						0u
#define	ADC_ANALOG_COMPARATOR						1u
#define	ADC_EXTERNAL_INTERRUPT_REQUEST_0			2u
#define	ADC_TIMER_COUNTER_0_COMPARE_MATCH			3u
#define	ADC_TIMER_COUNTER_0_OVERFLOW				4u
#define	ADC_ADC_TIMER_COUNTER_0_COMPARE_MATCH_B		5u
#define	ADC_TIMER_COUNTER_1_OVERFLOW				6u
#define	ADC_TIMER_COUNTER_1_CAPURE_EVENT			7u

#define ADC_SFIOR_TRIGGERSOURCE_MASKING			0b00011111u

#define ADC_ADMUX_ANALOG_CHANNLE_MASKING		0b11100000u

#define ADC_SINGLE_CONV_ASYNCH						0u
#define ADC_CHAIN_CONV_ASYNCH						1u

typedef enum ADC_Error
{
	ADC_CHANNEL_OK=0u,
	ADC_CHANNEL_NOK=1u,
	ADC_PTR_ERROR=2u,
	ADC_TIME_OUT=3u,
	ADC_BUSY=4u,
}ADC_Error_t;

/* Lock Shared Resources*/
#define ADC_IDLE			1u
#define ADC_BUZY			0u


#endif
