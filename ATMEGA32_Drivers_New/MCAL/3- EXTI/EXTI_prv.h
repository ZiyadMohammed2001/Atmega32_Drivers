
/********************************************************************/
/********************************************************************/
/*********************** Author: Ziyad Mohammed   *******************/
/*********************** File  : EXTI_PRV.h       *******************/
/*********************** Version: 1.00            *******************/
/********************************************************************/
/********************************************************************/

#ifndef EXTI_PRV_H_
#define EXTI_PRV_H_

typedef enum IntEXTIError
{
	EXTI_NUM_INCORRECT = 0u,
	EXTI_NUM_CORRECT = 1u,
	EXTI_SENSE_INCORRECT = 2u,
	EXTI_SENSE_CORRECT = 3u,
	EXTI_CALL_BACK_NULL_ERROR = 4u
}IntEXTIError_t;


#endif
