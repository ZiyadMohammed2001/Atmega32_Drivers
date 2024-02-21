
/********************************************************************/
/********************************************************************/
/*********************** Author: Ziyad Mohammed   *******************/
/*********************** File  : PORT_REG.h       *******************/
/*********************** Version: 1.00            *******************/
/********************************************************************/
/********************************************************************/

#ifndef PORT_REG_H_
#define PORT_REG_H_

#define PORT_PORTA       *((volatile uint8*)0x3B)
#define PORT_DDRA        *((volatile uint8*)0x3A)

#define PORT_PORTB       *((volatile uint8*)0x38)
#define PORT_DDRB        *((volatile uint8*)0x37)

#define PORT_PORTC       *((volatile uint8*)0x35)
#define PORT_DDRC        *((volatile uint8*)0x34)

#define PORT_PORTD       *((volatile uint8*)0x32)
#define PORT_DDRD        *((volatile uint8*)0x31)

#endif
