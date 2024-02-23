
/********************************************************************/
/********************************************************************/
/*********************** Author: Ziyad Mohammed   *******************/
/*********************** File  : ADC_Interface.h  *******************/
/*********************** Version: 1.00            *******************/
/********************************************************************/
/********************************************************************/

#ifndef ADC_INTERFACE_H_
#define ADC_INTERFACE_H_
#include "ADC_prv.h"
/*Selecting Channel*/
typedef enum
{
	ADC_SINGLE_ENDED_CH0 = 0,
	ADC_SINGLE_ENDED_CH1,
	ADC_SINGLE_ENDED_CH2,
	ADC_SINGLE_ENDED_CH3,
	ADC_SINGLE_ENDED_CH4,
	ADC_SINGLE_ENDED_CH5,
	ADC_SINGLE_ENDED_CH6,
	ADC_SINGLE_ENDED_CH7,
	ADC_DIFFERENTIAL_ADC0_ADC0_10X,
	ADC_DIFFERENTIAL_ADC1_ADC0_10X,
	ADC_DIFFERENTIAL_ADC0_ADC0_200X,
	ADC_DIFFERENTIAL_ADC1_ADC0_200X,
	ADC_DIFFERENTIAL_ADC2_ADC2_10X,
	ADC_DIFFERENTIAL_ADC3_ADC2_10X,
	ADC_DIFFERENTIAL_ADC2_ADC2_200X,
	ADC_DIFFERENTIAL_ADC3_ADC2_200X,
	ADC_DIFFERENTIAL_ADC0_ADC1_1X,
	ADC_DIFFERENTIAL_ADC1_ADC1_1X,
	ADC_DIFFERENTIAL_ADC2_ADC1_1X,
	ADC_DIFFERENTIAL_ADC3_ADC1_1X,
	ADC_DIFFERENTIAL_ADC4_ADC1_1X,
	ADC_DIFFERENTIAL_ADC5_ADC1_1X,
	ADC_DIFFERENTIAL_ADC6_ADC1_1X,
	ADC_DIFFERENTIAL_ADC7_ADC1_1X,
	ADC_DIFFERENTIAL_ADC0_ADC2_1X,
	ADC_DIFFERENTIAL_ADC1_ADC2_1X,
	ADC_DIFFERENTIAL_ADC2_ADC2_1X,
	ADC_DIFFERENTIAL_ADC3_ADC2_1X,
	ADC_DIFFERENTIAL_ADC4_ADC2_1X,
	ADC_DIFFERENTIAL_ADC5_ADC2_1X,
	ADC_SINGLE_ENDED_1_22_VOLT,
	ADC_SINGLE_ENDED_0_VOLT,
}ADC_Channel_t;

typedef struct
{
	uint8 ChainSize;
	uint8* ChainArr;
	void(*NotificationFunc)(void);
	uint16* ResultArr;
}ADC_ChainConv_t;

/**
 * @Details: ADC Function Init.
 */
void ADC_voidInit(void);

/**
 * @Details ADC_u16StartConversionSynch to start conversion synchronous.
 * @param Copy_u8Channel for channel Number.
 * @param Copy_pu16ADC_Data	For Results.
 * @return Error State.
 */

ADC_Error_t ADC_u16StartConversionSynch(uint8 Copy_u8Channel, uint16*Copy_pu16ADC_Data);

/**
 * @Details ADC_u16StartSingleConversionASynch to start conversion Asynchronous.
 * @param Copy_u8Channel for channel Number.
 * @param Copy_pu16ADC_Data	For Results.
 * @return Error State.
 */
ADC_Error_t ADC_u16StartSingleConversionASynch(uint8 Copy_u8Channel, uint16*Copy_pu16ADC_Data, void(*Copy_pvNotificatiobFunc)(void));

/**
 * @Details ADC_u8StartChainConvertersionAsynch to chart chin converter Asynchronous.
 * @param Copy_pstChain
 * @return
 */
ADC_Error_t ADC_u8StartChainConvertersionAsynch(ADC_ChainConv_t* Copy_pstChain);

#endif
