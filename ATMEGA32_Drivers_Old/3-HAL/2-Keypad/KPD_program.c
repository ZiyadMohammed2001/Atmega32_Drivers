/************************************************/
/*                     Name: Ziyad Mohammed     */
/*                     Date: 2/10/2021          */
/*                     SWC: LCD                 */
/*                     Version: 1.0             */
/************************************************/
/*LIB Layer*/
#include"STD_TYPES.h"
#include "BIT_MATH.h"
#define F_CPU  8000000UL
#include <avr/delay.h>

/*MCAL*/
#include "DIO_interface.h"

/*HAL*/
#include "KPD_interface.h"
#include "KPD_private.h"
#include "KPD_config.h"

static u8 KPD_Au8RowPins[4]      = {KPD_u8_R1_PIN,KPD_u8_R2_PIN,KPD_u8_R3_PIN,KPD_u8_R4_PIN};
static u8 KPD_Au8RowPorts[4]     = {KPD_u8_R1_PORT,KPD_u8_R2_PORT,KPD_u8_R3_PORT,KPD_u8_R4_PORT};

static u8 KPD_Au8ColumnsPins[4]  = {KPD_u8_C1_PIN,KPD_u8_C2_PIN,KPD_u8_C3_PIN,KPD_u8_C4_PIN};
static u8 KPD_Au8ColumnsPorts[4] = {KPD_u8_C1_PORT,KPD_u8_C2_PORT,KPD_u8_C3_PORT,KPD_u8_C4_PORT};

static u8 KPD_Au8Keys[4][4] = KPD_KEYS ;

u8 KPD_u8GetKey(u8 * Copy_pu8RetutnKey)
{
	u8 Local_u8ErrorState = STD_TYPES_OK;
	u8 Local_u8RowCounter , Local_u8ColumnCounter , Local_u8PinValue , Local_u8Flag=0;
	if (Copy_pu8RetutnKey!= NULL)
	{
		/* Apply KPD Algo*/
		*Copy_pu8RetutnKey = KPD_u8_KEY_NOT_PRESSED;
		/* Activate Each row then Check The Columns */
		for(Local_u8RowCounter=0 ; Local_u8RowCounter < 4 ; Local_u8RowCounter++)
		{
			//Activate The Row.
			DIO_u8SetPinValue(KPD_Au8RowPorts[Local_u8RowCounter],KPD_Au8RowPins[Local_u8RowCounter],DIO_u8_LOW);
			//Nested loop.
			for(Local_u8ColumnCounter = 0 ; Local_u8ColumnCounter < 4 ; Local_u8ColumnCounter ++)
			{
				//Check Columns VALUES.
				DIO_u8GetPinValue(KPD_Au8ColumnsPorts[Local_u8ColumnCounter],KPD_Au8ColumnsPins[Local_u8ColumnCounter],&Local_u8PinValue);
				//Check if pin value is low.
				if(Local_u8PinValue==DIO_u8_LOW)
				{
					// Key pressed.
					// Debouncing
					_delay_ms(30);
					// wait for Pin goes High
					while(Local_u8PinValue == DIO_u8_LOW)
					{
						DIO_u8GetPinValue(KPD_Au8ColumnsPorts[Local_u8ColumnCounter],KPD_Au8ColumnsPins[Local_u8ColumnCounter],&Local_u8PinValue);
					}
					/* Return Key Value */
					*Copy_pu8RetutnKey = KPD_Au8Keys[Local_u8RowCounter][Local_u8ColumnCounter];
					/* Terminate Columns Loop*/
					//flag.
					Local_u8Flag = 1;
					break;
				}
			}
			/* Deactivate the Row*/
			DIO_u8SetPinValue(KPD_Au8RowPorts[Local_u8RowCounter],KPD_Au8RowPins[Local_u8RowCounter],DIO_u8_HIGH);
			if (Local_u8Flag != 0)
			{
				break;
			}
		}
	}
	else
	{
		Local_u8ErrorState = STD_TYPES_NOK;
	}
	/*Apply Keypad Algorithm */
	/*Activate Each Row Then Check The Columns */

	return Local_u8ErrorState ;
}
