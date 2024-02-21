/************************************************/
/*                     Name: Ziyad Mohammed     */
/*                     Date: 24/9/2021          */
/*                     SWC: LCD                 */
/*                     Version: 1.0             */
/************************************************/
/*LIB Layer*/
#include"STD_TYPES.h"
#include "BIT_MATH.h"
#define F_CPU  8000000UL
#include <avr/delay.h>

/*MCAL*/
#include "DIO_interface.h"

/*HAL*/
#include "LCD_interface.h"
#include "LCD_private.h"
#include "LCD_config.h"


void LCD_voidInit(void)
{
	_delay_ms(35);
#if (LCD_u8_MODE == LCD_u8_8_BIT_MODE)
	/* Function Set Command */
	LCD_voidWriteCmnd(0b00111000);
#elif (LCD_u8_MODE == LCD_u8_4_BIT_MODE)
	/* Rs = 0 (Command Byte) */
	DIO_u8SetPinValue(LCD_u8_RS_PORT,LCD_u8_RS_PIN,DIO_u8_LOW);
	/* Rw = 0 (write Operation) */
	DIO_u8SetPinValue(LCD_u8_RW_PORT,LCD_u8_RW_PIN,DIO_u8_LOW);
	/* Send 4 Bits Sequence. */
	PRIVATE_voidSetHalfPort(0b00100000);
	/* Enable Pulse */
	DIO_u8SetPinValue(LCD_u8_EN_PORT,LCD_u8_EN_PIN,DIO_u8_HIGH);
	_delay_us(1);
	DIO_u8SetPinValue(LCD_u8_EN_PORT,LCD_u8_EN_PIN,DIO_u8_LOW);
	/* Send Normal Command */
	LCD_voidWriteCmnd(0b00101000);
#else
	#error"Wrong Choice"
#endif

	_delay_us(40);
	/* Display ON/OFF Control */
	LCD_voidWriteCmnd(0b00001111);
	_delay_us(40);
	/*Display Clear*/
	LCD_voidWriteCmnd(0x01);
	_delay_ms(2);
	LCD_voidWriteCmnd(0b00000110);
}

void LCD_voidWriteChar(u8 Copy_u8Char)
{
	/* Rs = 1 (Data Byte) */
	DIO_u8SetPinValue(LCD_u8_RS_PORT,LCD_u8_RS_PIN,DIO_u8_HIGH);
	/* Rw = 0 (write Operation) */
	DIO_u8SetPinValue(LCD_u8_RW_PORT,LCD_u8_RW_PIN,DIO_u8_LOW);
#if (LCD_u8_MODE == LCD_u8_8_BIT_MODE)
	/* Send Data Byte to LCD */
	DIO_u8SetPortValue(LCD_u8_DATA_PORT,Copy_u8Char);
	/* Enable Pulse */
	DIO_u8SetPinValue(LCD_u8_EN_PORT,LCD_u8_EN_PIN,DIO_u8_HIGH);
	_delay_us(1);
	DIO_u8SetPinValue(LCD_u8_EN_PORT,LCD_u8_EN_PIN,DIO_u8_LOW);
#elif (LCD_u8_MODE == LCD_u8_4_BIT_MODE)
	/* Send Most Nibbles to LCD */
	PRIVATE_voidSetHalfPort(Copy_u8Char);
	/* Enable Pulse */
	DIO_u8SetPinValue(LCD_u8_EN_PORT,LCD_u8_EN_PIN,DIO_u8_HIGH);
	_delay_us(1);
	DIO_u8SetPinValue(LCD_u8_EN_PORT,LCD_u8_EN_PIN,DIO_u8_LOW);
	/* Send Least 4 bits to LCD */
	PRIVATE_voidSetHalfPort(Copy_u8Char<<4);
	/* Enable Pulse */
	DIO_u8SetPinValue(LCD_u8_EN_PORT,LCD_u8_EN_PIN,DIO_u8_HIGH);
	_delay_us(1);
	DIO_u8SetPinValue(LCD_u8_EN_PORT,LCD_u8_EN_PIN,DIO_u8_LOW);
#else
	#error "Wrong Choice"
#endif
}
void LCD_voidWriteCmnd(u8 Copy_u8Cmnd)
{
	/* Rs = 0 (Command Byte) */
	DIO_u8SetPinValue(LCD_u8_RS_PORT,LCD_u8_RS_PIN,DIO_u8_LOW);
	/* Rw = 0 (write Operation) */
	DIO_u8SetPinValue(LCD_u8_RW_PORT,LCD_u8_RW_PIN,DIO_u8_LOW);
#if (LCD_u8_MODE == LCD_u8_8_BIT_MODE)

	/* Send Data Byte to LCD */
	DIO_u8SetPortValue(LCD_u8_DATA_PORT,Copy_u8Cmnd);
	/* Enable Pulse */
	DIO_u8SetPinValue(LCD_u8_EN_PORT,LCD_u8_EN_PIN,DIO_u8_HIGH);
	_delay_us(1);
	DIO_u8SetPinValue(LCD_u8_EN_PORT,LCD_u8_EN_PIN,DIO_u8_LOW);
#elif (LCD_u8_MODE == LCD_u8_4_BIT_MODE)
	/* Send Most Nibbles to LCD */
	PRIVATE_voidSetHalfPort(Copy_u8Cmnd);
	/* Enable Pulse */
	DIO_u8SetPinValue(LCD_u8_EN_PORT,LCD_u8_EN_PIN,DIO_u8_HIGH);
	_delay_us(1);
	DIO_u8SetPinValue(LCD_u8_EN_PORT,LCD_u8_EN_PIN,DIO_u8_LOW);
	/* Send Least 4 bits to LCD */
	PRIVATE_voidSetHalfPort(Copy_u8Cmnd<<4);
	/* Enable Pulse */
	DIO_u8SetPinValue(LCD_u8_EN_PORT,LCD_u8_EN_PIN,DIO_u8_HIGH);
	_delay_us(1);
	DIO_u8SetPinValue(LCD_u8_EN_PORT,LCD_u8_EN_PIN,DIO_u8_LOW);
	#else
	#error "Wrong Choice"
#endif
}
void LCD_voidWriteString (u8* Copy_pu8String , u8 Copy_u8NumberOfCharacters)
{
	u8 Local_u8String=0;
	for (Local_u8String=0; Local_u8String<Copy_u8NumberOfCharacters ; Local_u8String++)
	{
		// Write Character on LCD.
		LCD_voidWriteChar(Copy_pu8String[Local_u8String]);

		// Delay to let the LCD show the character.
		_delay_ms(2);
	}
}

/*void LCD_voidPrintString (u8* Copy_pu8String)
{
	u8 Local_u8String=0;
	while((Copy_pu8String[Local_u8String])>0)
	{
		// Write Character on LCD.
		LCD_voidWriteChar(Copy_pu8String[Local_u8String]);
		// Delay to let the LCD show the character.
		_delay_ms(2);
		Local_u8String++ ;
	}
}
*/
void LCD_voidPrintString (u8* Copy_pu8String)
{
	u8 Local_u8String=0;
	while(Copy_pu8String[Local_u8String]!='\0')
	{
		LCD_voidWriteChar(Copy_pu8String[Local_u8String]);
		Local_u8String++;
	}
}
void LCD_voidPrintNumber (u32 Copy_u32Number)
{
	u32 Local_u32Temp=1,Local_u32New;
	// check if number = 0
	if (Copy_u32Number==0)
	{
		LCD_voidWriteChar('0');
	}
	while(Copy_u32Number!=0)
	{
		Local_u32Temp = Local_u32Temp * 10;
		Local_u32New = Copy_u32Number % 10 ;
		Copy_u32Number = Copy_u32Number / 10 ;
		Local_u32Temp = Local_u32Temp + Local_u32New;
	}
	while(Local_u32Temp!=1)
	{
		u32 Local_u32Var ;
		Local_u32Var =Local_u32Temp %10 ;
		Local_u32Temp = Local_u32Temp / 10 ;
		LCD_voidWriteChar('0'+Local_u32Var);
	}
}
u8   LCD_u8GoToXY(u8 Copy_u8LineNum,u8 Copy_u8CharLocation)
{
	u8 Local_u8ErrorState = STD_TYPES_OK;
	switch(Copy_u8LineNum)
	{
	case LCD_u8_LINE_1:LCD_voidWriteCmnd(0x80 + Copy_u8CharLocation);break;
	case LCD_u8_LINE_2:LCD_voidWriteCmnd(0xC0 + Copy_u8CharLocation);break;
	default           : Local_u8ErrorState = STD_TYPES_NOK;
	}
	return Local_u8ErrorState;
}

//Draw Special character.
u8 LCD_u8DrawCharacter(u8 Copy_u8NumberOfCharacter)
{
	u8 Local_u8ErrorState = STD_TYPES_OK;
	//Set CGRAM Address at AC
	switch(Copy_u8NumberOfCharacter)
	{
	case LCD_u8_CHARACTER_0 : LCD_voidWriteCmnd(LCD_u8_DRAWCHARACTER_0);break;
	case LCD_u8_CHARACTER_1 : LCD_voidWriteCmnd(LCD_u8_DRAWCHARACTER_1);break;
	case LCD_u8_CHARACTER_2 : LCD_voidWriteCmnd(LCD_u8_DRAWCHARACTER_2);break;
	case LCD_u8_CHARACTER_3 : LCD_voidWriteCmnd(LCD_u8_DRAWCHARACTER_3);break;
	case LCD_u8_CHARACTER_4 : LCD_voidWriteCmnd(LCD_u8_DRAWCHARACTER_4);break;
	case LCD_u8_CHARACTER_5 : LCD_voidWriteCmnd(LCD_u8_DRAWCHARACTER_5);break;
	case LCD_u8_CHARACTER_6 : LCD_voidWriteCmnd(LCD_u8_DRAWCHARACTER_6);break;
	case LCD_u8_CHARACTER_7 : LCD_voidWriteCmnd(LCD_u8_DRAWCHARACTER_7);break;
	default: Local_u8ErrorState = STD_TYPES_NOK;
	}
	return Local_u8ErrorState;
}
//Read Special character.
u8 LCD_u8PrintDrawnCharacter(u8 Copy_u8CharacterNumber)
{
	u8 Local_u8ErrorState = STD_TYPES_OK;
	if (Copy_u8CharacterNumber<8)
	{
		//Display our Patterns.
		LCD_voidWriteChar(Copy_u8CharacterNumber);
	}
	else
	{
		Local_u8ErrorState = STD_TYPES_NOK;
	}
	return Local_u8ErrorState;
}

void LCD_voidSavedCharacters(void)
{
	LCD_voidWriteCmnd(LCD_u8_DRAWCHARACTER_0);

	LCD_voidWriteChar(0b00001110);
	LCD_voidWriteChar(0b00001110);
	LCD_voidWriteChar(0b00000100);
	LCD_voidWriteChar(0b00011111);
	LCD_voidWriteChar(0b00010101);
	LCD_voidWriteChar(0b00000100);
	LCD_voidWriteChar(0b00000100);
	LCD_voidWriteChar(0b00001110);

	LCD_voidWriteCmnd(LCD_u8_DRAWCHARACTER_1);

	LCD_voidWriteChar(0b00000000);
	LCD_voidWriteChar(0b00000000);
	LCD_voidWriteChar(0b00000011);
	LCD_voidWriteChar(0b00011010);
	LCD_voidWriteChar(0b00011111);
	LCD_voidWriteChar(0b00011010);
	LCD_voidWriteChar(0b00000011);
	LCD_voidWriteChar(0b00000000);

    LCD_voidWriteCmnd(LCD_u8_DRAWCHARACTER_2);

	LCD_voidWriteChar(0b00000000);
	LCD_voidWriteChar(0b00000000);
	LCD_voidWriteChar(0b00000001);
	LCD_voidWriteChar(0b00000001);
	LCD_voidWriteChar(0b00011111);
	LCD_voidWriteChar(0b00000001);
	LCD_voidWriteChar(0b00000001);
	LCD_voidWriteChar(0b00000000);

    LCD_voidWriteCmnd(LCD_u8_DRAWCHARACTER_3);

	LCD_voidWriteChar(0b00000000);
	LCD_voidWriteChar(0b00000000);
	LCD_voidWriteChar(0b00010000);
	LCD_voidWriteChar(0b00010000);
	LCD_voidWriteChar(0b00011111);
	LCD_voidWriteChar(0b00010000);
	LCD_voidWriteChar(0b00010000);
	LCD_voidWriteChar(0b00000000);

    LCD_voidWriteCmnd(LCD_u8_DRAWCHARACTER_4);

	LCD_voidWriteChar(0b00000000);
	LCD_voidWriteChar(0b00000000);
	LCD_voidWriteChar(0b00000001);
	LCD_voidWriteChar(0b00000001);
	LCD_voidWriteChar(0b00011111);
	LCD_voidWriteChar(0b00000001);
	LCD_voidWriteChar(0b00000001);
	LCD_voidWriteChar(0b00000000);

}
//EX Print My name in Arabic using special characters.
u8 LCD_u8printSavedCharacters(u8 Copy_u8LineNumber ,u8 Copy_u8CharacterLocation )
{
	u8 Local_u8ErrorState = STD_TYPES_OK;

	if ((Copy_u8LineNumber<LCD_u8_LOCATION_2)&&(Copy_u8CharacterLocation<40))
	{
		LCD_voidSavedCharacters();

		LCD_u8GoToXY(Copy_u8LineNumber,Copy_u8CharacterLocation);

		u8 Local_u8Counter ;

		for(Local_u8Counter=0;Local_u8Counter<8;Local_u8Counter++)
		{
			LCD_u8PrintDrawnCharacter(Local_u8Counter);
		}
	}
	else
	{
		Local_u8ErrorState = STD_TYPES_OK;
	}

	return Local_u8ErrorState;
}

//Shifting Function
u8 LCD_u8InfiniteShiftingDisplayRegion(u8 Copy_u8ShiftingDirection)
{
	u8 Local_u8ErrorState = STD_TYPES_OK;
	switch(Copy_u8ShiftingDirection)
	{
	case LCD_u8_Shifting_Right  :
		while(1)
		{
			LCD_voidWriteCmnd(0b00011000);
			_delay_ms(500);
		}
		break;
	case LCD_u8_Shifting_Left  :
		while(1)
		{
			LCD_voidWriteCmnd(0b00011100);
			_delay_ms(500);
		}
		break;
	default: Local_u8ErrorState = STD_TYPES_NOK;
	}
	return Local_u8ErrorState;
}

u8 LCD_u8ShiftingDisplayRegion(u8 Copy_u8ShiftingDirection,u8 Copy_u8ShiftingSteps)
{
	u8 Local_u8ErrorState = STD_TYPES_OK;
	switch(Copy_u8ShiftingDirection)
	{
	case LCD_u8_Shifting_Right  :
		while(Copy_u8ShiftingSteps>0)
		{
			LCD_voidWriteCmnd(0b00011000);
			Copy_u8ShiftingSteps--;
			_delay_ms(500);
		}
		break;
	case LCD_u8_Shifting_Left  :
		while(Copy_u8ShiftingSteps>0)
		{
			LCD_voidWriteCmnd(0b00011100);
			Copy_u8ShiftingSteps--;
			_delay_ms(500);
		}
		break;
	default: Local_u8ErrorState = STD_TYPES_NOK;
	}
	return Local_u8ErrorState;
}
//If you want to over write something in characters make it at main before call function of saved character at main.
u8 LCD_u8PrintTwoWordsInSinusoidalWave(u8* Copy_pu8String)
{
	u8 Local_u8ErrorState = STD_TYPES_OK;
	u8 Local_u8Counter        = 0;
	LCD_voidSavedCharacters();
	if (LCD_u8_SizeOfArabicString<9)
	{
		while(1)
		{
			_delay_ms(500);
			LCD_u8GoToXY(LCD_u8_LINE_1,(LCD_u8_SizeOfArabicString)*Local_u8Counter);
			LCD_voidPrintString(&Copy_pu8String[0]);
			LCD_u8GoToXY(LCD_u8_LINE_2,(LCD_u8_SizeOfArabicString)*Local_u8Counter);
			LCD_u8PrintDrawnCharacter(0);
		    LCD_u8PrintDrawnCharacter(1);
			LCD_u8PrintDrawnCharacter(2);
			LCD_u8PrintDrawnCharacter(3);
			LCD_u8PrintDrawnCharacter(4);
			Local_u8Counter++;
			_delay_ms(1000);

			LCD_u8GoToXY(LCD_u8_LINE_2,(LCD_u8_SizeOfArabicString)*Local_u8Counter);
			LCD_voidPrintString(&Copy_pu8String[0]);
			LCD_u8GoToXY(LCD_u8_LINE_1,(LCD_u8_SizeOfArabicString)*Local_u8Counter);
			LCD_u8PrintDrawnCharacter(0);
		    LCD_u8PrintDrawnCharacter(1);
			LCD_u8PrintDrawnCharacter(2);
			LCD_u8PrintDrawnCharacter(3);
			LCD_u8PrintDrawnCharacter(4);
			Local_u8Counter++;
			_delay_ms(1000);

			LCD_u8GoToXY(LCD_u8_LINE_1,(LCD_u8_SizeOfArabicString)*Local_u8Counter);
			LCD_voidPrintString(&Copy_pu8String[0]);
			LCD_u8GoToXY(LCD_u8_LINE_2,(LCD_u8_SizeOfArabicString)*Local_u8Counter);
			LCD_u8PrintDrawnCharacter(0);
		    LCD_u8PrintDrawnCharacter(1);
			LCD_u8PrintDrawnCharacter(2);
			LCD_u8PrintDrawnCharacter(3);
			LCD_u8PrintDrawnCharacter(4);
			_delay_ms(1000);
			Local_u8Counter=0;

			LCD_u8GoToXY(LCD_u8_LINE_2,(LCD_u8_SizeOfArabicString)*Local_u8Counter);
			LCD_voidPrintString(&Copy_pu8String[0]);
			LCD_u8GoToXY(LCD_u8_LINE_1,(LCD_u8_SizeOfArabicString)*Local_u8Counter);
			LCD_u8PrintDrawnCharacter(0);
		    LCD_u8PrintDrawnCharacter(1);
			LCD_u8PrintDrawnCharacter(2);
			LCD_u8PrintDrawnCharacter(3);
			LCD_u8PrintDrawnCharacter(4);
			Local_u8Counter++;
			_delay_ms(1000);

			LCD_u8GoToXY(LCD_u8_LINE_1,(LCD_u8_SizeOfArabicString)*Local_u8Counter);
			LCD_voidPrintString(&Copy_pu8String[0]);
			LCD_u8GoToXY(LCD_u8_LINE_2,(LCD_u8_SizeOfArabicString)*Local_u8Counter);
			LCD_u8PrintDrawnCharacter(0);
		    LCD_u8PrintDrawnCharacter(1);
			LCD_u8PrintDrawnCharacter(2);
			LCD_u8PrintDrawnCharacter(3);
			LCD_u8PrintDrawnCharacter(4);
			_delay_ms(1000);
			Local_u8Counter++;

			LCD_u8GoToXY(LCD_u8_LINE_2,(LCD_u8_SizeOfArabicString)*Local_u8Counter);
			LCD_voidPrintString(&Copy_pu8String[0]);
			LCD_u8GoToXY(LCD_u8_LINE_1,(LCD_u8_SizeOfArabicString)*Local_u8Counter);
			LCD_u8PrintDrawnCharacter(0);
		    LCD_u8PrintDrawnCharacter(1);
			LCD_u8PrintDrawnCharacter(2);
			LCD_u8PrintDrawnCharacter(3);
			LCD_u8PrintDrawnCharacter(4);
			Local_u8Counter=0;
			_delay_ms(500);

		}
	}
	else
	{
		Local_u8ErrorState = STD_TYPES_OK;
	}
	return Local_u8ErrorState;
}

static void PRIVATE_voidSetHalfPort(u8 Copy_u8Value)
{
	if(GET_BIT(Copy_u8Value,7))
	{
		DIO_u8SetPinValue(LCD_u8_D7_PORT,LCD_u8_D7_PIN,DIO_u8_HIGH);
	}
	else
	{
		DIO_u8SetPinValue(LCD_u8_D7_PORT,LCD_u8_D7_PIN,DIO_u8_LOW);
	}
	if(GET_BIT(Copy_u8Value,6))
	{
		DIO_u8SetPinValue(LCD_u8_D6_PORT,LCD_u8_D6_PIN,DIO_u8_HIGH);
	}
	else
	{
		DIO_u8SetPinValue(LCD_u8_D6_PORT,LCD_u8_D6_PIN,DIO_u8_LOW);
	}
	if(GET_BIT(Copy_u8Value,5))
	{
		DIO_u8SetPinValue(LCD_u8_D5_PORT,LCD_u8_D5_PIN,DIO_u8_HIGH);
	}
	else
	{
		DIO_u8SetPinValue(LCD_u8_D5_PORT,LCD_u8_D5_PIN,DIO_u8_LOW);
	}
	if(GET_BIT(Copy_u8Value,4))
	{
		DIO_u8SetPinValue(LCD_u8_D4_PORT,LCD_u8_D4_PIN,DIO_u8_HIGH);
	}
	else
	{
		DIO_u8SetPinValue(LCD_u8_D4_PORT,LCD_u8_D4_PIN,DIO_u8_LOW);
	}
}
