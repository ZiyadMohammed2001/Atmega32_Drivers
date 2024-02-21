/********************************************************************/
/********************************************************************/
/*********************** Author: Ziyad Mohammed   *******************/
/*********************** File  : LED_cfg.h        *******************/
/*********************** Version: 1.00            *******************/
/********************************************************************/
/********************************************************************/

#include "STD_TYPES.h"

#include "DIO_interface.h"

#include "LED_cfg.h"
#include "LED_prv.h"
#include "LED_interface.h"


static DIO_SetPinValueErrorState_t Local_u8DIOErrorState = DIO_SET_VALUE_WAIT;

LED_ACTIVE_ERROR_t LED_u8SetLEDON(uint8 Copy_u8ActiveMode,uint8 Copy_u8Port,uint8 Copy_u8Pin)
{
	LED_ACTIVE_ERROR_t local_u8_ErrorState = LED_ACTIVE_INCORRECT;

	switch (Copy_u8ActiveMode)
	{
	case LED_ACTIVE_LOW :
		Local_u8DIOErrorState = DIO_u8SetPinValue(Copy_u8Port,Copy_u8Pin,LED_ACTIVE_LOW_PRV);
		if (DIO_SET_VALUE_PORT_SUCESS == Local_u8DIOErrorState)
		{
			local_u8_ErrorState = LED_ACTIVE_CORRECT;
			Local_u8DIOErrorState = DIO_SET_VALUE_WAIT;
		}
		break;
	case LED_ACTIVE_HIGH:
		Local_u8DIOErrorState = DIO_u8SetPinValue(Copy_u8Port,Copy_u8Pin,LED_ACTIVE_HIGH_PRV);
		if (DIO_SET_VALUE_PORT_SUCESS == Local_u8DIOErrorState)
		{
			local_u8_ErrorState = LED_ACTIVE_CORRECT;
			Local_u8DIOErrorState = DIO_SET_VALUE_WAIT;
		}
	break;
	default:
		local_u8_ErrorState = LED_ACTIVE_INCORRECT;
	}
	return local_u8_ErrorState;
}
LED_ACTIVE_ERROR_t LED_u8SetLEDOFF(uint8 Copy_u8ActiveMode,uint8 Copy_u8Port,uint8 Copy_u8Pin)
{
	LED_ACTIVE_ERROR_t local_u8_ErrorState = LED_ACTIVE_INCORRECT;
	switch (Copy_u8ActiveMode)
	{
	case LED_ACTIVE_LOW :
		Local_u8DIOErrorState = DIO_u8SetPinValue(Copy_u8Port,Copy_u8Pin,LED_ACTIVE_HIGH_PRV);
		if (DIO_SET_VALUE_PORT_SUCESS == Local_u8DIOErrorState)
		{
			local_u8_ErrorState = LED_ACTIVE_CORRECT;
			Local_u8DIOErrorState = DIO_SET_VALUE_WAIT;
		}
		break;
	case LED_ACTIVE_HIGH:
		Local_u8DIOErrorState = DIO_u8SetPinValue(Copy_u8Port,Copy_u8Pin,LED_ACTIVE_LOW_PRV);
		if (DIO_SET_VALUE_PORT_SUCESS == Local_u8DIOErrorState)
		{
			local_u8_ErrorState = LED_ACTIVE_CORRECT;
			Local_u8DIOErrorState = DIO_SET_VALUE_WAIT;
		}
	break;
	default:
		local_u8_ErrorState = LED_ACTIVE_INCORRECT;
	}
	return local_u8_ErrorState;
}
