
/********************************************************************/
/********************************************************************/
/*********************** Author: Ziyad Mohammed   *******************/
/*********************** File  : ADC_CFG.h        *******************/
/*********************** Version: 1.00            *******************/
/********************************************************************/
/********************************************************************/

#ifndef ADC_CFG_H_
#define ADC_CFG_H_

 /**
  * @details configure the reference voltage, Options:
  * 												  1- AREF_REF
  * 												  2- AVCC_REF
  * 												  3- INTERNAL_2560mV_REF
  */

#define ADC_u8REF_VOLT					AVCC_REF

/**
 * @details configure the required ADC resolution, options are:
 * 																1- EIGHT_BITS
 *                                                              2- TEN_BITS
 */

#define ADC_u8RESOLUTION 				EIGHT_BITS


/**
 * @details configure the required ADC Prescaler, options are:
 * 																1- DIVISION_BY_2
																2- DIVISION_BY_4
																3- DIVISION_BY_8
																4- DIVISION_BY_16
																5- DIVISION_BY_32
																6- DIVISION_BY_64
																7- DIVISION_BY_128
 */

#define ADC_u8PRESCALER_VAL			DIVISION_BY_128
/**
 * @details Configure the ADC Auto Trigger source, Options are:
 * 																1- ADC_FREE_RUNNING_MODE
 * 																2- ADC_ANALOG_COMPARATOR
 * 																3- ADC_EXTERNAL_INTERRUPT_REQUEST_0
 * 																4- ADC_TIMER_COUNTER_0_COMPARE_MATCH
 * 																5- ADC_TIMER_COUNTER_0_OVERFLOW
 * 																6- ADC_ADC_TIMER_COUNTER_0_COMPARE_MATCH_B
 * 																7- ADC_TIMER_COUNTER_1_OVERFLOW
 * 																8- ADC_TIMER_COUNTER_1_CAPURE_EVENT
 */
#define ADC_u8TRIGGER_SOURCE		ADC_FREE_RUNNING_MODE

#define ADC_u32TIME_OUT_CONFIG		50000u

#endif
