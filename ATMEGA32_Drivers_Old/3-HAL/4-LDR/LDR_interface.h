/************************************************/
/*                     Name: Ziyad Mohammed     */
/*                     Date: 22/10/2021         */
/*                     SWC: LDR                 */
/*                     Version: 1.0             */
/************************************************/
//Any macros need to change in interface.

#ifndef TEMPSENSOR_INTERFACE_H
#define TEMPSENSOR_INTERFACE_H

u8 LDR_u8GetLDRValue(u8 Copy_u8ChannelNum,u8 Copy_u8EN_OR_DIS_Conversion,u8 * Copy_pu16ReturnedLDRValue);

#endif

