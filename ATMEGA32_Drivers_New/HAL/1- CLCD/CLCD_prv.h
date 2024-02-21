/********************************************************************/
/********************************************************************/
/*********************** Author: Ziyad Mohammed   *******************/
/*********************** File  : CLCD_prv.h       *******************/
/*********************** Version: 1.00            *******************/
/********************************************************************/
/********************************************************************/

#ifndef CLCD_PRV_H_
#define CLCD_PRV_H_

#define EIGHT_BIT_MODE		1u
#define FOUR_BIT_MODE		2u

#define CLCD_RW_ENABLED		1u
#define CLCD_RW_DISABLED	2u

static  void voidSendEnablePulse(void);


#if CLCD_OP_MODE	== FOUR_BIT_MODE
static void voidSetCLCDHalfDataPort(uint8 Copy_Nipple);
#endif

typedef enum
{
	CLCD_POSITION_WAITING 	= 0u,
	CLCD_POSITION_Y_SUCEESS = 1u,
	CLCD_POSITION_Y_FAILED  = 2u,
	CLCD_POSITION_X_SUCEESS = 3u,
	CLCD_POSITION_X_FAILED  = 4u,
}CLCD_PostionXY_Status;

#define CLCD_FIRST_ROW		0u
#define CLCD_SECOUND_ROW	1U

#define CLCD_POSITION_X_MAX	0x67U

#endif
