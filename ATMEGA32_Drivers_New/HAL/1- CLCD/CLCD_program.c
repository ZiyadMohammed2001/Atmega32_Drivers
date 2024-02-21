/********************************************************************/
/********************************************************************/
/*********************** Author: Ziyad Mohammed   *******************/
/*********************** File  : CLCD_cfg.h       *******************/
/*********************** Version: 1.00            *******************/
/********************************************************************/
/********************************************************************/

#include "BIT_MATH.h"
#include "STD_TYPES.h"
#include "DEFINES.h"

#include <util/delay.h>

#include "DIO_interface.h"

#include "CLCD_cfg.h"
#include "CLCD_prv.h"
#include "CLCD_interface.h"


#define F_CPU 16000000UL

static  void voidSendEnablePulse(void)
{
	/*Send Enable Pulse.*/
	DIO_u8SetPinValue(CLCD_CTRL_PORT,CLCD_E_PIN,DIO_u8_PIN_HIGH);
	_delay_ms(2);
	DIO_u8SetPinValue(CLCD_CTRL_PORT,CLCD_E_PIN,DIO_u8_PIN_LOW);
}


#if CLCD_OP_MODE	== FOUR_BIT_MODE
static void voidSetCLCDHalfDataPort(uint8 Copy_Nipple)
{
	DIO_u8SetPinValue(CLCD_CTRL_PORT,CLCD_D4_PIN,GET_BIT(Copy_Nipple,0));
	DIO_u8SetPinValue(CLCD_CTRL_PORT,CLCD_D5_PIN,GET_BIT(Copy_Nipple,1));
	DIO_u8SetPinValue(CLCD_CTRL_PORT,CLCD_D6_PIN,GET_BIT(Copy_Nipple,2));
	DIO_u8SetPinValue(CLCD_CTRL_PORT,CLCD_D7_PIN,GET_BIT(Copy_Nipple,3));
}
#endif


void CLCD_voidSendCmd(uint8 Copy_u8Cmd)
{
	/*Set Rs pin to low for command.*/
	DIO_u8SetPinValue(CLCD_CTRL_PORT,CLCD_RS_PIN,DIO_u8_PIN_LOW);

#if CLCD_RW_CTRL_EN == CLCD_RW_ENABLED
	/*Set Rw Pin to low for write operation.*/
	DIO_u8SetPinValue(CLCD_CTRL_PORT,CLCD_RW_PIN,DIO_u8_PIN_LOW);
#endif

#if CLCD_OP_MODE ==	EIGHT_BIT_MODE
	/*Send the command on data pin.*/
	DIO_u8SetPortValue(CLCD_DATA_PORT,Copy_u8Cmd);

	/*Send Enable Pulse.*/
	voidSendEnablePulse();

#elif CLCD_OP_MODE	== FOUR_BIT_MODE

	voidSetCLCDHalfDataPort((Copy_u8Cmd>>4));

	/*Send Enable Pulse.*/
	voidSendEnablePulse();

	voidSetCLCDHalfDataPort(Copy_u8Cmd);

	/*Send Enable Pulse.*/
	voidSendEnablePulse();

#endif
}

void CLCD_voidSendData (uint8 Copy_u8Data)
{

	/*Set Rs pin to high for command.*/
	DIO_u8SetPinValue(CLCD_CTRL_PORT,CLCD_RS_PIN,DIO_u8_PIN_HIGH);

#if CLCD_RW_CTRL_EN == CLCD_RW_ENABLED
	/*Set Rw Pin to low for write operation.*/
	DIO_u8SetPinValue(CLCD_CTRL_PORT,CLCD_RW_PIN,DIO_u8_PIN_LOW);
#endif

#if CLCD_OP_MODE ==	EIGHT_BIT_MODE
	/*Send the command on data pin.*/
	DIO_u8SetPortValue(CLCD_DATA_PORT,Copy_u8Data);

	/*Send Enable Pulse.*/
	voidSendEnablePulse();

#elif CLCD_OP_MODE	== FOUR_BIT_MODE

	voidSetCLCDHalfDataPort((Copy_u8Data>>4));

	/*Send Enable Pulse.*/
	voidSendEnablePulse();

	voidSetCLCDHalfDataPort(Copy_u8Data);

	/*Send Enable Pulse.*/
	voidSendEnablePulse();

#endif
}

void CLCD_voidInit(void)
{
	/*Wait for more than 30 ms after power on.*/
	_delay_ms(40);

#if CLCD_OP_MODE ==	EIGHT_BIT_MODE

	/*Function set command: 2 Lines, 5*7 font size.*/
	CLCD_voidSendCmd(0b00111000);

#elif CLCD_OP_MODE	== FOUR_BIT_MODE
	/*Function set command: 2 Lines, 5*7 font size.*/
	voidSetCLCDHalfDataPort(0b0010);
	/*Send Enable Pulse.*/
	voidSendEnablePulse();
	/*Function set command: 2 Lines, 5*7 font size.*/
	voidSetCLCDHalfDataPort(0b0010);
	/*Send Enable Pulse.*/
	voidSendEnablePulse();
	/*Function set command: 2 Lines, 5*7 font size.*/
	voidSetCLCDHalfDataPort(0b1000);
	/*Send Enable Pulse.*/
	voidSendEnablePulse();

#endif

	/*Display on/off control: Display , Cursor & blink are enable*/
	CLCD_voidSendCmd(0b00001111);

	/*Display Clear.*/
	CLCD_voidSendCmd(0b00000001);
}

void CLCD_vodDisplayClear(void)
{
	/*Display Clear.*/
	CLCD_voidSendCmd(0b00000001);
}

NULL_PTR_Error_State_t CLCD_u8SendString (const char* Copy_pcharString)
{
	NULL_PTR_Error_State_t Local_u8ErrorState = NULL_PTR_ERR;
	uint8 Local_u8String=0;
	if(NULL_PTR_ERR != Copy_pcharString)
	{
		Local_u8ErrorState = NULL_PTR_SUCESS;
		while(Copy_pcharString[Local_u8String]!='\0')
		{
			CLCD_voidSendData(Copy_pcharString[Local_u8String]);
			Local_u8String++;
		}
	}
	else
	{
		Local_u8ErrorState = NULL_PTR_ERR;
	}
	return Local_u8ErrorState;
}

void CLCD_voidSendNumber(sint32 Copy_s32Number)
{
	/*To Save The ASCII of the number in an Array.*/
	char Local_chNumberArr[10];
	/*To get the Right Digit.*/
	uint8 Local_u8RightDigit = 0;
	uint8 Local_u8Counter = 0;
	sint8 Local_s8PrintOnCLCD = 0;

	if (0 == Copy_s32Number)
	{
		CLCD_voidSendData('0');
		return ;
	}
	else if (Copy_s32Number < 0)
	{
		CLCD_voidSendData('-');
		Copy_s32Number *= -1;
	}
	while (0 != Copy_s32Number)
	{
		/*Extract the right most digit.*/
		Local_u8RightDigit = Copy_s32Number % 10;
		/*Get rid of the right most digit.*/
		Copy_s32Number /=10;
		/*Convert to ASCII Value, then Save the ASCII In the array.*/
		Local_chNumberArr[Local_u8Counter] = Local_u8RightDigit + '0';
		Local_u8Counter++;
	}
	for((Local_s8PrintOnCLCD = (Local_u8Counter-1));Local_s8PrintOnCLCD>=0;Local_s8PrintOnCLCD--)
	{
		CLCD_voidSendData(Local_chNumberArr[Local_s8PrintOnCLCD]);
	}
}

CLCD_PostionXY_Status CLCD_u8GoToXY(uint8 Copy_u8XPos, uint8 Copy_u8YPos)
{
	uint8 Local_u8DDRamAdd =0;
	uint8 Local_u8ErrorState = CLCD_POSITION_WAITING;
	if(Copy_u8XPos <= CLCD_POSITION_X_MAX)
	{
		Local_u8ErrorState = CLCD_POSITION_X_SUCEESS;
	if(CLCD_FIRST_ROW == Copy_u8YPos)
	{
		Local_u8DDRamAdd = Copy_u8XPos;
		Local_u8ErrorState = CLCD_POSITION_Y_SUCEESS;
	}
	else if(CLCD_SECOUND_ROW == Copy_u8YPos)
	{
		Local_u8DDRamAdd = Copy_u8XPos + 0x40 ;
		Local_u8ErrorState = CLCD_POSITION_Y_SUCEESS;
	}
	else
	{
		Local_u8ErrorState = CLCD_POSITION_Y_FAILED;
	}
	/*Set Bit 7 for Set DDRAM Address Command.*/
	Local_u8DDRamAdd |= 1<<7u;

	CLCD_voidSendCmd(Local_u8DDRamAdd);
	}
	else
	{
		Local_u8ErrorState = CLCD_POSITION_X_FAILED;
	}
	return Local_u8ErrorState;
}

void CLCD_voidSendSpecialCharacter(uint8 *Copy_u8Pattern,uint8 Copy_u8PatternNumber, uint8 Copy_u8XPos, uint8 Copy_u8YPos)
{
	uint8 Local_u8CGRAMAdd = Copy_u8PatternNumber * 8u;
	uint8 Local_u8LoopCounter;

	/*Set Bit Number 6 for Set CGRAM Address Command.*/
	Local_u8CGRAMAdd |= 1<<6u;

	/*Set CGRAM address.*/
	CLCD_voidSendCmd(Local_u8CGRAMAdd);

	/*Write the pattern into CGRAM.*/
	for(Local_u8LoopCounter = 0;Local_u8LoopCounter<8;Local_u8LoopCounter++)
	{
		CLCD_voidSendData(Copy_u8Pattern[Local_u8LoopCounter]);
	}

	/*Goto DDRAM to display the pattern.*/
	CLCD_u8GoToXY(Copy_u8XPos,Copy_u8YPos);

	/*Display the pattern written inside CGRAM.*/
	CLCD_voidSendData(Copy_u8PatternNumber);
}
