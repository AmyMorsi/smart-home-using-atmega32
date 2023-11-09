//file guard
#ifndef _DIO
#define _DIO


//Define Ports
#define DIO_PORTA 0
#define DIO_PORTB 1
#define DIO_PORTC 2
#define DIO_PORTD 3

//Define Pins
#define DIO_PIN0 0
#define DIO_PIN1 1
#define DIO_PIN2 2
#define DIO_PIN3 3
#define DIO_PIN4 4
#define DIO_PIN5 5
#define DIO_PIN6 6
#define DIO_PIN7 7

//Pin Directions
#define DIO_INPUT 0
#define DIO_OUTPUT 1

// port Direction Options (Needed only)
#define DIO_INPUT_PORT 0x00
#define DIO_OUTPUT_PORT 0xFF
// Pin Value Options
#define DIO_HIGH 1
#define DIO_LOW 0

// Port Value Options (Needed only)
#define DIO_PORT_HIGH   0xff
#define DIO_PORT_LOW    0x00


// Word Value Options (needed only)
#define DIO_Word0 0
#define DIO_Word1 1
#define DIO_HIGH_WORD   0b1111
#define DIO_LOW_WORD    0
// WORD Direction Options (Needed only)
#define DIO_INPUT_Word  0b0000
#define DIO_OUTPUT_Word 0b1111
// Sizes
#define DIO_WORD 4
#define DIO_HALF_WORD 2
#define DIO_BYTE 8
//Prototype of Function
//IO Pins Functions
void DIO_SetPinValue(u8 U8PortIdCopy,u8 U8PinIdCopy,u8 U8PinValueCopy);

void DIO_SetPinDirection(u8 U8PortIdCopy,u8 U8PinIdCopy,u8 U8PinDirCopy);

u8 DIO_GetPinValue(u8 U8PortIdCopy,u8 U8PinIdCopy);

u8 DIO_GetInputPinValue(u8 U8PortIdCopy,u8 U8PinIdCopy);//needed in transistors

void DIO_TogglePinValue(u8 U8PortIdCopy,u8 U8PinIdCopy);

//Word Options
void DIO_SetWordValue(u8 U8PortIdCopy,u8 U8FirstPinIdCopy,u8 U8WordValueCopy);

void DIO_SetWordDirection(u8 U8PortIdCopy,u8 U8FirstPinIdCopy,u8 U8WordDirCopy);


//IO Ports Functions
void DIO_SetPortValue(u8 U8PortIdCopy,u8 U8PortValueCopy);

void DIO_SetPortDirection(u8 U8PortIdCopy,u8 U8PortDirCopy);

u8 DIO_GetPortValue(u8 U8PortIdCopy);


#endif
