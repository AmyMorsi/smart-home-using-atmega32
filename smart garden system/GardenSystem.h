/*
 * GardenSystem.h
 *
 *  Created on: Sep 6, 2023
 *      Author: Morad
 */


#ifndef GARDENSYSTEM_H_
#define GARDENSYSTEM_H_

#define Red_LED_port      DIO_PORTD
#define Red_LED_pin       DIO_PIN5

#define Green_LED_port    DIO_PORTD
#define Green_LED_pin     DIO_PIN6

#define Soil_Sensor_port  DIO_PORTA
#define Soil_Sensor_pin   DIO_PIN3

void Garden_Setup(void);
u8 Get_Soil_Sensor_Value(void);
void Check_Soil_Sensor_Value(u8 CopySoil_Sensor_Value);

#endif /* GARDENSYSTEM_H_ */
