/************************************************/
/*                     Name: Ziyad Mohammed     */
/*                     Date: 15/10/2021         */
/*                     SWC: GIE                 */
/*                     Version: 1.0             */
/************************************************/
#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "GIE_interface.h"

#define GIE_u8_SREG_REG            *((volatile u8*)0x5f)

void GIE_voidEnable(void)
{
	SET_BIT(GIE_u8_SREG_REG,7);
}

void GIE_voidDisable(void)
{
	CLR_BIT(GIE_u8_SREG_REG,7);
}
