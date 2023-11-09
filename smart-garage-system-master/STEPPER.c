#include "STD_TYPES.h"
#include "DIO.h"
#include "STEPPER.h"

#include <util/delay.h>

void STEPPER_INIT(void)
{
	DIO_SetPinDirection(STEPPER_PORT, Coil1Pin,DIO_OUTPUT);
	DIO_SetPinDirection(STEPPER_PORT, Coil2Pin,DIO_OUTPUT);
	DIO_SetPinDirection(STEPPER_PORT, Coil3Pin,DIO_OUTPUT);
	DIO_SetPinDirection(STEPPER_PORT, Coil4Pin,DIO_OUTPUT);

}

void STEPPER_45_Left(u8 period) {

  DIO_SetPortValue(STEPPER_PORT, Coil4); // activate coil 4
  _delay_ms(period);
  DIO_SetPortValue(STEPPER_PORT, Coil3); // activate coil 3
  _delay_ms(period);
  DIO_SetPortValue(STEPPER_PORT, Coil2); // activate coil 2
  _delay_ms(period);
  DIO_SetPortValue(STEPPER_PORT, Coil1); // activate coil 1
  _delay_ms(period);
}

void STEPPER_45_Right(u8 period) {

  DIO_SetPortValue(STEPPER_PORT, Coil1); // activate coil 1
  _delay_ms(period);
  DIO_SetPortValue(STEPPER_PORT, Coil2); // activate coil 2
  _delay_ms(period);
  DIO_SetPortValue(STEPPER_PORT, Coil3); // activate coil 3
  _delay_ms(period);
  DIO_SetPortValue(STEPPER_PORT, Coil4); // activate coil 4
  _delay_ms(period);
}
void STEPPER_90_Left(u8 period) {

  DIO_SetPortValue(STEPPER_PORT, Coil1+Coil4); // activate coil 1 and coil 4
  _delay_ms(period);
  DIO_SetPortValue(STEPPER_PORT, Coil4+Coil3); // activate coil 4 and coil 3
  _delay_ms(period);
  DIO_SetPortValue(STEPPER_PORT, Coil3+Coil2); // activate coil 3 and coil 2
  _delay_ms(period);
  DIO_SetPortValue(STEPPER_PORT, Coil2+Coil1); // activate coil 2 and coil 1
  _delay_ms(period);
}

void STEPPER_90_Right(u8 period) {

  DIO_SetPortValue(STEPPER_PORT, Coil1+Coil2); // activate coil 1 and coil 2
  _delay_ms(period);
  DIO_SetPortValue(STEPPER_PORT, Coil2+Coil3); // activate coil 2 and coil 3
  _delay_ms(period);
  DIO_SetPortValue(STEPPER_PORT, Coil3+Coil4); // activate coil 3 and coil 4
  _delay_ms(period);
  DIO_SetPortValue(STEPPER_PORT, Coil4+Coil1); // activate coil 4 and coil 1
  _delay_ms(period);
}

void STEPPER_Stop(void) {

  DIO_SetPortValue(STEPPER_PORT, CoilsOff); // trun off all the coils
}
