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

#include <util/delay.h>

#define C0R0 0x01
#define C0R1 0x02
#define C0R2 0x04
#define C0R3 0x08
#define C1R0 0x1E
#define C1R1 0x1D
#define C1R2 0x1B
#define C1R3 0x17

//u8 LED_ON(u8 r, u8 c)
//{
//	u8 port_value=0;
//	u8 row_mask = 0 ;
//	if(c==1)
//	{
//		SET_BIT(port_value,Cx);
//		SET_BIT(row_mask,BIT(r));
//		row_mask = (~row_mask)&(0x0F);
//	}
//	else if(c==0)
//	{
//		CLR_BIT(port_value,Cx);
//		SET_BIT(row_mask,BIT(r));
//	}
//
//	port_value|=(row_mask&0xE0);
//
//
//	return port_value;
//}


int main(void)
{



DIO_VidSetPortDirection(PORTB,0xff);
DIO_VidSetPortDirection(PORTA,0xff);


// 000-[C R3 R2 R1 R0]
u8 pv[2][4]={
		{C0R0,C0R1,C0R2,C0R3},
		{C1R0,C1R1,C1R2,C1R3}
};





	while(1)
	{

		for(u8 i=0; i<2; i++)
		{
			for(u8 j=0; j<4; j++)
			{
//				pv = LED_ON(j,i);
//				DIO_VidSetPortValue(PORTA,pv);
				DIO_VidSetPortValue(PORTB,pv[i][j]);
//				DIO_VidSetPortValue(PORTB,0b00000001);

				_delay_ms(1000);
			}
		}






	}
}
