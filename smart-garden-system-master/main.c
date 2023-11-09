/*
 * main.c
 *
 *  Created on: Sep 2, 2023
 *      Author: Morad
 */

#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "DIO.h"
#include "GardenSystem.h"
#include <util/delay.h>

void main(void)
{
	//initiate Garden system
	Garden_Setup();
	while(1)
	{
		Check_Soil_Sensor_Value(Get_Soil_Sensor_Value());
	}
}
