/*
 * main.c
 *
 *  Created on: Nov 30, 2020
 *      Author: neutr
 */


#include "DIO_Interface.h"
#include "LCD_Interface.h"
#include <util/delay.h>


int main(void)
{

	LCD_voidInit();


//	LCD_voidSendCommand(0x01); //clear display
//	LCD_voidSendCommand(0x80); //set cursor position to 0,0


	LCD_voidSendData('a');
	LCD_voidSendData('b');
	_delay_ms(500);

	while(1)
	{

	}
}
