/********************************************************************/
/********************************************************************/
/*********************** Author: Ziyad Mohammed   *******************/
/*********************** File  : LED_interface.h  *******************/
/*********************** Version: 1.00            *******************/
/********************************************************************/
/********************************************************************/

#ifndef LED_INTERFACE_H_
#define LED_INTERFACE_H_

#include "LED_prv.h"

#define LED_ACTIVE_LOW		0u
#define LED_ACTIVE_HIGH		1u

LED_ACTIVE_ERROR_t LED_u8SetLEDON (uint8 Copy_u8ActiveMode,uint8 Copy_u8Port,uint8 Copy_u8Pin);
LED_ACTIVE_ERROR_t LED_u8SetLEDOFF (uint8 Copy_u8ActiveMode,uint8 Copy_u8Port,uint8 Copy_u8Pin);

#endif
