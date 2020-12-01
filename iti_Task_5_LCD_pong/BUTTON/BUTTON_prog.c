/*
 * BUTTON_prog.h
 *
 *  Created on: Dec 1, 2020
 *      Author: mazen
 */
#include "../DIO/DIO_Interface.h"
#include "BUTTON_Interface.h"
#include "BUTTON_Config.h"
#include <util/delay.h>



Button_Type BUTTON_Init(u8 port, u8 pin,u8 type,u32 debounce_delay, u8 use_internal_pullup)
{
	Button_Type b;
	b.state = 0;
	b.port = port;
	b.pin = pin;
	b.type = type; //Normally Open(NO) or Noramlly Closed (NC)

	if(b.type == NO)
	{
		b.state = RELEASED;
	}
	else if(b.type == NC)
	{
		b.state = PRESSED;
	}

	b.debounce_delay = debounce_delay;

	DIO_VidSetPinDirection(b.port,b.pin,INPUT);
	if(use_internal_pullup > 0)
	{
		DIO_VidSetPinValue(b.port,b.pin,1); // enable internal pull up
	}


	return b;
}

void BUTTON_SetDebounceDelay(Button_Type*me, u32 deb_delay)
{
	me->debounce_delay = deb_delay;
}

void BUTTON_IsPressed(Button_Type* me)
{
	u8 value = 0;

	value=DIO_u8GetPinValue(me->port,me->pin);

	if(value == me->type) //first detected edge
	{
		_delay_ms(me->debounce_delay);
		value=DIO_u8GetPinValue(me->port,me->pin);
		if(value == me->type) //second detected edge
		{
			me->state=PRESSED;
		}
		else
		{
			me->state=RELEASED;
		}

	}


}

void BUTTON_GetButtonArray(Button_Type b_arr[],u8 port ,u8 no_buttons)
{

}


