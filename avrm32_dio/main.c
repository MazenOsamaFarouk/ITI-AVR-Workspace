/*
 * main.c
 *
 *  Created on: Nov 30, 2020
 *      Author: mazen
 */
#include "LIB/STD_TYPES.h"
#include "LIB/BIT_MAN.h"
#include <util/delay.h>

typedef struct
{
	volatile u8 PIN;
	volatile u8 DDR;
	volatile u8 PORT;
}PORT_t;

#define PORTA ((volatile PORT_t*)(0x39)) //address of PINA






int main(void)
{

	SET_BIT(PORTA->DDR,BIT(0));
	CLR_BIT(PORTA->DDR,BIT(1) );
	SET_BIT(PORTA->PORT,BIT(1));  //pull up resistor on A1

	while(1)
	{
		if(GET_BIT(PORTA->PIN,1) == 0) //button pressed
		{
			SET_BIT(PORTA->PORT,BIT(0));
			_delay_ms(1000);
		}
		else
		{
			CLR_BIT(PORTA->PORT,BIT(0));
		}

	}


}
