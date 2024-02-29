
/********************************************************************/
/********************************************************************/
/*********************** Author: Ziyad Mohammed   *******************/
/*********************** File  : USART_PRV.h      *******************/
/*********************** Version: 1.00            *******************/
/********************************************************************/
/********************************************************************/

#ifndef USART_PRV_H_
#define USART_PRV_H_
/*USART UCSRC Register Selection*/
#define USART_UCSRC				 (1<<URSEL)

/* USART Mode Selection. */
#define USART_ASYNCHRONOUS_MODE  (0<<UMSEL)
#define USART_SYNCHRONOUS_MODE   (1<<UMSEL)

/* USART Parity Mode Selection. */
#define USART_PARITY_DISABLED    (0<<UPM1) | (0<<UPM0)
#define USART_PARITY_EVEN        (1<<UPM1) | (0<<UPM0)
#define USART_PARITY_ODD         (1<<UPM1) | (1<<UPM0)

/* USART Stop Bit Selection. */
#define USART_ONE_STOP_BIT       (0<<USBS)
#define USART_TWO_STOP_BITS      (1<<USBS)

/* USART Character Size Selection. */
#define USART_5_BIT_SIZE         (0<<UCSZ1) | (0<<UCSZ0) //| (0<<UCSZ2)
#define USART_6_BIT_SIZE         (0<<UCSZ1) | (1<<UCSZ0) //| (0<<UCSZ2)
#define USART_7_BIT_SIZE         (1<<UCSZ1) | (0<<UCSZ0) //| (0<<UCSZ2)
#define USART_8_BIT_SIZE         (1<<UCSZ1) | (1<<UCSZ0) //| (0<<UCSZ2)
#define USART_9_BIT_SIZE         (1<<UCSZ1) | (1<<UCSZ0) //| (1<<UCSZ2)

/*USART States*/
#define USART_TRANSMIT_ENABLE 	1u
#define USART_TRANSMIT_DISABLE	0u
#define USART_RECIEVE_ENABLE  	1u
#define USART_RECIEVE_DISABLE 	0u

/*Config Interrupts States: */
/*RX Complete Interrupt*/
#define USART_RX_COMPELETE_INTERRUPT_DISABLE 			0u
#define USART_RX_COMPELETE_INTERRUPT_ENABLE				1u

/*TX Complete Interrupt State. */
#define USART_TX_COMPELETE_INTERRUPT_DISABLE			0u
#define USART_TX_COMPELETE_INTERRUPT_ENABLE				1u

/*USART Data Register Empty Interrupt State*/
#define USART_DATA_REGISTER_EMPTY_INTERRUPT_DISABLE		0u
#define USART_DATA_REGISTER_EMPTY_INTERRUPT_ENABLE		1u


#define BAUDRATE_DIVISION_FACTOR	16u
#define BAUDRATE_SUBTRACTION_FACTOR	1u
#define UBRRH_Shift					8u
#define USART_UCSRA_SET				1u
#define TIMEOUT_FAILED				0u



typedef enum
{
	USART_OK = 0u,
	USART_PTR_ERROR = 1u,
	USART_ERR_TIMEOUT_Tx=3u,
	USART_ERR_TIMEOUT_Rx=4u,
}USART_Errors_t;
#endif
