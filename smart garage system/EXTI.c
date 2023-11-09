#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "avr/io.h"
#include "EXTI.h"

/* Global pointer to function to hold INT0 ISR address */
void (*EXTI_pvInt0func)(void)=NULL;

void    EXTI_void_Int0Init(void){


	//Check Sense control :
#if   EXTI_SENSE_CONTROL == EXTI_LOW_LEVEL
	CLR_BIT(MCUCR , MCUCR_ISC00 );
	CLR_BIT(MCUCR , MCUCR_ISC01 );

#elif EXTI_SENSE_CONTROL == EXTI_ON_CHANGE
	SET_BIT(MCUCR , MCUCR_ISC00 );
	CLR_BIT(MCUCR , MCUCR_ISC01 );

#elif EXTI_SENSE_CONTROL == EXTI_FALLING_EDGE
	CLR_BIT(MCUCR , MCUCR_ISC00 );
	SET_BIT(MCUCR , MCUCR_ISC01 );

#elif EXTI_SENSE_CONTROL == EXTI_RISING_EDGE
	SET_BIT(MCUCR , MCUCR_ISC00 );
	SET_BIT(MCUCR , MCUCR_ISC01 );
#else
#error "Warning Sense control configration option"
#endif

	/*Check Peripheral intrrupt enable*/
#if INT0_INITIAL_STATE == EXTI_ENABLED
	SET_BIT(GICR , GICR_INT0 );

#elif INT0_INITIAL_STATE == EXTI_DISABLED
	CLR_BIT(GICR , GICR_INT0 );
#else
#error "Wrong Int0_INITIAL_STATE Configuration option "
#endif
}



u8 EXTI_u8Int0SetSenseControl(u8 u8SenseCopy ){
	u8 u8ErrorState_Copy = OK;
	switch( u8SenseCopy )
	{
	case EXTI_LOW_LEVEL :
		CLR_BIT(MCUCR , MCUCR_ISC00);
		CLR_BIT(MCUCR , MCUCR_ISC01);
		break;
	case EXTI_ON_CHANGE :
		SET_BIT(MCUCR , MCUCR_ISC00);
		CLR_BIT(MCUCR , MCUCR_ISC01);
		break;
	case EXTI_FALLING_EDGE :
		CLR_BIT(MCUCR , MCUCR_ISC00);
		SET_BIT(MCUCR , MCUCR_ISC01);
		break;
	case EXTI_RISING_EDGE :
		SET_BIT(MCUCR , MCUCR_ISC00);
		SET_BIT(MCUCR , MCUCR_ISC01);
		break;
	default : u8ErrorState_Copy = NOK ;

	}
	return u8ErrorState_Copy ;
}

u8 EXTI_u8Int0SetCallBack (void (*PvInt0Func_Copy) (void)){

	u8 u8ErrorStatusLocal = OK;
	if( PvInt0Func_Copy != NULL ){
		//global ptr = local variable
		EXTI_pvInt0func = PvInt0Func_Copy;
	}
	else{
		u8ErrorStatusLocal = NULL_POINTER;
	}
	return u8ErrorStatusLocal ;
}


/* ISR of INT0 */
void __vector_1 (void) __attribute__ ((signal));
void __vector_1 (void){
    if(EXTI_pvInt0func != NULL){
        //global ptr
        EXTI_pvInt0func();
    }
    else{
        /* DO NOTHING */
    }
}
