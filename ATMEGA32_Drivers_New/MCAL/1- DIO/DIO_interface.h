#ifndef DIO_INTERFACE_H_
#define DIO_INTERFACE_H_

#include "DIO_prv.h"
#include "STD_TYPES.h"

typedef enum DIO_Port
{
	DIO_u8PORTA = 0u,
	DIO_u8PORTB = 1u,
	DIO_u8PORTC = 2u,
	DIO_u8PORTD = 3u,
}DIO_Port_t;

typedef enum DIO_PIN_Num
{
	DIO_u8PIN0	=0u,
	DIO_u8PIN1	=1u,
	DIO_u8PIN2	=2u,
	DIO_u8PIN3	=3u,
	DIO_u8PIN4	=4u,
	DIO_u8PIN5	=5u,
	DIO_u8PIN6	=6u,
	DIO_u8PIN7	=7u,
}DIO_PIN_Num_t;

typedef enum DIO_Pin_Direction
{
	DIO_u8_PIN_INPUT 	= 0u,
	DIO_u8_PIN_OUTPUT 	= 1u,
}DIO_Pin_Direction_t;

typedef enum DIO_Pin_Value
{
	DIO_u8_PIN_HIGH = 1u,
	DIO_u8_PIN_LOW	= 0u,
}DIO_Pin_Value_t;

DIO_SetPinDirectionErrorState_t DIO_u8SetPinDirection(DIO_Port_t Copy_u8Port, DIO_PIN_Num_t Copy_u8PinNum, DIO_Pin_Direction_t Copy_u8Direction);

DIO_SetPinValueErrorState_t DIO_u8SetPinValue(DIO_Port_t Copy_u8Port, DIO_PIN_Num_t Copy_u8PinNum, DIO_Pin_Value_t Copy_u8Value);

DIO_TogglePinValueErrorState_t DIO_u8TogglePinValue(DIO_Port_t Copy_u8Port, DIO_PIN_Num_t Copy_u8PinNum);

DIO_GetPinValueErrorState_t DIO_u8GetPinValue(DIO_Port_t Copy_u8Port, DIO_PIN_Num_t Copy_u8PinNum, DIO_Pin_Value_t *Copy_pu8Value);

DIO_SetPortDirectionErrorState_t DIO_u8SetPortDirection (DIO_Port_t Copy_u8Port,uint8 Copy_u8Direction);

DIO_SetPortValueErrorState_t DIO_u8SetPortValue (DIO_Port_t Copy_u8Port, uint8 Copy_u8Value);

DIO_GetPortValueErrorState_t DIO_u8GetPortValue (DIO_Port_t Copy_u8Port, uint8 *Copy_u8Value);
#endif
