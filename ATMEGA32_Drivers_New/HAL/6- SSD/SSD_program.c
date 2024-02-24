
/********************************************************************/
/********************************************************************/
/*********************** Author: Ziyad Mohammed   *******************/
/*********************** File  : SSD_Program.c    *******************/
/*********************** Version: 1.00            *******************/
/********************************************************************/
/********************************************************************/

#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "DEFINES.h"

#include "DIO_interface.h"
#include "DIO_cfg.h"

#include "SSD_interface.h"
#include "SSD_prv.h"


uint8 SSD_Arr[] = {SSD_ZERO,SSD_ONE,SSD_TWO,SSD_THEE,SSD_FOUR,SSD_FIVE,SSD_SIX,SSD_SEVEN,SSD_EIGHT,SSD_NINE};

SSD_ErrorStates_t SSD_u8SetNumber(SSD_t const *Copy_stSSD, uint8 Copy_u8Number)
{
	SSD_ErrorStates_t Local_u8Error = SSD_OK;

	if (Copy_stSSD == NULL)
	{
		Local_u8Error = SSD_PTR_ERROR;
	}
	else
	{
		uint8 Local_u8NumberToArrIndex;
		uint8 Local_u8Counter;

		Local_u8NumberToArrIndex = SSD_Arr[Copy_u8Number];
		switch(Copy_stSSD->SSD_Type)
		{
		case SSD_Anode:
			DIO_u8SetPinValue(Copy_stSSD->u8EnablePort, Copy_stSSD->u8EnablePin, DIO_u8_PIN_HIGH);
			if (Copy_stSSD->u8FirstLedPin == DIO_u8PIN0)
			{
				for (Local_u8Counter = 0; Local_u8Counter < 7; Local_u8Counter++)
				{
					DIO_u8SetPinValue(Copy_stSSD->u8Port, Local_u8Counter, ((GET_BIT(Local_u8NumberToArrIndex, Local_u8Counter-1)) ^ 1));
				}
			}
			else if(Copy_stSSD->u8FirstLedPin == DIO_u8PIN1)
			{
				for (Local_u8Counter = 1; Local_u8Counter < 8; Local_u8Counter++)
				{
					DIO_u8SetPinValue(Copy_stSSD->u8Port, Local_u8Counter, ((GET_BIT(Local_u8NumberToArrIndex, Local_u8Counter-1)) ^ 1));
				}
			}
			break;
		case SSD_Cathod:
			DIO_u8SetPinValue(Copy_stSSD->u8EnablePort, Copy_stSSD->u8EnablePin, DIO_u8_PIN_LOW);
			if (Copy_stSSD->u8FirstLedPin == DIO_u8PIN0)
			{
				for (Local_u8Counter = 0; Local_u8Counter < 7; Local_u8Counter++)
				{
					DIO_u8SetPinValue(Copy_stSSD->u8Port, Local_u8Counter, (GET_BIT(Local_u8NumberToArrIndex, Local_u8Counter)));
				}
			}
			else if(Copy_stSSD->u8FirstLedPin == DIO_u8PIN1)
			{
				for (Local_u8Counter = 1; Local_u8Counter < 8; Local_u8Counter++)
				{
					DIO_u8SetPinValue(Copy_stSSD->u8Port, Local_u8Counter, (GET_BIT(Local_u8NumberToArrIndex, Local_u8Counter -1)));
				}
			}
			break;
		case SSD_FtKat:
			DIO_u8SetPinValue(Copy_stSSD->u8EnablePort, Copy_stSSD->u8EnablePin, DIO_u8_PIN_HIGH);
			for (Local_u8Counter = 1; Local_u8Counter < 8; Local_u8Counter++)
			{
				DIO_u8SetPinValue(Copy_stSSD->u8Port, Local_u8Counter, (GET_BIT(Local_u8NumberToArrIndex, Local_u8Counter -1)));
			}
			break;
		default:
			Local_u8Error = SSD_WRONG_CONFIGURATION;
		}
	}
	return Local_u8Error;
}

SSD_ErrorStates_t SSD_EnableDotLED(SSDDotLED_t const * Copy_SSDDotLED)
{
	SSD_ErrorStates_t Local_u8Error = SSD_OK;
	if(NULL != Copy_SSDDotLED)
	{
		switch(Copy_SSDDotLED ->SSD_Type)
		{
		case SSD_Anode:
			DIO_u8SetPinValue(Copy_SSDDotLED->u8Port, Copy_SSDDotLED->u8Pin, DIO_u8_PIN_LOW);
			break;
		case SSD_Cathod:
			DIO_u8SetPinValue(Copy_SSDDotLED->u8Port, Copy_SSDDotLED->u8Pin, DIO_u8_PIN_HIGH);
			break;
		default:
			Local_u8Error = SSD_WRONG_CONFIGURATION;
		}
	}
	else
	{
		Local_u8Error = SSD_PTR_ERROR;
	}
	return Local_u8Error;
}

SSD_ErrorStates_t SSD_DisableDotLED(SSDDotLED_t const * Copy_SSDDotLED)
{
	SSD_ErrorStates_t Local_u8Error = SSD_OK;
	if(NULL != Copy_SSDDotLED)
	{
		switch(Copy_SSDDotLED ->SSD_Type)
		{
		case SSD_Anode:
			DIO_u8SetPinValue(Copy_SSDDotLED->u8Port, Copy_SSDDotLED->u8Pin, DIO_u8_PIN_HIGH);
			break;
		case SSD_Cathod:
			DIO_u8SetPinValue(Copy_SSDDotLED->u8Port, Copy_SSDDotLED->u8Pin, DIO_u8_PIN_LOW);
			break;
		default:
			Local_u8Error = SSD_WRONG_CONFIGURATION;
		}
	}
	else
	{
		Local_u8Error = SSD_PTR_ERROR;
	}
	return Local_u8Error;
}

