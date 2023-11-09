/*
 * ExitButton.c
 *
 *  Created on: Sep 6, 2023
 *      Author: Morad
 */
#include "STD_TYPES.h"
#include "DIO.h"
#include "GateControl.h"
#include "ExitButton.h"
#include "GarageSystem.h"
void ExitButtonInit(void)
{
	DIO_SetPinDirection(ExitButton_Port,ExitButton_PIN,DIO_INPUT);
}
u8 GetExitButtonStatus(void)
{
	if(DIO_GetInputPinValue(ExitButton_Port,ExitButton_PIN)==ExitButton_Pressed)
		return ExitButton_Pressed;
	else
		return ExitButton_NotPressed;
}
void ExitGarage(void)
{
	if(GetGateState()==ClosedGate)
		OpenGate();
	else //gate is opened
		CloseGate();
}
