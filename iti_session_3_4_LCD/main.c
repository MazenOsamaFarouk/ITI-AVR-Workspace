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

#include <util/delay.h>


int main(void)
{
char longStr[]="This is a long string to test the DDRAM buffer";
	//init..
		LCD_VidInit();

		LCD_VidPrintString(longStr);
		LCD_VidScrollDisplay(23,LEFT,500);
		LCD_VidScrollDisplay(23,RIGHT,500);

		_delay_ms(500);


		while(1)
		{

		}
	return 0 ;
}
