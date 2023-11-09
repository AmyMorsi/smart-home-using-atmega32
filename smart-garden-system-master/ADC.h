/*
 * ACD.h
 *
 *  Created on: Aug 16, 2023
 *      Author: Mariam
 */

#ifndef ADC_H_
#define ADC_H_

#include "STD_TYPES.h"

// ADMUX   :  ADC multiplexer selection register
#define ADMUX_REFS1          7                         //Reference selection bitl
#define ADMUX_REFS0          6                         //Reference selection bit0
#define ADMUX_ADLAR          5                         //ADC left adjust result
#define ADMUX_MUX4           4
#define ADMUX_MUX3           3
#define ADMUX_MUX2           2
#define ADMUX_MUX1           1
#define ADMUX_MUX0           0

//ADCSRA   :  ADC control and status register A
#define ADCSRA_ADEN          7                        //ADC enable
#define ADCSRA_ADSC          6                        //Start conversion
#define ADCSRA_ADATE         5                        //Auto trigger enable
#define ADCSRA_ADIF          4                        //Interrupt flag
#define ADCSRA_ADIE          3                        //Interrupt enable
#define ADCSRA_ADPS2         2                        //Prescaler bit2
#define ADCSRA_ADPS1         1                        //Prescaler bitl
#define ADCSRA_ADPS0         0                        //Prescaler bit0

// ADCH_Reg 	 ADC High Register
// ADCL_Reg      ADC Low Register

// 8  OPTIONS :
#define ADC_PINS_PORT                     DIO_PORTA

#define ADC0_PIN                          DIO_PIN0
#define ADC1_PIN                          DIO_PIN1
#define ADC2_PIN                          DIO_PIN2
#define ADC3_PIN                          DIO_PIN3
#define ADC4_PIN                          DIO_PIN4
#define ADC5_PIN                          DIO_PIN5
#define ADC6_PIN                          DIO_PIN6
#define ADC7_PIN                          DIO_PIN7



//Configure table 84 as macro here to bus it as channel in u8 Copy_u8Channel
#define SINGLE_ENDED_ADC0                  0
#define SINGLE_ENDED_ADC1                  1
#define SINGLE_ENDED_ADC2                  2
//and so on...
#define DIFF_ENDED_ADC0_POS_ADC0_NEG_G10   0b01000
//and so on...






void ADC_Init(void);   // ADC Initialization And Enable

u8 ADC_Read(u8 channel);  // Read From The ADC Channel



#endif /* ADC_H_ */
