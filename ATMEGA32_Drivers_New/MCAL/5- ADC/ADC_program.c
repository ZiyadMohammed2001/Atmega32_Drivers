
/********************************************************************/
/********************************************************************/
/*********************** Author: Ziyad Mohammed   *******************/
/*********************** File  : ADC_Program.c   *******************/
/*********************** Version: 1.00            *******************/
/********************************************************************/
/********************************************************************/

#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "DEFINES.h"

#include "ADC_interface.h"
#include "ADC_prv.h"
#include "ADC_cfg.h"
#include "ADC_reg.h"

static uint16* ADC_pu16ConversionResult = NULL;
static void(*ADC_pvNotificationFunc)(void) = NULL;
static uint8 ADC_u8BuzyFlag = ADC_IDLE;
static ADC_ChainConv_t* ADC_pstChainData = NULL;
static uint8 ADC_u8ChannelCounter;
static uint8 ADC_u8IntReason = 0;

void ADC_voidInit(void)
{
#if ADC_u8REF_VOLT == AREF_REF
	CLR_BIT(ADMUX, ADMUX_REFS0);
	CLR_BIT(ADMUX, ADMUX_REFS1);

#elif ADC_u8REF_VOLT == AVCC_REF
	SET_BIT(ADMUX, ADMUX_REFS0);
	CLR_BIT(ADMUX, ADMUX_REFS1);

#elif ADC_u8REF_VOLT == INTERNAL_2560mV_REF
	SET_BIT(ADMUX, ADMUX_REFS0);
	SET_BIT(ADMUX, ADMUX_REFS1);
#else
#error Wrong ADC_u8REF_VOLT Configuration Option.

#endif

#if ADC_u8RESOLUTION == EIGHT_BITS
	SET_BIT(ADMUX, ADMUX_ADLAR);
#elif ADC_u8RESOLUTION == TEN_BITS
	CLR_BIT(ADMUX, ADMUX_ADLAR);
#else
#error wrong ADC_u8RESOLUTION configuration option
#endif


	/* configure prescaler bits */
	ADCSRA &= ADC_ADCSRA_PRESCALLER_MASKING;			/*Masking first 3-Bits.*/
	ADCSRA |= ADC_u8PRESCALER_VAL;						/*Assign the Needed Value.*/

	/*Configure Trigger Source.*/
	SFIOR &= ADC_SFIOR_TRIGGERSOURCE_MASKING;
	SFIOR |= ((ADC_u8TRIGGER_SOURCE)<<5);
	/*ADC Enable*/
	SET_BIT(ADCSRA,ADCSRA_ADEN);
}

ADC_Error_t ADC_u16StartConversionSynch(uint8 Copy_u8Channel, uint16*Copy_pu16ADC_Data)
{
	ADC_Error_t Local_u8ErrorState = ADC_CHANNEL_OK;
	uint32 Local_u32TimeOutCounter = 0u;
	/*Check If ADC isn't Busy.*/
	if (ADC_u8BuzyFlag == ADC_IDLE)
	{
		if (NULL_PTR_ERR != Copy_pu16ADC_Data)
		{
			if(((Copy_u8Channel>=ADC_SINGLE_ENDED_CH0))&&((Copy_u8Channel)<=ADC_SINGLE_ENDED_0_VOLT))
			{

				/*ADC is Now Busy.*/
				ADC_u8BuzyFlag = ADC_BUZY;

				/*Configure the analog Channel.*/
				ADMUX &= ADC_ADMUX_ANALOG_CHANNLE_MASKING;
				ADMUX|=Copy_u8Channel;

				/*Start Conversion.*/
				SET_BIT(ADCSRA, ADCSRA_ADSC);

				/*Wait until the conversion is complete.*/
				while((GET_BIT(ADCSRA,ADCSRA_ADIF)==0)&&(Local_u32TimeOutCounter < ADC_u32TIME_OUT_CONFIG))
				{
					Local_u32TimeOutCounter++;
				}
				if(Local_u32TimeOutCounter == ADC_u32TIME_OUT_CONFIG)
				{
					/*Loop is broken because flag isn't raised until time out is passed.*/
					Local_u8ErrorState = ADC_TIME_OUT;
				}
				else
				{
					/*Loop is broken because flag is raised before the time out is passed.*/
					/*Clear the conversion complete flag.*/
					SET_BIT(ADCSRA,ADCSRA_ADIF);
#if ADC_u8RESOLUTION == EIGHT_BITS
					*Copy_pu16ADC_Data = ADCH;
#elif	ADC_u8RESOLUTION == TEN_BITS
					*Copy_pu16ADC_Data = ADC;
#endif
					/*ADC is Now IDLE*/
					ADC_u8BuzyFlag = ADC_IDLE;
				}

			}
			else
			{
				Local_u8ErrorState = ADC_CHANNEL_NOK;
			}
		}
		else
		{
			Local_u8ErrorState = ADC_PTR_ERROR;
		}
	}
	else
	{
		/*ADC is Busy, assign the error state.*/
		Local_u8ErrorState = ADC_BUSY;
	}
	return Local_u8ErrorState;
}


ADC_Error_t ADC_u16StartSingleConversionASynch(uint8 Copy_u8Channel, uint16*Copy_pu16ADC_Data, void(*Copy_pvNotificatiobFunc)(void))
{
	ADC_Error_t Local_u8ErrorState = ADC_CHANNEL_OK;

	/*Check If ADC isn't Busy.*/
	if (ADC_u8BuzyFlag == ADC_IDLE)
	{
		if ((NULL_PTR_ERR != Copy_pu16ADC_Data) && (NULL_PTR_ERR != Copy_pvNotificatiobFunc))
		{
			if(((Copy_u8Channel>=ADC_SINGLE_ENDED_CH0))&&((Copy_u8Channel)<=ADC_SINGLE_ENDED_0_VOLT))
			{
				/*ADC is Now Busy.*/
				ADC_u8BuzyFlag = ADC_BUZY;

				/*ADC Interrupt From Single Conversion Asych.*/
				ADC_u8IntReason = ADC_SINGLE_CONV_ASYNCH;

				/*Initialize The Result Pointer Globally.*/
				ADC_pu16ConversionResult =  Copy_pu16ADC_Data;

				/*Initialize The Notification Function Globally.*/
				ADC_pvNotificationFunc = Copy_pvNotificatiobFunc;

				/*Configure the analog Channel.*/
				ADMUX &= ADC_ADMUX_ANALOG_CHANNLE_MASKING;
				ADMUX|=Copy_u8Channel;

				/*Start Conversion.*/
				SET_BIT(ADCSRA, ADCSRA_ADSC);

				/*Enable the ADC Conversion Complete Interrupt*/
				SET_BIT(ADCSRA,ADCSRA_ADIE);

			}
			else
			{
				Local_u8ErrorState = ADC_CHANNEL_NOK;
			}
		}
		else
		{
			Local_u8ErrorState = ADC_PTR_ERROR;
		}
	}
	else
	{
		/*ADC is Busy, assign the error state.*/
		Local_u8ErrorState = ADC_BUSY;
	}
	return Local_u8ErrorState;
}
ADC_Error_t ADC_u8StartChainConvertersionAsynch(ADC_ChainConv_t* Copy_pstChain)
{
	ADC_Error_t Local_u8ErrorState = ADC_CHANNEL_OK;
	if ((NULL != Copy_pstChain)&&(NULL !=(Copy_pstChain ->ChainArr))&&(NULL !=(Copy_pstChain -> NotificationFunc))&&(NULL !=(Copy_pstChain -> ResultArr)))
	{
		/*Check if ADC is busy.*/
		if(ADC_IDLE == ADC_u8BuzyFlag)
		{
			/*ADC is now Busy.*/
			ADC_u8BuzyFlag = ADC_BUZY;

			/*ADC Interrupt From Chain Conversion Asych.*/
			ADC_u8IntReason = ADC_CHAIN_CONV_ASYNCH;

			/*Initialize The Global Chain Data.*/
			ADC_pstChainData = Copy_pstChain;
			ADC_u8ChannelCounter = 0;

			/*Set The First Channel.*/
			ADMUX &= ADC_ADMUX_ANALOG_CHANNLE_MASKING;
			ADMUX |= ADC_pstChainData -> ChainArr[ADC_u8ChannelCounter];

			/*Start The First Conversion.*/
			SET_BIT(ADCSRA,ADCSRA_ADSC);

			/*Enable ADC Conversion Complete Interrupt.*/
			SET_BIT(ADCSRA,ADCSRA_ADIE);
		}
		else
		{
			Local_u8ErrorState = ADC_BUSY;
		}
	}
	else
	{
		Local_u8ErrorState = ADC_PTR_ERROR;
	}
	return Local_u8ErrorState;
}

/**
 * @brief ADC Conversion Complete ISR
 */
void __vector_16 (void) __attribute__((signal));
void __vector_16 (void)
{
	if(ADC_u8IntReason == ADC_SINGLE_CONV_ASYNCH)/*Interrupt is due to single conversion.*/
	{
		if(ADC_pu16ConversionResult != NULL)
		{
#if ADC_u8RESOLUTION == EIGHT_BITS
			*ADC_pu16ConversionResult = ADCH;
#elif	ADC_u8RESOLUTION == TEN_BITS
			*ADC_pu16ConversionResult = ADC;
#endif
			/*Disable the ADC conversion complete interrupt*/
			CLR_BIT(ADCSRA, ADCSRA_ADIE);

			/*Invoke the application notification function*/
			if(ADC_pvNotificationFunc != NULL)
			{
				/*ADC is Now IDLE*/
				ADC_u8BuzyFlag = ADC_IDLE;
				ADC_pvNotificationFunc();
			}
			else
			{
				/*Notification Function Pointer is NULL.*/
			}
		}
		else
		{
			/*Conversion Result Pointer is NULL*/
		}
	}
	else if (ADC_u8IntReason == ADC_CHAIN_CONV_ASYNCH) /*Interrupt is due to chain conversion.*/
	{
#if ADC_u8RESOLUTION == EIGHT_BITS
		ADC_pstChainData -> ResultArr [ADC_u8ChannelCounter] = ADCH;
#elif	ADC_u8RESOLUTION == TEN_BITS
		ADC_pstChainData -> ResultArr [ADC_u8ChannelCounter] = ADC;
#endif
		/*Channel Counter Increment.*/
		ADC_u8ChannelCounter++;

		if(ADC_u8ChannelCounter< (ADC_pstChainData -> ChainSize))
		{
			/*Chain isn't Finished yet.*/
			/*Start Next Conversion.*/
			/*Set The First Channel.*/
			ADMUX &= ADC_ADMUX_ANALOG_CHANNLE_MASKING;
			ADMUX |= ADC_pstChainData -> ChainArr[ADC_u8ChannelCounter];

			/*Start The First Conversion.*/
			SET_BIT(ADCSRA,ADCSRA_ADSC);
		}
		else
		{
			/*Chain is Finished.*/
			/*ADC is now IDLE*/
			ADC_u8BuzyFlag = ADC_IDLE;

			/*Disable the ADC Interrupt.*/
			CLR_BIT(ADCSRA, ADCSRA_ADIE);

			/*Invoke the notification function.*/
			if((ADC_pstChainData->NotificationFunc)!= NULL)
			{
				ADC_pstChainData->NotificationFunc();
			}
			else
			{
				/*Do Nothing.*/
			}
		}
	}
}

