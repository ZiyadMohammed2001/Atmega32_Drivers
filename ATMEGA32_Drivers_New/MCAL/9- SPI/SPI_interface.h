
/********************************************************************/
/********************************************************************/
/******************** Author: Ziyad Mohammed      *******************/
/******************** File  : SPI_Interface.h     *******************/
/******************** Version: 1.00               *******************/
/********************************************************************/
/********************************************************************/

#ifndef SPI_INTERFACE_H_
#define SPI_INTERFACE_H_

#include "SPI_prv.h"

typedef enum
{
	SPI_INTERRUPT = 0u,
}SPI_Interrupt_t;

void SPI_voidInit(void);
SPI_Errors_t SPI_u8SendReceiveSynch(uint8 Copy_u8DataToTransmit, uint8 *Ptr_u8DataToReceive, uint32 Copy_u32Timeout);
SPI_Errors_t SPI_u8SetCallBack(SPI_Interrupt_t Copy_u8TmrIntSource, void (*Copy_pvCallBackFunc)(void));

#endif
