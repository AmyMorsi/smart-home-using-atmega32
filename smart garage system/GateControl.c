#include "STD_TYPES.h"
#include "STEPPER.h"
#include "GarageSystem.h"
#include "GateControl.h"
#include "USART.h"
#include "IRsensor.h"
#include "CLCD.h"
#include "DIO.h"
#include "util/delay.h"
static u8 GateState = ClosedGate;
u8 period = 10;

void SetGateState(u8 U8GateStateCopy)
{
	if(U8GateStateCopy==ClosedGate)
		GateState = ClosedGate;
	else if (U8GateStateCopy==OpenedGate)
		GateState = OpenedGate;
}
u8 GetGateState(void)
{
	return GateState;
}

void OpenGate(void){
	if(GetGateState() == ClosedGate)
	{
		USART_Send_String("Door Is Opening\r");
		STEPPER_90_Left(period);
		LCD_Entered();
		SetGateState(OpenedGate);
		SetWaitingTime(DefaultWaitingTime);
		SetWaitingTimeState(Waiting);
	}
}

void CloseGate(void){
	USART_Send_String("in close\r");

	if(GetGateState() == OpenedGate)
	{
		while(IR_GetReading()==IR_ActiveMode)
		{
			LCD_Alert();
		}
		USART_Send_String("Door Is closing\r");
		STEPPER_Stop();
		STEPPER_90_Right(period);
		LCD_Welcome();
		SetGateState(ClosedGate);
		SetPasswordState(PasswordNotMatches);
		SetWaitingTime(DefaultWaitingTime);
		SetWaitingTimeState(DefaultWaitingState);
	}
}
