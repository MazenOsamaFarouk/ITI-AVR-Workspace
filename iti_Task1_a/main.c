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
#include "_7SEGMENT/_7Seg.h"
#include <util/delay.h>


void count_up(_7Seg * ss)
{
	for(u8 i=0; i<10; i++ )
	{
		_7SEG_VidDisplayNum(ss, i);
		_delay_ms(500);
	}
}

void count_down(_7Seg * ss)
{
	for(u8 i=9; i !=0; i-- )
	{
		_7SEG_VidDisplayNum(ss, i);
		_delay_ms(500);
	}
}

void count99(_7Seg * ss1, _7Seg * ss2)
{
	for(u8 i=0; i<100; i++)
	{
		_7SEG_VidDisplayNum(ss2,(i/10));
		_7SEG_VidDisplayNum(ss1,(i%10));
		_delay_ms(500);
	}
}



int main(void)
{

_7SEG_PIN ss1_pins[]={
		{PORTA,0},
		{PORTA,1},
		{PORTA,2},
		{PORTA,3},
		{PORTA,4},
		{PORTA,5},
		{PORTA,6},
		{PORTA,7},
};

_7SEG_PIN ss2_pins[]={
		{PORTB,0},
		{PORTB,1},
		{PORTB,2},
		{PORTB,3},
		{PORTB,4},
		{PORTB,5},
		{PORTB,6},
		{PORTB,7},
};

_7Seg ss1,ss2;

ss1.pins = ss1_pins;
ss1.type = COM_CATHODE;

ss2.pins = ss2_pins;
ss2.type = COM_CATHODE;

_7SEG_VidInit(&ss1);
_7SEG_VidInit(&ss2);


DIO_VidSetPinDirection(PORTC,0,INPUT);
DIO_VidSetPinDirection(PORTC,1,INPUT);
DIO_VidSetPinDirection(PORTC,2,INPUT);
DIO_VidSetPinDirection(PORTC,3,INPUT);

// enable pull-ups
DIO_VidSetPinValue(PORTC,0,1);
DIO_VidSetPinValue(PORTC,1,1);
DIO_VidSetPinValue(PORTC,2,1);
DIO_VidSetPinValue(PORTC,3,1);

u8 dip_sw = 0;



	while(1)
	{


		dip_sw = DIO_u8GetPortValue(PORTC); //switch is pressed

		switch(dip_sw)
		{
			case 1: _7SEG_VidDisplayOff(&ss2);  count_up(&ss1); break;
			case 2: _7SEG_VidDisplayOff(&ss1);  count_down(&ss2);  break;
			case 4: count99(&ss1,&ss2); break;
			default:  _7SEG_VidDisplayOff(&ss2);  _7SEG_VidDisplayOff(&ss1);  break;

		}



	}
}
