/********************************************************************/
/********************************************************************/
/*********************** Author: Ziyad Mohammed   *******************/
/*********************** File  : SW_cfg.h         *******************/
/*********************** Version: 1.00            *******************/
/********************************************************************/
/********************************************************************/

#include "STD_TYPES.h"

#include "DIO_interface.h"

#include "SW_cfg.h"
#include "SW_prv.h"
#include "SW_interface.h"

SwitchPullTypeError_t Switch_u8GetState(const Switch_Configuration_t* Switch_Configuration, uint8 *Copy_u8SwitchState)
{
	SwitchPullTypeError_t Local_u8ErrorState = SW_Error_Wait;
	DIO_SetPinValueErrorState_t Local_u8DIOErrorState = DIO_SET_VALUE_WAIT;

	if(NULL != Copy_u8SwitchState)
	{
		switch (Switch_Configuration ->Switch_PullType)
		{
		case SWITCH_PULL_UP:
			Local_u8ErrorState = SW_PULL_TYPE_CORRECT;
			Local_u8DIOErrorState = DIO_u8GetPinValue(Switch_Configuration->Switch_Port,Switch_Configuration->Switch_Pin,Copy_u8SwitchState);
			if (DIO_SET_VALUE_PORT_SUCESS == Local_u8DIOErrorState)
			{
				Local_u8DIOErrorState = DIO_SET_VALUE_WAIT;
				/*Continue checks*/
				if(*Copy_u8SwitchState == SW_PULL_UP_PRESSED)
				{
					*Copy_u8SwitchState = SW_PRESSED;
				}
				else
				{
					*Copy_u8SwitchState = SW_NOT_PRESSED;
				}
			}
			break;
		case SWITCH_PULL_DOWN:
			Local_u8ErrorState = SW_PULL_TYPE_CORRECT;
			Local_u8DIOErrorState = DIO_u8GetPinValue(Switch_Configuration->Switch_Port,Switch_Configuration->Switch_Pin,Copy_u8SwitchState);
			if (DIO_SET_VALUE_PORT_SUCESS == Local_u8DIOErrorState)
			{
				Local_u8DIOErrorState = DIO_SET_VALUE_WAIT;
				/*Continue checks*/
				if(*Copy_u8SwitchState == SW_PULL_DOWN_PRESSED)
				{
					*Copy_u8SwitchState = SW_PRESSED;
				}
				else
				{
					*Copy_u8SwitchState = SW_NOT_PRESSED;
				}
			}
			break;
		default:
			Local_u8ErrorState = SW_PULL_TYPE_INCORRECT;
		}
	}
	else
	{
		Local_u8ErrorState = SW_NULL_PTR_ERROR;
	}

	return Local_u8ErrorState;
}
