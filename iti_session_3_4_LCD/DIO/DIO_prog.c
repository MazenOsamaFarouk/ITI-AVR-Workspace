/*
 * DIO_prog.c
 *
 *  Created on: Nov 29, 2020
 *      Author: Mazen Osama
 */

#include "../LIB/STD_TYPES.h"
#include "../LIB/BIT_CALC.h"

#include "DIO_Register.h"


void DIO_VidSetPinDirection(u8 LOC_u8Port, u8 LOC_u8Pin, u8 LOC_u8Mode )
{
	if(LOC_u8Mode == 1)
	{
		switch(LOC_u8Port)
		{
		case 0 : SET_BIT(DDRA,LOC_u8Pin); break;
		case 1 : SET_BIT(DDRB,LOC_u8Pin); break;
		case 2 : SET_BIT(DDRC,LOC_u8Pin); break;
		case 3 : SET_BIT(DDRD,LOC_u8Pin); break;
		}
	}
	else if(LOC_u8Mode == 0)
	{
		switch(LOC_u8Port)
		{
		case 0 : CLR_BIT(DDRA,LOC_u8Pin); break;
		case 1 : CLR_BIT(DDRB,LOC_u8Pin); break;
		case 2 : CLR_BIT(DDRC,LOC_u8Pin); break;
		case 3 : CLR_BIT(DDRD,LOC_u8Pin); break;

		}
	}
}



void DIO_VidSetPinValue(u8 LOC_u8Port, u8 LOC_u8Pin, u8 LOC_u8Value )
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

void DIO_VidTogPinValue(u8 LOC_u8Port, u8 LOC_u8Pin)
{
	switch(LOC_u8Port)
	{
	case 0 : TOG_BIT(PORTA,LOC_u8Pin); break;
	case 1 : TOG_BIT(PORTB,LOC_u8Pin); break;
	case 2 : TOG_BIT(PORTC,LOC_u8Pin); break;
	case 3 : TOG_BIT(PORTD,LOC_u8Pin); break;

	}
}



u8 DIO_u8GetPinValue(u8 LOC_u8Port, u8 LOC_u8Pin )
{
	u8 result = 0;
	switch(LOC_u8Port)
	{
	case 0: result = GET_BIT(PINA,LOC_u8Pin) ; break ;

	case 1: result = GET_BIT(PINB,LOC_u8Pin) ; break ;

	case 2: result = GET_BIT(PINC,LOC_u8Pin) ; break ;

	case 3: result = GET_BIT(PIND,LOC_u8Pin) ; break ;

	}

	return result;
}



void DIO_VidSetPortDirection(u8 LOC_u8Port,  u8 LOC_u8Mode )
{
	switch(LOC_u8Port)
			{
			case 0 : DDRA = LOC_u8Mode;  break;
			case 1 : DDRB = LOC_u8Mode; break;
			case 2 : DDRC = LOC_u8Mode; break;
			case 3 : DDRD = LOC_u8Mode; break;

			}

}


void DIO_VidSetPortValue(u8 LOC_u8Port, u8 LOC_u8Value )
{
	switch(LOC_u8Port)
	{
		case 0 : PORTA = LOC_u8Value;  break;
		case 1 : PORTB = LOC_u8Value; break;
		case 2 : PORTC = LOC_u8Value; break;
		case 3 : PORTD = LOC_u8Value; break;

	}

}


void DIO_VidInsPortValue(u8 LOC_u8Port,u8 LOC_u8Value, u8 LOC_u8No_bits, u8 LOC_u8offset)
{
	u8 prep = 0 ;
	u8 shield = 0 ;

	/* 1. prepare offset value */
	prep = (LOC_u8Value<<LOC_u8offset);
	/* 2. prepare shield mask */
	shield = (((1<<LOC_u8No_bits)-1)<<LOC_u8offset); //shield = (2^(No_bits)-1)<<offset ;

	/* 3. combine the shield and the prepared value to output to the port*/
	switch(LOC_u8Port)
	{
	case 0 : PORTA = (PORTA & (~shield)) | (prep & shield) ;  break;
	case 1 : PORTB = (PORTB & (~shield)) | (prep & shield) ;  break;
	case 2 : PORTC = (PORTC & (~shield)) | (prep & shield) ;  break;
	case 3 : PORTD = (PORTD & (~shield)) | (prep & shield) ;  break;

	}
}


u8 DIO_u8GetPortValue(u8 LOC_u8Port)
{
	u8 result = 0;
		switch(LOC_u8Port)
		{
		case 0: result=PINA; break ;

		case 1: result=PINB; break ;

		case 2: result=PINC; break ;

		case 3: result=PIND; break ;

		}

		return result;

}



