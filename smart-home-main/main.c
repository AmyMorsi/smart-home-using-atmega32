/****************************************************/
/****************************************************/
/************** Creator: Mahmoud Moner **************/
/************** Date:4/9/2023 ***********************/
/************** Smart Home Project ******************/
/****************************************************/
/****************************************************/

/* LIB */
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include <util/delay.h>

/* MCAL */
#include "DIO.h"
#include "GIE_interface.h"
#include "ADC_interface.h"
#include "EXTI_interface.h"
#include "TIMERS_interface.h"
#include "USART.h"
#include <avr/eeprom.h>
#include "EEPROM.h"

/*HALL*/
#include "CLCD.h"
#include "DC_MOTOR.h"
#include "KPD.h"
#include "IR.h"

#define DOOR_u8_DELAY_LCD      200

void flame_buzzer(void);

static u8 Global_u8PinValue ;
static u8 Global_u8OpenWendwoFlag = 1 ;
static u8 Global_u8OpenWendwoFlag_1 = 1 ;


u8 static Global_u8DoorFlage = 0;

u8 static Global_u8DoorOpenFlag = 0 ;//at frist door is closed
int main()
{
	/*Init functions*/
	DIO_voidInit();

	CLCD_voidInit();

	ADC_voidInit();

	UART_Init();

	GIE_voidEnable();

	KPD_Init();

	/////////////////////////////////////////Door System//////////////////////////////////////////////////////
	u16 address=0x00;
	u16 address_read=0x00;
	//u16 data ;
	u8 counter=0;
	u8 pass[3];
	u8 key_pressed =KPD_NOT_PRESSED_KEY ;
	/////////////////////////////////////////Door System//////////////////////////////////////////////////////

	////////////////////////////////Flame sensor/////////////////////////////////////////////////////////////
	Global_u8PinValue = 1;
	EXTI_u8EXTISetCallBack(EXTI_1, &flame_buzzer);
	EXTI_u8EXTIEnable(EXTI_1, EXTI_CHANGING_STATE);
	////////////////////////////////Flame sensor/////////////////////////////////////////////////////////////

	/////////////////////////////// Start_Program ///////////////////////////////////////////////////////////
	CLCD_voidSendString("Wellcom to Smart");
	CLCD_u8GoToxy(2,2);
	CLCD_voidSendString("Home System");



	/*Tempt*/
	u16 Local_u16DigitalValueTempt, Local_u16AnalogValueTempt, Local_u16TempValue;
	/*LDR*/
	u16 Local_u16AnalogValue;
	u16 Global_u16DigitalValue ;
	/*USART*/
	static u8 Local_u8_Resive_char,Local_u8ChoseOp;

	while(1)
	{
		/*Chose Operation*/
		UART_SendChar('\r');
		USART_voidSendString("Enter your Operation: 1-Temperature Sensor , 2-Roof System , 3-Room System  4-Door System , 9-To Break from any operation");
		UART_SendChar('\r');
		/*Get USART Ooreation Char*/
		Local_u8ChoseOp = UART_GetChar();
		UART_SendChar(Local_u8ChoseOp);
		UART_SendChar('\r');

		/////////////////////////////////Window System/////////////////////////////////////////////////////////////
		///////////////////////////////////////////////////////////////////////////////////////////////////////////
		while( Local_u8ChoseOp == '1' && Local_u8ChoseOp != '9' )
		{
			/*GET Digital VALUE*/
			ADC_u8GetDigitalValueNonBlocking(ADC_u8_CHANNEL_3, &Local_u16DigitalValueTempt);

			/*GET ANALOG VALUE*/
			Local_u16AnalogValueTempt = (u16)((Local_u16DigitalValueTempt * 5000UL)/1024);

			/*GET TEMP VALUE*/
			Local_u16TempValue = (Local_u16AnalogValueTempt *1)/10;

			/*To break*/
			if( Local_u8_Resive_char == '9')
			{
				break;
			}

			USART_voidSendString("Windows System:  5-Closing if Cold 6-Opening if Cold 7-Opening if Hot 8-Closing if Hot ");
			UART_SendChar('\r');

			/*get Local_u8_Resive_char*/
			Local_u8_Resive_char = UART_GetChar();
			UART_SendChar(Local_u8_Resive_char);
			UART_SendChar('\r');
			if( Local_u16TempValue <= 30 && Local_u8_Resive_char != '9' ) // Close
			{
				USART_voidSendString("Its Cold!");
				UART_SendChar('\r');

				/* Already Close */
				if(Local_u8_Resive_char == '5'  && Global_u8OpenWendwoFlag == 0)
				{
					USART_voidSendString("Window is already Close!");
					UART_SendChar('\r');
				}

				/* Already Opend */
				if(Local_u8_Resive_char == '6'  && Global_u8OpenWendwoFlag == 1)
				{
					USART_voidSendString("Window is already Opend!");
					UART_SendChar('\r');
				}

				///////////
				if(Local_u8_Resive_char == '5'  && Global_u8OpenWendwoFlag == 1)
				{
					Global_u8OpenWendwoFlag = 0; /// Close flag
					USART_voidSendString("Closing Window...");
					UART_SendChar('\r');
					MOTOR_CCWMotion();
					_delay_ms(200);
					USART_voidSendString("Windows System:  5-Closing if Cold 6-Opening if Cold 7-Opening if Hot 8-Closing if Hot ");
					UART_SendChar('\r');
					while( Local_u16TempValue <= 30 && Local_u8_Resive_char == '5' )
					{
						////UART_SendChar('\r');
						MOTOR_StopMotion();

						Local_u8_Resive_char = UART_GetChar();//Get New Char
						UART_SendChar(Local_u8_Resive_char);
						UART_SendChar('\r');

						/* Already Close */
						if(Local_u8_Resive_char == '5'  && Global_u8OpenWendwoFlag == 0)
						{
							USART_voidSendString("Window is already Close!");
							UART_SendChar('\r');
							USART_voidSendString("Windows System:  5-Closing if Cold 6-Opening if Cold 7-Opening if Hot 8-Closing if Hot ");
													UART_SendChar('\r');
						}

					//	USART_voidSendString("Windows System:  5-Closing if Cold 6-Opening if Cold 7-Opening if Hot 8-Closing if Hot ");
					//	UART_SendChar('\r');

						if(Local_u8_Resive_char == '6')
						{
							/* Already Open */
							if(Local_u8_Resive_char == '6'  && Global_u8OpenWendwoFlag == 1)
							{
								USART_voidSendString("Window is already Open!");
								UART_SendChar('\r');
							}
							Global_u8OpenWendwoFlag = 1; /// open flag

						//	UART_SendChar(Local_u8_Resive_char);
							//UART_SendChar('\r');

							USART_voidSendString("Its Cold!");
							UART_SendChar('\r');

							USART_voidSendString("Opening Window...");
							UART_SendChar('\r');

							MOTOR_CWMotion();
							_delay_ms(200);
							MOTOR_StopMotion();

						//	USART_voidSendString("Windows System:  5-Closing if Cold 6-Opening if Cold 7-Opening if Hot 8-Closing if Hot ");
							//UART_SendChar('\r');
						}

					}
				}
				else if(Local_u8_Resive_char == '6'  && Global_u8OpenWendwoFlag == 0)
				{
					/* Already Open */
					if(Local_u8_Resive_char == '6'  && Global_u8OpenWendwoFlag == 1)
					{
						USART_voidSendString("Window is already Open!");
						UART_SendChar('\r');
					}

					Global_u8OpenWendwoFlag = 1; ///Open Flag
					/*Get New Char*/
					UART_SendChar(Local_u8_Resive_char);
					UART_SendChar('\r');

					USART_voidSendString("Opening Window...");
					UART_SendChar('\r');

					MOTOR_CWMotion();
					_delay_ms(200);
					MOTOR_StopMotion();

					USART_voidSendString("Windows System:  5-Closing if Cold 6-Opening if Cold 7-Opening if Hot 8-Closing if Hot ");
					UART_SendChar('\r');
				}

			}

			else if( Local_u16TempValue > 30) //Open
			{
				UART_SendChar('\r');
				USART_voidSendString("Its Hot!");
				UART_SendChar('\r');

				/* Already Closed */
				if(Local_u8_Resive_char == '8'  && Global_u8OpenWendwoFlag == 0)
				{
					USART_voidSendString("Window is already Closed!");
					UART_SendChar('\r');
				}

				/* Already Open */
				if(Local_u8_Resive_char == '7'  && Global_u8OpenWendwoFlag == 1)
				{
					USART_voidSendString("Window is already Open!");
					UART_SendChar('\r');
				}

				////////

				if(Global_u8OpenWendwoFlag_1 == 1 || Global_u8OpenWendwoFlag_1 == 0 )
				{
					if(Local_u8_Resive_char == '7' && Global_u8OpenWendwoFlag == 0 && Global_u8OpenWendwoFlag_1 == 1)
					{
						Global_u8OpenWendwoFlag = 1;// OPEN FLAG

						USART_voidSendString("Opening Window...");
						UART_SendChar('\r');

						MOTOR_CWMotion();
						_delay_ms(200);
						MOTOR_StopMotion();


						//USART_voidSendString("Windows System:  5-Closing if Cold 6-Opening if Cold 7-Opening if Hot 8-Closing if Hot ");
						UART_SendChar('\r');
						////////
						while( Local_u16TempValue > 30 && Local_u8_Resive_char == '7' && Global_u8OpenWendwoFlag_1 == 0)
						{
							/* gET nEW cHAR */
							UART_SendChar(Local_u8_Resive_char);
							UART_SendChar('\r');

							USART_voidSendString("Its Hot!");
							UART_SendChar('\r');

							/* Already Open */
							if(Local_u8_Resive_char == '7'  && Global_u8OpenWendwoFlag == 1 && Global_u8OpenWendwoFlag_1 ==0 )
							{
								USART_voidSendString("Window is already Open!");
								UART_SendChar('\r');
							}
							USART_voidSendString("Windows System:  5-Closing if Cold 6-Opening if Cold 7-Opening if Hot 8-Closing if Hot ");
							UART_SendChar('\r');

							MOTOR_StopMotion();

							Local_u8_Resive_char = UART_GetChar();/// new charrrrr

							//////////
							if(Local_u8_Resive_char == '8' && Local_u16TempValue > 30)
							{
								/* Already Closed */
								if(Local_u8_Resive_char == '8'  && Global_u8OpenWendwoFlag == 0)
								{
									USART_voidSendString("Window is already Closed!");
									UART_SendChar('\r');
								}

								Global_u8OpenWendwoFlag = 0;//close flag

								UART_SendChar(Local_u8_Resive_char);
								UART_SendChar('\r');

								USART_voidSendString("Closing Window...");
								UART_SendChar('\r');

								MOTOR_CCWMotion();
								_delay_ms(200);
								MOTOR_StopMotion();
							}

						}

					}
					else if(Local_u8_Resive_char == '8' && Global_u8OpenWendwoFlag == 1)
					{
						/* Already Closed */
						if(Local_u8_Resive_char == '8'  && Global_u8OpenWendwoFlag == 0)
						{
							USART_voidSendString("Window is already Closed!");
							UART_SendChar('\r');
						}

						Global_u8OpenWendwoFlag = 0;//// as we mintioned many times it an closed flag :]

						USART_voidSendString("Closing Window...");
						UART_SendChar('\r');

						MOTOR_CCWMotion();
						_delay_ms(200);
						MOTOR_StopMotion();
					}
					else if(Local_u8ChoseOp == '9')
					{
						break;
					}
					//Global_u8OpenWendwoFlag_1 = 0;
				}
			}

		}
		/////////////////////////////////Window System/////////////////////////////////////////////////////////////


		///////////////////////////////// Roof LEDS /////////////////////////////////////////////////////////////

		while( Local_u8ChoseOp == '2' && Local_u8ChoseOp != '9')
		{
			static u8 i = 0;
			if( i == 0 )
			{
				USART_voidSendString("Roof System");
				UART_SendChar('\r');
				USART_voidSendString("Press 2 to Countinue and 9 or any char to Exite");
				UART_SendChar('\r');
				i++;
			}

			//ADC_voidInit();
			ADC_u8GetDigitalValueNonBlocking(ADC_u8_CHANNEL_7, &Global_u16DigitalValue);

			/*GET ANALOG VALUE*/
			Local_u16AnalogValue = (u16)((Global_u16DigitalValue * 5000UL)/1024);

			if( Local_u16AnalogValue <= 3000  )
			{
				DIO_SetPinValue(DIO_PORTA , DIO_PIN5, DIO_HIGH);
				//DIO_u8SetPinValue(DIO_u8_PORTB , DIO_u8_PIN1, DIO_LOW);
			}
			else if(Local_u16AnalogValue > 3000 )
			{
				DIO_SetPinValue(DIO_PORTA , DIO_PIN5, DIO_LOW);
				//DIO_u8SetPinValue(DIO_u8_PORTB , DIO_u8_PIN1, DIO_HIGH)
			}

			if(UART_CheckSentChar())
			{
				Local_u8ChoseOp = UART_GetChar();
				UART_SendChar(Local_u8ChoseOp);
				UART_SendChar('\r');
			}


		}
		///////////////////////////////// Roof LEDS /////////////////////////////////////////////////////////////

		///////////////////////////////// Room LEDS /////////////////////////////////////////////////////////////

		while(Local_u8ChoseOp == '3' && Local_u8ChoseOp != '9')
		{
			static u8 i = 0;
			if( i == 0 )
			{
				USART_voidSendString("Room System");
				UART_SendChar('\r');
				USART_voidSendString("Press 3 to Countinue and 9 or any char to Exite");
				UART_SendChar('\r');
				i++;
			}

			static u8 Local_u8IRValue;
			IR_Init();
			Local_u8IRValue = IR_GetReading();
			if( Local_u8IRValue == IR_ActiveMode )
			{
				DIO_SetPinValue(DIO_PORTA, DIO_PIN6, DIO_HIGH );
			}
			else if( Local_u8IRValue == IR_NonActiveMode )
			{
				DIO_SetPinValue(DIO_PORTA, DIO_PIN6, DIO_LOW );
			}

			if(UART_CheckSentChar())
			{
				Local_u8ChoseOp = UART_GetChar();
				UART_SendChar(Local_u8ChoseOp);
				UART_SendChar('\r');
			}


		}
		///////////////////////////////// Room LEDS /////////////////////////////////////////////////////////////

		///////////////////////////////// Door System /////////////////////////////////////////////////////////////
		while(Local_u8ChoseOp == '4' && Local_u8ChoseOp != '9' && Global_u8DoorOpenFlag == 0)
		{
			CLCD_voidLCDClear();
			static u8 i = 0;
			if( i == 0 )
			{
				USART_voidSendString("Door System");
				UART_SendChar('\r');
				USART_voidSendString("Press 4 to Countinue and 9 or any char to Exite");
				UART_SendChar('\r');
				i++;
			}
			/********************************* setting Admin password **********************************************/

			if ( EEPROM_read_byte(address)==0xff)
			{
				CLCD_u8GoToxy(1,3);
				CLCD_voidSendString("login  for");
				CLCD_u8GoToxy(2,3);
				CLCD_voidSendString("first time");
				_delay_ms(DOOR_u8_DELAY_LCD);
				CLCD_voidLCDClear();

				CLCD_voidSendString("Set admin pass");

				CLCD_u8GoToxy(2,0);
				CLCD_voidSendString("Admin pass:");

				for (u8 i=0 ;i<4;i++)
				{

					key_pressed = KPD_NOT_PRESSED_KEY ;//return the variable that holds the pressed key from keypad to its initial value
					while (key_pressed == KPD_NOT_PRESSED_KEY )//repeat till the user press any key
					{
						key_pressed = KPD_GetPressedKey();//if the user pressed any button in keypad save the value in key_pressed


					}

					pass[i]=key_pressed;//add the entered character to the pass array
					CLCD_u8GoToxy(2,(11+i));
					CLCD_voidSendData(key_pressed);
					EEPROM_write_byte(address,pass[i]);
					address++;



				}

				CLCD_voidLCDClear();
				CLCD_u8GoToxy(1,3);
				CLCD_voidSendString("Pass Saved");
				_delay_ms(DOOR_u8_DELAY_LCD);

			}





			/********************************* Select Mode **********************************************/
			CLCD_voidLCDClear();
			CLCD_voidSendString("Select Mode :");

			CLCD_u8GoToxy(2,0);
			CLCD_voidSendString("0:Admin 1:Guest");


			key_pressed = KPD_NOT_PRESSED_KEY ;//return the variable that holds the pressed key from keypad to its initial value
			while ( key_pressed== KPD_NOT_PRESSED_KEY )//repeat till the user press any key
			{
				key_pressed = KPD_GetPressedKey();//if the user pressed any button in keypad save the value in key_pressed


			}

			if ( key_pressed == '0'  )
			{
				CLCD_voidLCDClear();
				CLCD_voidSendString("Admin Mode");

				CLCD_u8GoToxy(2,0);
				CLCD_voidSendString("Enter Pass:");
			}else if (key_pressed == '1' )
			{
				CLCD_voidLCDClear();
				CLCD_voidSendString("Guest Mode");

				CLCD_u8GoToxy(2,0);
				CLCD_voidSendString("Enter Pass:");
			}



			/********************************* Enter password **********************************************/
			//if(Global_u8DoorOpenFlag == 0)
			//{
			for (u8 i=0 ;i<4;i++)
			{

				key_pressed = KPD_NOT_PRESSED_KEY ;//return the variable that holds the pressed key from keypad to its initial value
				while (key_pressed == KPD_NOT_PRESSED_KEY )//repeat till the user press any key
				{
					key_pressed = KPD_GetPressedKey();//if the user pressed any button in keypad save the value in key_pressed


				}

				pass[i]=key_pressed;//add the entered character to the pass array
				CLCD_u8GoToxy(2,(11+i));
                CLCD_voidSendData(key_pressed);
				if ( EEPROM_read_byte(address_read)== pass[i]   )
				{
					counter++;
				}
				address_read++;
			}



			/********************************* Check password **********************************************/

			CLCD_voidLCDClear();

			if(counter == 4) // Correct Pass
			{
				CLCD_u8GoToxy(1,2);

				CLCD_voidSendString("correct Pass");
				Global_u8DoorFlage = 1;
				//DIO_SetPinValue(DIO_PORTD,DIO_PIN1,DIO_HIGH);
				_delay_ms(DOOR_u8_DELAY_LCD);
				//	DIO_SetPinValue(DIO_PORTD,DIO_PIN1,DIO_LOW);

				CLCD_voidLCDClear();


			}
			else if(counter != 4) // wrong pass & Check again pass for thress times
			{
				for (u8 k=0;k<3;k++)
				{
					counter=0;
					address_read=0x00;
					CLCD_u8GoToxy(1,2);
					CLCD_voidSendString("wrong Pass");
					CLCD_u8GoToxy(2,0);

					CLCD_voidSendString("Please Try Again");
					//	DIO_SetPinValue(DIO_PORTD,DIO_PIN0,DIO_HIGH);
					_delay_ms(DOOR_u8_DELAY_LCD);
					CLCD_voidLCDClear();


					for (u8 j=0 ;j<4;j++)
					{

						key_pressed = KPD_NOT_PRESSED_KEY ;//return the variable that holds the pressed key from keypad to its initial value
						while (key_pressed == KPD_NOT_PRESSED_KEY )//repeat till the user press any key
						{
							key_pressed = KPD_GetPressedKey();//if the user pressed any button in keypad save the value in key_pressed


						}

						pass[j]=key_pressed;//add the entered character to the pass array
						if ( EEPROM_read_byte(address_read)== pass[j]   )
						{
							counter++;
						}
						address_read++;
					}

					if(counter == 4)
					{
						CLCD_u8GoToxy(1,2);


						CLCD_voidSendString("correct Pass");
						Global_u8DoorFlage = 1;

						//	DIO_SetPinValue(DIO_PORTD,DIO_PIN0,DIO_LOW);
						//DIO_SetPinValue(DIO_PORTD,DIO_PIN1,DIO_HIGH);
						_delay_ms(DOOR_u8_DELAY_LCD);
						CLCD_voidLCDClear();
						//	DIO_SetPinValue(DIO_PORTD,DIO_PIN1,DIO_LOW);


						break;


					}


				}

			}


			if(Global_u8DoorFlage == 1)
			{
				/* Opening Door */
				MOTOR2_CWMotion();
				CLCD_voidSendString("Opening Door..");
				_delay_ms(DOOR_u8_DELAY_LCD);
				MOTOR2_StopMotion();
				CLCD_voidLCDClear();

				Global_u8DoorOpenFlag = 1; /// Door is Open

				/* Closing Door */
				_delay_ms(DOOR_u8_DELAY_LCD);
				MOTOR2_CCWMotion();
				CLCD_voidSendString("Closing Door..");
				_delay_ms(DOOR_u8_DELAY_LCD);
				MOTOR2_StopMotion();
				CLCD_voidLCDClear();

				Global_u8DoorOpenFlag = 0; /// Door is CLOSE
			}
			while(!UART_CheckSentChar());
			//USART_voidSendString("Sorry Enter another char to break");
			Local_u8ChoseOp = UART_GetChar();
			UART_SendChar(Local_u8ChoseOp);
			UART_SendChar('\r');

		}
		///////////////////////////////// Door System /////////////////////////////////////////////////////////////

	}
	return 0;
}

void flame_buzzer(void)
{
	if(Global_u8PinValue == 1)
	{
		DIO_SetPinValue(DIO_PORTD, DIO_PIN2, DIO_HIGH);

		CLCD_voidLCDClear();
		CLCD_voidSendString("Warning..");
		CLCD_u8GoToxy(CLCD_u8_LINE2,0);
		CLCD_voidSendString("There is a fire");

		USART_voidSendString("Their is a fire");
		UART_SendChar('\r');

		if(Global_u8OpenWendwoFlag == 0 && Global_u8DoorOpenFlag == 0 )
		{
			USART_voidSendString("All Windows are Opening Now");
			UART_SendChar('\r');

			USART_voidSendString("All Door are Opening Now");
			UART_SendChar('\r');

			/*Open Window*/
			MOTOR_CWMotion();

			/*Open Door*/
			MOTOR2_CWMotion();

			_delay_ms(200);
			while(1)
			{
				/*stop Window*/
				MOTOR_StopMotion();

				/*stop door*/
				MOTOR2_StopMotion();
			}
		}

	}
}
