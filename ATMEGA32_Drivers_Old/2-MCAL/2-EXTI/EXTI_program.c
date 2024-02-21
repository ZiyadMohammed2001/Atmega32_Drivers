/************************************************/
/*                     Name: Ziyad Mohammed     */
/*                     Date: 9/10/2021          */
/*                     SWC: EXTI                */
/*                     Version: 1.0             */
/************************************************/
/*LIB Layer*/
#include"STD_TYPES.h"
#include "BIT_MATH.h"

/*MCAL*/
#include "EXTI_interface.h"
#include "EXTI_private.h"
#include "EXTI_config.h"

static void(*EXTI_Apf[3])(void) = {NULL,NULL,NULL}; //Array of pointer to functions.

/*void EXTI_voidEXTIEnable(void)
{
	// Select Trigger Source of EXTI0 => Falling Edge .

	SET_BIT(EXTI_u8_MCUCR_REG,1);
	CLR_BIT(EXTI_u8_MCUCR_REG,0);

	// Enable EXTI0(PIE).
	SET_BIT(EXTI_u8_GICR_REG,6);
}*/


u8 EXTI_u8Init(EXTINum_Type Copy_ENUEXTINumber,EXTITrigSrc_t Copy_EnuEXTITrigSrc)
{
	u8 Local_u8ErrorState = STD_TYPES_OK;
	// Select EXTI Number
	switch (Copy_ENUEXTINumber)
	{
	case EXTI_u8_EXTI0:
		// Select Trigger source.
		switch (Copy_EnuEXTITrigSrc)
		{
		case EXTI_u8_ANY_LOGIGAL_CHANGE:			CLR_BIT(EXTI_u8_MCUCR_REG,1);  SET_BIT(EXTI_u8_MCUCR_REG,0);/*Enable EXTI0*/		SET_BIT(EXTI_u8_GICR_REG,6);		break;
		case EXTI_u8_LOWLEVEL:                      CLR_BIT(EXTI_u8_MCUCR_REG,1);  CLR_BIT(EXTI_u8_MCUCR_REG,0);/*Enable EXTI0*/		SET_BIT(EXTI_u8_GICR_REG,6);		break;
		case EXTI_u8_FALLINGEDGE:                   SET_BIT(EXTI_u8_MCUCR_REG,1);  CLR_BIT(EXTI_u8_MCUCR_REG,0);/*Enable EXTI0*/		SET_BIT(EXTI_u8_GICR_REG,6);		break;
		case EXTI_u8_RAISINGEDGE:                   SET_BIT(EXTI_u8_MCUCR_REG,1);  SET_BIT(EXTI_u8_MCUCR_REG,0);/*Enable EXTI0*/		SET_BIT(EXTI_u8_GICR_REG,6);		break;
		default: Local_u8ErrorState = STD_TYPES_NOK;
		}
		break;
    case EXTI_u8_EXTI1:
    	// Select Trigger source.
    	switch (Copy_EnuEXTITrigSrc)
    	{
    	case EXTI_u8_ANY_LOGIGAL_CHANGE:			CLR_BIT(EXTI_u8_MCUCR_REG,3);  SET_BIT(EXTI_u8_MCUCR_REG,2);/*Enable EXTI1*/		SET_BIT(EXTI_u8_GICR_REG,7);		break;
    	case EXTI_u8_LOWLEVEL:                      CLR_BIT(EXTI_u8_MCUCR_REG,3);  CLR_BIT(EXTI_u8_MCUCR_REG,2);/*Enable EXTI1*/		SET_BIT(EXTI_u8_GICR_REG,7);		break;
    	case EXTI_u8_FALLINGEDGE:                   SET_BIT(EXTI_u8_MCUCR_REG,3);  CLR_BIT(EXTI_u8_MCUCR_REG,2);/*Enable EXTI1*/		SET_BIT(EXTI_u8_GICR_REG,7);		break;
    	case EXTI_u8_RAISINGEDGE:                   SET_BIT(EXTI_u8_MCUCR_REG,3);  SET_BIT(EXTI_u8_MCUCR_REG,2);/*Enable EXTI1*/		SET_BIT(EXTI_u8_GICR_REG,7);		break;
    	default: Local_u8ErrorState = STD_TYPES_NOK;
    	}
    	break;
    case EXTI_u8_EXTI2:
        // Select Trigger source.
        switch (Copy_EnuEXTITrigSrc)
        {
        case EXTI_u8_FALLINGEDGE:                   CLR_BIT(EXTI_u8_MCUCSR_REG,6);  /*Enable EXTI2*/		SET_BIT(EXTI_u8_GICR_REG,5);		break;
        case EXTI_u8_RAISINGEDGE:                   SET_BIT(EXTI_u8_MCUCSR_REG,6);  /*Enable EXTI2*/	    SET_BIT(EXTI_u8_GICR_REG,5);		break;
        default: Local_u8ErrorState = STD_TYPES_NOK;
        }
        break;
        default: Local_u8ErrorState = STD_TYPES_NOK;
	}
	return Local_u8ErrorState ;
}
u8 EXTI_u8Enable(EXTINum_Type Copy_ENUEXTINumber)
{
	u8 Local_u8ErrorState = STD_TYPES_OK;
	switch(Copy_ENUEXTINumber)
	{
	case EXTI_u8_EXTI0:SET_BIT(EXTI_u8_GICR_REG,6); break;
	case EXTI_u8_EXTI1:SET_BIT(EXTI_u8_GICR_REG,7); break;
	case EXTI_u8_EXTI2:SET_BIT(EXTI_u8_GICR_REG,5); break;
	default: Local_u8ErrorState = STD_TYPES_NOK;
	}
	return Local_u8ErrorState ;
}
u8 EXTI_u8Disable(EXTINum_Type Copy_ENUEXTINumber)
{
	u8 Local_u8ErrorState = STD_TYPES_OK;
	switch(Copy_ENUEXTINumber)
	{
	case EXTI_u8_EXTI0:CLR_BIT(EXTI_u8_GICR_REG,6); break;
	case EXTI_u8_EXTI1:CLR_BIT(EXTI_u8_GICR_REG,7); break;
	case EXTI_u8_EXTI2:CLR_BIT(EXTI_u8_GICR_REG,5); break;
	default: Local_u8ErrorState = STD_TYPES_NOK;
	}
	return Local_u8ErrorState ;
}
u8 EXTI_u8SetCallBack(EXTINum_Type Copy_ENUEXTINumber,void(*Copy_pf)(void))
{
	u8 Local_u8ErrorState = STD_TYPES_OK;
	if((Copy_ENUEXTINumber>=EXTI_u8_EXTI0)&&(Copy_ENUEXTINumber<=EXTI_u8_EXTI2)&&(Copy_pf!=NULL)) // because enum is signed value so it may be negative Value.
	{
		// Update global pointer to function.
		EXTI_Apf[Copy_ENUEXTINumber] = Copy_pf;
	}
	else
	{
		Local_u8ErrorState = STD_TYPES_NOK;
	}
	return Local_u8ErrorState ;
}
// ISR of EXTI0 Imp.
void __vector_1(void) __attribute__((signal));
void __vector_1(void)
{
	if (EXTI_Apf[EXTI_u8_EXTI0]!=NULL)
	{
		EXTI_Apf[EXTI_u8_EXTI0]();
	}
}

// ISR of EXTI1 Imp.
void __vector_2(void) __attribute__((signal));
void __vector_2(void)
{
	if (EXTI_Apf[EXTI_u8_EXTI1]!=NULL)
	{
		EXTI_Apf[EXTI_u8_EXTI1]();
	}
}

// ISR of EXTI2 Imp.
void __vector_3(void) __attribute__((signal));
void __vector_3(void)
{
	if (EXTI_Apf[EXTI_u8_EXTI2]!=NULL)
	{
		EXTI_Apf[EXTI_u8_EXTI2]();
	}
}
