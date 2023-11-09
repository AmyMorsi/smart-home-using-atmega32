/*
 * USART.c
 *
 *  Created on: Aug 24, 2023
 *      Author: Morad
 */


#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "DIO.h"
#include "GarageSystem.h"
#include "avr/io.h"
#include <util/delay.h>
#include "stdio.h"
#include "string.h"
#include "USART.h"

void USART_Init(void)
{
	//set baud rate 96600
	UBRRL = 51;
	UBRRH = 0;
	//frame format
	SET_BIT(UCSRC , USART_URSEL);
	//  Word Size [8 bits], By default = 8 bits
	SET_BIT(UCSRC , USART_UCSZ0);
	SET_BIT(UCSRC , USART_UCSZ1);
	CLR_BIT(UCSRB , USART_UCSZ2);
	//Disable Parity
	CLR_BIT(UCSRC , USART_UPM0);
	CLR_BIT(UCSRC , USART_UPM1);
	//Stop bit --> 1 bit
	CLR_BIT(UCSRC , USART_USBS);
	//Enable TX ,RX
	SET_BIT(UCSRB , USART_TXEN);
	SET_BIT(UCSRB , USART_RXEN);

}

void USART_Send_Char(u8 U8Char_Copy)
{
	while(GET_BIT(UCSRA , USART_UDRE )==0);
	UDR = U8Char_Copy;
	_delay_ms(1);

}

u8 USART_Receive_Char(void)
{
	//wait for flag RXC ==0
	_delay_ms(2);

	while(GET_BIT(UCSRA , USART_RXC )==0);
	//return Received
	return UDR;

}

void USART_Send_String(u8* PU8Data_Copy)
{
	u8 index=0;
	while(index<strlen(PU8Data_Copy))
	{
		USART_Send_Char(*(PU8Data_Copy+index));
		index++;
	}

}
u8* USART_Receive_String(void)
{
	static u8 EnteredPassword[PasswordSize];
	u8 index = 0;
	u8 EnteredChar;
	while (index < PasswordSize ) // Receive up to PasswordSize characters
	{
		EnteredPassword[index]=USART_Receive_Char();
		// Check for newline character (Enter key) to terminate input
		if (EnteredPassword[index] == '\r')
		{
			EnteredPassword[index] = '\0'; // Null-terminate the string
			break;
		}

		index++;
	}

	return EnteredPassword;
}
