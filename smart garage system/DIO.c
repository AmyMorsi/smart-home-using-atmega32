#include"STD_TYPES.h"
#include"BIT_MATH.h"
#include"DIO.h"
#include"avr/io.h"
#include<util/delay.h>
#include<stdio.h>
//IO Pins
void DIO_SetPinValue(u8 U8PortIdCopy,u8 U8PinIdCopy,u8 U8PinValueCopy)
{
	if ((U8PortIdCopy<=DIO_PORTD)&&(U8PinIdCopy<=DIO_PIN7))
	{
		if(U8PinValueCopy==DIO_HIGH)
		{
			switch(U8PortIdCopy)
			{
				case DIO_PORTA: SET_BIT(PORTA,U8PinIdCopy); break;
				case DIO_PORTB: SET_BIT(PORTB,U8PinIdCopy); break;
				case DIO_PORTC: SET_BIT(PORTC,U8PinIdCopy); break;
				case DIO_PORTD: SET_BIT(PORTD,U8PinIdCopy); break;
			}
		}
		else if(U8PinValueCopy==DIO_LOW)
		{
			switch(U8PortIdCopy)
			{
				case DIO_PORTA: CLR_BIT(PORTA,U8PinIdCopy); break;
				case DIO_PORTB: CLR_BIT(PORTB,U8PinIdCopy); break;
				case DIO_PORTC: CLR_BIT(PORTC,U8PinIdCopy); break;
				case DIO_PORTD: CLR_BIT(PORTD,U8PinIdCopy); break;

			}
		}
		else
		{
			//Not Valid Status
		}

	}
	else
	{
		//out of range
	}
}

void DIO_SetPinDirection(u8 U8PortIdCopy,u8 U8PinIdCopy,u8 U8PinDirCopy)
{
	if ((U8PortIdCopy<=DIO_PORTD)&&(U8PinIdCopy<=DIO_PIN7))
		{
			if(U8PinDirCopy==DIO_OUTPUT)
			{
				switch(U8PortIdCopy)
				{
					case DIO_PORTA: SET_BIT(DDRA,U8PinIdCopy); break;
					case DIO_PORTB: SET_BIT(DDRB,U8PinIdCopy); break;
					case DIO_PORTC: SET_BIT(DDRC,U8PinIdCopy); break;
					case DIO_PORTD: SET_BIT(DDRD,U8PinIdCopy); break;
				}
			}
			else if(U8PinDirCopy==DIO_INPUT)
			{
				switch(U8PortIdCopy)
				{
					case DIO_PORTA: CLR_BIT(DDRA,U8PinIdCopy); break;
					case DIO_PORTB: CLR_BIT(DDRB,U8PinIdCopy); break;
					case DIO_PORTC: CLR_BIT(DDRC,U8PinIdCopy); break;
					case DIO_PORTD: CLR_BIT(DDRD,U8PinIdCopy); break;

				}
			}

		}
}

u8 DIO_GetPinValue(u8 U8PortIdCopy,u8 U8PinIdCopy)
{
	if ((U8PortIdCopy<=DIO_PORTD)&&(U8PinIdCopy<=DIO_PIN7))
	{
		switch(U8PortIdCopy)
		{
			case DIO_PORTA: return GET_BIT(PINA,U8PinIdCopy); break;
			case DIO_PORTB: return GET_BIT(PINB,U8PinIdCopy); break;
			case DIO_PORTC: return GET_BIT(PINC,U8PinIdCopy); break;
			case DIO_PORTD: return GET_BIT(PIND,U8PinIdCopy); break;
		}
	}

	return 0xFF;
}


u8 DIO_GetInputPinValue(u8 U8PortIdCopy,u8 U8PinIdCopy)
{
	if ((U8PortIdCopy<=DIO_PORTD)&&(U8PinIdCopy<=DIO_PIN7))
	{
		switch(U8PortIdCopy)
		{
			case DIO_PORTA: return GET_BIT(PINA,U8PinIdCopy); break;
			case DIO_PORTB: return GET_BIT(PINB,U8PinIdCopy); break;
			case DIO_PORTC: return GET_BIT(PINC,U8PinIdCopy); break;
			case DIO_PORTD: return GET_BIT(PIND,U8PinIdCopy); break;
		}
	}
	return 0xFF;
}





void DIO_TogglePinValue(u8 U8PortIdCopy,u8 U8PinIdCopy)
{
	//u8 PortValue;
	if ((U8PortIdCopy<=DIO_PORTD)&&(U8PinIdCopy<=DIO_PIN7))
	{
		//PortValue = DIO_GetPortValue(U8PortIdCopy);
		switch(U8PortIdCopy)
		{
			case DIO_PORTA:TOG_BIT(PORTA,U8PinIdCopy); break;
			case DIO_PORTB:TOG_BIT(PORTB,U8PinIdCopy); break;
			case DIO_PORTC:TOG_BIT(PORTC,U8PinIdCopy); break;
			case DIO_PORTD:TOG_BIT(PORTD,U8PinIdCopy); break;
		}
	//	DIO_SetPortValue(U8PortIdCopy,PortValue);
	}
}


void DIO_SetWordValue(u8 U8PortIdCopy,u8 U8FirstPinIdCopy,u8 U8WordValueCopy)
{

	if ( (U8PortIdCopy <= DIO_PORTD) && (U8FirstPinIdCopy<(DIO_BYTE-DIO_WORD)) )
		{
			u8 tempWordVal,WordBit=0;
			for(WordBit=0;WordBit<DIO_WORD;WordBit++)
			{
				tempWordVal=GET_BIT(U8WordValueCopy,U8FirstPinIdCopy);

				switch(U8PortIdCopy)
				{
					case DIO_PORTA: {
						if(tempWordVal)
							SET_BIT(PORTA,(U8FirstPinIdCopy+WordBit));
						else
							CLR_BIT(PORTA,(U8FirstPinIdCopy+WordBit));
					}break;
					case DIO_PORTB: {
						if(tempWordVal)
							SET_BIT(PORTB,(U8FirstPinIdCopy+WordBit));
						else
							CLR_BIT(PORTB,(U8FirstPinIdCopy+WordBit));
					}break;
					case DIO_PORTC: {
						if(tempWordVal)
							SET_BIT(PORTC,(U8FirstPinIdCopy+WordBit));
						else
							CLR_BIT(PORTC,(U8FirstPinIdCopy+WordBit));
					}break;
					case DIO_PORTD: {
						if(tempWordVal)
							SET_BIT(PORTD,(U8FirstPinIdCopy+WordBit));
						else
							CLR_BIT(PORTD,(U8FirstPinIdCopy+WordBit));
					}break;
				}

			}
		}
}

void DIO_SetWordDirection(u8 U8PortIdCopy,u8 U8FirstPinIdCopy,u8 U8WordDirCopy)
{

	if ( (U8PortIdCopy <= DIO_PORTD) && (U8FirstPinIdCopy<=(DIO_BYTE-DIO_WORD)) )
		{
			u8 tempWordDirect,WordBit=0;
			for(WordBit=0;WordBit<DIO_WORD;WordBit++)
			{
				tempWordDirect=GET_BIT(U8WordDirCopy,WordBit);
				switch(U8PortIdCopy)
				{
					case DIO_PORTA: {
						if(tempWordDirect)
							SET_BIT(DDRA,(U8FirstPinIdCopy+WordBit));
						else
							CLR_BIT(DDRA,(U8FirstPinIdCopy+WordBit));
					}break;
					case DIO_PORTB: {
						if(tempWordDirect)
							SET_BIT(DDRB,(U8FirstPinIdCopy+WordBit));
						else
							CLR_BIT(DDRB,(U8FirstPinIdCopy+WordBit));
					}break;
					case DIO_PORTC: {
						if(tempWordDirect)
							SET_BIT(DDRC,(U8FirstPinIdCopy+WordBit));
						else
							CLR_BIT(DDRC,(U8FirstPinIdCopy+WordBit));
					}break;
					case DIO_PORTD: {
						if(tempWordDirect)
							SET_BIT(DDRD,(U8FirstPinIdCopy+WordBit));
						else
							CLR_BIT(DDRD,(U8FirstPinIdCopy+WordBit));
					}break;
				}

			}
		}
}



//IO Ports
void DIO_SetPortValue(u8 U8PortIdCopy,u8 U8PortValueCopy)
{
	if (U8PortIdCopy<=DIO_PORTD)
	{
		switch(U8PortIdCopy)
		{
			case DIO_PORTA: PORTA=U8PortValueCopy; break;
			case DIO_PORTB: PORTB=U8PortValueCopy; break;
			case DIO_PORTC: PORTC=U8PortValueCopy; break;
			case DIO_PORTD: PORTD=U8PortValueCopy; break;
		}
	}
}

void DIO_SetPortDirection(u8 U8PortIdCopy,u8 U8PortDirCopy)
{
	if (U8PortIdCopy<=DIO_PORTD)
		{
			switch(U8PortIdCopy)
			{
				case DIO_PORTA: DDRA=U8PortDirCopy; break;
				case DIO_PORTB: DDRB=U8PortDirCopy; break;
				case DIO_PORTC: DDRC=U8PortDirCopy; break;
				case DIO_PORTD: DDRD=U8PortDirCopy; break;
			}
		}
}
u8 DIO_GetPortValue(u8 U8PortIdCopy)
{
	if (U8PortIdCopy<=DIO_PORTD)
	{
		switch(U8PortIdCopy)
		{
			case DIO_PORTA: return PINA; break;
			case DIO_PORTB: return PINB; break;
			case DIO_PORTC: return PINC; break;
			case DIO_PORTD: return PIND; break;
		}
	}
	return 0xff;//out of range
}
