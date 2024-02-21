
/********************************************************************/
/********************************************************************/
/*********************** Author: Ziyad Mohammed   *******************/
/*********************** File  : PORT_Program.c   *******************/
/*********************** Version: 1.00            *******************/
/********************************************************************/
/********************************************************************/

#include "STD_TYPES.h"

#include "PORT_reg.h"
#include "PORT_interface.h"
#include "PORT_cfg.h"
#include "PORT_prv.h"

void PORT_voidInit(void)
{
	PORT_DDRA = PORT_PORTA_DIA;
	PORT_DDRB = PORT_PORTB_DIA;
	PORT_DDRC = PORT_PORTC_DIA;
	PORT_DDRD = PORT_PORTD_DIA;

	PORT_PORTA = PORT_PORTA_INITIAL_VAL;
	PORT_PORTB = PORT_PORTB_INITIAL_VAL;
	PORT_PORTC = PORT_PORTC_INITIAL_VAL;
	PORT_PORTD = PORT_PORTD_INITIAL_VAL;
}
