/*
 * GarageSystem.c
 *
 *  Created on: Sep 5, 2023
 *      Author: Morad
 */
#include "STD_TYPES.h"
#include "DIO.h"
#include "CLCD.h"
#include "GarageSystem.h"

static u16 WaitingTime = DefaultWaitingTime;
static u8 WaitingTimeState = Waiting;
static u8 PasswordState = PasswordNotMatches;
static u8 Password[4]={'0','0','0','0'};
void StartSystem(void)
{
	CLCD_void_Init();
	LCD_Welcome();
}
void LCD_Welcome(void)
{
	CLCD_void_SendCommand(CLCD_INIT_DisplayClear);
	CLCD_VOID_SetCursorPosition(0,4);
	CLCD_void_SendStringData("Welcome!");
	CLCD_VOID_SetCursorPosition(1,0);
	CLCD_void_SendStringData("Enter Password :");
}
void LCD_Entered(void)
{
	CLCD_void_SendCommand(CLCD_INIT_DisplayClear);
	CLCD_void_SendStringData("Hello Mr.ENG ^-^");
	CLCD_VOID_SetCursorPosition(CLCD_SecondLine,0);
	CLCD_void_SendStringData("Door Is Opening");
}
void LCD_CLosingCounter(u8 Counter)
{
	//CLCD_void_SendCommand(CLCD_INIT_DisplayClear);
	//CLCD_void_SendStringData("Closing after:");
	CLCD_VOID_SetCursorPosition(1,6);
	CLCD_void_SendData(Counter);
}
void LCD_Alert(void)
{
	CLCD_void_SendCommand(CLCD_INIT_DisplayClear);
	CLCD_void_SendStringData("Couldn't close");
	CLCD_VOID_SetCursorPosition(1,0);
	CLCD_void_SendStringData("Move your Car");

}
void LCD_WrongPassword(void)
{
	CLCD_void_SendCommand(CLCD_INIT_DisplayClear);
	CLCD_void_SendStringData("Invalid Password");
	CLCD_VOID_SetCursorPosition(CLCD_SecondLine,0);
	CLCD_void_SendStringData("Try Again : ");
}
void SetPassword(u8* PtrPassword)
{
	u8 i;
	for(i=0;i<4;i++)
		Password[i]=*(PtrPassword+1);
}
u8* GetPassword(void)
{
	return Password;
}
void SetPasswordState(u8 U8PasswordState)
{
	if(U8PasswordState==PasswordMatches)
		PasswordState=PasswordMatches;
	else if(U8PasswordState==PasswordNotMatches)
		PasswordState=PasswordNotMatches;
}
u8 GetPasswordState(void)
{
	return PasswordState;
}
void SetWaitingTime(u16 U8NewWaitingTime)
{
	WaitingTime=U8NewWaitingTime;
}
u16 GetWaitingTime(void)
{
	return WaitingTime;
}
void SetWaitingTimeState(u8 U8NewState)
{
	if(U8NewState==Waiting)
		WaitingTimeState=Waiting;
	else if(U8NewState==TimeOut)
		WaitingTimeState=TimeOut;

}
u8 GetWaitingTimeState(void)
{
	return WaitingTimeState;
}

u8 CheckPassword(u8* PtrPassword)
{
	u8 i,Result= PasswordMatches;
	for(i=0;i<4;i++)
	{
		if(Password[i]!=*(PtrPassword+i))
		{
			Result= PasswordNotMatches;
			break;
		}
	}
	return Result;
}
