
/********************************************************************/
/********************************************************************/
/*********************** Author: Ziyad Mohammed   *******************/
/*********************** File  : EXTI_Program.c   *******************/
/*********************** Version: 1.00            *******************/
/********************************************************************/
/********************************************************************/

#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "DEFINES.h"

#include "EXTI_prv.h"
#include "EXTI_interface.h"
#include "EXTI_reg.h"
#include "EXTI_cfg.h"

/*Array of pointer to function to hold ISR Call Back addresses.*/
static void (*EXTI_pfINTFuncPtr[3])(void) = {NULL};

void EXTI_voidInitInt0(void)
{
	/*Implement INT0 sense control configuration.*/
#if INT0_SENSE_CTRL == EXTI_u8LOW_LEVEL
	CLR_BIT(MCUCR,MCUCR_ISC00);
	CLR_BIT(MCUCR,MCUCR_ISC01);
#elif INT0_SENSE_CTRL == EXTI_u8ON_CHANGE
	SET_BIT(MCUCR,MCUCR_ISC00);
	CLR_BIT(MCUCR,MCUCR_ISC01);
#elif INT0_SENSE_CTRL == EXTI_u8FALLING_EDGE
	CLR_BIT(MCUCR,MCUCR_ISC00);
	SET_BIT(MCUCR,MCUCR_ISC01);
#elif INT0_SENSE_CTRL == EXTI_u8RISING_EDGE
	SET_BIT(MCUCR,MCUCR_ISC00);
	SET_BIT(MCUCR,MCUCR_ISC01);
#else
#error Wrong INT0_SENSE_CTRL Configuration option.
#endif

	/*Implement INT0 Initial State Configuration.*/
#if INT0_INITIAL_STATE == DISABLED
	CLR_BIT(GICR,GICR_INT0);
#elif INT0_INITIAL_STATE == ENABLED
	SET_BIT(GICR,GICR_INT0);
#else
#error Wrong INT0_INITIAL_STATE Initial State Configuration Option.
#endif

}
void EXTI_voidInitInt1(void)
{
	/*Implement INT1 sense control configuration.*/
#if INT1_SENSE_CTRL == EXTI_u8LOW_LEVEL
	CLR_BIT(MCUCR,MCUCR_ISC10);
	CLR_BIT(MCUCR,MCUCR_ISC11);
#elif INT1_SENSE_CTRL == EXTI_u8ON_CHANGE
	SET_BIT(MCUCR,MCUCR_ISC10);
	CLR_BIT(MCUCR,MCUCR_ISC11);
#elif INT1_SENSE_CTRL == EXTI_u8FALLING_EDGE
	CLR_BIT(MCUCR,MCUCR_ISC10);
	SET_BIT(MCUCR,MCUCR_ISC11);
#elif INT1_SENSE_CTRL == EXTI_u8RISING_EDGE
	SET_BIT(MCUCR,MCUCR_ISC10);
	SET_BIT(MCUCR,MCUCR_ISC11);
#else
#error Wrong INT1_SENSE_CTRL Configuration option.
#endif

	/*Implement INT1 Initial State Configuration.*/
#if INT1_INITIAL_STATE == DISABLED
	CLR_BIT(GICR,GICR_INT1);
#elif INT1_INITIAL_STATE == ENABLED
	SET_BIT(GICR,GICR_INT1);
#else
#error Wrong INT1_INITIAL_STATE Initial State Configuration Option.
#endif

}
void EXTI_voidInitInt2(void)
{
	/*Implement INT2 sense control configuration.*/
#if INT2_SENSE_CTRL == EXTI_u8FALLING_EDGE
	CLR_BIT(MCUCSR,MCUCSR_ISC2);
#elif INT2_SENSE_CTRL == EXTI_u8RISING_EDGE
	SET_BIT(MCUCSR,MCUCSR_ISC2);
#else
#error Wrong INT2_SENSE_CTRL Configuration option.
#endif

	/*Implement INT2 Initial State Configuration.*/
#if INT2_INITIAL_STATE == DISABLED
	CLR_BIT(GICR,GICR_INT2);
#elif INT2_INITIAL_STATE == ENABLED
	SET_BIT(GICR,GICR_INT2);
#else
#error Wrong INT2_INITIAL_STATE Initial State Configuration Option.
#endif
}

IntEXTIError_t EXTI_u8SetSenseCtrl(uint8 Copy_u8IntNum, uint8 Copy_u8Sense)
{
	IntEXTIError_t Local_enum_ErrorState_Num = EXTI_NUM_CORRECT;
	IntEXTIError_t Local_enum_ErrorState_Sense = EXTI_SENSE_CORRECT;
	switch(Copy_u8IntNum)
	{
	case EXTI_u8INT0:
		switch(Copy_u8Sense)
		{
		case EXTI_u8LOW_LEVEL:
			CLR_BIT(MCUCR,MCUCR_ISC00);
			CLR_BIT(MCUCR,MCUCR_ISC01);
			break;
		case EXTI_u8ON_CHANGE:
			SET_BIT(MCUCR,MCUCR_ISC00);
			CLR_BIT(MCUCR,MCUCR_ISC01);
			break;
		case EXTI_u8FALLING_EDGE:
			CLR_BIT(MCUCR,MCUCR_ISC00);
			SET_BIT(MCUCR,MCUCR_ISC01);
			break;
		case EXTI_u8RISING_EDGE:
			SET_BIT(MCUCR,MCUCR_ISC00);
			SET_BIT(MCUCR,MCUCR_ISC01);
			break;
		default: Local_enum_ErrorState_Sense = EXTI_SENSE_INCORRECT;
		}
		break;
		case EXTI_u8INT1:
			switch(Copy_u8Sense)
			{
			case EXTI_u8LOW_LEVEL:
				CLR_BIT(MCUCR,MCUCR_ISC10);
				CLR_BIT(MCUCR,MCUCR_ISC11);
				break;
			case EXTI_u8ON_CHANGE:
				SET_BIT(MCUCR,MCUCR_ISC10);
				CLR_BIT(MCUCR,MCUCR_ISC11);
				break;
			case EXTI_u8FALLING_EDGE:
				CLR_BIT(MCUCR,MCUCR_ISC10);
				SET_BIT(MCUCR,MCUCR_ISC11);
				break;
			case EXTI_u8RISING_EDGE:
				SET_BIT(MCUCR,MCUCR_ISC10);
				SET_BIT(MCUCR,MCUCR_ISC11);
				break;
			default: Local_enum_ErrorState_Sense = EXTI_SENSE_INCORRECT;
			}
			break;
			case EXTI_u8INT2:
				switch(Copy_u8Sense)
				{
				case EXTI_u8FALLING_EDGE:
					CLR_BIT(MCUCSR,MCUCSR_ISC2);
					break;
				case EXTI_u8RISING_EDGE:
					SET_BIT(MCUCSR,MCUCSR_ISC2);
					break;
				default: Local_enum_ErrorState_Sense = EXTI_SENSE_INCORRECT;
				}
				break;
				default:
					Local_enum_ErrorState_Num = EXTI_NUM_INCORRECT;
	}
	return Local_enum_ErrorState_Num;
}

IntEXTIError_t EXTI_u8IntEnable(uint8 Copy_u8IntNum)
{
	IntEXTIError_t Local_enum_ErrorState_Num = EXTI_NUM_CORRECT;
	switch(Copy_u8IntNum)
	{
	case EXTI_u8INT0:
		SET_BIT(GICR,GICR_INT0);
		break;
	case EXTI_u8INT1:
		SET_BIT(GICR,GICR_INT1);
		break;
	case EXTI_u8INT2:
		SET_BIT(GICR,GICR_INT2);
		break;
	default: Local_enum_ErrorState_Num = EXTI_NUM_INCORRECT;
	}
	return Local_enum_ErrorState_Num;
}

IntEXTIError_t EXTI_u8IntDisable(uint8 Copy_u8IntNum)
{
	IntEXTIError_t Local_enum_ErrorState_Num = EXTI_NUM_CORRECT;
	switch(Copy_u8IntNum)
	{
	case EXTI_u8INT0:
		CLR_BIT(GICR,GICR_INT0);
		break;
	case EXTI_u8INT1:
		CLR_BIT(GICR,GICR_INT1);
		break;
	case EXTI_u8INT2:
		CLR_BIT(GICR,GICR_INT2);
		break;
	default: Local_enum_ErrorState_Num = EXTI_NUM_INCORRECT;
	}
	return Local_enum_ErrorState_Num;
}

IntEXTIError_t EXTI_u8SetCallBack(uint8 Copy_u8IntNum, void(*Copy_pfFuncPtr)(void))
{
	IntEXTIError_t Local_enum_ErrorState_Num = EXTI_NUM_CORRECT;
	if (Copy_pfFuncPtr != NULL)
	{
		switch(Copy_u8IntNum)
		{
		case EXTI_u8INT0:	EXTI_pfINTFuncPtr [EXTI_u8INT0] = Copy_pfFuncPtr;		break;
		case EXTI_u8INT1:	EXTI_pfINTFuncPtr [EXTI_u8INT1] = Copy_pfFuncPtr;		break;
		case EXTI_u8INT2:	EXTI_pfINTFuncPtr [EXTI_u8INT2] = Copy_pfFuncPtr;		break;
		default: Local_enum_ErrorState_Num = EXTI_NUM_INCORRECT;
		}
	}
	else
	{
		Local_enum_ErrorState_Num = EXTI_CALL_BACK_NULL_ERROR;
	}
	return Local_enum_ErrorState_Num;
}

/**
 * @brief INT0 ISR
 */

void __vector_1 (void)	__attribute__((signal));
void __vector_1 (void)
{
	if (EXTI_pfINTFuncPtr[EXTI_u8INT0]!= NULL)
	{
		EXTI_pfINTFuncPtr[EXTI_u8INT0]();
	}
}
/**
 * @brief INT1 ISR
 */

void __vector_2 (void)	__attribute__((signal));
void __vector_2 (void)
{
	if (EXTI_pfINTFuncPtr[EXTI_u8INT1]!= NULL)
	{
		EXTI_pfINTFuncPtr[EXTI_u8INT1]();
	}
}
/**
 * @brief INT2 ISR
 */

void __vector_3 (void)	__attribute__((signal));
void __vector_3 (void)
{
	if (EXTI_pfINTFuncPtr[EXTI_u8INT2]!= NULL)
	{
		EXTI_pfINTFuncPtr[EXTI_u8INT2]();
	}
}
