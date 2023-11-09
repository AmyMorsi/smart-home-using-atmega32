/*
 * ADC.c
 *
 *  Created on: Aug 16, 2023
 *      Author: Mariam
 */
#include "ADC.h"

#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "DIO.h"
#include "avr/io.h"


void ADC_Init (void)
{
	// ADC Enable
	SET_BIT(ADCSRA , ADCSRA_ADEN);

	// Prescaler Configuration as 128
	SET_BIT(ADCSRA , ADCSRA_ADPS2);
	SET_BIT(ADCSRA , ADCSRA_ADPS1);
	SET_BIT(ADCSRA , ADCSRA_ADPS0);


	// Referance Voltage as AVCC with external capacitor
	CLR_BIT (ADMUX  , ADMUX_REFS1);
	SET_BIT (ADMUX  , ADMUX_REFS0);

	/*ADC Data Rgith Adjustment 10 bits
	CLR_BIT(ADMUX , ADMUX_ADLAR);*/

	/*Activate Left adjustment result 8 bits */
	SET_BIT(ADMUX , ADMUX_ADLAR);

}

u8 ADC_Read (u8 channel)
{
	//step 1 : Clear MUX bits in ADMUX
	ADMUX   &= 0b11100000;


	//Step 2 : Set the required  ADC Channel Selection into the MUX bits
	ADMUX   |=channel;


	// Step 3 : Start Single Converstion
	SET_BIT(ADCSRA , ADCSRA_ADSC );


	// Step 4 :  Polling (busy wait ) until the conversion complete flag is set
	while((GET_BIT(ADCSRA , ADCSRA_ADIF)) == 0);


	// Step 5 :  Clear Conversion Complete Flag
	SET_BIT(ADCSRA,ADCSRA_ADIF);

	// Step 7 :   return value in ADCH (Left adjustment result 8 bits)

	return ADCH;
}
