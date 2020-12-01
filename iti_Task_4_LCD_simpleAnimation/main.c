/*
 * main.c
 *
 *  Created on: Nov 29, 2020
 *      Author: mazen
 *  Description: Task 1_a for ITI-AVR course
 *  control 2 seven segment displays using 4 dip switches.
 *  use the dip switches to put the system in 1 of 3 modes:
 *  1. mode 1 -> count up on one of the seven segments
 *  2. mode 2 -> count down one the other seven segment
 *  3. mode 3 -> count to  99 using both seven segments
 */


//#include <avr/io.h>
//#include <util/delay.h>

#include "LIB/STD_TYPES.h"
#include "LIB/BIT_MAN.h"

#include "DIO/DIO_Interface.h"
#include "LCD/LCD_Interface.h"

#include "custom_chars.h"

#include <util/delay.h>







const u8 custom_chars[][8] = {STICK_FIG,STICK_FIG_RUN,BALL,GOAL};

int main(void)
{
	//init..
	LCD_VidInit();


	//load all custom charahcters into CGRAM
	for(int i=0; i<4 ; i++)
	{
		LCD_VidSaveCustomChar(custom_chars[i],i);
	}




	// frame 1
	LCD_VidSendCommand(CLEAR_DISPLAY);
	LCD_VidSetCursorPosition(0,0);
	LCD_VidPrintCustomChar(0);

	LCD_VidSetCursorPosition(1,0);
	LCD_VidPrintCustomChar(2);

	LCD_VidSetCursorPosition(15,0);
	LCD_VidPrintCustomChar(3);
	// end frame 1

	_delay_ms(1000);

	//frame 2
	LCD_VidSendCommand(CLEAR_DISPLAY);
	LCD_VidSetCursorPosition(1,0);
	LCD_VidPrintCustomChar(1);

	LCD_VidSetCursorPosition(2,0);
	LCD_VidPrintCustomChar(2);

	LCD_VidSetCursorPosition(15,0);
	LCD_VidPrintCustomChar(3);
	//end frame2

	// frames 3~8
	for(int i=2; i!=10 ;i++)
	{
		LCD_VidSendCommand(CLEAR_DISPLAY);
		LCD_VidSetCursorPosition(i,0);
		LCD_VidPrintCustomChar(1);

		LCD_VidSetCursorPosition(i+1,0);
		LCD_VidPrintCustomChar(2);

		LCD_VidSetCursorPosition(15,0);
		LCD_VidPrintCustomChar(3);
		_delay_ms(500);
	}
	//end of frames 3~8

	for(int i=10; i<15 ;i++)
	{
		LCD_VidSendCommand(CLEAR_DISPLAY);
		LCD_VidSetCursorPosition(10,0);
		LCD_VidPrintCustomChar(0);

		LCD_VidSetCursorPosition(i,0);
		LCD_VidPrintCustomChar(2);

		LCD_VidSetCursorPosition(15,0);
		LCD_VidPrintCustomChar(3);
		_delay_ms(500);
	}

	LCD_VidSetCursorPosition(0,1); ///move to second line

	char greeting[] = ">>>GOOOOOOOAL<<<" ;
	for(int i=0; greeting[i] != '\0'; i++)
		{
			LCD_VidSendChar(greeting[i]) ;
			_delay_ms(100);
		}


	while(1)
	{




	}
return 0 ;

}
