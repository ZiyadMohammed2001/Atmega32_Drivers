
/********************************************************************/
/********************************************************************/
/*********************** Author: Ziyad Mohammed   *******************/
/*********************** File  : WDT_interface.h  *******************/
/*********************** Version: 1.00            *******************/
/********************************************************************/
/********************************************************************/

#ifndef WDT_INTERFACE_H
#define WDT_INTERFACE_H

#include "WDT_prv.h"

/* Macros for application */
typedef enum
{
	WDT_PRESCALER_16K    =0u, 			/*Typical Time-out 16.3ms*/
	WDT_PRESCALER_32K    =1u, 			/*Typical Time-out 32.5ms*/
	WDT_PRESCALER_64K    =2u, 			/*Typical Time-out 65ms*/
	WDT_PRESCALER_128K   =3u, 			/*Typical Time-out 0.13s*/
	WDT_PRESCALER_256K   =4u, 			/*Typical Time-out 0.26s*/
	WDT_PRESCALER_512K   =5u, 			/*Typical Time-out 0.52s*/
	WDT_PRESCALER_1024K  =6u, 			/*Typical Time-out 1.0s*/
	WDT_PRESCALER_2048K  =7u 			/*Typical Time-out 2.1s*/
}WDT_Prescaler_t;


/* Function prototypes */
WDT_ErrorState_t WDT_voidEnable(WDT_Prescaler_t Copy_u8_Prescaler);
void WDT_voidDisable(void);
void WDT_voidRefresh(void);

#endif /* WDT_INTERFACE_H */
