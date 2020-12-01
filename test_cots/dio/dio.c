/*
 * dio.c
 *
 *  Created on: Nov 25, 2020
 *      Author: mazen
 */



#include "dio.h"





void DIO_SetPin(u8 LOC_u8Port, u8 LOC_u8Pin, u8 LOC_u8Value )
{

	if(LOC_u8Value == 1)
	{
		switch(LOC_u8Port)
		{
		case 0 : SET_BIT(PORTA,LOC_u8Pin); break;
		case 1 : SET_BIT(PORTB,LOC_u8Pin); break;
		case 2 : SET_BIT(PORTC,LOC_u8Pin); break;
		case 3 : SET_BIT(PORTD,LOC_u8Pin); break;

		}
	}
	else if(LOC_u8Value == 0)
	{
		switch(LOC_u8Port)
		{
		case 0 : CLR_BIT(PORTA,LOC_u8Pin); break;
		case 1 : CLR_BIT(PORTB,LOC_u8Pin); break;
		case 2 : CLR_BIT(PORTC,LOC_u8Pin); break;
		case 3 : CLR_BIT(PORTD,LOC_u8Pin); break;

		}

	}

}
