
/********************************************************************/
/********************************************************************/
/*********************** Author: Ziyad Mohammed   *******************/
/*********************** File  : USART_CFG.h      *******************/
/*********************** Version: 1.00            *******************/
/********************************************************************/
/********************************************************************/

#ifndef USART_CFG_H_
#define USART_CFG_H_

/* Define F_CPU*/
#define F_CPU_C					16000000

/* USART Baud Rate Configuration. */
#define USART_BAUD_RATE 		9600

/* Configuration settings. */
/* Configure USART Mode, Options:
 * 								1- USART_ASYNCHRONOUS_MODE
 * 								2- USART_SYNCHRONOUS_MODE
 * 									*/
#define USART_MODE               USART_ASYNCHRONOUS_MODE
/* Configure Parity Bit, Options:
 * 								1- USART_PARITY_DISABLED
 * 								2- USART_PARITY_EVEN
 * 								3- USART_PARITY_ODD
 * 									*/
#define USART_PARITY_MODE        USART_PARITY_DISABLED
/* Configure Stop Bit, Options:
 * 								1-USART_ONE_STOP_BIT
 * 								2-USART_TWO_STOP_BITS
 * 								*/
#define USART_STOP_BIT           USART_ONE_STOP_BIT
/*Configure character size, Options:
 * 								1- USART_5_BIT_SIZE
 * 								2- USART_6_BIT_SIZE
 * 								3- USART_7_BIT_SIZE
 * 								4- USART_8_BIT_SIZE
 * 								5- USART_9_BIT_SIZE
 * 										*/
#define USART_CHARACTER_SIZE     USART_8_BIT_SIZE

/* Configure USART Work Environment, Options
 * 											1- USART_TRANSMIT_ENABLE
 * 											2- USART_TRANSMIT_DISABLE
 * 											3- USART_RECIEVE_ENABLE
 * 											4- USART_RECIEVE_DISABLE
 * 												*/

#define USART_TRANSMIT_STATE			USART_TRANSMIT_ENABLE
#define USART_RECIEVE_STATE				USART_RECIEVE_ENABLE

/*Config Interrupts Enable
 * 1-	RX Complete Interrupt, Options:
 * 															1-	 USART_RX_COMPELETE_INTERRUPT_DISABLE
 * 															2-	 USART_RX_COMPELETE_INTERRUPT_ENABLE
 * 2-	TX Complete Interrupt, Options
 * 															1-   USART_TX_COMPELETE_INTERRUPT_DISABLE
 * 															2-   USART_TX_COMPELETE_INTERRUPT_ENABLE
 * 3-	USART Data Register Empty Interrupt State, Options
 * 															1-   USART_DATA_REGISTER_EMPTY_INTERRUPT_DISABLE
 * 															2-   USART_DATA_REGISTER_EMPTY_INTERRUPT_ENABLE
 * 															 */

#define USART_RX_COMPELETE_INTERRUPT_STATE			USART_RX_COMPELETE_INTERRUPT_DISABLE
#define USART_TX_COMPELETE_INTERRUPT_STATE			USART_TX_COMPELETE_INTERRUPT_DISABLE
#define USART_DATA_REGISTER_EMPTY_INTERRUPT_STATE	USART_DATA_REGISTER_EMPTY_INTERRUPT_DISABLE

#endif /*USART_CFG_H_*/

