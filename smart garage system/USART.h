/*
 * USART.h
 *
 *  Created on: Aug 24, 2023
 *      Author: Morad
 */

#ifndef USART_H_
#define USART_H_


/* USART Control and Status Register B   UCSRB */

#define    USART_RXCIE        7
#define    USART_TXCIE        6
#define    USART_UDRIE        5
#define    USART_RXEN         4
#define    USART_TXEN         3
#define    USART_UCSZ         2
#define    USART_UCSZ2        2
#define    USART_RXB8         1
#define    USART_TXB8         0


/* USART Control and Status Register A UCSRA   */

#define    USART_RXC          7
#define    USART_TXC          6
#define    USART_UDRE         5
#define    USART_FE           4
#define    USART_DOR          3
#define    USART_UPE          2
#define    USART_U2X          1
#define    USART_MPCM         0




/* USART Baud Rate Register Low  UBRRL   */

/* USART I/O Data Register  UDR */

/* USART Baud Rate Register High UBRRH */

//the same address ..
/* USART Control and Status Register C UCSRC  */


/* USART Register C */
#define    USART_URSEL        7
#define    USART_UMSEL        6
#define    USART_UPM1         5
#define    USART_UPM0         4
#define    USART_USBS         3
#define    USART_UCSZ1        2
#define    USART_UCSZ0        1
#define    USART_UCPOL        0


void UART_Init(void);
u8* USART_Receive_String(void);
u8   USART_Receive_Char(void);
void USART_voidSendString(u8* Copy_pu8Data);
void USART_voidReceiveString(u8* Copy_pu8Data);


#endif /* USART_H_ */

