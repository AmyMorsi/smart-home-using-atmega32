#ifndef STEPPER_H_
#define STEPPER_H_

#include "STD_TYPES.h"
#include "DIO.h"

 #define Coil1Pin DIO_PIN0
 #define Coil2Pin DIO_PIN1
 #define Coil3Pin DIO_PIN2
 #define Coil4Pin DIO_PIN3

#define STEPPER_PORT  DIO_PORTB

 #define Coil1 0x01
 #define Coil2 0x02
 #define Coil3 0x04
 #define Coil4 0x08
#define CoilsOff 0x00
void STEPPER_INIT(void);
void STEPPER_45_Right(u8 period);
void STEPPER_45_Left(u8 period);
void STEPPER_90_Right(u8 period);
void STEPPER_90_Left(u8 period);
void STEPPER_Stop(void);


#endif /* STEPPER_H_ */

