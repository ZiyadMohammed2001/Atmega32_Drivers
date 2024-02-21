/*
 * ADC_main.c
 *
 *  Created on: Feb 17, 2024
 *      Author: Ziyad
 */
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "DEFINES.h"

#include "PORT_interface.h"
#include "DIO_interface.h"
#include "ADC_interface.h"

int main(void)
{
	uint8 Local_u8DigitalReading;
	PORT_voidInit();
	ADC_voidInit();
	while(1)
	{
		ADC_u16StartConversionSynch(ADC_SINGLE_ENDED_CH0,(uint16*)&Local_u8DigitalReading);
		DIO_u8SetPortValue(DIO_u8PORTB,Local_u8DigitalReading);
	}
}

