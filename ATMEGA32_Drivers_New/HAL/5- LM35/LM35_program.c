
/********************************************************************/
/********************************************************************/
/*********************** Author: Ziyad Mohammed   *******************/
/*********************** File  : LM35_Program.c   *******************/
/*********************** Version: 1.00            *******************/
/********************************************************************/
/********************************************************************/

#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "DEFINES.h"

#include "ADC_interface.h"
#include "ADC_cfg.h"

#include "LM35_interface.h"
#include "LM35_prv.h"

uint8 LM35_u8GetTemp(uint8 Copy_u8Channel,uint8* Copy_pu8Temp)
{
	uint8 Local_u8LM35_LocalErrorState = LM35_OK;
	uint16 Local_u16_ADCReading;
	if(NULL_PTR_ERR != Copy_pu8Temp)
	{
		/*Check ADC Error State*/
		Local_u8LM35_LocalErrorState = ADC_u16GetChannelReading(Copy_u8Channel,&Local_u16_ADCReading);
		if (ADC_CHANNEL_OK == Local_u8LM35_LocalErrorState)
		{
#if ADC_u8RESOLUTION == EIGHT_BITS
			* Copy_pu8Temp = (uint8)(((uint32)Local_u16_ADCReading * 500UL)/256UL);
#elif ADC_u8RESOLUTION == TEN_BITS
			* Copy_pu8Temp = (uint8)(((uint32)Local_u16_ADCReading * 500UL)/1024UL);
#endif
		}
		else
		{
			Local_u8LM35_LocalErrorState = ADC_CHANNEL_NOK;
		}
	}
	else
	{
		Local_u8LM35_LocalErrorState = LM35_NULL_PTR_ERROR;
	}
	return Local_u8LM35_LocalErrorState;
}

