/*Prebulid*/
/************************************************/
/*                     Name: Ziyad Mohammed     */
/*                     Date: 22/10/2021         */
/*                     SWC: TEMPSENSOR          */
/*                     Version: 1.0             */
/************************************************/

#include "STD_TYPES.h"
#include "BIT_MATH.h"
//MCAL
#include "ADC_interface.h"
#include "ADC_private.h"
#include "ADC_config.h"

u8 TEMPSENSOR_u8GetTempretureValue(u8 Copy_u8ChannelNum,u8 Copy_u8EN_OR_DIS_Conversion,u8 * Copy_pu8ReturnedTempValue)//local temp.
{
	u8 Local_u8ErrorState = STD_TYPES_OK;
	u16 Local_u16DigitalValue , Local_u16AnalogValue;
	if (Copy_pu8ReturnedTempValue != NULL)
	{
		ADC_u8GedDigitalValueSynch(Copy_u8ChannelNum,&Local_u16DigitalValue,Copy_u8EN_OR_DIS_Conversion);

        #if ADC_u8_RIGHT_OR_LEFT_ADJUSTMENT == ADC_u8_RIGHT_ADJUSTMENT
		Local_u16AnalogValue = ((u32)Local_u16DigitalValue * 2560) /1024;
        #elif ADC_u8_RIGHT_OR_LEFT_ADJUSTMENT == ADC_u8_LEFT_ADJUSTMENT
		Local_u16AnalogValue = ((u32)Local_u16DigitalValue * 2560) /256;
        #endif
		Local_u16AnalogValue = Local_u16AnalogValue / 10 ;
		* Copy_pu8ReturnedTempValue=Local_u16AnalogValue;

	}
	else
	{
		Local_u8ErrorState = STD_TYPES_NOK;
	}
	return Local_u8ErrorState;
}
