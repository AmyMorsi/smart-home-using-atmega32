/*
 * ExitButton.h
 *
 *  Created on: Sep 6, 2023
 *      Author: Morad
 */

#ifndef EXITBUTTON_H_
#define EXITBUTTON_H_

#define ExitButton_Port DIO_PORTD
#define ExitButton_PIN DIO_PIN2

#define ExitButton_Pressed 0
#define ExitButton_NotPressed 0xFF
void ExitButtonInit(void);
u8 GetExitButtonStatus(void);
void ExitGarage(void);
#endif /* EXITBUTTON_H_ */
