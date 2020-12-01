/*
 * LCD_Programe.c
 *
 *  Created on: Nov 30, 2020
 *      Author: neutr
 */
#include "STD_Type.h"
#include "LCD_Config.h"
#include "DIO_Interface.h"
#include <util/delay.h>

void LCD_voidSendCommand(u8 Copy_U8Command)
{
	DIO_voidSetPinValue(controlport, RS,0);	//RS = 0	D0
	DIO_voidSetPinValue(controlport, RW,0);	//RW = 0	D1
	_delay_ms(1);
	DIO_SetPortValue(dataport,Copy_U8Command);
	_delay_ms(1);

	// Enable Sequence
	DIO_voidSetPinValue(controlport, E, 1); // Enable = 1
	_delay_ms(1);
	DIO_voidSetPinValue(controlport, E, 0); // Enable = 0
	_delay_ms(1);
}

void LCD_voidSendData(u8 Copy_U8Data)
{
	DIO_voidSetPinValue(controlport, RS,1);	//RS = 1	D0
	DIO_voidSetPinValue(controlport, RW,0);	//RW = 0	D1
	_delay_ms(1);
	DIO_SetPortValue(dataport,Copy_U8Data);
	_delay_ms(1);
	// Enable Sequence
	DIO_voidSetPinValue(controlport, E,1);
	_delay_ms(1);
	DIO_voidSetPinValue(controlport, E,0);
	_delay_ms(1);
}



void LCD_voidInit(void)
{
	_delay_ms(50);

	DIO_voidSetPinDirection(controlport, RS,1);  // RS = output
	DIO_voidSetPinDirection(controlport, RW,1);  // RE = output
	DIO_voidSetPinDirection(controlport, E,1);   // E  = output
	_delay_ms(1);

	DIO_SetPortDirection(dataport, 0xff);  //set portc as output
	LCD_voidSendCommand(0b00111000); // 0x38
	_delay_ms(1);

	LCD_voidSendCommand(0b00001110);  // 0x0f
	_delay_ms(1);
	LCD_voidSendCommand(0x06);
	LCD_voidSendCommand(0b00000001); // 0x01
	_delay_ms(2);
//	LCD_voidSendCommand(0x80); //set cursor position to display origin


}





void LCD_VidSendString(u8 Copy_U8String)
{

}

