/*Prebulid*/
/************************************************/
/*                     Name: Ziyad Mohammed     */
/*                     Date: 2/10/2021          */
/*                     SWC: LCD                 */
/*                     Version: 1.0             */
/************************************************/

#include "STD_TYPES.h"

//MCAL
#include "DIO_interface.h"

//HAL
#include "LCD_interface.h"
#include "KPD_interface.h"

#define F_CPU  8000000UL
#include <avr/delay.h>

#define SYSTEM_u8_PASSWORD_DIGIT     4

int main (void)
{
	DIO_u8Init();
	LCD_voidInit();

		u8 Local_u8Key;

		while(1)
		{
			// Scan Keypad
			KPD_u8GetKey(&Local_u8Key);
			if(Local_u8Key != KPD_u8_KEY_NOT_PRESSED)
			{
				LCD_voidWriteChar(Local_u8Key);
			}
		}

	//Assignment 1 // Calculator.
	u8 Local_u8Value;
	while(1)
	{
	DIO_u8GetPinValue(DIO_u8_PORTA,DIO_u8_PIN0,&Local_u8Value);
	LCD_voidWriteCmnd(0b00000001);
	_delay_ms(2);
	u8 Local_u8Key , Local_u8Operation=100 , Local_u8Counter=0,Local_u8PrintResult=0;
	s32 Local_u16Result ;
	s32 Local_Au16Operand[6]  ={0,0,0,0,0,0};
	u8 Local_Au16Operations[5]={0,0,0,0,0};
	LCD_u8GoToXY(LCD_u8_LINE_1,LCD_u8_LOCATION_0);

	while(Local_u8Value == 1)
	{
		DIO_u8GetPinValue(DIO_u8_PORTA,DIO_u8_PIN0,&Local_u8Value);
		// Scan Keypad
		KPD_u8GetKey(&Local_u8Key);
		if(Local_u8Key != KPD_u8_KEY_NOT_PRESSED)
		{
			if ((Local_u8Key >=48)&&(Local_u8Key<=57))
			{
			    LCD_voidWriteChar(Local_u8Key);
			    Local_Au16Operand[Local_u8Counter]= ((Local_u8Key-48) + (Local_Au16Operand[Local_u8Counter])*10 );
			}
			else if((Local_u8Key == 43)||(Local_u8Key == 45 )||(Local_u8Key == 120)||(Local_u8Key == 47)||(Local_u8Key ==37))
			{
				LCD_voidWriteChar(Local_u8Key);
				Local_Au16Operations[Local_u8Counter]=Local_u8Key ;
				Local_u8Counter++;
			}
			else if (Local_u8Key == 61)
			{
				LCD_voidWriteChar(Local_u8Key);
				Local_u8PrintResult=1;
			}
			if      ((Local_Au16Operations[0]==43) &&(Local_Au16Operations[1]==0)&&(Local_Au16Operations[2]==0)&&(Local_Au16Operations[3]==0)&&(Local_Au16Operations[4]==0))     Local_u8Operation=0;// +
			else if ((Local_Au16Operations[0]==45) &&(Local_Au16Operations[1]==0)&&(Local_Au16Operations[2]==0)&&(Local_Au16Operations[3]==0)&&(Local_Au16Operations[4]==0))     Local_u8Operation=1;// -
			else if ((Local_Au16Operations[0]==47) &&(Local_Au16Operations[1]==0)&&(Local_Au16Operations[2]==0)&&(Local_Au16Operations[3]==0)&&(Local_Au16Operations[4]==0))     Local_u8Operation=2;// /
			else if ((Local_Au16Operations[0]==120)&&(Local_Au16Operations[1]==0)&&(Local_Au16Operations[2]==0)&&(Local_Au16Operations[3]==0)&&(Local_Au16Operations[4]==0))     Local_u8Operation=3;// x
			else if ((Local_Au16Operations[0]==37) &&(Local_Au16Operations[1]==0)&&(Local_Au16Operations[2]==0)&&(Local_Au16Operations[3]==0)&&(Local_Au16Operations[4]==0))     Local_u8Operation=4;// %

			else if ((Local_Au16Operations[0]==43) &&(Local_Au16Operations[1]==43)&&(Local_Au16Operations[2]==0)&&(Local_Au16Operations[3]==0)&&(Local_Au16Operations[4]==0))    Local_u8Operation=5;   // + +
			else if ((Local_Au16Operations[0]==43) &&(Local_Au16Operations[1]==43)&&(Local_Au16Operations[2]==43)&&(Local_Au16Operations[3]==0)&&(Local_Au16Operations[4]==0))   Local_u8Operation=6;  // + + +
			else if ((Local_Au16Operations[0]==43) &&(Local_Au16Operations[1]==43)&&(Local_Au16Operations[2]==43)&&(Local_Au16Operations[3]==43)&&(Local_Au16Operations[4]==0))  Local_u8Operation=7; // + + + +
			else if ((Local_Au16Operations[0]==43) &&(Local_Au16Operations[1]==43)&&(Local_Au16Operations[2]==43)&&(Local_Au16Operations[3]==43)&&(Local_Au16Operations[4]==43)) Local_u8Operation=8;// + + + + +

			else if ((Local_Au16Operations[0]==45) &&(Local_Au16Operations[1]==45)&&(Local_Au16Operations[2]==0)&&(Local_Au16Operations[3]==0)&&(Local_Au16Operations[4]==0))    Local_u8Operation=9;    // - -
			else if ((Local_Au16Operations[0]==45) &&(Local_Au16Operations[1]==45)&&(Local_Au16Operations[2]==45)&&(Local_Au16Operations[3]==0)&&(Local_Au16Operations[4]==0))   Local_u8Operation=10;  // - - -
			else if ((Local_Au16Operations[0]==45) &&(Local_Au16Operations[1]==45)&&(Local_Au16Operations[2]==45)&&(Local_Au16Operations[3]==45)&&(Local_Au16Operations[4]==0))  Local_u8Operation=11; // - - - -
			else if ((Local_Au16Operations[0]==45) &&(Local_Au16Operations[1]==45)&&(Local_Au16Operations[2]==45)&&(Local_Au16Operations[3]==45)&&(Local_Au16Operations[4]==45)) Local_u8Operation=12;// - - - - -

			else if ((Local_Au16Operations[0]==43) &&(Local_Au16Operations[1]==120)&&(Local_Au16Operations[2]==47)) Local_u8Operation=13;

			if(Local_u8PrintResult==1)
			{
			switch (Local_u8Operation)
			{
			case 0:
				Local_u16Result = (Local_Au16Operand[0] + Local_Au16Operand[1]);
				LCD_u8GoToXY(LCD_u8_LINE_2,LCD_u8_LOCATION_0);
				LCD_voidPrintNumber(Local_u16Result);
				break;
			case 1:
				if (Local_Au16Operand[0]>Local_Au16Operand[1])
				{
					LCD_u8GoToXY(LCD_u8_LINE_2,LCD_u8_LOCATION_0);
					Local_u16Result = (Local_Au16Operand[0] - Local_Au16Operand[1]);
					LCD_voidPrintNumber(Local_u16Result);
				}
				else if (Local_Au16Operand[0]<Local_Au16Operand[1])
				{
					LCD_u8GoToXY(LCD_u8_LINE_2,LCD_u8_LOCATION_0);
					LCD_voidWriteChar('-');
					LCD_u8GoToXY(LCD_u8_LINE_2,LCD_u8_LOCATION_1);
					Local_u16Result = (Local_Au16Operand[1] - Local_Au16Operand[0]);
					LCD_voidPrintNumber(Local_u16Result);
				}
				else if(Local_Au16Operand[0]==Local_Au16Operand[1])
				{
					LCD_u8GoToXY(LCD_u8_LINE_2,LCD_u8_LOCATION_0);
					LCD_voidWriteChar('0');
				}
				break;
			case 2:
				if (Local_Au16Operand[0]==0)
				{
					LCD_u8GoToXY(LCD_u8_LINE_2,LCD_u8_LOCATION_0);
					LCD_voidWriteChar('0');
				}
				else if (Local_Au16Operand[1]==0)
				{
					LCD_u8GoToXY(LCD_u8_LINE_2,LCD_u8_LOCATION_0);
					u8 Local_CalculatorError[] ="Math Error";
					LCD_voidPrintString(&Local_CalculatorError[0]);
				}
				else if (Local_Au16Operand[0]==Local_Au16Operand[1])
				{
				    LCD_u8GoToXY(LCD_u8_LINE_2,LCD_u8_LOCATION_0);
				    LCD_voidPrintNumber(1);
				}
				else if (Local_Au16Operand[0]<Local_Au16Operand[1])
				{
					LCD_u8GoToXY(LCD_u8_LINE_2,LCD_u8_LOCATION_0);
					LCD_voidWriteChar('0');
					LCD_u8GoToXY(LCD_u8_LINE_2,LCD_u8_LOCATION_1);
					LCD_voidWriteChar(',');
					Local_u16Result = (((Local_Au16Operand[0]*100) / Local_Au16Operand[1]));
					LCD_voidPrintNumber(Local_u16Result);
				}
				else if (Local_Au16Operand[0]>Local_Au16Operand[1])
				{
					LCD_u8GoToXY(LCD_u8_LINE_2,LCD_u8_LOCATION_0);
					Local_u16Result = (Local_Au16Operand[0] / Local_Au16Operand[1]);
					if (((Local_Au16Operand[0] / Local_Au16Operand[1])*100)==0)
					{
						LCD_voidPrintNumber(Local_u16Result);
					}
					else
					{
						LCD_voidPrintNumber(Local_u16Result);
						LCD_voidWriteChar(',');
						Local_u16Result = (((Local_Au16Operand[0]*100) / Local_Au16Operand[1])-(Local_u16Result*100));
						LCD_voidPrintNumber(Local_u16Result);
					}
				}
				break;
			case 3:
				Local_u16Result = (Local_Au16Operand[0] * Local_Au16Operand[1]);
				LCD_u8GoToXY(LCD_u8_LINE_2,LCD_u8_LOCATION_0);
				LCD_voidPrintNumber(Local_u16Result);
				break;
			case 4:
				Local_u16Result = (Local_Au16Operand[0] % Local_Au16Operand[1]);
				LCD_u8GoToXY(LCD_u8_LINE_2,LCD_u8_LOCATION_0);
				LCD_voidPrintNumber(Local_u16Result);
				break;
				//New.
			case 5:
				Local_u16Result = (Local_Au16Operand[0] + Local_Au16Operand[1]+ Local_Au16Operand[2]);
				LCD_u8GoToXY(LCD_u8_LINE_2,LCD_u8_LOCATION_0);
				LCD_voidPrintNumber(Local_u16Result);
				break;
			case 6:
				Local_u16Result = (Local_Au16Operand[0] + Local_Au16Operand[1]+ Local_Au16Operand[2]+ Local_Au16Operand[3]);
				LCD_u8GoToXY(LCD_u8_LINE_2,LCD_u8_LOCATION_0);
				LCD_voidPrintNumber(Local_u16Result);
				break;
			case 7:
				Local_u16Result = (Local_Au16Operand[0] + Local_Au16Operand[1]+ Local_Au16Operand[2]+ Local_Au16Operand[3]+ Local_Au16Operand[4]);
				LCD_u8GoToXY(LCD_u8_LINE_2,LCD_u8_LOCATION_0);
				LCD_voidPrintNumber(Local_u16Result);
				break;
			case 8:
				Local_u16Result = (Local_Au16Operand[0] + Local_Au16Operand[1]+ Local_Au16Operand[2]+ Local_Au16Operand[3]+ Local_Au16Operand[4]+ Local_Au16Operand[5]);
				LCD_u8GoToXY(LCD_u8_LINE_2,LCD_u8_LOCATION_0);
				LCD_voidPrintNumber(Local_u16Result);
				break;

			case 9:
				Local_u16Result = (Local_Au16Operand[0] - Local_Au16Operand[1]- Local_Au16Operand[2]);
				if(Local_u16Result>=0)
				{
					LCD_u8GoToXY(LCD_u8_LINE_2,LCD_u8_LOCATION_0);
					LCD_voidPrintNumber(Local_u16Result);
				}
				else if (Local_u16Result<0)
				{
					LCD_u8GoToXY(LCD_u8_LINE_2,LCD_u8_LOCATION_0);
					LCD_voidWriteChar('-');
					Local_u16Result = (Local_u16Result * -1) ;
					LCD_voidPrintNumber(Local_u16Result);
				}
				break;
			case 10:
				Local_u16Result = (Local_Au16Operand[0] - Local_Au16Operand[1]- Local_Au16Operand[2]- Local_Au16Operand[3]);
				if(Local_u16Result>=0)
				{
					LCD_u8GoToXY(LCD_u8_LINE_2,LCD_u8_LOCATION_0);
					LCD_voidPrintNumber(Local_u16Result);
				}
				else if (Local_u16Result<0)
				{
					LCD_u8GoToXY(LCD_u8_LINE_2,LCD_u8_LOCATION_0);
					LCD_voidWriteChar('-');
					Local_u16Result = (Local_u16Result * -1) ;
					LCD_voidPrintNumber(Local_u16Result);
				}
				break;
			case 11:
				Local_u16Result = (Local_Au16Operand[0] - Local_Au16Operand[1] - Local_Au16Operand[2] - Local_Au16Operand[3] - Local_Au16Operand[4]);
				if(Local_u16Result>=0)
				{
					LCD_u8GoToXY(LCD_u8_LINE_2,LCD_u8_LOCATION_0);
					LCD_voidPrintNumber(Local_u16Result);
				}
				else if (Local_u16Result<0)
				{
					LCD_u8GoToXY(LCD_u8_LINE_2,LCD_u8_LOCATION_0);
					LCD_voidWriteChar('-');
					Local_u16Result = (Local_u16Result * -1) ;
					LCD_voidPrintNumber(Local_u16Result);
				}
				break;
			case 12:
				Local_u16Result = (Local_Au16Operand[0] - Local_Au16Operand[1] - Local_Au16Operand[2] - Local_Au16Operand[3] - Local_Au16Operand[4] - Local_Au16Operand[5]);
				if(Local_u16Result>=0)
				{
					LCD_u8GoToXY(LCD_u8_LINE_2,LCD_u8_LOCATION_0);
					LCD_voidPrintNumber(Local_u16Result);
				}
				else if (Local_u16Result<0)
				{
					LCD_u8GoToXY(LCD_u8_LINE_2,LCD_u8_LOCATION_0);
					LCD_voidWriteChar('-');
					Local_u16Result = (Local_u16Result * -1) ;
					LCD_voidPrintNumber(Local_u16Result);
				}
				break;
			case 13 :
				Local_u16Result = (Local_Au16Operand[0] +(( Local_Au16Operand[1] * Local_Au16Operand[2])/Local_Au16Operand[3]));
				LCD_u8GoToXY(LCD_u8_LINE_2,LCD_u8_LOCATION_0);
				LCD_voidPrintNumber(Local_u16Result);
				LCD_voidWriteChar(',');
				Local_u16Result  = (( Local_Au16Operand[1] * Local_Au16Operand[2])/Local_Au16Operand[3]) ;
				Local_u16Result = ((( Local_Au16Operand[1] * Local_Au16Operand[2] * 100 )/Local_Au16Operand[3])-(Local_u16Result*100));
				LCD_voidPrintNumber(Local_u16Result);
				break;
			}

		}
		}
	}
	}

	/*//Assignment 2
	u8 Local_u8Key, Local_u8Counter=0 ;
	u16 Local_u8Password=1234, Local_u8EnteredPassword=0 , Local_u8Tries=0;
	u8 Local_Au8Password[] = "Enter Password :";
	LCD_voidPrintString(&Local_Au8Password[0]);

	while(1)
	{
	for( ;Local_u8Counter<SYSTEM_u8_PASSWORD_DIGIT;)
	{
		    // Scan Keypad
			KPD_u8GetKey(&Local_u8Key);
			if(Local_u8Key != KPD_u8_KEY_NOT_PRESSED)
			{
				LCD_u8GoToXY(LCD_u8_LINE_2,Local_u8Counter);
				LCD_voidWriteChar(Local_u8Key);
				_delay_ms(70);
				LCD_u8GoToXY(LCD_u8_LINE_2,Local_u8Counter);
				LCD_voidWriteChar('*');
				Local_u8Counter++;
				Local_u8EnteredPassword = ((Local_u8Key-48) + Local_u8EnteredPassword*10 );
		   }
	}


	if(Local_u8EnteredPassword == Local_u8Password)
	{
		LCD_voidWriteCmnd(0b00000001);
		_delay_ms(2);
		u8 Local_u8Status[] = "Welcome Ziyad";
		LCD_voidPrintString(&Local_u8Status[0]);
		DIO_u8SetPinValue(DIO_u8_PORTA,DIO_u8_PIN0,DIO_u8_HIGH);
		DIO_u8SetPinValue(DIO_u8_PORTA,DIO_u8_PIN1,DIO_u8_LOW);
		break;
	}
	//New.
	else if(Local_u8EnteredPassword != Local_u8Password)
	{
		LCD_voidWriteCmnd(0b00000001);
		_delay_ms(2);
		LCD_u8GoToXY(LCD_u8_LINE_1,LCD_u8_LOCATION_0);
		u8 Local_Au8Tries[] = "Try Again";
		LCD_voidPrintString(&Local_Au8Tries[0]);

		LCD_u8GoToXY(LCD_u8_LINE_1,LCD_u8_LOCATION_15);
		LCD_voidPrintNumber((Local_u8Tries+1));
		Local_u8Tries++;
		Local_u8EnteredPassword=0;
		Local_u8Counter=0;
		LCD_u8GoToXY(LCD_u8_LINE_2,LCD_u8_LOCATION_0);
	}
	if(Local_u8Tries==3)
	{
		LCD_voidWriteCmnd(0b00000001);
		_delay_ms(2);
		u8 Local_Au8Close[] = "No More Tries";
		LCD_voidPrintString(&Local_Au8Close[0]);
		DIO_u8SetPinValue(DIO_u8_PORTA,DIO_u8_PIN0,DIO_u8_LOW);
		DIO_u8SetPinValue(DIO_u8_PORTA,DIO_u8_PIN1,DIO_u8_HIGH);
		break;
	}
	}*/

/*
	//Assignment 3 with Buzzer & Motor
	u8 Local_u8Key, Local_u8Counter=0 ;
	u16 Local_u8Password=1234, Local_u8EnteredPassword=0 , Local_u8Tries=0;
	u8 Local_Au8Password[] = "Enter Password :";
	LCD_voidPrintString(&Local_Au8Password[0]);
	u8 Local_Au8Tries[] = "Try Again";
	u8 Local_u8Choices[]="1- DC Motor.                            2- Exit.";
	u8 Local_u8FinalExit[]=" System Closed. ";
	u8 Local_u8MotorDashBoard[]=" 1-C.W  3-Stop                           2-CC.W 4-Return";
	u8 Local_u8Choice=0;
	u8 Local_u8Select=0;
	u8 Local_u8Flag =0 ;
	while(1)
	{
	for( ;Local_u8Counter<SYSTEM_u8_PASSWORD_DIGIT;)
	{
		    // Scan Keypad
			KPD_u8GetKey(&Local_u8Key);
			if(Local_u8Key != KPD_u8_KEY_NOT_PRESSED)
			{
				LCD_u8GoToXY(LCD_u8_LINE_2,Local_u8Counter);
				LCD_voidWriteChar(Local_u8Key);
				_delay_ms(70);
				LCD_u8GoToXY(LCD_u8_LINE_2,Local_u8Counter);
				LCD_voidWriteChar('*');
				Local_u8Counter++;
				Local_u8EnteredPassword = ((Local_u8Key-48) + Local_u8EnteredPassword*10 );
		   }
	}


	if(Local_u8EnteredPassword == Local_u8Password)
	{
		LCD_voidWriteCmnd(0b00000001);
		_delay_ms(2);
		u8 Local_u8Status[] = "   Welcome To                           Motor Dash Board";
		LCD_voidPrintString(&Local_u8Status[0]);
		//New.
		_delay_ms(1000);
		LCD_voidWriteCmnd(0b00000001);
		_delay_ms(2);
		LCD_u8GoToXY(LCD_u8_LINE_1,LCD_u8_LOCATION_2);
		LCD_voidPrintString(&Local_u8Choices[0]);

		while (1)
		{
			KPD_u8GetKey(&Local_u8Choice);
			if(Local_u8Choice != KPD_u8_KEY_NOT_PRESSED)
			{
			while ((Local_u8Choice=='1')&&(Local_u8Flag==0))//
			{
				Local_u8Flag=1;
				LCD_voidWriteCmnd(0b00000001);
				_delay_ms(2);
				LCD_u8GoToXY(LCD_u8_LINE_1,LCD_u8_LOCATION_0);
				LCD_voidPrintString(&Local_u8Status[0]);
				LCD_voidWriteCmnd(0b00000001);
				_delay_ms(2);
				LCD_u8GoToXY(LCD_u8_LINE_1,LCD_u8_LOCATION_0);
				LCD_voidPrintString(&Local_u8MotorDashBoard[0]);

				while (Local_u8Flag==1)
				{
					KPD_u8GetKey(&Local_u8Select);
					if (Local_u8Select != KPD_u8_KEY_NOT_PRESSED)
					{
					if (Local_u8Select=='1')
					{
						LCD_u8GoToXY(LCD_u8_LINE_1,LCD_u8_LOCATION_0);
						LCD_voidWriteChar('>');
						LCD_u8GoToXY(LCD_u8_LINE_2,LCD_u8_LOCATION_0);
						LCD_voidWriteChar(' ');
						LCD_u8GoToXY(LCD_u8_LINE_1,LCD_u8_LOCATION_7);
						LCD_voidWriteChar(' ');
						DIO_u8SetPinValue(DIO_u8_PORTA,DIO_u8_PIN0,DIO_u8_LOW);
						DIO_u8SetPinValue(DIO_u8_PORTA,DIO_u8_PIN1,DIO_u8_HIGH);
					}
					else if (Local_u8Select=='2')
					{
						LCD_u8GoToXY(LCD_u8_LINE_2,LCD_u8_LOCATION_0);
						LCD_voidWriteChar('>');
						LCD_u8GoToXY(LCD_u8_LINE_1,LCD_u8_LOCATION_0);
						LCD_voidWriteChar(' ');
						LCD_u8GoToXY(LCD_u8_LINE_1,LCD_u8_LOCATION_7);
						LCD_voidWriteChar(' ');
						DIO_u8SetPinValue(DIO_u8_PORTA,DIO_u8_PIN1,DIO_u8_LOW);
						DIO_u8SetPinValue(DIO_u8_PORTA,DIO_u8_PIN0,DIO_u8_HIGH);
					}
					else if (Local_u8Select=='3')
					{
						LCD_u8GoToXY(LCD_u8_LINE_1,LCD_u8_LOCATION_7);
						LCD_voidWriteChar('>');
						LCD_u8GoToXY(LCD_u8_LINE_1,LCD_u8_LOCATION_0);
						LCD_voidWriteChar(' ');
						LCD_u8GoToXY(LCD_u8_LINE_2,LCD_u8_LOCATION_0);
						LCD_voidWriteChar(' ');
						DIO_u8SetPinValue(DIO_u8_PORTA,DIO_u8_PIN1,DIO_u8_LOW);
						DIO_u8SetPinValue(DIO_u8_PORTA,DIO_u8_PIN0,DIO_u8_LOW);
					}
					else if (Local_u8Select=='4')
					{
						DIO_u8SetPinValue(DIO_u8_PORTA,DIO_u8_PIN1,DIO_u8_LOW);
						DIO_u8SetPinValue(DIO_u8_PORTA,DIO_u8_PIN0,DIO_u8_LOW);
						Local_u8Flag=0;
						Local_u8Select=0;
						LCD_voidWriteCmnd(0b00000001);
						_delay_ms(2);
						LCD_u8GoToXY(LCD_u8_LINE_1,LCD_u8_LOCATION_2);
						LCD_voidPrintString(&Local_u8Choices[0]);
						KPD_u8GetKey(&Local_u8Choice);

					}
					}
				}
			}
			if (Local_u8Choice=='2')
			{
				LCD_voidWriteCmnd(0b00000001);
				_delay_ms(2);
				LCD_u8GoToXY(LCD_u8_LINE_1,LCD_u8_LOCATION_0);
				LCD_voidPrintString(&Local_u8FinalExit[0]);
				while(1);
				break;
			}
			}
		}
	}

	else if(Local_u8EnteredPassword != Local_u8Password)
	{
		LCD_voidWriteCmnd(0b00000001);
		_delay_ms(2);
		LCD_u8GoToXY(LCD_u8_LINE_1,LCD_u8_LOCATION_0);
		LCD_voidPrintString(&Local_Au8Tries[0]);

		LCD_u8GoToXY(LCD_u8_LINE_1,LCD_u8_LOCATION_15);
		LCD_voidPrintNumber((Local_u8Tries+1));
		Local_u8Tries++;
		Local_u8EnteredPassword=0;
		Local_u8Counter=0;
		LCD_u8GoToXY(LCD_u8_LINE_2,LCD_u8_LOCATION_0);
	}
	if(Local_u8Tries==3)
	{
		LCD_voidWriteCmnd(0b00000001);
		_delay_ms(2);
		u8 Local_Au8Close[] = "No More Tries";
		LCD_voidPrintString(&Local_Au8Close[0]);

		//Buzzer
		DIO_u8SetPinValue(DIO_u8_PORTD,DIO_u8_PIN3,DIO_u8_HIGH);
		_delay_ms(3000);
		DIO_u8SetPinValue(DIO_u8_PORTD,DIO_u8_PIN3,DIO_u8_LOW);

		break;
	}
	}

		while(1);

	return 0 ;
}*/



