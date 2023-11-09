/*
 * GardenSystem.c
 *
 *  Created on: Sep 6, 2023
 *      Author: Morad
 */


#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "DIO.h"
#include "DC_MOTOR.h"
#include "GardenSystem.h"
#include "ADC.h"

void Garden_Setup(void){
	MOTOR_Init();
	ADC_Init();

	DIO_SetPinDirection(DIO_PORTA,DIO_PIN3,DIO_INPUT);
	DIO_SetPinDirection(DIO_PORTD,DIO_PIN5,DIO_OUTPUT); // red led
	DIO_SetPinDirection(DIO_PORTD,DIO_PIN6,DIO_OUTPUT); // green led

	DIO_SetPinValue(DIO_PORTD,DIO_PIN5,DIO_LOW);
	DIO_SetPinValue(DIO_PORTD,DIO_PIN6,DIO_LOW);
}

u8 Get_Soil_Sensor_Value(void){
	u8 soil_sensor;
	soil_sensor = ADC_Read(Soil_Sensor_pin);
	return soil_sensor;
}

void Check_Soil_Sensor_Value(u8 CopySoil_Sensor_Value){
	if(CopySoil_Sensor_Value > 10) // soil is dry
	{
		MOTOR_CWMotion();
		DIO_SetPinValue(DIO_PORTD,DIO_PIN5,DIO_HIGH);
		DIO_SetPinValue(DIO_PORTD,DIO_PIN6,DIO_LOW);
	}
	else
	{
		MOTOR_StopMotion();
		DIO_SetPinValue(DIO_PORTD,DIO_PIN5,DIO_LOW);
		DIO_SetPinValue(DIO_PORTD,DIO_PIN6,DIO_HIGH);
	}
}
