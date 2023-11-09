/*
 * DC_MOTOR.c
 *
 * Created: 8/16/2023 5:21:43 PM
 * Author : ahmed
 */

#include "DC_MOTOR.h"

void MOTOR_Init(void)
{
	DIO_SetPinDirection(MOTOR_PORT, MOTOR_ENA, DIO_OUTPUT);
	DIO_SetPinDirection(MOTOR_PORT, MOTOR_IN1, DIO_OUTPUT);
	DIO_SetPinDirection(MOTOR_PORT, MOTOR_IN2, DIO_OUTPUT);

	DIO_SetPinValue(MOTOR_PORT, MOTOR_ENA, DIO_HIGH);
}

void MOTOR_CWMotion(void)
{
	DIO_SetPinValue(MOTOR_PORT, MOTOR_IN2, DIO_LOW);
	DIO_SetPinValue(MOTOR_PORT, MOTOR_IN1, DIO_HIGH);
}

void MOTOR_CCWMotion(void)
{
	DIO_SetPinValue(MOTOR_PORT, MOTOR_IN1, DIO_LOW);
	DIO_SetPinValue(MOTOR_PORT, MOTOR_IN2, DIO_HIGH);
}

void MOTOR_StopMotion(void)
{
	DIO_SetPinValue(MOTOR_PORT, MOTOR_IN1, DIO_LOW);
	DIO_SetPinValue(MOTOR_PORT, MOTOR_IN2, DIO_LOW);
}
