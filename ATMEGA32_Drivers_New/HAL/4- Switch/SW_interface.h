/********************************************************************/
/********************************************************************/
/*********************** Author: Ziyad Mohammed   *******************/
/*********************** File  : SW_interface.h   *******************/
/*********************** Version: 1.00            *******************/
/********************************************************************/
/********************************************************************/

#ifndef SW_INTERFACE_H_
#define SW_INTERFACE_H_

#include "SW_prv.h"

typedef enum
{
	SWITCH_PULL_UP 		= 0,
	SWITCH_PULL_DOWN 	= 1,
}Switch_PullType_t;

typedef struct
{
	uint8 Switch_Port;
	uint8 Switch_Pin;
	uint8 Switch_PullType;
}Switch_Configuration_t;

SwitchPullTypeError_t Switch_u8GetState(const Switch_Configuration_t* Switch_Configuration, uint8 *Copy_u8SwitchState);

#endif
