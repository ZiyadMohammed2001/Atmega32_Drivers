
/********************************************************************/
/********************************************************************/
/*********************** Author: Ziyad Mohammed   *******************/
/*********************** File  : WDT_program.c    *******************/
/*********************** Version: 1.00            *******************/
/********************************************************************/
/********************************************************************/
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "DEFINES.h"

#include "WDT_reg.h"
#include "WDT_interface.h"
#include "WDT_cfg.h"
#include "WDT_prv.h"

WDT_ErrorState_t WDT_voidEnable(WDT_Prescaler_t Copy_u8_Prescaler)
{
	WDT_ErrorState_t local_u8ErrorState = WDT_PRESCALLER_OK;
	if ((Copy_u8_Prescaler>=WDT_PRESCALER_16K)&&(Copy_u8_Prescaler<=WDT_PRESCALER_2048K))
	{
		/* Set WDE and WDP bits according to prescaler */
		WDTCR = (1 << WDE) | (Copy_u8_Prescaler);
	}
	else
	{
		local_u8ErrorState = WDT_PRESCALLER_ERROR;
	}
	return local_u8ErrorState;
}

void WDT_voidDisable(void)
{
	{
		/* Write logical one to WDTOE and WDE */
		WDTCR = (1<<WDTOE) | (1<<WDE);
		/* Turn off WDT */
		WDTCR = 0x00;
	}
}

void WDT_voidRefresh(void) {
	/* Reset the WDT */
	asm volatile ("wdr");
}
