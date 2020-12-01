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


const u8 custom_chars[][8] = {MEEM,ALEF_MAD,ZAIN,NOON,ALEF,SEEN,TAA_MARBOUTA};


void display_arabic_name()
{

		LCD_VidPrintCustomChar(6);
		LCD_VidPrintCustomChar(0);
		LCD_VidPrintCustomChar(1);
		LCD_VidPrintCustomChar(5);
		LCD_VidPrintCustomChar(4);
		LCD_VidPrintCustomChar(3);
		LCD_VidPrintCustomChar(2);
		LCD_VidPrintCustomChar(1);
		LCD_VidPrintCustomChar(0);
}

int main(void)
{
	//init..
		LCD_VidInit();

	//load all custom charahcters into CGRAM
	for(int i=0; i<7 ; i++)
	{
		LCD_VidSaveCustomChar(custom_chars[i],i);
	}

	u8 n = 15;
	u8 line_no= 0;



		while(1)
		{


			LCD_VidSendCommand(CLEAR_DISPLAY);
			LCD_VidSetCursorPosition(n,line_no);
			display_arabic_name();
			_delay_ms(500);


			if(n<0)
			{
				n = 15;
			}
			else
			{
				n-= 2 ;
			}


	line_no = (line_no+1)%2 ;



		}
	return 0 ;
}
