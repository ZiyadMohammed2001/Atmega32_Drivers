
/********************************************************************/
/********************************************************************/
/*********************** Author: Ziyad Mohammed   *******************/
/*********************** File  : GIE_Program.c    *******************/
/*********************** Version: 1.00            *******************/
/********************************************************************/
/********************************************************************/

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "GIE_interface.h"
#include "GIE_reg.h"

void GIE_voidEnableGlobal(void)
{
	//SET_BIT(GIE_SREG,GIE_SREG_I);
	 __asm __volatile("SEI");	/*Inline assembly instruction to Set 1 bit in one CLK Cycle*/
}
void GIE_voidDisableGlobal(void)
{
	//CLR_BIT(GIE_SREG,GIE_SREG_I);
	 __asm __volatile("CLI");	/*Inline assembly instruction to clear 1 bit in one CLK Cycle*/
}
