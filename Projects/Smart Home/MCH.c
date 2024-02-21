/************************************************/
/*                     Name: Ziyad Mohammed     */
/*                     Date: 2/2/2022           */
/*                     SWC: Smart Home Project  */
/*                     Version: 1.0             */
/************************************************/

#include <avr/delay.h>
#define F_CPU 8000000UL
#include "MCH_prototype.h"
#include "TMR_interface.h"
#include "GIE_interface.h"
#include "STD_TYPES.h"
#include "DIO_interface.h"
#include "LCD_interface.h"
#include "USART_interface.h"
#include "MCH_config.h"
#include "MCH_prototype.h"

u8 Local_u8SendChar;
u8 Local_u8PassCounter = 0;
u8 Local_u8LocalUserCounter=0;
u8 Local_u8LocalUserNameCounter=0;
u8 Local_u8Alarm = 0 ;
u8 Local_u8Search=0;
u32 Local_u32EnteredPass = 0;
u8 Local_u8Screen_E [] = "Wrong Password";
u8 Local_u8EnterPass[] = "Enter Password :";
u8 Local_u8Flag=0;
u8 Local_u8NoTries[] = "No More Tries";
u8 MCH_u8TimeOut=0;
u8 MCH_u8EnteredName=0;
u8 Local_u8EnteredPasswordFlag=0;
u8 Local_u8Add [] ="Add";
u8 Local_u8Remove [] ="Remove";
u8 Local_u8Enter [] ="Enter";
u8 MCH_u8MotorStart=0;
u8 MCH_u8MotorFlag=0;
u8 MCH_u8MotorDirection=0;

void App_voidTimeOut(void);
int main (void)
{
	/* Initialize the nedded strings.*/
	u8 Local_u8Screen_W [] ="Welcome";
	u8 Local_u8Added [] ="Added";
	u8 Local_u8Removed [] ="Removed";
	u8 Local_u8Screen_F [] = "1-Remove 2-Enter";
	u8 Local_u8EnterName[] = "Enter Name :";
	u8 Local_u8Full[] = "Sorry it's Full";
	u8 Local_u8RightPass[] = "Right Password";
	u8 Local_u8NotFound[] = "Not Found";
	u8 Local_u8Actions[] = "1-Light   2-Door";
	u8 Local_u8End[] = "End";
	u8 Local_u8NameExist = 0 ;
	u8 Local_u8SavedUsers[10][7]={"       ","       ","       ","       ","       ","       ","       ","       ","       ","       "};
	u8 Local_u8UserName[]="       ";
	u8 Local_u8Repeated[]="Repeated";
	u16 Local_u16SavedPass[10]={0,0,0,0,0,0,0,0,0,0};
	DIO_u8Init();
	/*Enable global interrupt.*/
	GIE_voidEnable();
	/*Set call back*/
	TMR_u8SetCallBack(TMR_u8_TMR0_OVF_MODE,&App_voidTimeOut);
	/*Start Timer*/
	TMR_u8TMR0NormalINIT(TMR_u8_TMR0_CLK_DIVIDED_8,1000000000,0,0);
	LCD_voidInit();
	USART_voidInit(USART_u8_RX_COMPLETE_INTERRUPT_DISABLE,USART_u8_TX_COMPLETE_INTERRUPT_DISABLE,USART_u8_DATA_REGISTER_EMPTY_INTERRUPT_DISABLE);
	MCH_u8LCDPrintOptions(Local_u8Screen_W,LCD_u8_LINE_1,LCD_u8_LOCATION_4,MCH_u8_CLEAR_SCREEN);
	_delay_ms(1000);
	MCH_voidPrintStart();
	/*100000 Tick nearly equal to 1 SEC.*/
	while(1)
	{
		USART_u8RecieveByte(&Local_u8SendChar);
		while (Local_u8SendChar != '!')
		{
		switch (Local_u8SendChar)
		{
		case '+': /*Add*/
			if (Local_u8LocalUserCounter<10)
			{
				MCH_u8TimeOut=0;//To take all of time.
				/*Put zero in Password variable.*/
				Local_u32EnteredPass = 0;
		    	MCH_u8LCDPrintOptions(Local_u8Add,LCD_u8_LINE_1,LCD_u8_LOCATION_6,MCH_u8_CLEAR_SCREEN);
			    _delay_ms(500);
			    /*! == Noting send.*/
			    Local_u8SendChar = '!';
			    /* & => Enter.*/
			    /*Enter pass.*/
			    MCH_u8LCDPrintOptions(Local_u8EnterPass,LCD_u8_LINE_1,LCD_u8_LOCATION_0,MCH_u8_CLEAR_SCREEN);
		        MCH_u8EnterPassword(&Local_u32EnteredPass);
		        /*Check Time out.*/
			    Local_u8PassCounter=0;
			if ((Local_u32EnteredPass == MCH_u32_LOCA_PASSWORD)&&(MCH_u8TimeOut<=MCH_u32_TIMEOUT_SEC))
			{
				/*Make Time out = 0 to start again.*/
				MCH_u8TimeOut=0;
				/* Make the alarm counter = 0.*/
				Local_u8Alarm=0;
				/*zero counter letters.*/
				Local_u8LocalUserNameCounter=0;
				/*Print Right Password.& delay.*/
				MCH_u8LCDPrintOptions(Local_u8RightPass,LCD_u8_LINE_1,LCD_u8_LOCATION_0,MCH_u8_CLEAR_SCREEN);
				_delay_ms(500);
				/*Enter Name*/
				MCH_u8LCDPrintOptions(Local_u8EnterName,LCD_u8_LINE_1,LCD_u8_LOCATION_0,MCH_u8_CLEAR_SCREEN);
				USART_u8RecieveByte(&Local_u8SendChar);
				LCD_u8GoToXY(LCD_u8_LINE_2,LCD_u8_LOCATION_0);
				MCH_u8TimeOut=0;/*To take all of time.*/
				MCH_u8EnterName(&Local_u8SavedUsers[Local_u8LocalUserCounter][Local_u8LocalUserNameCounter]);//Pass The needed array.
				/*Check if entered name successfully or not.*/
				if(MCH_u8EnteredName == 0)
				{
				/*Check repeated or not.*/
				Local_u8NameExist = 0 ;
				for (Local_u8Search=0;Local_u8Search<=Local_u8LocalUserCounter;Local_u8Search++)
				{
					if((Local_u8SavedUsers[Local_u8LocalUserCounter][0]==Local_u8SavedUsers[Local_u8Search][0])&&(Local_u8SavedUsers[Local_u8LocalUserCounter][1]==Local_u8SavedUsers[Local_u8Search][1])&&(Local_u8SavedUsers[Local_u8LocalUserCounter][2]==Local_u8SavedUsers[Local_u8Search][2])&&(Local_u8SavedUsers[Local_u8LocalUserCounter][3]==Local_u8SavedUsers[Local_u8Search][3])&&(Local_u8SavedUsers[Local_u8LocalUserCounter][4]==Local_u8SavedUsers[Local_u8Search][4])&&(Local_u8SavedUsers[Local_u8LocalUserCounter][5]==Local_u8SavedUsers[Local_u8Search][5])&&(Local_u8SavedUsers[Local_u8LocalUserCounter][6]==Local_u8SavedUsers[Local_u8Search][6]))
					{
						/*flag indicate exist or not.*/
						Local_u8NameExist++;
					}
				}
				if ((Local_u8NameExist==1)&&(MCH_u8TimeOut<=MCH_u32_TIMEOUT_SEC))
				{
				/*Put zero in Password variable.*/
				Local_u32EnteredPass = 0;
				/*Enter Password.*/
				MCH_u8LCDPrintOptions(Local_u8EnterPass,LCD_u8_LINE_1,LCD_u8_LOCATION_0,MCH_u8_CLEAR_SCREEN);
				Local_u8SendChar=0;
				Local_u8PassCounter=0;
				MCH_u8EnterPassword(&Local_u32EnteredPass);
				/*Check if entered pass or not. Not will case to remove name.*/
				if (Local_u32EnteredPass!=0)
				{
				MCH_u8LCDPrintOptions(Local_u8Added,LCD_u8_LINE_1,LCD_u8_LOCATION_5,MCH_u8_CLEAR_SCREEN);
				_delay_ms(1000);
				Local_u16SavedPass[Local_u8LocalUserCounter]=Local_u32EnteredPass;
				Local_u32EnteredPass=0;
				/*zero counter letters.*/
				Local_u8LocalUserNameCounter=0;/*repeated.*/
				/*Increment User counter .*/
				Local_u8LocalUserCounter++;
				MCH_voidPrintStart();
				}
				else if (Local_u32EnteredPass==0)
				{
					/*Remove entered name.*/
					for(Local_u8Search=0;Local_u8Search<7;Local_u8Search++)
					{
						Local_u8SavedUsers[Local_u8LocalUserCounter][Local_u8Search]=' ';
					}
				}
				}
				else if (Local_u8NameExist>1)//Else if to make sure... checking time here isn't very important.
				{
					MCH_u8LCDPrintOptions(Local_u8Repeated,LCD_u8_LINE_1,LCD_u8_LOCATION_0,MCH_u8_CLEAR_SCREEN);
					_delay_ms(1000);
					MCH_voidPrintStart();
					/*delete repeated name.Note..The last one deleted.*/
					for(Local_u8Search=0;Local_u8Search<7;Local_u8Search++)
					{
						Local_u8SavedUsers[Local_u8LocalUserCounter][Local_u8Search]=' ';
					}
					Local_u8NameExist=0;
					/**/ So you can write on it again You must decrement Local_u8LocalUserCounter.*/
					Local_u8LocalUserCounter--;
				}
			    }
			    }
			/*Exception here if accidentally pressed on add by the user.*/
			else if ((Local_u32EnteredPass != MCH_u32_LOCA_PASSWORD)&&(MCH_u8TimeOut<=MCH_u32_TIMEOUT_SEC))
			{
				Local_u32EnteredPass=0;
				MCH_u8LCDPrintOptions(Local_u8Screen_E,LCD_u8_LINE_1,LCD_u8_LOCATION_0,MCH_u8_CLEAR_SCREEN);
				Local_u8Alarm++;
				if (Local_u8Alarm==3)
				{
					DIO_u8SetPinValue(DIO_u8_PORTB,DIO_u8_PIN0,DIO_u8_HIGH);/*Buzzer.*/
					_delay_ms(800);
					MCH_u8LCDPrintOptions(Local_u8NoTries,LCD_u8_LINE_1,LCD_u8_LOCATION_0,MCH_u8_CLEAR_SCREEN);
					/*Not to do any thing till reset the system.*/
					while(1);
				}
				_delay_ms(800);
				MCH_voidPrintStart();
			}
		    }
			else if ((Local_u8LocalUserCounter>=10)&&(MCH_u8TimeOut<=MCH_u32_TIMEOUT_SEC))
			{
				MCH_u8LCDPrintOptions(Local_u8Full,LCD_u8_LINE_1,LCD_u8_LOCATION_0,MCH_u8_CLEAR_SCREEN);
				_delay_ms(1000);
				MCH_u8LCDPrintOptions(Local_u8Screen_F,LCD_u8_LINE_1,LCD_u8_LOCATION_0,MCH_u8_CLEAR_SCREEN);
			}
			if((MCH_u8TimeOut>MCH_u32_TIMEOUT_SEC)||(MCH_u8EnteredName ==1)||(Local_u32EnteredPass!=0))
			{
				MCH_voidPrintStart();
				MCH_u8TimeOut=0;
				MCH_u8EnteredName =0;
			}
			break;
		case '-':/*Remove.*/
			MCH_u8LCDPrintOptions(Local_u8Remove,LCD_u8_LINE_1,LCD_u8_LOCATION_5,MCH_u8_CLEAR_SCREEN);
			_delay_ms(500);
			/*Enter Name.*/
			MCH_u8LCDPrintOptions(Local_u8EnterName,LCD_u8_LINE_1,LCD_u8_LOCATION_0,MCH_u8_CLEAR_SCREEN);
			USART_u8RecieveByte(&Local_u8SendChar);
			Local_u8LocalUserNameCounter=0;
			LCD_u8GoToXY(LCD_u8_LINE_2,LCD_u8_LOCATION_0);
			MCH_u8EnterName(&Local_u8UserName[Local_u8LocalUserNameCounter]);
			if(MCH_u8EnteredName==0)
			{
			/*for loop on the remain parts to be ' '*/
			for(;Local_u8LocalUserNameCounter<7;Local_u8LocalUserNameCounter++)
				{
					Local_u8UserName[Local_u8LocalUserNameCounter]= ' ';
				}
			/*Put zero in Password variable.*/
			Local_u32EnteredPass = 0;
			/*Enter Password.*/
			MCH_u8LCDPrintOptions(Local_u8EnterPass,LCD_u8_LINE_1,LCD_u8_LOCATION_0,MCH_u8_CLEAR_SCREEN);
			Local_u8SendChar=0;
			Local_u8PassCounter=0;
			Local_u8NameExist=0;
			/*Search for the User Name in the Memory.*/
			for(Local_u8Search=0;Local_u8Search<10;Local_u8Search++)
			{
			   	/*Enter User Name.*/
				while((Local_u8EnteredPasswordFlag==0)&&(Local_u8SendChar!='&')&&(Local_u8UserName[0]==Local_u8SavedUsers[Local_u8Search][0])&&(Local_u8UserName[1]==Local_u8SavedUsers[Local_u8Search][1])&&(Local_u8UserName[2]==Local_u8SavedUsers[Local_u8Search][2])&&(Local_u8UserName[3]==Local_u8SavedUsers[Local_u8Search][3])&&(Local_u8UserName[4]==Local_u8SavedUsers[Local_u8Search][4])&&(Local_u8UserName[5]==Local_u8SavedUsers[Local_u8Search][5])&&(Local_u8UserName[6]==Local_u8SavedUsers[Local_u8Search][6]))
					{
						USART_u8RecieveByte(&Local_u8SendChar);
						MCH_u8EnterPassword(&Local_u32EnteredPass);
						/*flag to indicate if the name exist or not.*/
						Local_u8NameExist=1;
					}
			if ((Local_u8NameExist==1)&&(Local_u8EnteredPasswordFlag==0))
				{
					while((Local_u32EnteredPass!=MCH_u32_LOCA_PASSWORD)&&(Local_u8Alarm<2)&&(Local_u8NameExist==1)/*&&(Local_u8EnteredPasswordFlag==0)*/)
						{
						MCH_u32WrongPassword(MCH_u32_LOCA_PASSWORD);
				    	}
	    	/*Removing Process.*/
	    	if((Local_u32EnteredPass==MCH_u32_LOCA_PASSWORD)&&(Local_u8NameExist==1))
				{/*do thing to indicate correct pass one time an to do actions.*/
					Local_u8Alarm=0;
					for(;Local_u8Search<9;Local_u8Search++)/*Less than 10 same as removed one.*/
					{
						/*Transfer User name.*/
						for(Local_u8LocalUserNameCounter=0;Local_u8LocalUserNameCounter<7;Local_u8LocalUserNameCounter++)
						{
							Local_u8SavedUsers[Local_u8Search][Local_u8LocalUserNameCounter] = Local_u8SavedUsers[(Local_u8Search+1)][Local_u8LocalUserNameCounter];
						}
						/*Transfer Password.*/
						Local_u16SavedPass[Local_u8Search] = Local_u16SavedPass [(Local_u8Search+1)];
					}
				}
			/*zero counter letters.*/
			Local_u8LocalUserNameCounter=0;
	    	Local_u8LocalUserCounter--;/*so we can use the place that we removed.*/
	    	MCH_u8LCDPrintOptions(Local_u8Removed,LCD_u8_LINE_1,LCD_u8_LOCATION_0,MCH_u8_CLEAR_SCREEN);
	    	_delay_ms(500);
	    	MCH_voidPrintStart();
				}
			else if ((Local_u8Search==9)&&(Local_u8NameExist==0)&&(Local_u8EnteredPasswordFlag==0))
			{
				MCH_u8LCDPrintOptions(Local_u8NotFound,LCD_u8_LINE_1,LCD_u8_LOCATION_0,MCH_u8_CLEAR_SCREEN);
				_delay_ms(1000);
               	MCH_voidPrintStart();
			}
			}
			}
			if((MCH_u8EnteredName==1)||(Local_u8EnteredPasswordFlag==1))
			{
				MCH_voidPrintStart();
				MCH_u8TimeOut=0;/*remove.*/
				MCH_u8EnteredName =0;
				Local_u8EnteredPasswordFlag=0;
			}
			break;
		case '=':/*Enter to open or close the door*/
			MCH_u8LCDPrintOptions(Local_u8Enter,LCD_u8_LINE_1,LCD_u8_LOCATION_5,MCH_u8_CLEAR_SCREEN);
			_delay_ms(500);
			/*Enter Name.*/
			MCH_u8LCDPrintOptions(Local_u8EnterName,LCD_u8_LINE_1,LCD_u8_LOCATION_0,MCH_u8_CLEAR_SCREEN);
			USART_u8RecieveByte(&Local_u8SendChar);
			Local_u8LocalUserNameCounter=0;
			LCD_u8GoToXY(LCD_u8_LINE_2,LCD_u8_LOCATION_0);
			MCH_u8EnterName(&Local_u8UserName[Local_u8LocalUserNameCounter]);
			if(MCH_u8EnteredName==0)
			{
			/*for loop on the remain parts to be ' '*/
			for(;Local_u8LocalUserNameCounter<7;Local_u8LocalUserNameCounter++)
			{
				Local_u8UserName[Local_u8LocalUserNameCounter]= ' ';
			}
			/*Put zero in Password variable.*/
			Local_u32EnteredPass = 0;
			/*Enter Password.*/
			MCH_u8LCDPrintOptions(Local_u8EnterPass,LCD_u8_LINE_1,LCD_u8_LOCATION_0,MCH_u8_CLEAR_SCREEN);
			Local_u8SendChar=0;
			Local_u8PassCounter=0;
			Local_u8NameExist=0;
			/*Search for the User Name in the Memory.*/
			for(Local_u8Search=0;Local_u8Search<10;Local_u8Search++)
			{
				/*Enter User Name.*/
				while((Local_u8EnteredPasswordFlag==0)&&(Local_u8SendChar!='&')&&(Local_u8UserName[0]==Local_u8SavedUsers[Local_u8Search][0])&&(Local_u8UserName[1]==Local_u8SavedUsers[Local_u8Search][1])&&(Local_u8UserName[2]==Local_u8SavedUsers[Local_u8Search][2])&&(Local_u8UserName[3]==Local_u8SavedUsers[Local_u8Search][3])&&(Local_u8UserName[4]==Local_u8SavedUsers[Local_u8Search][4])&&(Local_u8UserName[5]==Local_u8SavedUsers[Local_u8Search][5])&&(Local_u8UserName[6]==Local_u8SavedUsers[Local_u8Search][6]))
				{
						USART_u8RecieveByte(&Local_u8SendChar);
						MCH_u8EnterPassword(&Local_u32EnteredPass);
						Local_u8NameExist=1;
				}
				if ((Local_u8EnteredPasswordFlag==0)&&(Local_u8NameExist==1))
				{
				while((Local_u8EnteredPasswordFlag==0)&&(Local_u32EnteredPass!=Local_u16SavedPass[Local_u8Search])&&(Local_u8Alarm<2)&&(Local_u8NameExist==1))
				{
					MCH_u32WrongPassword(Local_u16SavedPass[Local_u8Search]);
				}
				MCH_u8LCDPrintOptions(Local_u8RightPass,LCD_u8_LINE_1,LCD_u8_LOCATION_0,MCH_u8_CLEAR_SCREEN);
				_delay_ms(800);
				MCH_u8LCDPrintOptions(Local_u8Actions,LCD_u8_LINE_1,LCD_u8_LOCATION_0,MCH_u8_CLEAR_SCREEN);
				while((Local_u32EnteredPass==Local_u16SavedPass[Local_u8Search])&&(Local_u8SendChar!='@')&&(Local_u8NameExist==1))
				{
					Local_u8Alarm=0;
					USART_u8RecieveByte(&Local_u8SendChar);
					/*Actions.*/
					if(Local_u8SendChar=='(')
					{
						/*Turn on light.*/
						DIO_u8SetPinValue(DIO_u8_PORTB,DIO_u8_PIN3,DIO_u8_HIGH);
					}
					else if(Local_u8SendChar==')')
					{
						MCH_u8MotorFlag=1;
						MCH_u8MotorStart=0;
						MCH_u8MotorDirection=0;/*Right*/
					}
					else if(Local_u8SendChar=='#')
					{
						/*Turn off light.*/
						DIO_u8SetPinValue(DIO_u8_PORTB,DIO_u8_PIN3,DIO_u8_LOW);
					}
					else if (Local_u8SendChar=='$')
					{
						MCH_u8MotorFlag=1;
						MCH_u8MotorStart=0;
						MCH_u8MotorDirection=1;//Left
					}
					/*flag to make local search =10.*/
					Local_u8Flag=1;
				}
				if(Local_u8Flag==1)
				{
					/*To terminate for loop.*/
					Local_u8Search=10;
					MCH_u8LCDPrintOptions(Local_u8End,LCD_u8_LINE_1,LCD_u8_LOCATION_0,MCH_u8_CLEAR_SCREEN);
					_delay_ms(800);
					MCH_voidPrintStart();
				}
				}
				else if ((Local_u8EnteredPasswordFlag==0)&&(Local_u8Search==9)&&(Local_u8NameExist==0))/*Local_u8EnteredPasswordFlag==0=> Only to make sure.*/
				{
					MCH_u8LCDPrintOptions(Local_u8NotFound,LCD_u8_LINE_1,LCD_u8_LOCATION_0,MCH_u8_CLEAR_SCREEN);
					_delay_ms(1000);
					MCH_voidPrintStart();
				}
			}
		    }
			if((MCH_u8EnteredName==1)||(Local_u8EnteredPasswordFlag==1))
				{
					MCH_voidPrintStart();
					MCH_u8TimeOut=0;
					MCH_u8EnteredName =0;
					Local_u8EnteredPasswordFlag=0;
				}
			break;
		}
		USART_u8RecieveByte(&Local_u8SendChar);
		}
	}
	return 0 ;
}

void App_voidTimeOut(void)
{
	MCH_u8TimeOut++;
	/*Motor.*/
	if (MCH_u8MotorStart==3)
	{
		/*MCH_u8MotorStart=0;*/
		DIO_u8SetPinValue(DIO_u8_PORTB,DIO_u8_PIN2,DIO_u8_LOW);
		DIO_u8SetPinValue(DIO_u8_PORTB,DIO_u8_PIN1,DIO_u8_LOW);
		MCH_u8MotorFlag=0;
	}
	else if((MCH_u8MotorDirection=0)&&(MCH_u8MotorFlag==1)&&(MCH_u8MotorStart<3))//Right
	{
		MCH_u8MotorStart++;
		/*Open Door*/
		DIO_u8SetPinValue(DIO_u8_PORTB,DIO_u8_PIN2,DIO_u8_HIGH);
		DIO_u8SetPinValue(DIO_u8_PORTB,DIO_u8_PIN1,DIO_u8_LOW);
	}
	else if ((MCH_u8MotorDirection=1)&&(MCH_u8MotorFlag==1)&&(MCH_u8MotorStart<3))//Left
	{
		MCH_u8MotorStart++;
		/*Close Door*/
		DIO_u8SetPinValue(DIO_u8_PORTB,DIO_u8_PIN2,DIO_u8_LOW);
		DIO_u8SetPinValue(DIO_u8_PORTB,DIO_u8_PIN1,DIO_u8_HIGH);
	}
}
