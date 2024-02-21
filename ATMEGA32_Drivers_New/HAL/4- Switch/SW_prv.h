/********************************************************************/
/********************************************************************/
/*********************** Author: Ziyad Mohammed   *******************/
/*********************** File  : SW_prv.h         *******************/
/*********************** Version: 1.00            *******************/
/********************************************************************/
/********************************************************************/

#ifndef SW_PRV_H_
#define SW_PRV_H_

#define SW_PULL_UP_PRESSED			0u
#define SW_PULL_DOWN_PRESSED		1u

typedef enum
{
	SW_Error_Wait 			= 0u,
	SW_PULL_TYPE_CORRECT 	= 1u,
	SW_PULL_TYPE_INCORRECT 	= 2u,
	SW_NULL_PTR_ERROR 		= 3u,
}SwitchPullTypeError_t;

#endif
