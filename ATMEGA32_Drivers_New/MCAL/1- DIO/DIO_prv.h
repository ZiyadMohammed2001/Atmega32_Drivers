#ifndef DIO_PRV_H_
#define DIO_PRV_H_

typedef enum SetPinDirectionErrorState
{
	DIO_SET_DIRECTION_WAIT							= 0u,
	DIO_SET_DIRECTION_PORT_SUCESS 					= 1u,
	DIO_SET_DIRECTION_PORT_FAIL 					= 2u,
	DIO_SET_DIRECTION_PIN_NUM_SUCESS 				= 3u,
	DIO_SET_DIRECTION_PIN_NUM_FAIL 					= 4u,
	DIO_SET_DIRECTION_PORT_DIRECTION_SUCESS		 	= 5u,
	DIO_SET_DIRECTION_PORT_DIRECTION_FAIL 			= 6u,
}DIO_SetPinDirectionErrorState_t;

typedef enum SetPinValueErrorState
{
	DIO_SET_VALUE_WAIT								= 0u,
	DIO_SET_VALUE_PORT_SUCESS 						= 1u,
	DIO_SET_VALUE_PORT_FAIL 						= 2u,
	DIO_SET_VALUE_PIN_NUM_SUCESS 					= 3u,
	DIO_SET_VALUE_PIN_NUM_FAIL 						= 4u,
	DIO_SET_VALUE_PORT_VALUE_SUCESS 				= 5u,
	DIO_SET_VALUE_PORT_VALUE_FAIL 					= 6u,
}DIO_SetPinValueErrorState_t;

typedef enum TogglePinValueErrorState
{
	DIO_TOGGLE_VALUE_WAIT							= 0u,
	DIO_TOGGLE_VALUE_PORT_SUCESS 					= 1u,
	DIO_TOGGLE_VALUE_PORT_FAIL 						= 2u,
	DIO_TOGGLE_VALUE_PIN_NUM_SUCESS 				= 3u,
	DIO_TOGGLE_VALUE_PIN_NUM_FAIL 					= 4u,
}DIO_TogglePinValueErrorState_t;


typedef enum GetPinValueErrorState
{
	DIO_GET_VALUE_WAIT								= 0u,
	DIO_GET_VALUE_PORT_SUCESS 						= 1u,
	DIO_GET_VALUE_PORT_FAIL 						= 2u,
	DIO_GET_VALUE_PIN_NUM_SUCESS 					= 3u,
	DIO_GET_VALUE_PIN_NUM_FAIL 						= 4u,
	DIO_GET_VALUE_PORT_VALUE_SUCESS 				= 5u,
	DIO_GET_VALUE_PORT_VALUE_FAIL 					= 6u,
}DIO_GetPinValueErrorState_t;

typedef enum SetPortDirectionErrorState
{
	DIO_PORT_SET_DIRECTION_WAIT						= 0u,
	DIO_PORT_SET_DIRECTION_PORT_SUCESS 				= 1u,
	DIO_PORT_SET_DIRECTION_PORT_FAIL 				= 2u,
}DIO_SetPortDirectionErrorState_t;

typedef enum SetPortValueErrorState
{
	DIO_PORT_SET_PORT_WAIT							= 0u,
	DIO_PORT_SET_PORT_PORT_SUCESS 					= 1u,
	DIO_PORT_SET_PORT_PORT_FAIL 					= 2u,
}DIO_SetPortValueErrorState_t;

typedef enum GetPortValueErrorState
{
	DIO_PORT_GET_PORT_WAIT							= 0u,
	DIO_PORT_GET_PORT_PORT_SUCESS 					= 1u,
	DIO_PORT_GET_PORT_PORT_FAIL 					= 2u,
	DIO_PORT_GET_VALUE_SUCESS						= 3u,
	DIO_PORT_GET_VALUE_FAIL							= 4u,
}DIO_GetPortValueErrorState_t;
#endif
