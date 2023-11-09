//Life Guard
#ifndef _CLCD
#define _CLCD

// LCD Ports
#define CLCD_DATA_PORT DIO_PORTC
#define CLCD_CTRL_PORT DIO_PORTA


// Control Pins
#define CLCD_RS_PIN   DIO_PIN0
#define CLCD_RW_PIN   DIO_PIN1
#define CLCD_EN_PIN   DIO_PIN2

//PORT and PINS Directions
#define CLCD_DATA_PORT_DIRECTION      DIO_OUTPUT_PORT
#define CLCD_CONTROL_PORT_DIRECTION   0b00000111


//macros objects
#define CLCD_FirstLine 0
#define CLCD_SecondLine 1
#define CLCD_Number_of_Lines 2
#define CLCD_Number_of_Line_Chars 16
#define StartingAddressOfLine0 0x80 //the starting address of the DDRAM for the first line
#define StartingAddressOfLine1 0xC0 //the starting address of the DDRAM for the second line
//Initialization Commands
//1 Function Set
#define CLCD_INIT_FunctionSet_2Lines_SmallFont 0b00111000
#define CLCD_INIT_FunctionSet_2Lines_LargeFont 0b00111100
#define CLCD_INIT_FunctionSet_1Lines_SmallFont 0b00110000
#define CLCD_INIT_FunctionSet_1Lines_LargeFont 0b00110100
//2 Display Control
#define CLCD_INIT_DisplayControl_WithoutCursor 0b00001100
#define CLCD_INIT_DisplayControl_WithCursor 0b00001111
//3 Display Control
#define CLCD_INIT_DisplayClear 0b00000001


void CLCD_void_SetPinsDirection();

void CLCD_void_Init();

void CLCD_void_Execute();

void CLCD_void_SendData(u8 U8DataCopy);

void CLCD_void_SendStringData(u8* String);

void CLCD_void_SendCommand(u8 U8CommandCopy);

void CLCD_VOID_SetCursorPosition(u8 LineNum , u8 ColumnNum);

#endif
