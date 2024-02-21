/************************************************/
/*                     Name: Ziyad Mohammed     */
/*                     Date: 16/10/2021         */
/*                     SWC: ADC                 */
/*                     Version: 1.0             */
/************************************************/
/*LIB Layer*/
#include "STD_TYPES.h"
#include "BIT_MATH.h"

/*MCAL*/
#include "ADC_interface.h"
#include "ADC_private.h"
#include "ADC_config.h"
#if ADC_u8_RIGHT_OR_LEFT_ADJUSTMENT == ADC_u8_RIGHT_ADJUSTMENT
#if ADC_u8_AsynchVersion == 1
static u16 *ADC_pu16DigitalValue = NULL;                    //For Async version 1
static void (*ADC_pfNotification)(void) = NULL ;            //For Async version 1
#elif ADC_u8_AsynchVersion == 2
static void (*ADC_pfNotification)(u16) = NULL ;               //For Async version 2
#endif
#elif ADC_u8_RIGHT_OR_LEFT_ADJUSTMENT == ADC_u8_LEFT_ADJUSTMENT
#if ADC_u8_AsynchVersion == 1
static u8 *ADC_pu8DigitalValue = NULL;                    //For Async version 1
static void (*ADC_pfNotification)(void) = NULL ;            //For Async version 1
#elif ADC_u8_AsynchVersion == 2
static void (*ADC_pfNotification)(u8) = NULL ;               //For Async version 2
#endif
#endif
static u8 ADC_u8BuzyFlag = ADC_u8_NOT_BUSY ;

void ADC_voidInit(u8 Copy_u8VREF,u8 Copy_u8TypeOfConversion,u8 Copy_u8Prescaler_CLK,u8 Copy_u8EN_OR_DIS_ADC)
{
	// Select VREF.
	// Clear Channel region.
	ADC_u8_ADMUX_REG &= 0b00111111;
	//Select VREF.
	ADC_u8_ADMUX_REG |= Copy_u8VREF;
	// Select Adjustment.
    #if ADC_u8_RIGHT_OR_LEFT_ADJUSTMENT == ADC_u8_RIGHT_ADJUSTMENT
	ADC_u8_ADMUX_REG &= 0b11011111;
	ADC_u8_ADMUX_REG |= ADC_u8_RIGHT_ADJUST;
    #elif ADC_u8_RIGHT_OR_LEFT_ADJUSTMENT == ADC_u8_LEFT_ADJUSTMENT
	ADC_u8_ADMUX_REG &= 0b11011111;
	ADC_u8_ADMUX_REG |= ADC_u8_LEFT_ADJUST;
    #endif
	//Select Conversion Mode.
	ADC_u8_ADCSRA_REG &= 0b11011111;
	ADC_u8_ADCSRA_REG |= Copy_u8TypeOfConversion;
	//Select Prescaler.
	ADC_u8_ADCSRA_REG &= 0b11111000;
	ADC_u8_ADCSRA_REG |=Copy_u8Prescaler_CLK;
	// Enable ADC.
	ADC_u8_ADCSRA_REG &= 0b01111111;
	ADC_u8_ADCSRA_REG |= Copy_u8EN_OR_DIS_ADC;
}

#if ADC_u8_RIGHT_OR_LEFT_ADJUSTMENT == ADC_u8_RIGHT_ADJUSTMENT
u8 ADC_u8GedDigitalValueSynch(u8 Copy_u8ChannelNum,u16 * Copy_pu16ReturnedDigitalValue,u8 Copy_u8EN_OR_DIS_Conversion)
{
	u8 Local_u8ErrorState = STD_TYPES_OK;
	u32 Local_u32TimeoutCounter = 0;
	if ((Copy_u8ChannelNum<=31)&&(Copy_pu16ReturnedDigitalValue!=NULL))
	{
		// Clear Channel region.
		ADC_u8_ADMUX_REG &= 0b11100000;
		//Select Channel.
		ADC_u8_ADMUX_REG |= Copy_u8ChannelNum;
		//Select Conversion.
		ADC_u8_ADCSRA_REG &= 10111111;
		ADC_u8_ADCSRA_REG |= Copy_u8EN_OR_DIS_Conversion;
		//Wait for the flag.
		//while (GET_BIT(ADC_u8_ADCSRA_REG,4)==0);//while (!GET_BIT(ADC_u8_ADCSRA_REG,4));
		//time out Mechanism if happen problem.//solve stuck.
		while((GET_BIT(ADC_u8_ADCSRA_REG,4)==0)&&(Local_u32TimeoutCounter<500000))
		{
			Local_u32TimeoutCounter++;
		}
		// check the flag is set.
		if(GET_BIT(ADC_u8_ADCSRA_REG,4))
		{
		// CLear Flag.
		ADC_u8_ADCSRA_REG &= 11101111;
		ADC_u8_ADCSRA_REG |= ADC_u8_CLEARFLAG ;
		//Read Digital value.
		* Copy_pu16ReturnedDigitalValue = ADC_u16_ADC_REG;
		}
		else
		{
			Local_u8ErrorState = STD_TYPES_NOK;
		}
	}
	else
	{
		Local_u8ErrorState = STD_TYPES_NOK;
	}
	return Local_u8ErrorState;
}

#if ADC_u8_AsynchVersion == 1
u8 ADC_u8GedDigitalValueAsynch(u8 Copy_u8ChannelNum,u16 * Copy_pu16ReturnedDigitalValue,void(*Copy_pf)(void),u8 Copy_u8EN_OR_DIS_Conversion,u8 Copy_u8EN_OR_DIS_Intrrupt)
{
	u8 Local_u8ErrorState = STD_TYPES_OK;
	if((ADC_u8BuzyFlag == ADC_u8_NOT_BUSY)&&(Copy_u8ChannelNum<32)&&(Copy_pu16ReturnedDigitalValue!=NULL)&&(Copy_pf!=NULL))
	{
		//Update Busy flag to busy state;
		ADC_u8BuzyFlag = ADC_u8_BUSY;
		//Update Global Pointers.
		ADC_pu16DigitalValue = Copy_pu16ReturnedDigitalValue ;
		ADC_pfNotification   = Copy_pf;
		// Clear Channel region.
	    ADC_u8_ADMUX_REG &= 0b11100000;
	    //Select Channel.
	    ADC_u8_ADMUX_REG |= Copy_u8ChannelNum;
	    //Enable ADC Interrupt.
	    ADC_u8_ADCSRA_REG &=0b11110111;
	    ADC_u8_ADCSRA_REG |=Copy_u8EN_OR_DIS_Intrrupt;
	    //Start Conversion.
	    ADC_u8_ADCSRA_REG &=0b10111111;
	    ADC_u8_ADCSRA_REG |=Copy_u8EN_OR_DIS_Conversion;
	}
	else
	{
		Local_u8ErrorState = STD_TYPES_NOK;
	}
	return Local_u8ErrorState;
}

//ISR of ADC
void __vector_16(void) __attribute__((signal));
void __vector_16(void)
{
	if ((ADC_pu16DigitalValue !=NULL)&&(ADC_pfNotification != NULL))
	{
		//Update Busy flag to Not busy state;
		ADC_u8BuzyFlag = ADC_u8_NOT_BUSY;
		// Update Pointer with the result.
        *ADC_pu16DigitalValue = ADC_u16_ADC_REG;
		// Call Notification Function
		ADC_pfNotification();
		//Disable ADC Interrupt.
	    ADC_u8_ADCSRA_REG &=0b11110111;
	    ADC_u8_ADCSRA_REG |=ADC_u8_INTERRUPTDISABLE;
	}
}

#elif ADC_u8_AsynchVersion == 2
u8 ADC_u8GedDigitalValueAsynch(u8 Copy_u8ChannelNum,void(*Copy_pf)(u16),u8 Copy_u8EN_OR_DIS_Conversion,u8 Copy_u8EN_OR_DIS_Intrrupt)
{
	u8 Local_u8ErrorState = STD_TYPES_OK;
	if((ADC_u8BuzyFlag == ADC_u8_NOT_BUSY)&&(Copy_u8ChannelNum<32)&&(Copy_pf!=NULL))
	{
		//Update Busy flag to busy state;
		ADC_u8BuzyFlag = ADC_u8_BUSY;
		//Update Global Pointers.
		ADC_pfNotification   = Copy_pf;
		// Clear Channel region.
	    ADC_u8_ADMUX_REG &= 0b11100000;
	    //Select Channel.
	    ADC_u8_ADMUX_REG |= Copy_u8ChannelNum;
	    //Enable ADC Interrupt.
	    ADC_u8_ADCSRA_REG &=0b11110111;
	    ADC_u8_ADCSRA_REG |=Copy_u8EN_OR_DIS_Intrrupt;
	    //Start Conversion.
	    ADC_u8_ADCSRA_REG &=0b10111111;
	    ADC_u8_ADCSRA_REG |=Copy_u8EN_OR_DIS_Conversion;
	}
	else
	{
		Local_u8ErrorState = STD_TYPES_NOK;
	}
	return Local_u8ErrorState;
}

//ISR of ADC
void __vector_16(void) __attribute__((signal));
void __vector_16(void)
{
	if (ADC_pfNotification != NULL)
	{
		//Update Busy flag to Not busy state;
		ADC_u8BuzyFlag = ADC_u8_NOT_BUSY;
		// Call Notification Function
		ADC_pfNotification(ADC_u16_ADC_REG);
		//Disable ADC Interrupt.
	    ADC_u8_ADCSRA_REG &=0b11110111;
	    ADC_u8_ADCSRA_REG |=ADC_u8_INTERRUPTDISABLE;
	}
}
#endif

#elif ADC_u8_RIGHT_OR_LEFT_ADJUSTMENT == ADC_u8_LEFT_ADJUSTMENT

u8 ADC_u8GedDigitalValueSynch(u8 Copy_u8ChannelNum,u8 * Copy_pu8ReturnedDigitalValue,u8 Copy_u8EN_OR_DIS_Conversion)
{
	u8 Local_u8ErrorState = STD_TYPES_OK;
	u32 Local_u32TimeoutCounter = 0;
	if ((Copy_u8ChannelNum<=31)&&(Copy_pu8ReturnedDigitalValue!=NULL))
	{
		// Clear Channel region.
		ADC_u8_ADMUX_REG &= 0b11100000;
		//Select Channel.
		ADC_u8_ADMUX_REG |= Copy_u8ChannelNum;
		//Select Conversion.
		ADC_u8_ADCSRA_REG &= 10111111;
		ADC_u8_ADCSRA_REG |= Copy_u8EN_OR_DIS_Conversion;
		//Wait for the flag.
		//while (GET_BIT(ADC_u8_ADCSRA_REG,4)==0);//while (!GET_BIT(ADC_u8_ADCSRA_REG,4));
		//time out Mechanism if happen problem.//solve stuck.
		while((GET_BIT(ADC_u8_ADCSRA_REG,4)==0)&&(Local_u32TimeoutCounter<500000))
		{
			Local_u32TimeoutCounter++;
		}
		// check the flag is set.
		if(GET_BIT(ADC_u8_ADCSRA_REG,4))
		{
		// CLear Flag.
		ADC_u8_ADCSRA_REG &= 11101111;
		ADC_u8_ADCSRA_REG |= ADC_u8_CLEARFLAG ;
		//Read Digital value.
		* Copy_pu8ReturnedDigitalValue = ADC_u8_ADCH_REG ;
		}
		else
		{
			Local_u8ErrorState = STD_TYPES_NOK;
		}
	}
	else
	{
		Local_u8ErrorState = STD_TYPES_NOK;
	}
	return Local_u8ErrorState;
}
#if ADC_u8_AsynchVersion == 1
u8 ADC_u8GedDigitalValueAsynch(u8 Copy_u8ChannelNum,u8 * Copy_pu8ReturnedDigitalValue,void(*Copy_pf)(void),u8 Copy_u8EN_OR_DIS_Conversion,u8 Copy_u8EN_OR_DIS_Intrrupt)
{
	u8 Local_u8ErrorState = STD_TYPES_OK;
	if((ADC_u8BuzyFlag == ADC_u8_NOT_BUSY)&&(Copy_u8ChannelNum<32)&&(Copy_pu8ReturnedDigitalValue!=NULL)&&(Copy_pf!=NULL))
	{
		//Update Busy flag to busy state;
		ADC_u8BuzyFlag = ADC_u8_BUSY;
		//Update Global Pointers.
		ADC_pu8DigitalValue = Copy_pu8ReturnedDigitalValue ;
		ADC_pfNotification   = Copy_pf;
		// Clear Channel region.
	    ADC_u8_ADMUX_REG &= 0b11100000;
	    //Select Channel.
	    ADC_u8_ADMUX_REG |= Copy_u8ChannelNum;
	    //Enable ADC Interrupt.
	    ADC_u8_ADCSRA_REG &=0b11110111;
	    ADC_u8_ADCSRA_REG |=Copy_u8EN_OR_DIS_Intrrupt;
	    //Start Conversion.
	    ADC_u8_ADCSRA_REG &=0b10111111;
	    ADC_u8_ADCSRA_REG |=Copy_u8EN_OR_DIS_Conversion;
	}
	else
	{
		Local_u8ErrorState = STD_TYPES_NOK;
	}
	return Local_u8ErrorState;
}

//ISR of ADC
void __vector_16(void) __attribute__((signal));
void __vector_16(void)
{
	if ((ADC_pu8DigitalValue !=NULL)&&(ADC_pfNotification != NULL))
	{
		//Update Busy flag to Not busy state;
		ADC_u8BuzyFlag = ADC_u8_NOT_BUSY;
		// Update Pointer with the result.
        *ADC_pu8DigitalValue = ADC_u8_ADCH_REG;
		// Call Notification Function
		ADC_pfNotification();
		//Disable ADC Interrupt.
	    ADC_u8_ADCSRA_REG &=0b11110111;
	    ADC_u8_ADCSRA_REG |=ADC_u8_INTERRUPTDISABLE;
	}
}
#elif ADC_u8_AsynchVersion == 2
u8 ADC_u8GedDigitalValueAsynch(u8 Copy_u8ChannelNum,void(*Copy_pf)(u8),u8 Copy_u8EN_OR_DIS_Conversion,u8 Copy_u8EN_OR_DIS_Intrrupt)
{
	u8 Local_u8ErrorState = STD_TYPES_OK;
	if((ADC_u8BuzyFlag == ADC_u8_NOT_BUSY)&&(Copy_u8ChannelNum<32)&&(Copy_pf!=NULL))
	{
		//Update Busy flag to busy state;
		ADC_u8BuzyFlag = ADC_u8_BUSY;
		//Update Global Pointers.
		ADC_pfNotification   = Copy_pf;
		// Clear Channel region.
	    ADC_u8_ADMUX_REG &= 0b11100000;
	    //Select Channel.
	    ADC_u8_ADMUX_REG |= Copy_u8ChannelNum;
	    //Enable ADC Interrupt.
	    ADC_u8_ADCSRA_REG &=0b11110111;
	    ADC_u8_ADCSRA_REG |=Copy_u8EN_OR_DIS_Intrrupt;
	    //Start Conversion.
	    ADC_u8_ADCSRA_REG &=0b10111111;
	    ADC_u8_ADCSRA_REG |=Copy_u8EN_OR_DIS_Conversion;
	}
	else
	{
		Local_u8ErrorState = STD_TYPES_NOK;
	}
	return Local_u8ErrorState;
}

//ISR of ADC
void __vector_16(void) __attribute__((signal));
void __vector_16(void)
{
	if (ADC_pfNotification != NULL)
	{
		//Update Busy flag to Not busy state;
		ADC_u8BuzyFlag = ADC_u8_NOT_BUSY;
		// Call Notification Function
		ADC_pfNotification(ADC_u8_ADCH_REG);

		//Disable ADC Interrupt.
	    ADC_u8_ADCSRA_REG &=0b11110111;
	    ADC_u8_ADCSRA_REG |=ADC_u8_INTERRUPTDISABLE;
	}
}
#endif
#endif
