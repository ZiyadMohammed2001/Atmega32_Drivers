
/********************************************************************/
/********************************************************************/
/******************** Author: Ziyad Mohammed      *******************/
/******************** File  : USART_Interface.h   *******************/
/******************** Version: 1.00               *******************/
/********************************************************************/
/********************************************************************/

#ifndef USART_INTERFACE_H_
#define USART_INTERFACE_H_

#include "USART_prv.h"

typedef enum
{
	USART_RX_COMPELETE						=0u,
	USART_DATA_REGISTER_EMPTY				=1u,
	USART_TX_COMPELETE						=2u,
}USART_Int_SRC_t;

// Function Declarations
void USART_Init(void);
USART_Errors_t USART_Transmit(uint8 data, uint32 timeout);
USART_Errors_t USART_Receive(uint8 *data, uint32 timeout);
USART_Errors_t USART_TransmitString(const char *str, uint32 timeout);
USART_Errors_t USART_ReceiveString(char *str, uint32 timeout, uint8 max_length);
USART_Errors_t USART_u8SetCallBack(USART_Int_SRC_t Copy_u8TmrIntSource, void (*Copy_pvCallBackFunc)(void));


#endif
