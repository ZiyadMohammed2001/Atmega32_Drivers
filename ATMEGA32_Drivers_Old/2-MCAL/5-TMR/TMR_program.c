/************************************************/
/*                     Name: Ziyad Mohammed     */
/*                     Date: 29/10/2021         */
/*                     SWC: TMR                 */
/*                     Version: 1.0             */
/************************************************/
/*LIB Layer*/
#include "STD_TYPES.h"
#include "BIT_MATH.h"

/*MCAL*/
#include "TMR_private.h"
#include "TMR_config.h"
#include "TMR_interface.h"

//static void(*TMR_pfOVF)(void) = NULL;
static void (*TMR_APF[5])(void) = {NULL,NULL,NULL,NULL,NULL}; //Array of pointer to function.

u8 TMR_u8SetCallBack(u8 Copy_u8TMRMode,void(*Copy_pf)(void))
{
	u8 Local_u8ErrorState = STD_TYPES_OK;
	if(Copy_pf!= NULL)
	{
		//Update Global Pointer to function.
		TMR_APF[Copy_u8TMRMode] = Copy_pf;
	}
	else
	{
		Local_u8ErrorState = STD_TYPES_NOK;
	}
	return Local_u8ErrorState;
}

static u8 Preload_u8_TMR = 0;

#if TMR_u8_TIMER0_ON_OR_OFF == TMR_TIMER0_ON
u8 Counter0_u8_Handle_TMR0 = 0;
u8 Counter0_u8_OverFlow_TMR0 = 0;
#if TMR_u8_TIMER0_MODE ==TMR_u8_TIMER0_NORMAL_MODE
static u32 Local_u32NumberOfTick=0;
static u32 Local_u32NumberOfOverFlow=0;
static u32 *Preload_pu32_TMR0 = &Local_u32NumberOfTick ;
static u32 *CounterOVR_pu32_TMR0 = &Local_u32NumberOfOverFlow;
u8 TMR_u8TMR0NormalINIT(u8 Copy_u8CLK,u32 Copy_u32Time_NanoSec,u8 Copy_u8CompareMatchUnit,u8 Copy_u8_CompareMatchOutputMode)
{
	u8 Local_u8ErrorState = STD_TYPES_OK;
	//Select Mode.
	TMR_u8_TMR0_TCCR0_REG&=0b10110111;
	TMR_u8_TMR0_TCCR0_REG|= TMR_u8_TMR0_NORMAL_WAVEFORM_GENERATION_MODE;
	//Enable Over Flow Interrupt.
	TMR_u8_TIMSK_REG&=0b11111110;
	TMR_u8_TIMSK_REG|=TMR_u8_TMR0_OVER_FLOW_INTERRUPT_ENABLE ;
	//Set Action on Compare Match Unit
	TMR_u8_TMR0_TCCR0_REG &=0b11001111;
	TMR_u8_TMR0_TCCR0_REG |=Copy_u8_CompareMatchOutputMode;
	//Set Compare Match Unit.
	if (Copy_u8CompareMatchUnit==0)
	{
		TMR_u8_TMR0_OCR0_REG=0;
	}
	else
	{
		TMR_u8_TMR0_OCR0_REG = (Copy_u8CompareMatchUnit-1);
	}
	switch(Copy_u8CLK)
	{
	case TMR_u8_TMR0_NO_SOURCE_CLK :
		//Select Clock.
		TMR_u8_TMR0_TCCR0_REG&=0b11111000;
		TMR_u8_TMR0_TCCR0_REG|=TMR_u8_TMR0_NO_SOURCE_CLK;
		break;
	case TMR_u8_TMR0_MP_CLK :
		//Freq = 8M HZ
		//Time Of One Tick = 0.125 MicroSec = 125NanoSec
		//Time of over flow = 32 MicroSec
		if(Copy_u32Time_NanoSec==32000)
		{
			Preload_u8_TMR=1;
			//Set Preload Value into timer counter.
			TMR_u8_TMR0_TCNT0_REG = 0;
		}
		else if(Copy_u32Time_NanoSec<32000)
		{
			Preload_u8_TMR=2;
			//Set Preload Value into timer counter.
			*Preload_pu32_TMR0 = ((32000UL-Copy_u32Time_NanoSec)/1000);
			TMR_u8_TMR0_TCNT0_REG = *Preload_pu32_TMR0;
		}
		else if(Copy_u32Time_NanoSec>32000)
		{
			Preload_u8_TMR=3;
			Local_u32NumberOfOverFlow = (Copy_u32Time_NanoSec/32000UL);
			*CounterOVR_pu32_TMR0 = Local_u32NumberOfOverFlow;
			Local_u32NumberOfTick= (32-(((((Copy_u32Time_NanoSec*10000UL/32000)-(Local_u32NumberOfOverFlow*10000))*32000))/10000000));
			//Set Preload Value into timer counter.
			*Preload_pu32_TMR0 = Local_u32NumberOfTick;
			TMR_u8_TMR0_TCNT0_REG = *Preload_pu32_TMR0;
		}
		//Select Clock.
		TMR_u8_TMR0_TCCR0_REG&=0b11111000;
		TMR_u8_TMR0_TCCR0_REG|=TMR_u8_TMR0_MP_CLK;
		break;
	case TMR_u8_TMR0_CLK_DIVIDED_8 :
		//Freq = 1M HZ
		//Time Of One Tick = 1microSec = 1000NanoSec
		//Time of over flow = 256 MicroSec
		if(Copy_u32Time_NanoSec==256000)
		{
			Preload_u8_TMR=1;
			//Set Preload Value into timer counter.
			TMR_u8_TMR0_TCNT0_REG = 0;
		}
		else if(Copy_u32Time_NanoSec<256000)
		{
			Preload_u8_TMR=2;
			//Set Preload Value into timer counter.
			*Preload_pu32_TMR0 = ((256000UL-Copy_u32Time_NanoSec)/1000);
			TMR_u8_TMR0_TCNT0_REG = *Preload_pu32_TMR0;
		}
		else if(Copy_u32Time_NanoSec>256000)
		{
			Preload_u8_TMR=3;
			Local_u32NumberOfOverFlow = (Copy_u32Time_NanoSec/256000UL);//3906
			*CounterOVR_pu32_TMR0 = Local_u32NumberOfOverFlow;
			Local_u32NumberOfTick= (256-(((((Copy_u32Time_NanoSec*10000UL/256000)-(Local_u32NumberOfOverFlow*10000))*256000))/10000000));
			//Set Preload Value into timer counter.
			*Preload_pu32_TMR0 = Local_u32NumberOfTick;
			TMR_u8_TMR0_TCNT0_REG = *Preload_pu32_TMR0;
		}
		//Select Clock.
		TMR_u8_TMR0_TCCR0_REG&=0b11111000;
		TMR_u8_TMR0_TCCR0_REG|=TMR_u8_TMR0_CLK_DIVIDED_8;
		break;
	case TMR_u8_TMR0_CLK_DIVIDED_64 :
		//Freq = 1M HZ
		//Time Of One Tick = 8microSec = 8000NanoSec
		//Time of over flow = 2048 MicroSec
		if(Copy_u32Time_NanoSec==2048000)
		{
			Preload_u8_TMR=1;
			//Set Preload Value into timer counter.
			TMR_u8_TMR0_TCNT0_REG = 0;
		}
		else if(Copy_u32Time_NanoSec<2048000)
		{
			Preload_u8_TMR=2;
			//Set Preload Value into timer counter.
			*Preload_pu32_TMR0 = ((2048000UL-Copy_u32Time_NanoSec)/1000);
			TMR_u8_TMR0_TCNT0_REG = *Preload_pu32_TMR0;
		}
		else if(Copy_u32Time_NanoSec>2048000)
		{
			Preload_u8_TMR=3;
			Local_u32NumberOfOverFlow = (Copy_u32Time_NanoSec/2048000UL);//3906
			*CounterOVR_pu32_TMR0 = Local_u32NumberOfOverFlow;
			Local_u32NumberOfTick= (2048-(((((Copy_u32Time_NanoSec*10000UL/2048000)-(Local_u32NumberOfOverFlow*10000))*2048000))/10000000));
			//Set Preload Value into timer counter.
			*Preload_pu32_TMR0 = Local_u32NumberOfTick;
			TMR_u8_TMR0_TCNT0_REG = *Preload_pu32_TMR0;
		}
	//Select Clock.
		TMR_u8_TMR0_TCCR0_REG&=0b11111000;
		TMR_u8_TMR0_TCCR0_REG|=TMR_u8_TMR0_CLK_DIVIDED_64;
		break;
	case TMR_u8_TMR0_CLK_DIVIDED_256 :
		//Freq = 0.03125M HZ
		//Time Of One Tick = 32microSec = 32000NanoSec
		//Time of over flow = 8192 MicroSec
		if(Copy_u32Time_NanoSec==8192000)
		{
			Preload_u8_TMR=1;
			//Set Preload Value into timer counter.
			TMR_u8_TMR0_TCNT0_REG = 0;
		}
		else if(Copy_u32Time_NanoSec<8192000)
		{
			Preload_u8_TMR=2;
			//Set Preload Value into timer counter.
			*Preload_pu32_TMR0 = ((8192000UL-Copy_u32Time_NanoSec)/1000);
			TMR_u8_TMR0_TCNT0_REG = *Preload_pu32_TMR0;
		}
		else if(Copy_u32Time_NanoSec>8192000)
		{
			Preload_u8_TMR=3;
			Local_u32NumberOfOverFlow = (Copy_u32Time_NanoSec/8192000UL);//3906
			*CounterOVR_pu32_TMR0 = Local_u32NumberOfOverFlow;
			Local_u32NumberOfTick= (8192-(((((Copy_u32Time_NanoSec*10000UL/8192000)-(Local_u32NumberOfOverFlow*10000))*8192000))/10000000));
			//Set Preload Value into timer counter.
			*Preload_pu32_TMR0 = Local_u32NumberOfTick;
			TMR_u8_TMR0_TCNT0_REG = *Preload_pu32_TMR0;
		}
		//Select Clock.
		TMR_u8_TMR0_TCCR0_REG&=0b11111000;
		TMR_u8_TMR0_TCCR0_REG|=TMR_u8_TMR0_CLK_DIVIDED_256;
		break;
	case TMR_u8_TMR0_CLK_DIVIDED_1024 :
		//Freq = 7.8125*10^(-3)M HZ
		//Time Of One Tick = 128microSec = 128000NanoSec
		//Time of over flow = 32768 MicroSec
		if(Copy_u32Time_NanoSec==32768000)
		{
			Preload_u8_TMR=1;
			//Set Preload Value into timer counter.
			TMR_u8_TMR0_TCNT0_REG = 0;
		}
		else if(Copy_u32Time_NanoSec<32768000)
		{
			Preload_u8_TMR=2;
			//Set Preload Value into timer counter.
			*Preload_pu32_TMR0 = ((32768000UL-Copy_u32Time_NanoSec)/1000);
			TMR_u8_TMR0_TCNT0_REG = *Preload_pu32_TMR0;
		}
		else if(Copy_u32Time_NanoSec>32768000)
		{
			Preload_u8_TMR=3;
			Local_u32NumberOfOverFlow = (Copy_u32Time_NanoSec/32768000UL);
			*CounterOVR_pu32_TMR0 = Local_u32NumberOfOverFlow;
			Local_u32NumberOfTick= (32768-(((((Copy_u32Time_NanoSec*10000UL/32768000)-(Local_u32NumberOfOverFlow*10000))*32768000))/10000000));
			//Set Preload Value into timer counter.
			*Preload_pu32_TMR0 = Local_u32NumberOfTick;
			TMR_u8_TMR0_TCNT0_REG = *Preload_pu32_TMR0;
		}
		//Select Clock.
		TMR_u8_TMR0_TCCR0_REG&=0b11111000;
		TMR_u8_TMR0_TCCR0_REG|=TMR_u8_TMR0_CLK_DIVIDED_1024;
		break;
	//case TMR_u8_TMR0_EXTERNAL_CLK_FALLING_EDGE_PIN_T0 :
	//	Preload_u8_TMR=4;
	//	//Set Preload Value into timer counter.
	//	TMR_u8_TMR0_TCNT0_REG = 0;//ask.
	//	//Select Clock.
	//	TMR_u8_TMR0_TCCR0_REG&=0b11111000;
	//	TMR_u8_TMR0_TCCR0_REG|=TMR_u8_TMR0_EXTERNAL_CLK_FALLING_EDGE_PIN_T0;
	//	break;
	//case TMR_u8_TMR0_EXTERNAL_CLK_RISING_EDGE_PIN_T0 :
	//	Preload_u8_TMR=4;
	//	//Set Preload Value into timer counter.
	//	TMR_u8_TMR0_TCNT0_REG = 0;
	//	//Select Clock.
	//	TMR_u8_TMR0_TCCR0_REG&=0b11111000;
	//	TMR_u8_TMR0_TCCR0_REG|=TMR_u8_TMR0_EXTERNAL_CLK_RISING_EDGE_PIN_T0;
	//	break;
	default:Local_u8ErrorState = STD_TYPES_NOK;
	}
	return Local_u8ErrorState ;
}
//ISR of over flow timer 0 .
void __vector_11(void) __attribute__((signal));
void __vector_11(void)
{
	if(Preload_u8_TMR==1)
	{
		TMR_APF[TMR_u8_TMR0_OVF_MODE]();
	}
	else if(Preload_u8_TMR==2)
	{
		TMR_u8_TMR0_TCNT0_REG=*Preload_pu32_TMR0;
		TMR_APF[TMR_u8_TMR0_OVF_MODE]();
	}
	else if(Preload_u8_TMR==3)
	{
	static u16 Local_u16Counter = 0;
	Local_u16Counter++ ;
	if(Local_u16Counter ==((*CounterOVR_pu32_TMR0)+1))
	{
		//update Timer counter with preload value.
		TMR_u8_TMR0_TCNT0_REG=(*Preload_pu32_TMR0);
		//Action.
		//check if not = null;
		TMR_APF[TMR_u8_TMR0_OVF_MODE]();
		//Clear local Counter.
		Local_u16Counter = 0 ;
	}
	}
}
#elif TMR_u8_TIMER0_MODE == TMR_u8_TIMER0_CTC_WAVEFORM_GENERATION_MODE
static u32 CTC0_u32_Times=0;
static u32 *CTC0_pu32Times = &CTC0_u32_Times;
u8 TMR_u8TMR0CTCINIT(u8 Copy_u8NearestCompareMatchUnit,u8 Copy_u8CLK,u32 Copy_u32Time_NanoSec,u8 Copy_u8_CompareMatchOutputMode)
{
	u8 Local_u8ErrorState = STD_TYPES_OK;
	//Select Mode.
	TMR_u8_TMR0_TCCR0_REG&=0b10110111;
	TMR_u8_TMR0_TCCR0_REG|= TMR_u8_TMR0_CTC_WAVEFORM_GENERATION_MODE_PINB0;
	//Enable CTC Interrupt.
	SET_BIT(TMR_u8_TIMSK_REG,1);
	//Set Action on Compare Match Unit
	TMR_u8_TMR0_TCCR0_REG &=0b11001111;
	TMR_u8_TMR0_TCCR0_REG |=Copy_u8_CompareMatchOutputMode;
	switch(Copy_u8CLK)
	{
	case TMR_u8_TMR0_NO_SOURCE_CLK :
		//Select Clock.
		TMR_u8_TMR0_TCCR0_REG&=0b11111000;
		TMR_u8_TMR0_TCCR0_REG|=TMR_u8_TMR0_NO_SOURCE_CLK;
		break;
	case TMR_u8_TMR0_MP_CLK :
		//Select Clock.
		TMR_u8_TMR0_TCCR0_REG&=0b11111000;
		TMR_u8_TMR0_TCCR0_REG|=TMR_u8_TMR0_MP_CLK;
		break;
	case TMR_u8_TMR0_CLK_DIVIDED_8 :
		*CTC0_pu32Times=(Copy_u32Time_NanoSec/Copy_u8NearestCompareMatchUnit/1000);
		//Set Compare Match Value into timer counter.
		if(Copy_u8NearestCompareMatchUnit==0)
		{
			Local_u8ErrorState = STD_TYPES_NOK;
		}
		else
		{
		TMR_u8_TMR0_OCR0_REG = ((Copy_u8NearestCompareMatchUnit)-1);
		}
		//Select Clock.
		TMR_u8_TMR0_TCCR0_REG&=0b11111000;
		TMR_u8_TMR0_TCCR0_REG|=TMR_u8_TMR0_CLK_DIVIDED_8;
		break;
	case TMR_u8_TMR0_CLK_DIVIDED_64 :
		//Select Clock.
		TMR_u8_TMR0_TCCR0_REG&=0b11111000;
		TMR_u8_TMR0_TCCR0_REG|=TMR_u8_TMR0_CLK_DIVIDED_64;
		break;
	case TMR_u8_TMR0_CLK_DIVIDED_256 :
		//Select Clock.
		TMR_u8_TMR0_TCCR0_REG&=0b11111000;
		TMR_u8_TMR0_TCCR0_REG|=TMR_u8_TMR0_CLK_DIVIDED_256;
		break;
	case TMR_u8_TMR0_CLK_DIVIDED_1024 :
		//Select Clock.
		TMR_u8_TMR0_TCCR0_REG&=0b11111000;
		TMR_u8_TMR0_TCCR0_REG|=TMR_u8_TMR0_CLK_DIVIDED_1024;
		break;
	case TMR_u8_TMR0_EXTERNAL_CLK_FALLING_EDGE_PIN_PB0 :
		//Select Clock.
		TMR_u8_TMR0_TCCR0_REG&=0b11111000;
		TMR_u8_TMR0_TCCR0_REG|=TMR_u8_TMR0_EXTERNAL_CLK_FALLING_EDGE_PIN_PB0;
		break;
	case TMR_u8_TMR0_EXTERNAL_CLK_RISING_EDGE_PIN_PB0 :
		//Select Clock.
		TMR_u8_TMR0_TCCR0_REG&=0b11111000;
		TMR_u8_TMR0_TCCR0_REG|=TMR_u8_TMR0_EXTERNAL_CLK_RISING_EDGE_PIN_PB0;
		break;
	default:Local_u8ErrorState = STD_TYPES_NOK;
	}
	return Local_u8ErrorState ;
}
void TMR_voidTMR0ForcedOutputCompare(u8 Copy_u8_CompareMatchOutputMode)
{
	Preload_u8_TMR=8;
	//Set Action on Compare Match Unit
	TMR_u8_TMR0_TCCR0_REG &=0b11001111;
	TMR_u8_TMR0_TCCR0_REG |=Copy_u8_CompareMatchOutputMode;
	//Set Compare Match Mode.
	TMR_u8_TMR0_TCCR0_REG &=01111111;
	TMR_u8_TMR0_TCCR0_REG |= TMR_u8_TMR0_FORCE_OUTPUT_COMPARE_NO_PWM_ENABLE ;
}
//ISR of CTC timer 0 .
void __vector_10(void)__attribute__((signal));
void __vector_10(void)
{
	//Toggle every 1Sec
	static u16 Local_u16Counter = 0;
	Local_u16Counter++;
	if(Local_u16Counter==*CTC0_pu32Times)
	{
		//Action.
		TMR_APF[TMR_u8_TMR0_CTC_MODE]();
		//Clear Local_u16Counter.
		Local_u16Counter = 0;
	}
	else if (Preload_u8_TMR==8)
	{
		//Action.
		TMR_APF[TMR_u8_TMR0_CTC_MODE]();
	}
}
#elif TMR_u8_TIMER0_MODE == TMR_u8_TIMER0_NORMAL_COUNTER
u8 TMR_u8TMR0NormalCounter0INIT(u8 Copy_u8CLK , u32 *Copy_u32Counter )
{
	Preload_u8_TMR = 5;
	//static u8 Local_u8Handle=0;
	u8 Local_u8ErrorState = STD_TYPES_OK;
	//Select Mode.
	TMR_u8_TMR0_TCCR0_REG&=0b10110111;
	TMR_u8_TMR0_TCCR0_REG|= TMR_u8_TMR0_NORMAL_WAVEFORM_GENERATION_MODE;
	//Enable Over Flow Interrupt.
	TMR_u8_TIMSK_REG&=0b11111110;
	TMR_u8_TIMSK_REG|=TMR_u8_TMR0_OVER_FLOW_INTERRUPT_ENABLE;
	switch(Copy_u8CLK)
	{
	case TMR_u8_TMR0_NO_SOURCE_CLK :
		//Select Clock.
		TMR_u8_TMR0_TCCR0_REG&=0b11111000;
		TMR_u8_TMR0_TCCR0_REG|=TMR_u8_TMR0_NO_SOURCE_CLK;
		break;
	case TMR_u8_TMR0_MP_CLK :
		//Select Clock.
		TMR_u8_TMR0_TCCR0_REG&=0b11111000;
		TMR_u8_TMR0_TCCR0_REG|=TMR_u8_TMR0_MP_CLK;
		break;
	case TMR_u8_TMR0_CLK_DIVIDED_8 :
		//Select Clock.
		TMR_u8_TMR0_TCCR0_REG&=0b11111000;
		TMR_u8_TMR0_TCCR0_REG|=TMR_u8_TMR0_CLK_DIVIDED_8;
		break;
	case TMR_u8_TMR0_CLK_DIVIDED_64 :
		//Select Clock.
		TMR_u8_TMR0_TCCR0_REG&=0b11111000;
		TMR_u8_TMR0_TCCR0_REG|=TMR_u8_TMR0_CLK_DIVIDED_64;
		break;
	case TMR_u8_TMR0_CLK_DIVIDED_256 :
		//Select Clock.
		TMR_u8_TMR0_TCCR0_REG&=0b11111000;
		TMR_u8_TMR0_TCCR0_REG|=TMR_u8_TMR0_CLK_DIVIDED_256;
		break;
	case TMR_u8_TMR0_CLK_DIVIDED_1024 :
		//Select Clock.
		TMR_u8_TMR0_TCCR0_REG&=0b11111000;
		TMR_u8_TMR0_TCCR0_REG|=TMR_u8_TMR0_CLK_DIVIDED_1024;
		break;
	case TMR_u8_TMR0_EXTERNAL_CLK_FALLING_EDGE_PIN_PB0 :
		Preload_u8_TMR=4;
		//Set Preload Value into timer counter.
		//TMR_u8_TMR0_TCNT0_REG = 0;//ask.
		//Select Clock.
		TMR_u8_TMR0_TCCR0_REG&=0b11111000;
		TMR_u8_TMR0_TCCR0_REG|=TMR_u8_TMR0_EXTERNAL_CLK_FALLING_EDGE_PIN_PB0;
		break;
	case TMR_u8_TMR0_EXTERNAL_CLK_RISING_EDGE_PIN_PB0 :
		Preload_u8_TMR=4;
		//Set Preload Value into timer counter.
		//TMR_u8_TMR0_TCNT0_REG = 0;
		//Select Clock.
		TMR_u8_TMR0_TCCR0_REG&=0b11111000;
		TMR_u8_TMR0_TCCR0_REG|=TMR_u8_TMR0_EXTERNAL_CLK_RISING_EDGE_PIN_PB0;
		break;
	default:Local_u8ErrorState = STD_TYPES_NOK;
	}
	*Copy_u32Counter = ((Counter0_u8_OverFlow_TMR0 * 256UL)+TMR_u8_TMR0_TCNT0_REG);
    //	if((Counter0_u8_Handle_TMR0 > TMR_u8_TMR0_TCNT0_REG)||Counter0_u8_Handle_TMR0 < TMR_u8_TMR0_TCNT0_REG)
    //	{
    //		*Copy_u32Counter = *Copy_u32Counter + 1;
    //	}
    //	Counter0_u8_Handle_TMR0 = TMR_u8_TMR0_TCNT0_REG;
	// *Copy_u32Counter = TMR_u8_TMR0_TCNT0_REG;//test
	return Local_u8ErrorState;
}
//ISR of over flow timer 0 .
void __vector_11(void) __attribute__((signal));
void __vector_11(void)
{
	if (Preload_u8_TMR == 5)
	{
		Counter0_u8_OverFlow_TMR0++;
	}
}

#elif TMR_u8_TIMER0_MODE == TMR_u8_TIMER0_PWM_MODE
u8 TMR_u8TMR0PWM_TMR0INIT(u8 Copy_u8TimerMode,u8 Copy_u8ClockSelect,u8 Copy_u8InvertedORNonInverted,u8 Copy_u8SetDutyCycle)
{
	u8 Local_u8ErrorState = STD_TYPES_OK;
	switch(Copy_u8TimerMode)
	{
	case TMR_u8_TMR0_FAST_PWM_WAVEFORM_GENERATION_MODE_PINB3:
		TMR_u8_TMR0_TCCR0_REG&=0b10110111;
		TMR_u8_TMR0_TCCR0_REG|=TMR_u8_TMR0_FAST_PWM_WAVEFORM_GENERATION_MODE_PINB3;
		break;
	case TMR_u8_TMR0_PWM_PHASE_CORRECT_WAVEFORM_GENERATION_MODE_PINB3 :
		TMR_u8_TMR0_TCCR0_REG&=0b10110111;
		TMR_u8_TMR0_TCCR0_REG|=TMR_u8_TMR0_PWM_PHASE_CORRECT_WAVEFORM_GENERATION_MODE_PINB3;
	    break;
	default:Local_u8ErrorState = STD_TYPES_NOK;
	}
	//Select Inverting Mode.
	TMR_u8_TMR0_TCCR0_REG&=0b11001111;
	TMR_u8_TMR0_TCCR0_REG|=Copy_u8InvertedORNonInverted;
	//Set Compare Match Value into timer counter to control duty cycle.
	TMR_u8_TMR0_OCR0_REG = Copy_u8SetDutyCycle;// ((Copy_u8SetDutyCycle*255UL)/100);
	//Select Clock.
	TMR_u8_TMR0_TCCR0_REG&=0b11111000;
	TMR_u8_TMR0_TCCR0_REG|=Copy_u8ClockSelect;
	return Local_u8ErrorState;
}
#endif
//Used to update Compare match unit.
void TMR_voidTMR0SetCompareValue(u8 Copy_u8CompareMatchValue)
{
	TMR_u8_TMR0_OCR0_REG = Copy_u8CompareMatchValue ;
}
#endif


#if TMR_u8_TIMER1_ON_OR_OFF == TMR_TIMER1_ON
//Timer 1.
#if TMR_u8_TIMER1_MODE ==TMR_u8_TIMER1_NORMAL_MODE
static u32 Local_u32_TMR1NumberOfTick=0;
static u32 Local_u32_TMR1NumberOfOverFlow=0;
static u32 *Preload_pu32_TMR1 = &Local_u32_TMR1NumberOfTick ;
static u32 *CounterOVR_pu32_TMR1 = &Local_u32_TMR1NumberOfOverFlow;
u8 TMR_u8TMR1NormalINIT(u8 Copy_u8CLK,u32 Copy_u32Time_MicroSec,u8 Copy_u8CompareMatchUnitChannelA,u8 Copy_u8_CompareMatchOutputModeChannelA,u8 Copy_u8CompareMatchUnitChannelB,u8 Copy_u8_CompareMatchOutputModeChannelB)
{
	u8 Local_u8ErrorState = STD_TYPES_OK;
	//Select Mode.
	TMR_u16_TMR1_TCCR1_REG &= 0b1111110011100111;
	TMR_u16_TMR1_TCCR1_REG |= TMR_u16_TMR1_NORMAL_WAVEFORM_GENERATION_MODE ;
	//Enable Over Flow Interrupt.
	TMR_u8_TIMSK_REG&=0b11111011;
	TMR_u8_TIMSK_REG|=TMR_u8_TMR1_OVER_FLOW_INTERRUPT_ENABLE ;
	//Set Action on Compare Match Unit For Channel A.
	TMR_u8_TMR1_TCCR1A_REG &=0b00111111;
	TMR_u8_TMR1_TCCR1A_REG |=Copy_u8_CompareMatchOutputModeChannelA;
	//Set Compare Match Unit For Channel A.
	if (Copy_u8CompareMatchUnitChannelA==0)
	{
		TMR_u16_TMR1_OCR1A_REG = 0 ;
	}
	else
	{
		TMR_u16_TMR1_OCR1A_REG = (Copy_u8CompareMatchUnitChannelA-1);
	}
	//Set Action on Compare Match Unit For Channel B.
	TMR_u8_TMR1_TCCR1B_REG &=0b11001111;
	TMR_u8_TMR1_TCCR1B_REG |=Copy_u8_CompareMatchOutputModeChannelB;
	//Set Compare Match Unit For Channel B.
	if (Copy_u8CompareMatchUnitChannelB==0)
	{
		TMR_u16_TMR1_OCR1B_REG = 0 ;
	}
	else
	{
		TMR_u16_TMR1_OCR1B_REG = (Copy_u8CompareMatchUnitChannelB-1);
	}
	switch(Copy_u8CLK)
	{
	case TMR_u8_TMR1_NO_SOURCE_CLK :
		//Select Clock.
		TMR_u8_TMR1_TCCR1B_REG&=0b11111000;
		TMR_u8_TMR1_TCCR1B_REG|=TMR_u8_TMR1_NO_SOURCE_CLK;
		break;
	case TMR_u8_TMR1_MP_CLK :
		//Freq = 8M HZ
		//Time Of One Tick = 0.125 MicroSec = 125NanoSec
		//Time of over flow = 8192 MicroSec
		if(Copy_u32Time_MicroSec==8192)
		{
			Preload_u8_TMR=10;
			//Set Preload Value into timer counter.
			TMR_u16_TMR1_TCNT1_REG = 0;
		}
		else if(Copy_u32Time_MicroSec<8192)
		{
			Preload_u8_TMR=11;
			//Set Preload Value into timer counter.
			*Preload_pu32_TMR1 = (8192-Copy_u32Time_MicroSec);
			TMR_u16_TMR1_TCNT1_REG = *Preload_pu32_TMR1;
		}
		else if(Copy_u32Time_MicroSec>8192)
		{
			Preload_u8_TMR=12;
			Local_u32_TMR1NumberOfOverFlow = (Copy_u32Time_MicroSec/8192UL);
			*CounterOVR_pu32_TMR1 = Local_u32_TMR1NumberOfOverFlow;
			Local_u32_TMR1NumberOfTick= (8192-((((Copy_u32Time_MicroSec*10000/8192UL)-(Local_u32_TMR1NumberOfOverFlow*10000))*8192UL)/10000));
			//Set Preload Value into timer counter.
			*Preload_pu32_TMR1 = Local_u32_TMR1NumberOfTick;
			TMR_u16_TMR1_TCNT1_REG = *Preload_pu32_TMR1;
		}
		//Select Clock.
		TMR_u8_TMR1_TCCR1B_REG&=0b11111000;
		TMR_u8_TMR1_TCCR1B_REG|=TMR_u8_TMR1_MP_CLK;
		break;
	case TMR_u8_TMR1_CLK_DIVIDED_8 :
		//Freq = 1M HZ
		//Time Of One Tick = 1microSec = 1000NanoSec
		//Time of over flow = 65536 MicroSec
		if(Copy_u32Time_MicroSec==65536)
		{
			Preload_u8_TMR=10;
			//Set Preload Value into timer counter.
			TMR_u16_TMR1_TCNT1_REG = 0;
		}
		else if(Copy_u32Time_MicroSec<65536)
		{
			Preload_u8_TMR=11;
			//Set Preload Value into timer counter.
			*Preload_pu32_TMR1 = (65536-Copy_u32Time_MicroSec);
			TMR_u16_TMR1_TCNT1_REG = *Preload_pu32_TMR1;
		}
		else if(Copy_u32Time_MicroSec>65536)
		{
			Preload_u8_TMR=12;
			Local_u32_TMR1NumberOfOverFlow = (Copy_u32Time_MicroSec/65536UL);
			*CounterOVR_pu32_TMR1 = Local_u32_TMR1NumberOfOverFlow;
			Local_u32_TMR1NumberOfTick= (65536-((((Copy_u32Time_MicroSec*10000/65536UL)-(Local_u32_TMR1NumberOfOverFlow*10000))*65536UL)/10000));
			//Set Preload Value into timer counter.
			*Preload_pu32_TMR1 = Local_u32_TMR1NumberOfTick;
			TMR_u16_TMR1_TCNT1_REG = *Preload_pu32_TMR1;
		}
		//Select Clock.
		TMR_u8_TMR1_TCCR1B_REG&=0b11111000;
		TMR_u8_TMR1_TCCR1B_REG|=TMR_u8_TMR1_CLK_DIVIDED_8;
		break;
	case TMR_u8_TMR1_CLK_DIVIDED_64 :
		//Freq = 1M HZ
		//Time Of One Tick = 8microSec = 8000NanoSec
		//Time of over flow = 524288 MicroSec
		if(Copy_u32Time_MicroSec==524288)
		{
			Preload_u8_TMR=10;
			//Set Preload Value into timer counter.
			TMR_u16_TMR1_TCNT1_REG = 0;
		}
		else if(Copy_u32Time_MicroSec<524288)
		{
			Preload_u8_TMR=11;
			//Set Preload Value into timer counter.
			*Preload_pu32_TMR1 = (524288-Copy_u32Time_MicroSec);
			TMR_u16_TMR1_TCNT1_REG = *Preload_pu32_TMR1;
		}
		else if(Copy_u32Time_MicroSec>524288)
		{
			Preload_u8_TMR=12;
			Local_u32_TMR1NumberOfOverFlow = (Copy_u32Time_MicroSec/524288UL);
			*CounterOVR_pu32_TMR1 = Local_u32_TMR1NumberOfOverFlow;
			Local_u32_TMR1NumberOfTick= (524288-((((Copy_u32Time_MicroSec*10000/524288UL)-(Local_u32_TMR1NumberOfOverFlow*10000))*524288UL)/10000));
			//Set Preload Value into timer counter.
			*Preload_pu32_TMR1 = Local_u32_TMR1NumberOfTick;
			TMR_u16_TMR1_TCNT1_REG = *Preload_pu32_TMR1;
		}
	//Select Clock.
		TMR_u8_TMR1_TCCR1B_REG&=0b11111000;
		TMR_u8_TMR1_TCCR1B_REG|=TMR_u8_TMR1_CLK_DIVIDED_64;
		break;
	case TMR_u8_TMR1_CLK_DIVIDED_256 :
		//Freq = 0.03125M HZ
		//Time Of One Tick = 32microSec = 32000NanoSec
		//Time of over flow = 2097152 MicroSec
		if(Copy_u32Time_MicroSec==2097152)
		{
			Preload_u8_TMR=10;
			//Set Preload Value into timer counter.
			TMR_u16_TMR1_TCNT1_REG = 0;
		}
		else if(Copy_u32Time_MicroSec<2097152)
		{
			Preload_u8_TMR=11;
			//Set Preload Value into timer counter.
			*Preload_pu32_TMR1 = (2097152-Copy_u32Time_MicroSec);
			TMR_u16_TMR1_TCNT1_REG = *Preload_pu32_TMR1;
		}
		else if(Copy_u32Time_MicroSec>2097152)
		{
			Preload_u8_TMR=12;
			Local_u32_TMR1NumberOfOverFlow = (Copy_u32Time_MicroSec/2097152UL);
			*CounterOVR_pu32_TMR1 = Local_u32_TMR1NumberOfOverFlow;
			Local_u32_TMR1NumberOfTick= (2097152-((((Copy_u32Time_MicroSec*10000/2097152UL)-(Local_u32_TMR1NumberOfOverFlow*10000))*2097152UL)/10000));
			//Set Preload Value into timer counter.
			*Preload_pu32_TMR1 = Local_u32_TMR1NumberOfTick;
			TMR_u16_TMR1_TCNT1_REG = *Preload_pu32_TMR1;
		}
		//Select Clock.
		TMR_u8_TMR1_TCCR1B_REG&=0b11111000;
		TMR_u8_TMR1_TCCR1B_REG|=TMR_u8_TMR1_CLK_DIVIDED_256;
		break;
	case TMR_u8_TMR1_CLK_DIVIDED_1024 :
		//Freq = 7.8125*10^(-3)M HZ
		//Time Of One Tick = 128microSec = 128000NanoSec
		//Time of over flow = 8388608 MicroSec
		if(Copy_u32Time_MicroSec==8388608)
		{
			Preload_u8_TMR=10;
			//Set Preload Value into timer counter.
			TMR_u16_TMR1_TCNT1_REG = 0;
		}
		else if(Copy_u32Time_MicroSec<8388608)
		{
			Preload_u8_TMR=11;
			//Set Preload Value into timer counter.
			*Preload_pu32_TMR1 = (8388608-Copy_u32Time_MicroSec);
			TMR_u16_TMR1_TCNT1_REG = *Preload_pu32_TMR1;
		}
		else if(Copy_u32Time_MicroSec>8388608)
		{
			Preload_u8_TMR=12;
			Local_u32_TMR1NumberOfOverFlow = (Copy_u32Time_MicroSec/8388608UL);
			*CounterOVR_pu32_TMR1 = Local_u32_TMR1NumberOfOverFlow;
			Local_u32_TMR1NumberOfTick= (8388608-((((Copy_u32Time_MicroSec*10000/8388608UL)-(Local_u32_TMR1NumberOfOverFlow*10000))*8388608UL)/10000));
			//Set Preload Value into timer counter.
			*Preload_pu32_TMR1 = Local_u32_TMR1NumberOfTick;
			TMR_u16_TMR1_TCNT1_REG = *Preload_pu32_TMR1;
		}
		//Select Clock.
		TMR_u8_TMR1_TCCR1B_REG&=0b11111000;
		TMR_u8_TMR1_TCCR1B_REG|=TMR_u8_TMR1_CLK_DIVIDED_1024;
		break;
	default:Local_u8ErrorState = STD_TYPES_NOK;
	}
	return Local_u8ErrorState ;
}

//ISR of over flow timer 1 .
void __vector_9(void) __attribute__((signal));
void __vector_9(void)
{
	if(Preload_u8_TMR==10)
	{
		TMR_APF[TMR_u8_TMR1_OVF_MODE]();
	}
	else if(Preload_u8_TMR==11)
	{
		TMR_u16_TMR1_TCNT1_REG=*Preload_pu32_TMR1;
		TMR_APF[TMR_u8_TMR1_OVF_MODE]();
	}
	else if(Preload_u8_TMR==12)
	{
	static u16 Local_u16Counter_TMR1 = 0;
	Local_u16Counter_TMR1++ ;
	if(Local_u16Counter_TMR1 ==((*CounterOVR_pu32_TMR1)+1))
	{
		//update Timer counter with preload value.
		TMR_u16_TMR1_TCNT1_REG=(*Preload_pu32_TMR1);
		//Action.
		//check if not = null;
		TMR_APF[TMR_u8_TMR1_OVF_MODE]();
		//Clear local Counter.
		Local_u16Counter_TMR1 = 0 ;
	}
	}
}

#elif TMR_u8_TIMER1_MODE == TMR_u8_TIMER1_CTC_WAVEFORM_GENERATION_MODE
static u32 CTC1_u32_Times_A=0;
static u32 *CTC1_pu32Times_A = &CTC1_u32_Times_A;
static u32 CTC1_u32_Times_B=0;
static u32 *CTC1_pu32Times_B = &CTC1_u32_Times_B;
//don't forget action on HW pin.
u8 TMR_u8TMR1CTCINIT(u8 Copy_u8CTCMode,u8 Copy_u8SelectChannel_AORB,u16 Copy_u16NearestCompareMatchUnit,u8 Copy_u8CLK,u32 Copy_u32Time_MicroSec,u8 Copy_u8_CompareMatchOutputModeAORB)
{
	u8 Local_u8ErrorState = STD_TYPES_OK;
	//Select Mode.
	switch (Copy_u8CTCMode)
	{
	TMR_u16_TMR1_TCCR1_REG &= 0b1111110011100111;
	case TMR_u16_TMR1_CTC_WAVEFORM_GENERATION_MODE_1:
	TMR_u16_TMR1_TCCR1_REG |= TMR_u16_TMR1_CTC_WAVEFORM_GENERATION_MODE_1;
	break;
	case TMR_u16_TMR1_CTC_WAVEFORM_GENERATION_MODE_2:
	TMR_u16_TMR1_TCCR1_REG |= TMR_u16_TMR1_CTC_WAVEFORM_GENERATION_MODE_2;
	break;
	default : Local_u8ErrorState = STD_TYPES_NOK;
	}
	//Initialize Counter.
	TMR_u16_TMR1_TCNT1_REG = 0 ;
	switch(Copy_u8CLK)
	{
	case TMR_u8_TMR1_NO_SOURCE_CLK :
		//Select Clock.
		TMR_u8_TMR1_TCCR1B_REG&=0b11111000;
		TMR_u8_TMR1_TCCR1B_REG|=TMR_u8_TMR1_NO_SOURCE_CLK;
		break;
	case TMR_u8_TMR1_MP_CLK :
		//Select Clock.
		TMR_u8_TMR1_TCCR1B_REG&=0b11111000;
		TMR_u8_TMR1_TCCR1B_REG|=TMR_u8_TMR1_MP_CLK;
		break;
	case TMR_u8_TMR1_CLK_DIVIDED_8 :
		//Select Channel.
		if (Copy_u8CTCMode == TMR_u16_TMR1_CTC_WAVEFORM_GENERATION_MODE_2)
		{
			*CTC1_pu32Times_A=((Copy_u32Time_MicroSec*1UL/Copy_u16NearestCompareMatchUnit)/1UL);//1000
			//Set Compare Match Value into timer counter in Channel A.
			if(Copy_u16NearestCompareMatchUnit!=0)
			{
				TMR_u16_TMR1_ICR1_REG = ((Copy_u16NearestCompareMatchUnit*1UL)-1);//999
			}
			else
			{
				Local_u8ErrorState = STD_TYPES_NOK;
			}
		}
		else if(Copy_u8SelectChannel_AORB==TMR_u8_TMR1_COMPARE_OUTPUT_MODE_CAHNNEL_A_PIN_PD5 )
		{
			*CTC1_pu32Times_A=((Copy_u32Time_MicroSec*1UL/Copy_u16NearestCompareMatchUnit)/1UL);//1000
			//Set Compare Match Value into timer counter in Channel A.
			if(Copy_u16NearestCompareMatchUnit!=0)
			{
				TMR_u16_TMR1_OCR1A_REG = ((Copy_u16NearestCompareMatchUnit*1UL)-1);//999
			}
			else
			{
				Local_u8ErrorState = STD_TYPES_NOK;
			}
			//Enable CTC Interrupt For Channel A.
			TMR_u8_TIMSK_REG &=11101111;
			TMR_u8_TIMSK_REG |= TMR_u8_TMR1_OUTPUT_COMPARE_MATCH_INTERRUPT_ENABLE_A;
			//Set Action on Compare Match Unit For Channel A.
			TMR_u8_TMR1_TCCR1A_REG &=0b00111111;
			TMR_u8_TMR1_TCCR1A_REG |=Copy_u8_CompareMatchOutputModeAORB;
		}
		else if(Copy_u8SelectChannel_AORB==TMR_u8_TMR1_COMPARE_OUTPUT_MODE_CAHNNEL_B_PIN_PD4 )
		{
			*CTC1_pu32Times_B=(Copy_u32Time_MicroSec/Copy_u16NearestCompareMatchUnit);
			//Set Compare Match Value into timer counter in Channel B.
			if(Copy_u16NearestCompareMatchUnit==0)
			{
				TMR_u16_TMR1_OCR1B_REG = ((Copy_u16NearestCompareMatchUnit)-1);
			}
			else
			{
				Local_u8ErrorState = STD_TYPES_NOK;
			}
			//Enable CTC Interrupt For Channel B.
			TMR_u8_TIMSK_REG &=11110111;
			TMR_u8_TIMSK_REG |= TMR_u8_TMR1_OUTPUT_COMPARE_MATCH_INTERRUPT_ENABLE_B;
			//Set Action on Compare Match Unit For Channel A.
			TMR_u8_TMR1_TCCR1A_REG &=0b11001111;
			TMR_u8_TMR1_TCCR1A_REG |=Copy_u8_CompareMatchOutputModeAORB;
		}
		//Select Clock.
		TMR_u8_TMR1_TCCR1B_REG&=0b11111000;
		TMR_u8_TMR1_TCCR1B_REG|=TMR_u8_TMR1_CLK_DIVIDED_8;
		break;
	case TMR_u8_TMR1_CLK_DIVIDED_64 :
		//Select Clock.
		TMR_u8_TMR1_TCCR1B_REG&=0b11111000;
		TMR_u8_TMR1_TCCR1B_REG|=TMR_u8_TMR1_CLK_DIVIDED_64;
		break;
	case TMR_u8_TMR1_CLK_DIVIDED_256 :
		//Select Clock.
		TMR_u8_TMR1_TCCR1B_REG&=0b11111000;
		TMR_u8_TMR1_TCCR1B_REG|=TMR_u8_TMR1_CLK_DIVIDED_256;
		break;
	case TMR_u8_TMR1_CLK_DIVIDED_1024 :
		//Select Clock.
		TMR_u8_TMR1_TCCR1B_REG&=0b11111000;
		TMR_u8_TMR1_TCCR1B_REG|=TMR_u8_TMR1_CLK_DIVIDED_1024;
		break;
	case TMR_u8_TMR1_EXTERNAL_CLK_FALLING_EDGE_PIN_PB1 :
		//Select Clock.
		TMR_u8_TMR1_TCCR1B_REG&=0b11111000;
		TMR_u8_TMR1_TCCR1B_REG|=TMR_u8_TMR1_EXTERNAL_CLK_FALLING_EDGE_PIN_PB1;
		break;
	case TMR_u8_TMR1_EXTERNAL_CLK_RISING_EDGE_PIN_PB1 :
		//Select Clock.
		TMR_u8_TMR1_TCCR1B_REG&=0b11111000;
		TMR_u8_TMR1_TCCR1B_REG|=TMR_u8_TMR1_EXTERNAL_CLK_RISING_EDGE_PIN_PB1;
		break;
	default:Local_u8ErrorState = STD_TYPES_NOK;
	}
	return Local_u8ErrorState ;
}

void TMR_voidTMR1_AForcedOutputCompare(u8 Copy_u8_CompareMatchOutputMode_A)
{
	Preload_u8_TMR=21;
	//Set Action on Compare Match Unit
	TMR_u8_TMR1_TCCR1A_REG &=0b00111111;
	TMR_u8_TMR1_TCCR1A_REG |=Copy_u8_CompareMatchOutputMode_A;
	//Set Compare Match Mode.
	TMR_u8_TMR1_TCCR1A_REG &=11110111;
	TMR_u8_TMR1_TCCR1A_REG |= TMR_u8_TMR1_FORCED_COMPARE_MATCH_UNIT_CHANNEL_A ;
}
void TMR_voidTMR1_BForcedOutputCompare(u8 Copy_u8_CompareMatchOutputMode_B)
{
	Preload_u8_TMR=21;
	//Set Action on Compare Match Unit
	TMR_u8_TMR1_TCCR1A_REG &=0b11001111;
	TMR_u8_TMR1_TCCR1A_REG |=Copy_u8_CompareMatchOutputMode_B;
	//Set Compare Match Mode.
	TMR_u8_TMR1_TCCR1A_REG &=11111011;
	TMR_u8_TMR1_TCCR1A_REG |= TMR_u8_TMR1_FORCED_COMPARE_MATCH_UNIT_CHANNEL_B ;
}

//ISR of CTC timer 1 Channel A .
void __vector_7(void)__attribute__((signal));
void __vector_7(void)
{
	static u16 Local_u16Counter_A = 0;
	Local_u16Counter_A++;
	if(Local_u16Counter_A == *CTC1_pu32Times_A)
	{
		//Action.
		TMR_APF[TMR_u8_TMR1_CTC_MODE_Channel_A]();
		//Clear Local_u16Counter.
		Local_u16Counter_A = 0;
	}
	else if (Preload_u8_TMR==21)//Forced Compare Match unit Channel A.
	{
		//Action.
		TMR_APF[TMR_u8_TMR1_CTC_MODE_Channel_A]();
	}
}

//ISR of CTC timer 1 Channel B .
void __vector_8(void)__attribute__((signal));
void __vector_8(void)
{
	static u16 Local_u16Counter_B = 0;
	Local_u16Counter_B++;
	if(Local_u16Counter_B==*CTC1_pu32Times_B)
	{
		//Action.
		TMR_APF[TMR_u8_TMR1_CTC_MODE_Channel_B]();
		//Clear Local_u16Counter.
		Local_u16Counter_B = 0;
	}
 	else if (Preload_u8_TMR==22)//Forced Compare Match unit Channel B.
 	{
 		//Action.
 		TMR_APF[TMR_u8_TMR1_CTC_MODE_Channel_B]();
  	}
}
#elif TMR_u8_TIMER1_MODE == TMR_u8_TIMER1_PWM_8_9_10_BIT_PHASE_CORRECT_AND_FAST_PWM_MODE

u8 TMR_u8TMR1_A_PWM_TMR1INIT(u8 Copy_u8TimerMode_A,u16 Copy_u16PWMSelecion_A,u8 Copy_u8ClockSelect,u8 Copy_u8InvertedORNonInverted_A,u16 Copy_u16SetDutyCycle_A)
{
	u8 Local_u8ErrorState = STD_TYPES_OK;
	if(Copy_u8TimerMode_A ==TMR_u8_TMR1_FAST_PWM_WAVEFORM_GENERATION_MODE)
	{
		switch (Copy_u16PWMSelecion_A)
		{
		case TMR_u16_TMR1_PWM_FAST_8_Bit_WAVEFORM_GENERATION_MODE:
			TMR_u16_TMR1_TCCR1_REG &= 0b1111110011100111;
			TMR_u16_TMR1_TCCR1_REG |= TMR_u16_TMR1_PWM_FAST_8_Bit_WAVEFORM_GENERATION_MODE;
			//Set Compare Match Value into timer counter to control duty cycle.
			TMR_u16_TMR1_OCR1A_REG = ((Copy_u16SetDutyCycle_A*255UL)/100);
			//Select Inverting Mode.
			TMR_u8_TMR1_TCCR1A_REG&=0b00111111;
			TMR_u8_TMR1_TCCR1A_REG|=Copy_u8InvertedORNonInverted_A;
			break;
		case TMR_u16_TMR1_PWM_FAST_9_Bit_WAVEFORM_GENERATION_MODE:
			TMR_u16_TMR1_TCCR1_REG &= 0b1111110011100111;
			TMR_u16_TMR1_TCCR1_REG |= TMR_u16_TMR1_PWM_FAST_9_Bit_WAVEFORM_GENERATION_MODE;
			//Set Compare Match Value into timer counter to control duty cycle.
			TMR_u16_TMR1_OCR1A_REG = ((Copy_u16SetDutyCycle_A*511UL)/100);
			//Select Inverting Mode.
			TMR_u8_TMR1_TCCR1A_REG&=0b00111111;
			TMR_u8_TMR1_TCCR1A_REG|=Copy_u8InvertedORNonInverted_A;
			break;
		case TMR_u16_TMR1_PWM_FAST_10_Bit_WAVEFORM_GENERATION_MODE:
			TMR_u16_TMR1_TCCR1_REG &= 0b1111110011100111;
			TMR_u16_TMR1_TCCR1_REG |= TMR_u16_TMR1_PWM_FAST_10_Bit_WAVEFORM_GENERATION_MODE;
			//Set Compare Match Value into timer counter to control duty cycle.
			TMR_u16_TMR1_OCR1A_REG = ((Copy_u16SetDutyCycle_A*1023UL)/100);
			//Select Inverting Mode.
			TMR_u8_TMR1_TCCR1A_REG&=0b00111111;
			TMR_u8_TMR1_TCCR1A_REG|=Copy_u8InvertedORNonInverted_A;
			break;
		default : Local_u8ErrorState = STD_TYPES_NOK;
		}
	}

	if(Copy_u8TimerMode_A==TMR_u8_TMR1_PWM_PHASE_CORRECT_WAVEFORM_GENERATION_MODE)
	{
		switch (Copy_u16PWMSelecion_A)
		{
		case TMR_u16_TMR1_PWM_FAST_8_Bit_WAVEFORM_GENERATION_MODE:
			TMR_u16_TMR1_TCCR1_REG &= 0b1111110011100111;
			TMR_u16_TMR1_TCCR1_REG |= TMR_u16_TMR1_PWM_PHASE_CORRECT_8_Bit_WAVEFORM_GENERATION_MODE;
			//Set Compare Match Value into timer counter to control duty cycle.
			TMR_u16_TMR1_OCR1A_REG = ((Copy_u16SetDutyCycle_A*255UL)/100);
			//Select Inverting Mode.
			TMR_u8_TMR1_TCCR1A_REG&=0b00111111;
			TMR_u8_TMR1_TCCR1A_REG|=Copy_u8InvertedORNonInverted_A;
			break;
		case TMR_u16_TMR1_PWM_FAST_9_Bit_WAVEFORM_GENERATION_MODE:
			TMR_u16_TMR1_TCCR1_REG &= 0b1111110011100111;
			TMR_u16_TMR1_TCCR1_REG |= TMR_u16_TMR1_PWM_PHASE_CORRECT_9_Bit_WAVEFORM_GENERATION_MODE;
			//Set Compare Match Value into timer counter to control duty cycle.
			TMR_u16_TMR1_OCR1A_REG = ((Copy_u16SetDutyCycle_A*511UL)/100);
			//Select Inverting Mode.
			TMR_u8_TMR1_TCCR1A_REG&=0b00111111;
			TMR_u8_TMR1_TCCR1A_REG|=Copy_u8InvertedORNonInverted_A;
			break;
		case TMR_u16_TMR1_PWM_FAST_10_Bit_WAVEFORM_GENERATION_MODE:
			TMR_u16_TMR1_TCCR1_REG &= 0b1111110011100111;
			TMR_u16_TMR1_TCCR1_REG |= TMR_u16_TMR1_PWM_PHASE_CORRECT_10_Bit_WAVEFORM_GENERATION_MODE;
			//Set Compare Match Value into timer counter to control duty cycle.
			TMR_u16_TMR1_OCR1A_REG = ((Copy_u16SetDutyCycle_A*1023UL)/100);
			//Select Inverting Mode.
			TMR_u8_TMR1_TCCR1A_REG&=0b00111111;
			TMR_u8_TMR1_TCCR1A_REG|=Copy_u8InvertedORNonInverted_A;
			break;
		default : Local_u8ErrorState = STD_TYPES_NOK;
		}
	}
	//Select Clock.
	TMR_u8_TMR1_TCCR1B_REG&=0b11111000;
	TMR_u8_TMR1_TCCR1B_REG|=Copy_u8ClockSelect;
	return Local_u8ErrorState;
}

u8 TMR_u8TMR1_B_PWM_TMR1INIT(u8 Copy_u8TimerMode_B,u16 Copy_u16PWMSelecion_B,u8 Copy_u8ClockSelect,u8 Copy_u8InvertedORNonInverted_B,u16 Copy_u16SetDutyCycle_B)
{
	u8 Local_u8ErrorState = STD_TYPES_OK;
	if(Copy_u8TimerMode_B ==TMR_u8_TMR1_FAST_PWM_WAVEFORM_GENERATION_MODE)
	{
		switch (Copy_u16PWMSelecion_B)
		{
		case TMR_u16_TMR1_PWM_FAST_8_Bit_WAVEFORM_GENERATION_MODE:
			TMR_u16_TMR1_TCCR1_REG &= 0b1111110011100111;
			TMR_u16_TMR1_TCCR1_REG |= TMR_u16_TMR1_PWM_FAST_8_Bit_WAVEFORM_GENERATION_MODE;
			//Set Compare Match Value into timer counter to control duty cycle.
			TMR_u16_TMR1_OCR1B_REG = ((Copy_u16SetDutyCycle_B*255UL)/100);
			//Select Inverting Mode.
			TMR_u8_TMR1_TCCR1A_REG&=0b11001111;
			TMR_u8_TMR1_TCCR1A_REG|=Copy_u8InvertedORNonInverted_B;
			break;
		case TMR_u16_TMR1_PWM_FAST_9_Bit_WAVEFORM_GENERATION_MODE:
			TMR_u16_TMR1_TCCR1_REG &= 0b1111110011100111;
			TMR_u16_TMR1_TCCR1_REG |= TMR_u16_TMR1_PWM_FAST_9_Bit_WAVEFORM_GENERATION_MODE;
			//Set Compare Match Value into timer counter to control duty cycle.
			TMR_u16_TMR1_OCR1B_REG = ((Copy_u16SetDutyCycle_B*511UL)/100);
			//Select Inverting Mode.
			TMR_u8_TMR1_TCCR1A_REG&=0b11001111;
			TMR_u8_TMR1_TCCR1A_REG|=Copy_u8InvertedORNonInverted_B;
			break;
		case TMR_u16_TMR1_PWM_FAST_10_Bit_WAVEFORM_GENERATION_MODE:
			TMR_u16_TMR1_TCCR1_REG &= 0b1111110011100111;
			TMR_u16_TMR1_TCCR1_REG |= TMR_u16_TMR1_PWM_FAST_10_Bit_WAVEFORM_GENERATION_MODE;
			//Set Compare Match Value into timer counter to control duty cycle.
			TMR_u16_TMR1_OCR1B_REG = ((Copy_u16SetDutyCycle_B*1023UL)/100);
			//Select Inverting Mode.
			TMR_u8_TMR1_TCCR1A_REG&=0b11001111;
			TMR_u8_TMR1_TCCR1A_REG|=Copy_u8InvertedORNonInverted_B;
			break;
		default : Local_u8ErrorState = STD_TYPES_NOK;
		}
	}

	if(Copy_u8TimerMode_B==TMR_u8_TMR1_PWM_PHASE_CORRECT_WAVEFORM_GENERATION_MODE)
	{
		switch (Copy_u16PWMSelecion_B)
		{
		case TMR_u16_TMR1_PWM_FAST_8_Bit_WAVEFORM_GENERATION_MODE:
			TMR_u16_TMR1_TCCR1_REG &= 0b1111110011100111;
			TMR_u16_TMR1_TCCR1_REG |= TMR_u16_TMR1_PWM_PHASE_CORRECT_8_Bit_WAVEFORM_GENERATION_MODE;
			//Set Compare Match Value into timer counter to control duty cycle.
			TMR_u16_TMR1_OCR1B_REG = ((Copy_u16SetDutyCycle_B*255UL)/100);
			//Select Inverting Mode.
			TMR_u8_TMR1_TCCR1A_REG&=0b11001111;
			TMR_u8_TMR1_TCCR1A_REG|=Copy_u8InvertedORNonInverted_B;
			break;
		case TMR_u16_TMR1_PWM_FAST_9_Bit_WAVEFORM_GENERATION_MODE:
			TMR_u16_TMR1_TCCR1_REG &= 0b1111110011100111;
			TMR_u16_TMR1_TCCR1_REG |= TMR_u16_TMR1_PWM_PHASE_CORRECT_9_Bit_WAVEFORM_GENERATION_MODE;
			//Set Compare Match Value into timer counter to control duty cycle.
			TMR_u16_TMR1_OCR1B_REG = ((Copy_u16SetDutyCycle_B*511UL)/100);
			//Select Inverting Mode.
			TMR_u8_TMR1_TCCR1A_REG&=0b11001111;
			TMR_u8_TMR1_TCCR1A_REG|=Copy_u8InvertedORNonInverted_B;
			break;
		case TMR_u16_TMR1_PWM_FAST_10_Bit_WAVEFORM_GENERATION_MODE:
			TMR_u16_TMR1_TCCR1_REG &= 0b1111110011100111;
			TMR_u16_TMR1_TCCR1_REG |= TMR_u16_TMR1_PWM_PHASE_CORRECT_10_Bit_WAVEFORM_GENERATION_MODE;
			//Set Compare Match Value into timer counter to control duty cycle.
			TMR_u16_TMR1_OCR1B_REG = ((Copy_u16SetDutyCycle_B*1023UL)/100);
			//Select Inverting Mode.
			TMR_u8_TMR1_TCCR1A_REG&=0b11001111;
			TMR_u8_TMR1_TCCR1A_REG|=Copy_u8InvertedORNonInverted_B;
			break;
		default : Local_u8ErrorState = STD_TYPES_NOK;
		}
	}
	//Select Clock.
	TMR_u8_TMR1_TCCR1B_REG&=0b11111000;
	TMR_u8_TMR1_TCCR1B_REG|=Copy_u8ClockSelect;
	return Local_u8ErrorState;
}

#elif TMR_u8_TIMER1_MODE == TMR_u8_TIMER1_NORMAL_COUNTER
u8 Counter1_u8_Handle_TMR1 = 0;
static u16 Counter1_u16_OverFlow_TMR1 = 0;
u8 TMR_u8TMR1NormalCounter1INIT(u8 Copy_u8CLK , u32 *Copy_u32Counter)
{
	u8 Local_u8ErrorState = STD_TYPES_OK;
	//Select Mode.
	TMR_u16_TMR1_TCCR1_REG &= 0b1111110011100111;
	TMR_u16_TMR1_TCCR1_REG |= TMR_u16_TMR1_NORMAL_WAVEFORM_GENERATION_MODE;
	//Enable Over Flow Interrupt.
	TMR_u8_TIMSK_REG&=0b11111011;
	TMR_u8_TIMSK_REG|=TMR_u8_TMR1_OVER_FLOW_INTERRUPT_ENABLE ;
	switch(Copy_u8CLK)
	{
	case TMR_u8_TMR1_MP_CLK :
		//Select Clock.
		TMR_u8_TMR1_TCCR1B_REG&=0b11111000;
		TMR_u8_TMR1_TCCR1B_REG|=TMR_u8_TMR1_MP_CLK;
		break;
	case TMR_u8_TMR1_CLK_DIVIDED_8 :
		//Select Clock.
		TMR_u8_TMR1_TCCR1B_REG&=0b11111000;
		TMR_u8_TMR1_TCCR1B_REG|=TMR_u8_TMR1_CLK_DIVIDED_8;
		break;
	case TMR_u8_TMR1_CLK_DIVIDED_64 :
		//Select Clock.
		TMR_u8_TMR1_TCCR1B_REG&=0b11111000;
		TMR_u8_TMR1_TCCR1B_REG|=TMR_u8_TMR1_CLK_DIVIDED_64;
		break;
	case TMR_u8_TMR1_CLK_DIVIDED_256 :
		//Select Clock.
		TMR_u8_TMR1_TCCR1B_REG&=0b11111000;
		TMR_u8_TMR1_TCCR1B_REG|=TMR_u8_TMR1_CLK_DIVIDED_256;
		break;
	case TMR_u8_TMR1_CLK_DIVIDED_1024 :
		//Select Clock.
		TMR_u8_TMR1_TCCR1B_REG&=0b11111000;
		TMR_u8_TMR1_TCCR1B_REG|=TMR_u8_TMR1_CLK_DIVIDED_1024;
		break;
	case TMR_u8_TMR1_EXTERNAL_CLK_FALLING_EDGE_PIN_PB1 :
		//Select Clock.
		TMR_u8_TMR1_TCCR1B_REG&=0b11111000;
		TMR_u8_TMR1_TCCR1B_REG|=TMR_u8_TMR1_EXTERNAL_CLK_FALLING_EDGE_PIN_PB1;
		break;
	case TMR_u8_TMR1_EXTERNAL_CLK_RISING_EDGE_PIN_PB1 :
		//Select Clock.
		TMR_u8_TMR1_TCCR1B_REG&=0b11111000;
		TMR_u8_TMR1_TCCR1B_REG|=TMR_u8_TMR1_EXTERNAL_CLK_RISING_EDGE_PIN_PB1;
		break;
	default:Local_u8ErrorState = STD_TYPES_NOK;
	}
	*Copy_u32Counter = (u32)(((Counter1_u16_OverFlow_TMR1) * 1024UL)+TMR_u16_TMR1_TCNT1_REG);
	return Local_u8ErrorState;
}

//ISR of over flow timer 1 .
void __vector_9(void) __attribute__((signal));
void __vector_9(void)
{
	    //Counter.
		Counter1_u16_OverFlow_TMR1++;
}
#elif TMR_u8_TIMER1_MODE == TMR_u8_TIMER1_ADVANCED_PWM_FREQ_AND_TICK_TIME
u8 TMR_u8TMR1AdvancedPWMModes(u8 Copy_u8CLK,u16 Copy_u16PWMSelecion,u8 Copy_u8InvertedORNonInverted,u16 Copy_u16_TotalTimeMSec,u16 Copy_u16SetDutyCycle)
{
	u8 Local_u8ErrorState = STD_TYPES_OK;
	switch(Copy_u16PWMSelecion)
	{
	case TMR_u16_TMR1_PWM_PHASE_AND_FREQUENCY_CORRECT_WAVEFORM_GENERATION_MODE_1_Bottom:
		TMR_u16_TMR1_TCCR1_REG &= 0b1111110011100111;
		TMR_u16_TMR1_TCCR1_REG |= TMR_u16_TMR1_PWM_PHASE_AND_FREQUENCY_CORRECT_WAVEFORM_GENERATION_MODE_1_Bottom;
		break;
	case TMR_u16_TMR1_PWM_PHASE_AND_FREQUENCY_CORRECT_WAVEFORM_GENERATION_MODE_2_Bottom:
		TMR_u16_TMR1_TCCR1_REG &= 0b1111110011100111;
		TMR_u16_TMR1_TCCR1_REG |= TMR_u16_TMR1_PWM_PHASE_AND_FREQUENCY_CORRECT_WAVEFORM_GENERATION_MODE_2_Bottom;
		Copy_u16_TotalTimeMSec = TMR_u8_TMR1_NO_SELECTED_TIME;
		break;
	case TMR_u16_TMR1_PWM_PHASE_CORRECT_WAVEFORM_GENERATION_MODE_1_TOP:
		TMR_u16_TMR1_TCCR1_REG &= 0b1111110011100111;
		TMR_u16_TMR1_TCCR1_REG |= TMR_u16_TMR1_PWM_PHASE_CORRECT_WAVEFORM_GENERATION_MODE_1_TOP;
		break;
	case TMR_u16_TMR1_PWM_PHASE_CORRECT_WAVEFORM_GENERATION_MODE_2_TOP:
		TMR_u16_TMR1_TCCR1_REG &= 0b1111110011100111;
		TMR_u16_TMR1_TCCR1_REG |= TMR_u16_TMR1_PWM_PHASE_CORRECT_WAVEFORM_GENERATION_MODE_2_TOP;
		Copy_u16_TotalTimeMSec = TMR_u8_TMR1_NO_SELECTED_TIME;
		break;
	case TMR_u16_TMR1_PWM_FAST_WAVEFORM_GENERATION_MODE_1:
		TMR_u16_TMR1_TCCR1_REG &= 0b1111110011100111;
		TMR_u16_TMR1_TCCR1_REG |= TMR_u16_TMR1_PWM_FAST_WAVEFORM_GENERATION_MODE_1;
		break;
	case TMR_u16_TMR1_PWM_FAST_WAVEFORM_GENERATION_MODE_2:
		TMR_u16_TMR1_TCCR1_REG &= 0b1111110011100111;
		TMR_u16_TMR1_TCCR1_REG |= TMR_u16_TMR1_PWM_FAST_WAVEFORM_GENERATION_MODE_2;
		Copy_u16_TotalTimeMSec = TMR_u8_TMR1_NO_SELECTED_TIME;
		break;
	}
	/*//add.
	CLR_BIT(TMR_u8_TMR1_TCCR1A_REG,0);
	SET_BIT(TMR_u8_TMR1_TCCR1A_REG,1);
	SET_BIT(TMR_u8_TMR1_TCCR1B_REG,3);
	SET_BIT(TMR_u8_TMR1_TCCR1B_REG,4);*/
	//Select Inverting Mode.
	TMR_u8_TMR1_TCCR1A_REG&=0b00111111;
	TMR_u8_TMR1_TCCR1A_REG|=Copy_u8InvertedORNonInverted;
	//if Condition.
	if(Copy_u16_TotalTimeMSec != TMR_u8_TMR1_NO_SELECTED_TIME)
	{
	//Set Frequency => ToTal Time.
	TMR_u16_TMR1_ICR1_REG = (Copy_u16_TotalTimeMSec-1); // Action in the next bit.
	}
	else if(Copy_u16_TotalTimeMSec == 1)
	{
		TMR_u16_TMR1_ICR1_REG = 0;
	}
	else if(Copy_u16_TotalTimeMSec == TMR_u8_TMR1_NO_SELECTED_TIME)//Ask No Write or Write MAX Time of Prescaller 1.
	{
		TMR_u16_TMR1_ICR1_REG = 65535;
	}
	//Set Duty Cycle.
	TMR_u16_TMR1_OCR1A_REG = Copy_u16SetDutyCycle;
	//Select Clock.
	TMR_u8_TMR1_TCCR1B_REG&=0b11111000;
	TMR_u8_TMR1_TCCR1B_REG|=Copy_u8CLK;;
	return Local_u8ErrorState;
}
#elif TMR_u8_TIMER1_MODE == TMR_u8_TIMER1_SoftWare_ICU
volatile static u16 TMR_u16Ton=0 , TMR_u16Toff=0;
u8 TMR_u8TMR1SoftwareICU(u8 *Copy_u8DutyCycle,u32 *Copy_u32ToTalPeriodTime,u16 *Copy_u16OnPeriod,u16 *Copy_u16OffPeriod,u8 *Copy_u8Frequnecy)
{
	u8 Local_u8ErrorState = STD_TYPES_OK;
	if((Copy_u8DutyCycle !=NULL)&&(Copy_u32ToTalPeriodTime != NULL)&&(Copy_u16OnPeriod != NULL)&&(Copy_u16OffPeriod != NULL)&&(Copy_u8Frequnecy != NULL))
	{
		// Select Timer 1 mode => Normal.
		TMR_u16_TMR1_TCCR1_REG &= 0b1111110011100111;
		TMR_u16_TMR1_TCCR1_REG |= TMR_u16_TMR1_NORMAL_WAVEFORM_GENERATION_MODE;
		//Select ICP Trigger source => Rising edge;
		TMR_u8_TMR1_TCCR1B_REG &= 0b10111111;
		TMR_u8_TMR1_TCCR1B_REG |= TMR_u8_TMR1_SELECTING_POSITIVE_EDGE_TRIGGER;
		//Enable ICU Interrupt.
		TMR_u8_TIMSK_REG &=0b11011111;
		TMR_u8_TIMSK_REG |= TMR_u8_TMR1_INPUT_CAPTURE_INTERRUPT_ENABLE;
		//Select Clock.
		TMR_u8_TMR1_TCCR1B_REG&=0b11111000;
		TMR_u8_TMR1_TCCR1B_REG|=TMR_u8_TMR1_CLK_DIVIDED_8;
		if ((TMR_u16Ton !=0)&&(TMR_u16Toff !=0))
		{
			*Copy_u8DutyCycle = (u8)((TMR_u16Ton*100UL) /(TMR_u16Ton + TMR_u16Toff));
			*Copy_u32ToTalPeriodTime = TMR_u16Ton + TMR_u16Toff ;
			*Copy_u16OnPeriod = TMR_u16Ton ;
			*Copy_u16OffPeriod = TMR_u16Toff ;
			*Copy_u8Frequnecy = (256/(TMR_u16Ton + TMR_u16Toff)) ;
		}
	}
	else
	{
		Local_u8ErrorState = STD_TYPES_NOK;
	}
	return Local_u8ErrorState;
}

void __vector_6(void) __attribute__((signal));
void __vector_6(void)
{
	u16 Local_u16CurrentValue = 0;
	static u16 Local_u16OldValue = 0;
	static u8 Local_u8Flag=1;//To indicate rising Or Falling Edge.
	//Read Timer Counter.
	Local_u16CurrentValue = TMR_u16_TMR1_ICR1_REG;
	if(Local_u8Flag == 1)//Raising Edge.
	{
		//Update Flag => Falling Edge.
		Local_u8Flag=0;
		//Change Trigger Source => Falling Edge;
		TMR_u8_TMR1_TCCR1B_REG &=10111111;
		TMR_u8_TMR1_TCCR1B_REG |= TMR_u8_TMR1_SELECTING_NEGATIVE_EDGE_TRIGGER;
		//Calculate T OFF Period.
		TMR_u16Toff =  Local_u16CurrentValue - Local_u16OldValue ;
	}
	else //Falling Edge
	{
		//Update Flag => Raising Edge.
		Local_u8Flag=1;
		//Change Trigger Source => Raising Edge;
		TMR_u8_TMR1_TCCR1B_REG &=10111111;
		TMR_u8_TMR1_TCCR1B_REG |= TMR_u8_TMR1_SELECTING_POSITIVE_EDGE_TRIGGER;
		//Calculate TON Period.
		TMR_u16Ton =  Local_u16CurrentValue - Local_u16OldValue ;
	}
	//Update Old Value With The current Value.
	Local_u16OldValue =  Local_u16CurrentValue;
}
#endif
void TIMER_voidTimer1SetInputCaptureValue(u16 Copy_u16CaptureValue)
{
	/*Set The Input Capture Value to ICR1 Register*/
	TMR_u16_TMR1_ICR1_REG = Copy_u16CaptureValue;
}
void TMR_voidTMR1ASetCompareValue(u16 Copy_u16CompareValue)
{
	/* Set The Compare Value To OCR1 Channel A Register*/
	TMR_u16_TMR1_OCR1A_REG = Copy_u16CompareValue;
}

void TMR_voidTMR1BSetCompareValue(u16 Copy_u16CompareValue)
{
	/* Set The Compare Value To OCR1 Channel B Register*/
	TMR_u16_TMR1_OCR1B_REG = Copy_u16CompareValue;
}
#endif
