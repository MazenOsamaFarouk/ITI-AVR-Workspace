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


#define REFRESH_RATE 250
#define steve 	0
#define kick 	1
#define punch	2
#define duck	3
#define dead1	4
#define dead2	5


const u8 custom_chars[][8] = {STICK_FIG,KICK,PUNCH,DUCK,DEAD1,DEAD2};

int main(void)
{
	//init..
	LCD_VidInit();


	//load all custom charahcters into CGRAM
	for(int i=0; i<6 ; i++)
	{
		LCD_VidSaveCustomChar(custom_chars[i],i);
	}




	// frame 1
	LCD_VidSendCommand(CLEAR_DISPLAY);
	LCD_VidSetCursorPosition(0,0);
	LCD_VidPrintCustomChar(steve);

	LCD_VidSetCursorPosition(0,1);
	LCD_VidPrintString("This is Steve.",0);
	// end frame 1

	_delay_ms(REFRESH_RATE*2);

	// frame2~6
	LCD_VidSetCursorPosition(0,0);
	LCD_VidSendChar(' ');
	for(u8 i=0; i<8;i++)
	{
		LCD_VidSetCursorPosition(i,0);
		LCD_VidPrintCustomChar(steve);
		_delay_ms(REFRESH_RATE);
		LCD_VidSetCursorPosition(i,0);
		LCD_VidSendChar(' ');
	}
	LCD_VidSetCursorPosition(7,0);
	LCD_VidPrintCustomChar(steve);
	// end of frame2~6

	_delay_ms(REFRESH_RATE*4);

	// frame 7
	LCD_VidSetCursorPosition(0,1);
	LCD_VidPrintString("Steve is Smart   ",0);
	// end of frame 7

	_delay_ms(REFRESH_RATE*8);

	// frame 8
	LCD_VidSetCursorPosition(0,1);
	LCD_VidPrintString("He Plays KungFu ",0);
	// end of frame 8

	_delay_ms(REFRESH_RATE*8);

	//frame 9
	LCD_VidSetCursorPosition(0,1);
	LCD_VidPrintString(">>>>Fight !!<<<<",250);
	// end of frame 9

	_delay_ms(REFRESH_RATE*4);

	// frame 10
	LCD_VidSetCursorPosition(15,0);
	LCD_VidPrintCustomChar(steve);
	//end of frame 10

	_delay_ms(REFRESH_RATE*4);

	// frame 11~18
	for(u8 i=15; i != 8; i--)
	{
		LCD_VidSetCursorPosition(i,0);
		LCD_VidPrintCustomChar(steve);
		_delay_ms(REFRESH_RATE);
		LCD_VidSetCursorPosition(i,0);
		LCD_VidSendChar(' ');
	}
	LCD_VidSetCursorPosition(8,0);
	LCD_VidPrintCustomChar(steve);
	// end of frame 11~18
	_delay_ms(REFRESH_RATE*4);

	//frame 19
	LCD_VidSetCursorPosition(7,0);
	LCD_VidPrintCustomChar(kick);
	LCD_VidSetCursorPosition(8,0);
	LCD_VidPrintCustomChar(punch);
	// end of frame 19
	_delay_ms(REFRESH_RATE*4);

	// frame 20
	LCD_VidSetCursorPosition(7,0);
	LCD_VidPrintCustomChar(punch);
	LCD_VidSetCursorPosition(8,0);
	LCD_VidPrintCustomChar(duck);
	// end of frame 20
	_delay_ms(REFRESH_RATE*4);

	// frame 21
	LCD_VidSetCursorPosition(7,0);
	LCD_VidPrintCustomChar(duck);
	LCD_VidSetCursorPosition(8,0);
	LCD_VidPrintCustomChar(kick);
	// end of frame 21
	_delay_ms(REFRESH_RATE*4);

	// frame 22
	LCD_VidSetCursorPosition(7,0);
	LCD_VidPrintCustomChar(punch);
	LCD_VidSetCursorPosition(8,0);
	LCD_VidPrintCustomChar(kick);
	// end of frame 22
	_delay_ms(REFRESH_RATE*4);

	// frame 23
	LCD_VidSetCursorPosition(7,0);
	LCD_VidPrintCustomChar(duck);
	LCD_VidSetCursorPosition(8,0);
	LCD_VidPrintCustomChar(punch);
	// end of frame 23
	_delay_ms(REFRESH_RATE*4);

	// frame 24
	LCD_VidSetCursorPosition(7,0);
	LCD_VidPrintCustomChar(kick);
	LCD_VidSetCursorPosition(8,0);
	LCD_VidPrintCustomChar(duck);
	// end of frame 24
	_delay_ms(REFRESH_RATE*4);

	// frame 25
	LCD_VidSetCursorPosition(7,0);
	LCD_VidPrintCustomChar(steve);
	LCD_VidSetCursorPosition(8,0);
	LCD_VidPrintCustomChar(dead1);
	LCD_VidPrintCustomChar(dead2);
	// end of frame 25
	_delay_ms(REFRESH_RATE*4);

	// frame 26
	LCD_VidSetCursorPosition(0,1);
	LCD_VidPrintString("   >>>>KO<<<<   ",0);
	_delay_ms(REFRESH_RATE);
	LCD_VidSetCursorPosition(0,1);
	LCD_VidPrintString("                ",0);
	_delay_ms(REFRESH_RATE);
	LCD_VidSetCursorPosition(0,1);
	LCD_VidPrintString("   >>>>KO<<<<   ",0);
	_delay_ms(REFRESH_RATE*4);
	LCD_VidSetCursorPosition(0,1);
	LCD_VidPrintString("***Steve WON****",0);

	// end of frame 26


	while(1)
	{




	}
return 0 ;

}
