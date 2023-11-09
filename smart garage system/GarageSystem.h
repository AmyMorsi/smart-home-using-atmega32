/*
 * GarageSystem.h
 *
 *  Created on: Sep 5, 2023
 *      Author: Morad
 */

#ifndef GARAGESYSTEM_H_
#define GARAGESYSTEM_H_


//-----------------------------------------------------------------
//----------------------->    Macro Objects  <---------------------
//-----------------------------------------------------------------
#define TimeOut 0xff
#define Waiting 0x00
#define DefaultWaitingTime 1500//ms
#define DefaultWaitingState Waiting
#define PasswordMatches 1
#define PasswordNotMatches 0
#define PasswordSize 4
//-----------------------------------------------------------------


//------------------------------------------------------------------
//----------------------->Functions Prototypes<---------------------
//------------------------------------------------------------------
void StartSystem(void);
void LCD_Welcome(void);
void LCD_Entered(void);
void LCD_CLosingCounter(u8 Counter);
void LCD_Alert(void);
void LCD_WrongPassword(void);
void SetPasswordState(u8 U8PasswordState);
u8 GetPasswordState(void);
void SetPassword(u8* U8PtrPassword);
u8* GetPassword(void);
void SetWaitingTime(u16 U8NewWaitingTime);
u16 GetWaitingTime(void);
void SetWaitingTimeState(u8 U8NewState);
u8 GetWaitingTimeState(void);
u8 CheckPassword(u8* PtrPassword);
void OpenGate(void);
void CloseGate(void);
//------------------------------------------------------------------


#endif /* GARAGESYSTEM_H_ */
