/*
 * main.c
 *
 *  Created on: Sep 2, 2023
 *      Author: Morad
 */

#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "DIO.h"
#include "CLCD.h"
#include "IRsensor.h"
#include "ExitButton.h"
#include "GateControl.h"
#include "GarageSystem.h"
#include "USART.h"
#include "TIMER.h"
#include "EXTI.h"
#include "GIE.h"
#include <stdlib.h>
#include <util/delay.h>


void Timer0ISR(void);
void EXternalInit0ISR(void);
void EnteringPassword(void);
void main(void)
{
	//initiate LCD
	CLCD_void_Init();
	//initiate Exit button
	ExitButtonInit();
	//initiate IR Sensor
	IR_Init();
	// print welcome
	LCD_Welcome();
	//Enable general interrupt
	GIE_Enable();
	//initiate USART
	USART_Init();
	//timer1 Initialization on mode-> CTC & prescaler->64 & OCR->125
	TIMER0_Init();
	//calling back the interrupt
	TIMER0_u8SetCallBack(Timer0ISR);
	//__vector_10();
	//External interrupt
	EXTI_void_Int0Init();
	EXTI_u8Int0SetCallBack(&EXternalInit0ISR);
	//__vector_1();
	while(1)
	{
		if(GetGateState()==ClosedGate)
		{
			USART_Send_String("\rEnter Your Password :\r");
			EnteringPassword();
			if(GetPasswordState()==PasswordMatches)
				OpenGate();
		}
		else if (GetWaitingTimeState()==TimeOut)
			CloseGate();
	}
}
void Timer0ISR(void)
{
	static u16 TempWaitingTime;
    if (GetGateState() == OpenedGate && GetWaitingTimeState() == Waiting)
    {
    	TempWaitingTime=GetWaitingTime();
        if (TempWaitingTime > 0)
        {
        	SetWaitingTime(TempWaitingTime - 1);
        	if (TempWaitingTime==DefaultWaitingTime)
        	{
        		CLCD_void_SendCommand(CLCD_INIT_DisplayClear);
        		CLCD_void_SendStringData("Closing after:");
        	}
        	if(TempWaitingTime%500==0)
            	LCD_CLosingCounter(((u8)(TempWaitingTime/500))+48);//numbers in ASCII is between 48 & 57 --> 0 : 9
        }
        else
        {
            // Waiting time has expired, but gate remains open
            SetWaitingTimeState(TimeOut);
        }
    }
}

void EXternalInit0ISR(void)
{
	ExitGarage();
}
void EnteringPassword(void)
{
	if(GetPasswordState()==PasswordNotMatches)
	{
		u8* EnteredPassword;
		EnteredPassword = USART_Receive_String();

		if (CheckPassword(EnteredPassword) == PasswordNotMatches)
		{
			SetPasswordState(PasswordNotMatches);
			LCD_WrongPassword();
		}
		else
		{
			SetPasswordState(PasswordMatches);
			LCD_Entered();
		}
		free(EnteredPassword); // Free the dynamically allocated memory

	}
}
