/********************************************************************/
/********************************************************************/
/*********************** Author: Ziyad Mohammed   *******************/
/*********************** File  : KPD_cfg.h        *******************/
/*********************** Version: 1.00            *******************/
/********************************************************************/
/********************************************************************/

#include "STD_TYPES.h"

#include "DIO_interface.h"

#include "KPD_cfg.h"
#include "KPD_prv.h"
#include "KPD_interface.h"

/*Required:
 *	1-	All RoW Pins are input pulled up
 *	2-	All Column pins are output high. */

uint8 KPD_u8GetPressedKey(uint8*Copy_Pu8PressedKey)
{
	NULL_PTR_Error_State_t Local_u8ErrorState = NULL_PTR_ERR;
	uint8 Local_u8RowCounter =0;
	uint8 Local_u8ColCounter =0;
	uint8 Local_u8KeyState =0;
	static uint8 Local_u8ColArr[KPD_u8COL_NUM]={KPD_u8COL1_PIN,KPD_u8COL2_PIN,KPD_u8COL3_PIN,KPD_u8COL4_PIN};
	static uint8 Local_u8RowArr[KPD_u8ROW_NUM]={KPD_u8ROW1_PIN,KPD_u8ROW2_PIN,KPD_u8ROW3_PIN,KPD_u8ROW4_PIN};
	static uint8 Local_u8KPDArr[KPD_u8ROW_NUM][KPD_u8COL_NUM] = KPD_u8Button_ARR;

	if(NULL_PTR_ERR !=Copy_Pu8PressedKey)
	{
		Local_u8ErrorState = NULL_PTR_SUCESS;
		*Copy_Pu8PressedKey = KPD_u8NO_PRESSED_KEY_VAL;
		/*Activate column Pins and read the rows.*/
		for (Local_u8ColCounter = 0; Local_u8ColCounter < KPD_u8COL_NUM; Local_u8ColCounter++)
		{
			/*Activate the current column.*/
			DIO_u8SetPinValue(KPD_u8_COL_PORT,Local_u8ColArr[Local_u8ColCounter],DIO_u8_PIN_LOW);
			for (Local_u8RowCounter = 0; Local_u8RowCounter < KPD_u8ROW_NUM; Local_u8RowCounter++)
			{
				/*Read the current row.*/
				DIO_u8GetPinValue(KPD_u8ROW_PORT,Local_u8RowArr[Local_u8RowCounter],&Local_u8KeyState);
				/*if current row is low, button is pressed.*/
				if (Local_u8KeyState == DIO_u8_PIN_LOW)
				{
					*Copy_Pu8PressedKey= Local_u8KPDArr[Local_u8RowCounter][Local_u8ColCounter];

					/*Wait until Key is released*/
					while (Local_u8KeyState == DIO_u8_PIN_LOW)
					{
						DIO_u8GetPinValue(KPD_u8ROW_PORT,Local_u8RowArr[Local_u8RowCounter],&Local_u8KeyState);
					}
					return Local_u8ErrorState ;
				}
			}
			/*Deactivate the current column.*/
			DIO_u8SetPinValue(KPD_u8_COL_PORT,Local_u8ColArr[Local_u8ColCounter],DIO_u8_PIN_HIGH);
		}
	}
	else
	{
		Local_u8ErrorState = NULL_PTR_ERR;
	}
	return Local_u8ErrorState;
}
