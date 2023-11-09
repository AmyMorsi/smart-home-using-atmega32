#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "DIO.h"
//#include "GIE.h"
#include "avr/io.h"
#include "stdio.h"
#include "TIMER.h"
void (*TIMER0_pvCallBackFunc)(void) =NULL;


void TIMER0_Init(void){
	// wave generation : CTC mode
	CLR_BIT(TCCR0 , TCCR0_WGM00);
	SET_BIT(TCCR0 , TCCR0_WGM01);

	//Enable PIE of Compare Match interrupt
	SET_BIT(TIMSK , TIMSK_OCIE0);

	//Set compare match value
	OCR0=125;

	// prescaler 64
	SET_BIT(TCCR0 , TCCR0_CS00);
	SET_BIT(TCCR0 , TCCR0_CS01);
	CLR_BIT(TCCR0 , TCCR0_CS02);

}

u8   TIMER0_u8SetCallBack(void ( *Copy_pvCallBackFunc)(void)){

	u8 u8ErrorStstus_Local = OK;
	if(Copy_pvCallBackFunc != NULL){
		TIMER0_pvCallBackFunc = Copy_pvCallBackFunc;
	}
	else{
		u8ErrorStstus_Local = NOK;
	}
	return u8ErrorStstus_Local;
}


/* Actual ISR */
void __vector_10 (void) __attribute__((signal));
void __vector_10 (void){
	if(TIMER0_pvCallBackFunc != NULL){
		TIMER0_pvCallBackFunc();
	}
}








