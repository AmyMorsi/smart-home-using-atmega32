#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "DIO.h"
#include "CLCD.h"
#include<util/delay.h>
#include<string.h>


void CLCD_void_SetPinsDirection()
{
	DIO_SetPortDirection(CLCD_DATA_PORT,CLCD_DATA_PORT_DIRECTION);
	DIO_SetPinDirection(CLCD_CTRL_PORT,CLCD_RS_PIN ,DIO_OUTPUT);
	DIO_SetPinDirection(CLCD_CTRL_PORT,CLCD_RW_PIN ,DIO_OUTPUT);
	DIO_SetPinDirection(CLCD_CTRL_PORT,CLCD_EN_PIN ,DIO_OUTPUT);
}

void CLCD_void_Execute()
{
	DIO_SetPinValue(CLCD_CTRL_PORT,CLCD_EN_PIN,DIO_HIGH);
	_delay_ms(2);
	DIO_SetPinValue(CLCD_CTRL_PORT,CLCD_EN_PIN,DIO_LOW);
}

void CLCD_void_SendData(u8 U8DataCopy)
{
	// RS = 1 data Input
	DIO_SetPinValue(CLCD_CTRL_PORT,CLCD_RS_PIN ,DIO_HIGH);
	// RW  0  for writing
	DIO_SetPinValue(CLCD_CTRL_PORT,CLCD_RW_PIN ,DIO_LOW);
	DIO_SetPortValue(CLCD_DATA_PORT,U8DataCopy);
	CLCD_void_Execute();
}

void CLCD_void_SendStringData(u8* String)
{
	u8 i=0;
	for(i=0;i<strlen(String);i++)
		CLCD_void_SendData(String[i]);
}

//RS =1 RW = 0 --> write;
void CLCD_void_SendCommand(u8 U8CommandCopy)
{
	// RS = 0 Command Input
	DIO_SetPinValue(CLCD_CTRL_PORT,CLCD_RS_PIN ,DIO_LOW);
	// RW  0  for writing
	DIO_SetPinValue(CLCD_CTRL_PORT,CLCD_RW_PIN ,DIO_LOW);
	DIO_SetPortValue(CLCD_DATA_PORT,U8CommandCopy);
	CLCD_void_Execute();
}

void CLCD_void_Init()
{
	_delay_ms(30);
	CLCD_void_SetPinsDirection();
	CLCD_void_SendCommand(CLCD_INIT_FunctionSet_2Lines_SmallFont);
	CLCD_void_SendCommand(CLCD_INIT_DisplayControl_WithCursor);
	CLCD_void_SendCommand(CLCD_INIT_DisplayClear);
}
void CLCD_VOID_SetCursorPosition(u8 LineNum, u8 ColumnNum) {
    if (LineNum < CLCD_Number_of_Lines && ColumnNum < CLCD_Number_of_Line_Chars)
    {
        u8 Position;// = (LineNum * CLCD_Number_of_Line_Chars) + ColumnNum;
        if (LineNum == CLCD_FirstLine)
        	Position = StartingAddressOfLine0 + ColumnNum;
        else // LineNum == CLCD_SecondLine
        	Position = StartingAddressOfLine1 + ColumnNum;
        CLCD_void_SendCommand(Position);  // Set cursor to the new position
    }
}






