#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "DEFINES.h"

#include "DIO_cfg.h"
#include "DIO_interface.h"
#include "DIO_prv.h"
#include "DIO_reg.h"


DIO_SetPinDirectionErrorState_t DIO_u8SetPinDirection(DIO_Port_t Copy_u8Port, DIO_PIN_Num_t Copy_u8PinNum, DIO_Pin_Direction_t Copy_u8Direction)
{
	DIO_SetPinDirectionErrorState_t Local_u8ErrorState = DIO_SET_DIRECTION_WAIT;
	if((Copy_u8PinNum >= DIO_u8PIN0) && (Copy_u8PinNum<=DIO_u8PIN7))
	{
		Local_u8ErrorState = DIO_SET_DIRECTION_PIN_NUM_SUCESS;
		if(DIO_u8_PIN_INPUT == Copy_u8Direction)
		{
			Local_u8ErrorState = DIO_SET_DIRECTION_PORT_DIRECTION_SUCESS;
			switch (Copy_u8Port)
			{
			case DIO_u8PORTA:
				Local_u8ErrorState = DIO_SET_DIRECTION_PORT_SUCESS;
				CLR_BIT(DIO_DDRA,Copy_u8PinNum);
				break;
			case DIO_u8PORTB:
				Local_u8ErrorState = DIO_SET_DIRECTION_PORT_SUCESS;
				CLR_BIT(DIO_DDRB,Copy_u8PinNum);
				break;
			case DIO_u8PORTC:
				Local_u8ErrorState = DIO_SET_DIRECTION_PORT_SUCESS;
				CLR_BIT(DIO_DDRC,Copy_u8PinNum);
				break;
			case DIO_u8PORTD:
				Local_u8ErrorState = DIO_SET_DIRECTION_PORT_SUCESS;
				CLR_BIT(DIO_DDRD,Copy_u8PinNum);
				break;
			default:
				Local_u8ErrorState = DIO_SET_DIRECTION_PORT_FAIL;
				break;
			}
		}
		else if (DIO_u8_PIN_OUTPUT == Copy_u8Direction)
		{
			Local_u8ErrorState = DIO_SET_DIRECTION_PORT_DIRECTION_SUCESS;
			switch (Copy_u8Port)
			{
			case DIO_u8PORTA:
				Local_u8ErrorState = DIO_SET_DIRECTION_PORT_SUCESS;
				SET_BIT(DIO_DDRA,Copy_u8PinNum);
				break;
			case DIO_u8PORTB:
				Local_u8ErrorState = DIO_SET_DIRECTION_PORT_SUCESS;
				SET_BIT(DIO_DDRB,Copy_u8PinNum);
				break;
			case DIO_u8PORTC:
				Local_u8ErrorState = DIO_SET_DIRECTION_PORT_SUCESS;
				SET_BIT(DIO_DDRC,Copy_u8PinNum);
				break;
			case DIO_u8PORTD:
				Local_u8ErrorState = DIO_SET_DIRECTION_PORT_SUCESS;
				SET_BIT(DIO_DDRD,Copy_u8PinNum);
				break;
			default:
				Local_u8ErrorState = DIO_SET_DIRECTION_PORT_FAIL;
				break;
			}
		}
		else
		{
			Local_u8ErrorState = DIO_SET_DIRECTION_PORT_DIRECTION_FAIL;
		}
	}
	else
	{
		Local_u8ErrorState = DIO_SET_DIRECTION_PIN_NUM_FAIL;
	}
	return Local_u8ErrorState;
}

DIO_SetPinValueErrorState_t DIO_u8SetPinValue(DIO_Port_t Copy_u8Port, DIO_PIN_Num_t Copy_u8PinNum, DIO_Pin_Value_t Copy_u8Value)
{
	DIO_SetPinValueErrorState_t Local_u8ErrorState = DIO_SET_VALUE_WAIT;
	if((Copy_u8PinNum >= DIO_u8PIN0) && (Copy_u8PinNum<=DIO_u8PIN7))
	{
		Local_u8ErrorState = DIO_SET_VALUE_PIN_NUM_SUCESS;
		if(DIO_u8_PIN_LOW == Copy_u8Value)
		{
			Local_u8ErrorState = DIO_SET_VALUE_PORT_VALUE_SUCESS;
			switch (Copy_u8Port)
			{
			case DIO_u8PORTA:
				Local_u8ErrorState = DIO_SET_VALUE_PORT_SUCESS;
				CLR_BIT(DIO_PORTA,Copy_u8PinNum);
				break;
			case DIO_u8PORTB:
				Local_u8ErrorState = DIO_SET_VALUE_PORT_SUCESS;
				CLR_BIT(DIO_PORTB,Copy_u8PinNum);
				break;
			case DIO_u8PORTC:
				Local_u8ErrorState = DIO_SET_VALUE_PORT_SUCESS;
				CLR_BIT(DIO_PORTC,Copy_u8PinNum);
				break;
			case DIO_u8PORTD:
				Local_u8ErrorState = DIO_SET_VALUE_PORT_SUCESS;
				CLR_BIT(DIO_PORTD,Copy_u8PinNum);
				break;
			default:
				Local_u8ErrorState = DIO_SET_VALUE_PORT_FAIL;
				break;
			}
		}
		else if (DIO_u8_PIN_HIGH == Copy_u8Value)
		{
			Local_u8ErrorState = DIO_SET_VALUE_PORT_VALUE_SUCESS;
			switch (Copy_u8Port)
			{
			case DIO_u8PORTA:
				Local_u8ErrorState = DIO_SET_VALUE_PORT_SUCESS;
				SET_BIT(DIO_PORTA,Copy_u8PinNum);
				break;
			case DIO_u8PORTB:
				Local_u8ErrorState = DIO_SET_VALUE_PORT_SUCESS;
				SET_BIT(DIO_PORTB,Copy_u8PinNum);
				break;
			case DIO_u8PORTC:
				Local_u8ErrorState = DIO_SET_VALUE_PORT_SUCESS;
				SET_BIT(DIO_PORTC,Copy_u8PinNum);
				break;
			case DIO_u8PORTD:
				Local_u8ErrorState = DIO_SET_VALUE_PORT_SUCESS;
				SET_BIT(DIO_PORTD,Copy_u8PinNum);
				break;
			default:
				Local_u8ErrorState = DIO_SET_VALUE_PORT_FAIL;
				break;
			}
		}
		else
		{
			Local_u8ErrorState = DIO_SET_VALUE_PORT_VALUE_FAIL;
		}
	}
	else
	{
		Local_u8ErrorState = DIO_SET_VALUE_PIN_NUM_FAIL;
	}
	return Local_u8ErrorState;
}

DIO_TogglePinValueErrorState_t DIO_u8TogglePinValue(DIO_Port_t Copy_u8Port, DIO_PIN_Num_t Copy_u8PinNum)
{
	DIO_TogglePinValueErrorState_t Local_u8ErrorState = DIO_TOGGLE_VALUE_WAIT;
	if((Copy_u8PinNum >= DIO_u8PIN0) && (Copy_u8PinNum<=DIO_u8PIN7))
	{
		Local_u8ErrorState = DIO_TOGGLE_VALUE_PIN_NUM_SUCESS;
		switch (Copy_u8Port)
		{
		case DIO_u8PORTA:
			Local_u8ErrorState = DIO_TOGGLE_VALUE_PORT_SUCESS;
			TOG_BIT(DIO_PORTA,Copy_u8PinNum);
			break;
		case DIO_u8PORTB:
			Local_u8ErrorState = DIO_TOGGLE_VALUE_PORT_SUCESS;
			TOG_BIT(DIO_PORTB,Copy_u8PinNum);
			break;
		case DIO_u8PORTC:
			Local_u8ErrorState = DIO_TOGGLE_VALUE_PORT_SUCESS;
			TOG_BIT(DIO_PORTC,Copy_u8PinNum);
			break;
		case DIO_u8PORTD:
			Local_u8ErrorState = DIO_TOGGLE_VALUE_PORT_SUCESS;
			TOG_BIT(DIO_PORTD,Copy_u8PinNum);
			break;
		default:
			Local_u8ErrorState = DIO_TOGGLE_VALUE_PORT_FAIL;
			break;
		}
	}
	else
	{
		Local_u8ErrorState = DIO_TOGGLE_VALUE_PIN_NUM_FAIL;
	}
	return Local_u8ErrorState;
}

DIO_GetPinValueErrorState_t DIO_u8GetPinValue(DIO_Port_t Copy_u8Port, DIO_PIN_Num_t Copy_u8PinNum, DIO_Pin_Value_t *Copy_pu8Value)
{
	DIO_GetPinValueErrorState_t Local_u8ErrorState = DIO_GET_VALUE_WAIT;
	if((Copy_u8PinNum >= DIO_u8PIN0) && (Copy_u8PinNum<=DIO_u8PIN7))
	{
		Local_u8ErrorState = DIO_GET_VALUE_PIN_NUM_SUCESS;
		if(NULL_PTR_ERR != Copy_pu8Value)
		{
			Local_u8ErrorState = DIO_GET_VALUE_PORT_VALUE_SUCESS;
			switch (Copy_u8Port)
			{
			case DIO_u8PORTA:
				Local_u8ErrorState = DIO_GET_VALUE_PORT_SUCESS;
				*Copy_pu8Value = GET_BIT(DIO_PINA,Copy_u8PinNum);
				break;
			case DIO_u8PORTB:
				Local_u8ErrorState = DIO_GET_VALUE_PORT_SUCESS;
				*Copy_pu8Value = GET_BIT(DIO_PINB,Copy_u8PinNum);
				break;
			case DIO_u8PORTC:
				Local_u8ErrorState = DIO_GET_VALUE_PORT_SUCESS;
				*Copy_pu8Value = GET_BIT(DIO_PINC,Copy_u8PinNum);
				break;
			case DIO_u8PORTD:
				Local_u8ErrorState = DIO_GET_VALUE_PORT_SUCESS;
				*Copy_pu8Value = GET_BIT(DIO_PIND,Copy_u8PinNum);
				break;
			default:
				Local_u8ErrorState = DIO_GET_VALUE_PORT_FAIL;
				break;
			}
		}
		else
		{
			Local_u8ErrorState = DIO_GET_VALUE_PORT_VALUE_FAIL;
		}
	}
	else
	{
		Local_u8ErrorState = DIO_GET_VALUE_PIN_NUM_FAIL;
	}
	return Local_u8ErrorState;
}

DIO_SetPortDirectionErrorState_t DIO_u8SetPortDirection (DIO_Port_t Copy_u8Port,uint8 Copy_u8Direction)
{
	DIO_SetPortDirectionErrorState_t Local_u8ErrorState = DIO_PORT_SET_DIRECTION_WAIT;
	switch (Copy_u8Port)
	{
	case DIO_u8PORTA:
		Local_u8ErrorState = DIO_PORT_SET_DIRECTION_PORT_SUCESS;
		DIO_DDRA = Copy_u8Direction;
		break;
	case DIO_u8PORTB:
		Local_u8ErrorState = DIO_PORT_SET_DIRECTION_PORT_SUCESS;
		DIO_DDRB = Copy_u8Direction;
		break;
	case DIO_u8PORTC:
		Local_u8ErrorState = DIO_PORT_SET_DIRECTION_PORT_SUCESS;
		DIO_DDRC = Copy_u8Direction;
		break;
	case DIO_u8PORTD:
		Local_u8ErrorState = DIO_PORT_SET_DIRECTION_PORT_SUCESS;
		DIO_DDRD = Copy_u8Direction;
		break;
	default:
		Local_u8ErrorState = DIO_PORT_SET_DIRECTION_PORT_FAIL;
		break;
	}
	return Local_u8ErrorState;
}
DIO_SetPortValueErrorState_t DIO_u8SetPortValue (DIO_Port_t Copy_u8Port,uint8 Copy_u8Value)
{
	DIO_SetPortDirectionErrorState_t Local_u8ErrorState = DIO_PORT_SET_PORT_WAIT;
	switch (Copy_u8Port)
	{
	case DIO_u8PORTA:
		Local_u8ErrorState = DIO_PORT_SET_PORT_PORT_SUCESS;
		DIO_PORTA = Copy_u8Value;
		break;
	case DIO_u8PORTB:
		Local_u8ErrorState = DIO_PORT_SET_PORT_PORT_SUCESS;
		DIO_PORTB = Copy_u8Value;
		break;
	case DIO_u8PORTC:
		Local_u8ErrorState = DIO_PORT_SET_PORT_PORT_SUCESS;
		DIO_PORTC = Copy_u8Value;
		break;
	case DIO_u8PORTD:
		Local_u8ErrorState = DIO_PORT_SET_PORT_PORT_SUCESS;
		DIO_PORTD = Copy_u8Value;
		break;
	default:
		Local_u8ErrorState = DIO_PORT_SET_PORT_PORT_FAIL;
		break;
	}
	return Local_u8ErrorState;
}


DIO_GetPortValueErrorState_t DIO_u8GetPortValue (DIO_Port_t Copy_u8Port,uint8 *Copy_u8Value)
{
	DIO_GetPortValueErrorState_t Local_u8ErrorState = DIO_PORT_GET_PORT_WAIT;
	if(NULL_PTR_ERR != Copy_u8Value)
	{
		Local_u8ErrorState = DIO_PORT_GET_VALUE_SUCESS;
		switch (Copy_u8Port)
		{
		case DIO_u8PORTA:
			Local_u8ErrorState = DIO_PORT_GET_PORT_PORT_SUCESS;
			*Copy_u8Value = DIO_PINA;
			break;
		case DIO_u8PORTB:
			Local_u8ErrorState = DIO_PORT_GET_PORT_PORT_SUCESS;
			*Copy_u8Value = DIO_PINB;
			break;
		case DIO_u8PORTC:
			Local_u8ErrorState = DIO_PORT_GET_PORT_PORT_SUCESS;
			*Copy_u8Value = DIO_PINC;
			break;
		case DIO_u8PORTD:
			Local_u8ErrorState = DIO_PORT_GET_PORT_PORT_SUCESS;
			*Copy_u8Value = DIO_PIND;
			break;
		default:
			Local_u8ErrorState = DIO_PORT_GET_PORT_PORT_FAIL;
			break;
		}
	}
	else
	{
		Local_u8ErrorState = DIO_PORT_GET_VALUE_FAIL;
	}
	return Local_u8ErrorState;
}
