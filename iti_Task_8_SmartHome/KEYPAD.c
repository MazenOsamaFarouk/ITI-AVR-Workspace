/*
 * KEYPAD.c
 *
 *  Created on: Jun 12, 2020
 *      Author: mazen
 */

#include "DIO_Interface.h"
#include "KEYPAD.h"
#include <util/delay.h>

void KEYPAD_VidInit(void)
{
	DIO_VidSetPortDirection(KEYPAD_PORT,0xF0);
	DIO_VidSetPortValue(KEYPAD_PORT,0xFF); // activate pull up resistors
}

u8 KEYPAD_u8GetPressedKey(void)
{
	u8 pressed_key = 0;

	u8 col = 0 , row = 0 ;

	for(col=0 ; col<COLS ; col++)
	{
		DIO_VidSetPinValue(KEYPAD_PORT,col+4,0);

		for(row=0 ; row<ROWS ; row++)
		{
			if(DIO_u8GetPinValue(KEYPAD_PORT,row) == 0 )
			{
				pressed_key =  (row + (col*COLS))+1;
			}
			while(DIO_u8GetPinValue(KEYPAD_PORT,row) == 0){}
			_delay_ms(DEBOUNCE_DELAY);
		}

		DIO_VidSetPinValue(KEYPAD_PORT,col+4,1);

	}



	return pressed_key;
}
