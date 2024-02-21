/*************************************************/
/*                     Name: Ziyad Mohammed     */
/*                     Date: 17/9/2021          */
/*                     SWC: DIO                 */
/*                     Version: 1.0             */
/************************************************/
/*LIB Layer*/
#include"STD_TYPES.h"
#include "BIT_MATH.h"

/*MCAL*/
#include "DIO_interface.h"
#include "DIO_private.h"
#include "DIO_config.h"

void DIO_u8Init          (void)
{
	DIO_U8_DDRA_REG = PRIVATE_u8_CONC(DIO_u8_PA7_DIRECTION,DIO_u8_PA6_DIRECTION,DIO_u8_PA5_DIRECTION,DIO_u8_PA4_DIRECTION,
			                          DIO_u8_PA3_DIRECTION,DIO_u8_PA2_DIRECTION,DIO_u8_PA1_DIRECTION,DIO_u8_PA0_DIRECTION);
	DIO_U8_DDRB_REG = PRIVATE_u8_CONC(DIO_u8_PB7_DIRECTION,DIO_u8_PB6_DIRECTION,DIO_u8_PB5_DIRECTION,DIO_u8_PB4_DIRECTION,
			                          DIO_u8_PB3_DIRECTION,DIO_u8_PB2_DIRECTION,DIO_u8_PB1_DIRECTION,DIO_u8_PB0_DIRECTION);
	DIO_U8_DDRC_REG = PRIVATE_u8_CONC(DIO_u8_PC7_DIRECTION,DIO_u8_PC6_DIRECTION,DIO_u8_PC5_DIRECTION,DIO_u8_PC4_DIRECTION,
			                          DIO_u8_PC3_DIRECTION,DIO_u8_PC2_DIRECTION,DIO_u8_PC1_DIRECTION,DIO_u8_PC0_DIRECTION);
	DIO_U8_DDRD_REG = PRIVATE_u8_CONC(DIO_u8_PD7_DIRECTION,DIO_u8_PD6_DIRECTION,DIO_u8_PD5_DIRECTION,DIO_u8_PD4_DIRECTION,
			                          DIO_u8_PD3_DIRECTION,DIO_u8_PD2_DIRECTION,DIO_u8_PD1_DIRECTION,DIO_u8_PD0_DIRECTION);

	DIO_u8_PORTA_REG = PRIVATE_u8_CONC(DIO_u8_PA7_Values,DIO_u8_PA6_Values,DIO_u8_PA5_Values,DIO_u8_PA4_Values,
		                               DIO_u8_PA3_Values,DIO_u8_PA2_Values,DIO_u8_PA1_Values,DIO_u8_PA0_Values);
	DIO_u8_PORTB_REG = PRIVATE_u8_CONC(DIO_u8_PB7_Values,DIO_u8_PB6_Values,DIO_u8_PB5_Values,DIO_u8_PB4_Values,
		                               DIO_u8_PB3_Values,DIO_u8_PB2_Values,DIO_u8_PB1_Values,DIO_u8_PB0_Values);
	DIO_u8_PORTC_REG = PRIVATE_u8_CONC(DIO_u8_PC7_Values,DIO_u8_PC6_Values,DIO_u8_PC5_Values,DIO_u8_PC4_Values,
	                                   DIO_u8_PC3_Values,DIO_u8_PC2_Values,DIO_u8_PC1_Values,DIO_u8_PC0_Values);
	DIO_u8_PORTD_REG = PRIVATE_u8_CONC(DIO_u8_PD7_Values,DIO_u8_PD6_Values,DIO_u8_PD5_Values,DIO_u8_PD4_Values,
			                           DIO_u8_PD3_Values,DIO_u8_PD2_Values,DIO_u8_PD1_Values,DIO_u8_PD0_Values);
}

u8 DIO_u8SetPinDirection(u8 Copy_u8PortId, u8 Copy_u8PinId,u8 Copy_u8PinDirection)
{
	u8 Local_u8ErrorState = STD_TYPES_OK;
	if ((Copy_u8PortId <= DIO_U8_PORTD) && (Copy_u8PinId <= DIO_u8_PIN7))
	{
		switch (Copy_u8PortId)
		{
		case DIO_U8_PORTA:
			switch (Copy_u8PinDirection)
			{
			case DIO_u8_INPUT_PULLED_UP:
				SET_BIT(DIO_u8_PORTA_REG, Copy_u8PinId);
			case DIO_u8_INPUT_FLOATING:
				CLR_BIT(DIO_U8_DDRA_REG, Copy_u8PinId);
				break;
			case DIO_u8_OUTPUT:
				SET_BIT(DIO_U8_DDRA_REG, Copy_u8PinId);
				break;
			default:
				Local_u8ErrorState = STD_TYPES_NOK;
			}
			break;
		case DIO_U8_PORTB:
			switch (Copy_u8PinDirection)
			{
			case DIO_u8_INPUT_PULLED_UP:
				SET_BIT(DIO_u8_PORTB_REG, Copy_u8PinId);
			case DIO_u8_INPUT_FLOATING:
				CLR_BIT(DIO_U8_DDRB_REG, Copy_u8PinId);
				break;
			case DIO_u8_OUTPUT:
				SET_BIT(DIO_U8_DDRB_REG, Copy_u8PinId);
				break;
			default:
				Local_u8ErrorState = STD_TYPES_NOK;
			}
			break;
		case DIO_U8_PORTC:
			switch (Copy_u8PinDirection)
			{
			case DIO_u8_INPUT_PULLED_UP:
				SET_BIT(DIO_u8_PORTC_REG, Copy_u8PinId);
			case DIO_u8_INPUT_FLOATING:
				CLR_BIT(DIO_U8_DDRC_REG, Copy_u8PinId);
				break;
			case DIO_u8_OUTPUT:
				SET_BIT(DIO_U8_DDRC_REG, Copy_u8PinId);
				break;
			default:
				Local_u8ErrorState = STD_TYPES_NOK;
			}
			break;
		case DIO_U8_PORTD:
			switch (Copy_u8PinDirection)
			{
			case DIO_u8_INPUT_PULLED_UP:
				SET_BIT(DIO_u8_PORTD_REG, Copy_u8PinId);
			case DIO_u8_INPUT_FLOATING:
				CLR_BIT(DIO_U8_DDRD_REG, Copy_u8PinId);
				break;
			case DIO_u8_OUTPUT:
				SET_BIT(DIO_U8_DDRD_REG, Copy_u8PinId);
				break;
			default:
				Local_u8ErrorState = STD_TYPES_NOK;
			}
			break;
		}
	}
	else
	{
		Local_u8ErrorState = STD_TYPES_NOK;
	}
	return Local_u8ErrorState;
}


u8 DIO_u8SetPinValue(u8 Copy_u8PortId, u8 Copy_u8PinId, u8 Copy_u8PinValue)
{
	u8 Local_u8ErrorState = STD_TYPES_OK;
	if ((Copy_u8PinId <= DIO_u8_PIN7) && ((Copy_u8PinValue== DIO_u8_HIGH)||(Copy_u8PinValue== DIO_u8_LOW)))
	{
		switch (Copy_u8PortId)
		{
		case DIO_U8_PORTA :
			switch(Copy_u8PinValue)
			{
			case DIO_u8_HIGH :
			SET_BIT(DIO_u8_PORTA_REG , Copy_u8PinId);
			break;
			case DIO_u8_LOW :
			CLR_BIT(DIO_u8_PORTA_REG , Copy_u8PinId);
			break;
			}
			break;
		case DIO_U8_PORTB :
			switch(Copy_u8PinValue)
			{
			case DIO_u8_HIGH :
			SET_BIT(DIO_u8_PORTB_REG , Copy_u8PinId);
			break;
			case DIO_u8_LOW :
			CLR_BIT(DIO_u8_PORTB_REG , Copy_u8PinId);
			break;
			}
			break;
		case DIO_U8_PORTC :
			switch(Copy_u8PinValue)
			{
			case DIO_u8_HIGH :
			SET_BIT(DIO_u8_PORTC_REG , Copy_u8PinId);
			break;
			case DIO_u8_LOW :
			CLR_BIT(DIO_u8_PORTC_REG , Copy_u8PinId);
			break;
			}
			break;
		case DIO_U8_PORTD :
			switch(Copy_u8PinValue)
			{
			case DIO_u8_HIGH :
			SET_BIT(DIO_u8_PORTD_REG , Copy_u8PinId);
			break;
			case DIO_u8_LOW :
	    	CLR_BIT(DIO_u8_PORTD_REG , Copy_u8PinId);
			break;
			}
			break;
			default : Local_u8ErrorState = STD_TYPES_NOK ;
		}
	}
	else
	{
		Local_u8ErrorState = STD_TYPES_NOK;
	}
	return Local_u8ErrorState;
}
u8 DIO_u8GetPinValue(u8 Copy_u8PortId, u8 Copy_u8PinId,u8 * Copy_Pu8ReturnedValue)
{
	u8 Local_u8ErrorState = STD_TYPES_NOK;
	if ((Copy_u8PinId <= DIO_u8_PIN7)&&(Copy_Pu8ReturnedValue != NULL))
	{
		Local_u8ErrorState = STD_TYPES_OK;
		switch(Copy_u8PortId)
		{
		case DIO_U8_PORTA: *Copy_Pu8ReturnedValue = GET_BIT(DIO_U8_PINA_REG,Copy_u8PinId);break;
		case DIO_U8_PORTB: *Copy_Pu8ReturnedValue = GET_BIT(DIO_U8_PINB_REG,Copy_u8PinId);break;
		case DIO_U8_PORTC: *Copy_Pu8ReturnedValue = GET_BIT(DIO_U8_PINC_REG,Copy_u8PinId);break;
		case DIO_U8_PORTD: *Copy_Pu8ReturnedValue = GET_BIT(DIO_U8_PIND_REG,Copy_u8PinId);break;
		default : Local_u8ErrorState = STD_TYPES_NOK;
		}
	}
	return Local_u8ErrorState;
}
u8 DIO_u8TogglePinValue(u8 Copy_u8PortId, u8 Copy_u8PinId)
{
	u8 Local_u8ErrorState = STD_TYPES_OK;
	if (Copy_u8PinId <=DIO_u8_PIN7)
	{
		switch(Copy_u8PortId)
		{
		case DIO_U8_PORTA : TOG_BIT(DIO_u8_PORTA_REG,Copy_u8PinId);break;
		case DIO_U8_PORTB : TOG_BIT(DIO_u8_PORTB_REG,Copy_u8PinId);break;
		case DIO_U8_PORTC : TOG_BIT(DIO_u8_PORTC_REG,Copy_u8PinId);break;
		case DIO_U8_PORTD : TOG_BIT(DIO_u8_PORTD_REG,Copy_u8PinId);break;
		default : Local_u8ErrorState = STD_TYPES_NOK ;
		}
	}
	else
	{
		 Local_u8ErrorState = STD_TYPES_NOK;
	}
	return Local_u8ErrorState;
}
u8 DIO_u8SetPortDirection(u8 Copy_u8PortId, u8 Copy_u8PortDirection)
{
	u8 Local_u8ErrorState = STD_TYPES_OK;
	switch(Copy_u8PortId)
	{
	case DIO_U8_PORTA :
		switch (Copy_u8PortDirection)
		{
		case DIO_u8_INPUT_PULLED_UP : DIO_u8_PORTA_REG = 0xff;
		case DIO_u8_INPUT_FLOATING  : DIO_U8_DDRA_REG  = 0x00;break;
		case DIO_u8_OUTPUT          : DIO_U8_DDRA_REG  = 0xff;break;
		default : Local_u8ErrorState = STD_TYPES_NOK;
		}
		break;
		case DIO_U8_PORTB :
		switch (Copy_u8PortDirection)
		{
		case DIO_u8_INPUT_PULLED_UP : DIO_u8_PORTB_REG = 0xff;
		case DIO_u8_INPUT_FLOATING  : DIO_U8_DDRB_REG  = 0x00;break;
		case DIO_u8_OUTPUT          : DIO_U8_DDRB_REG  = 0xff;break;
		default : Local_u8ErrorState = STD_TYPES_NOK;
		}
		break;
		case DIO_U8_PORTC :
		switch (Copy_u8PortDirection)
		{
		case DIO_u8_INPUT_PULLED_UP : DIO_u8_PORTC_REG = 0xff;
		case DIO_u8_INPUT_FLOATING  : DIO_U8_DDRC_REG  = 0x00;break;
		case DIO_u8_OUTPUT          : DIO_U8_DDRC_REG  = 0xff;break;
		default : Local_u8ErrorState = STD_TYPES_NOK;
		}
		break;
		case DIO_U8_PORTD :
		switch (Copy_u8PortDirection)
		{
		case DIO_u8_INPUT_PULLED_UP : DIO_u8_PORTD_REG = 0xff;
		case DIO_u8_INPUT_FLOATING  : DIO_U8_DDRD_REG  = 0x00;break;
		case DIO_u8_OUTPUT          : DIO_U8_DDRD_REG  = 0xff;break;
		default : Local_u8ErrorState = STD_TYPES_NOK;
		}
		break;
		default : Local_u8ErrorState = STD_TYPES_NOK;
	}
	return Local_u8ErrorState;
}
u8 DIO_u8SetPortValue(u8 Copy_u8PortId, u8 Copy_u8PortValue)
{
	u8 Local_u8ErrorState = STD_TYPES_OK;
	switch (Copy_u8PortId)
	{
	case DIO_U8_PORTA : DIO_u8_PORTA_REG = Copy_u8PortValue ; break;
	case DIO_U8_PORTB : DIO_u8_PORTB_REG = Copy_u8PortValue ; break;
	case DIO_U8_PORTC : DIO_u8_PORTC_REG = Copy_u8PortValue ; break;
	case DIO_U8_PORTD : DIO_u8_PORTD_REG = Copy_u8PortValue ; break;
	default : Local_u8ErrorState = STD_TYPES_NOK;
	}
	return Local_u8ErrorState;
}
u8 DIO_u8GetPortValue(u8 Copy_u8PortId, u8 * Copy_Pu8PortValue)
{
	u8 Local_u8ErrorState = STD_TYPES_OK;
	if(Copy_Pu8PortValue != NULL)
	{
		switch (Copy_u8PortId)
		{
		case DIO_U8_PORTA : *Copy_Pu8PortValue = DIO_U8_PINA_REG ; break;
		case DIO_U8_PORTB : *Copy_Pu8PortValue = DIO_U8_PINB_REG ; break;
		case DIO_U8_PORTC : *Copy_Pu8PortValue = DIO_U8_PINC_REG ; break;
		case DIO_U8_PORTD : *Copy_Pu8PortValue = DIO_U8_PIND_REG ; break;
		default : Local_u8ErrorState = STD_TYPES_NOK;
		}
	}
	else
	{
		Local_u8ErrorState = STD_TYPES_NOK;
	}
	return Local_u8ErrorState;
}
