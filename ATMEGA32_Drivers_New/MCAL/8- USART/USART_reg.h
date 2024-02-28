
/********************************************************************/
/********************************************************************/
/*********************** Author: Ziyad Mohammed   *******************/
/*********************** File  : USART_REG.h      *******************/
/*********************** Version: 1.00            *******************/
/********************************************************************/
/********************************************************************/

#ifndef USART_REG_H_
#define USART_REG_H_

/* USART Baud Rate Register High */
#define UBRRH   (*(volatile uint16*)(0x40))

/* USART Control and Status Register B */
#define UCSRB   (*(volatile uint16*)(0x2A))
#define RXCIE   7 							/* RX Complete Interrupt Enable. */
#define TXCIE   6 							/* TX Complete Interrupt Enable. */
#define UDRIE   5 							/* USART Data Register Empty Interrupt Enable. */
#define RXEN    4 							/* Receiver Enable. */
#define TXEN    3 							/* Transmitter Enable. */
#define UCSZ2   2 							/* Character Size. */
#define RXB8    1 							/* Receive Data Bit 8. */
#define TXB8    0 							/* Transmit Data Bit 8. */

/* USART Control and Status Register A */
#define UCSRA   (*(volatile uint16*)(0x2B))
#define RXC     7 							/* USART Receive Complete. */
#define TXC     6 							/* USART Transmit Complete. */
#define UDRE    5 							/* USART Data Register Empty. */
#define FE      4 							/* Frame Error. */
#define DOR     3 							/* Data OverRun. */
#define PE      2 							/* Parity Error. */
#define U2X     1 							/* Double the USART Transmission Speed. */
#define MPCM    0 							/* Multi-processor Communication Mode. */

/* USART I/O Data Register */
#define UDR     (*(volatile uint16*)(0x2C))

/* USART Baud Rate Registers */
#define UBRRL   (*(volatile uint16*)(0x29))

/* USART Control and Status Register C */
#define UCSRC   (*(volatile uint16*)(0x40)) /* Shared with UBRRH. */
#define URSEL   7 							/* Register Select. */
#define UMSEL   6 							/* USART Mode Select. */
#define UPM1    5 							/* Parity Mode Bit 1. */
#define UPM0    4 							/* Parity Mode Bit 0. */
#define USBS    3 							/* Stop Bit Select. */
#define UCSZ1   2 							/* Character Size Bit 1. */
#define UCSZ0   1 							/* Character Size Bit 0. */
#define UCPOL   0 							/* Clock Polarity. */

#endif
