
/********************************************************************/
/********************************************************************/
/*********************** Author: Ziyad Mohammed   *******************/
/*********************** File  : USART_Program.c  *******************/
/*********************** Version: 1.00            *******************/
/********************************************************************/
/********************************************************************/

#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "DEFINES.h"

#include "USART_interface.h"
#include "USART_prv.h"
#include "USART_cfg.h"
#include "USART_reg.h"

static void (*USART_pvCallBAckFuncArr[3])(void) = {NULL};

void USART_Init(void)
{
	/* Set baud rate. */
	uint16 ubrr_value = (F_CPU_C / BAUDRATE_DIVISION_FACTOR / USART_BAUD_RATE) - BAUDRATE_SUBTRACTION_FACTOR;
	UBRRH = (uint8)(ubrr_value >> UBRRH_Shift);
	UBRRL = (uint8)(ubrr_value);

	/* Set frame format. */
	UCSRC = ((USART_MODE) | (USART_PARITY_MODE) | (USART_STOP_BIT) | (USART_CHARACTER_SIZE) | (USART_UCSRC));
	if((USART_CHARACTER_SIZE) == (USART_9_BIT_SIZE))
	{
		UCSRB &= 0b11111011;
		UCSRB |= (1<<UCSZ2);
	}
	else
	{
		UCSRB &= 0b11111011;
	}

	/* Receiver and Transmitter States. */
	UCSRB = ((USART_RECIEVE_STATE << RXEN) | (USART_TRANSMIT_STATE << TXEN));

	/* Enable receive complete interrupt. */
	UCSRB |= (USART_RX_COMPELETE_INTERRUPT_STATE << RXCIE);

	/* Optionally enable transmit complete interrupt. */
	UCSRB |= (USART_TX_COMPELETE_INTERRUPT_STATE << TXCIE);

	/* Optionally enable Data Register Empty interrupt. */
	UCSRB |= (USART_DATA_REGISTER_EMPTY_INTERRUPT_STATE << UDRIE);
}

USART_Errors_t USART_Transmit(uint8 data, uint32 timeout)
{
	USART_Errors_t Local_u8ErrorState = USART_OK;
	/*Wait until transmit buffer is ready of time out. */
	while (!(UCSRA & (USART_UCSRA_SET << UDRE)) && timeout)
	{
		timeout--;
	}

	if (timeout == TIMEOUT_FAILED)
	{
		/* Timeout occurred. */
		Local_u8ErrorState = USART_ERR_TIMEOUT_Tx;
	}
	else
	{
		/* Put data into buffer, sends the data.*/
		UDR = data;
	}
	return Local_u8ErrorState;
}

USART_Errors_t USART_Receive(uint8 *data, uint32 timeout)
{
	USART_Errors_t Local_u8ErrorState = USART_OK;
	if(NULL != data)
	{
		while (!(UCSRA & (USART_UCSRA_SET << RXC)) && timeout)
		{
			timeout--;
		}

		if (timeout == TIMEOUT_FAILED)
		{
			/* Timeout occurred. */
			Local_u8ErrorState = USART_ERR_TIMEOUT_Rx;
		}
		else
		{
			/*Get and return received data from buffer.*/
			*data = UDR;
		}
	}
	else
	{
		Local_u8ErrorState = USART_PTR_ERROR;
	}
	return Local_u8ErrorState;
}

USART_Errors_t USART_TransmitString(const char *str, uint32 timeout)
{
	USART_Errors_t Local_u8ErrorState = USART_OK;
	if(NULL != str)
	{
		while (*str != '\0')
		{
			if (USART_Transmit(*str++, timeout) == USART_ERR_TIMEOUT_Tx)
			{
				Local_u8ErrorState = USART_ERR_TIMEOUT_Tx;
				break;
			}
			else
			{
				/*The Transmitting works well*/
			}
		}
	}
	else
	{
		Local_u8ErrorState = USART_PTR_ERROR;
	}
	return Local_u8ErrorState;
}

USART_Errors_t USART_ReceiveString(char *str, uint32 timeout, uint8 max_length)
{
	USART_Errors_t Local_u8ErrorState = USART_OK;
	uint8 received_char, idx = 0;

	while (idx < (max_length - 1))
	{
		if (USART_Receive(&received_char, timeout) == USART_ERR_TIMEOUT_Rx)
		{
			/*Timeout occurred.*/
			Local_u8ErrorState = USART_ERR_TIMEOUT_Tx;
			break;
		}
		else
		{
			/*The Receiving works well. */
		}

		if (received_char == '\0' || received_char == '\n')
		{
			/* End of string. */
			break;
		}
		else
		{
			/*The string doesn't end*/
			str[idx++] = received_char;
		}
	}

	/*Null-terminate the string. */
	str[idx] = '\0';
	return Local_u8ErrorState;;
}

USART_Errors_t TIMERS_u8SetCallBack(USART_Int_SRC_t Copy_u8TmrIntSource, void (*Copy_pvCallBackFunc)(void))
{
	USART_Errors_t Local_u8ErrorState = USART_OK;
	if(Copy_pvCallBackFunc != NULL)
	{
		USART_pvCallBAckFuncArr[Copy_u8TmrIntSource]=Copy_pvCallBackFunc;
	}
	else
	{
		Local_u8ErrorState = USART_PTR_ERROR;
	}
	return Local_u8ErrorState;
}

void __vector_13(void) __attribute__((signal));
void __vector_13(void)
{
	if ((USART_pvCallBAckFuncArr[USART_RX_COMPELETE])!=NULL)
	{
		USART_pvCallBAckFuncArr[USART_RX_COMPELETE]();
		/*Flag is cleared when read the data in UDR.*/
	}
}
void __vector_14(void) __attribute__((signal));
void __vector_14(void)
{
	if ((USART_pvCallBAckFuncArr[USART_DATA_REGISTER_EMPTY])!=NULL)
	{
		USART_pvCallBAckFuncArr[USART_DATA_REGISTER_EMPTY]();
		/*Flag is cleared when read the data from UDR.*/
	}
}
void __vector_15(void) __attribute__((signal));
void __vector_15(void)
{
	if ((USART_pvCallBAckFuncArr[USART_TX_COMPELETE])!=NULL)
	{
		USART_pvCallBAckFuncArr[USART_TX_COMPELETE]();
		/*The TXC Flag bit is automatically cleared when a transmit complete interrupt is executed*/
	}
}
