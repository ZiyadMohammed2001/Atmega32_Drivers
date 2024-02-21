/********************************************************************/
/********************************************************************/
/*********************** Author: Ziyad Mohammed   *******************/
/*********************** File  : CLCD_cfg.h       *******************/
/*********************** Version: 1.00            *******************/
/********************************************************************/
/********************************************************************/

#ifndef CLCD_CFG_H_
#define CLCD_CFG_H_

/*Please, choose which port to connect CTRL Pins: Rs, RW, E.*/
/*options:
 * 1-	DIO_u8PORTA.
 * 2-	DIO_u8PORTB.
 * 3-	DIO_u8PORTC.
 * 4-	DIO_u8PORTD.
 */

/*Configure The operation mode, Optionn:
 *1-	EIGHT_BIT_MODE
 *2-	FOUR_BIT_MODE */

#define CLCD_OP_MODE		FOUR_BIT_MODE

/*Configure if the Rw pin is controlled or not, Options
 * 1-	CLCD_RW_ENABLED
 * 2-	CLCD_RW_DISABLED */
#define CLCD_RW_CTRL_EN		CLCD_RW_DISABLED

#if CLCD_RW_CTRL_EN == CLCD_RW_ENABLED

	#define CLCD_RW_PIN		DIO_u8PIN1

#endif

#define CLCD_CTRL_PORT		DIO_u8PORTA

#define CLCD_RS_PIN			DIO_u8PIN1
#define CLCD_E_PIN			DIO_u8PIN2

#define CLCD_DATA_PORT		DIO_u8PORTA

#if CLCD_OP_MODE == FOUR_BIT_MODE

#define	CLCD_D4_PIN			DIO_u8PIN3
#define	CLCD_D5_PIN			DIO_u8PIN4
#define	CLCD_D6_PIN			DIO_u8PIN5
#define	CLCD_D7_PIN			DIO_u8PIN6

#endif

#endif
