/*
 * IR.c
 *
 *  Created on: Sep 5, 2023
 *      Author: Morad
 */
#include "STD_TYPES.h"
#include "DIO.h"
#include "IRsensor.h"

void IR_Init(void)
{
	DIO_SetPinDirection(IR_PORT,IR_PIN,DIO_INPUT);
}
u8 IR_GetReading(void)
{
	if (DIO_GetInputPinValue(IR_PORT,IR_PIN)==IR_NonActiveMode)
			return IR_NonActiveMode;
	else
		return IR_ActiveMode;
}
