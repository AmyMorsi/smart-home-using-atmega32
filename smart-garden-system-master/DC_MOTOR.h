/*
 * DC_MOTOR.h
 *
 * Created: 8/16/2023 5:22:11 PM
 *  Author: ahmed
 */
#include "STD_TYPES.h"
#include "DIO.h"

#ifndef DC_MOTOR_H_
#define DC_MOTOR_H_

// configuration
#define MOTOR_PORT	DIO_PORTA
#define MOTOR_ENA	DIO_PIN5
#define MOTOR_IN1	DIO_PIN6
#define MOTOR_IN2	DIO_PIN7


void MOTOR_Init(void);
void MOTOR_CWMotion(void);
void MOTOR_CCWMotion(void);
void MOTOR_StopMotion(void);


#endif /* DC_MOTOR_H_ */
