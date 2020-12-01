/*
 * _7Seg.c
 *
 *  Created on: Jun 5, 2020
 *      Author: mazen
 */



#include "../LIB/STD_TYPES.h"
#include "../LIB/BIT_CALC.h"
#include "_7Seg.h"



#if MCU == AVR_ATMEGA32A
	#include "../DIO/DIO_Interface.h"
#elif MCU == ARM_STM32F10XX
	#include "DIO_interface.h"
#endif

const u8 seven_seg_digits[16]={ZERO,ONE,TWO,THREE,FOUR,FIVE,SIX,SEVEN,EIGHT,NINE,A,b,c,d,E,F};

#if MCU == ARM_STM32F10XX

const _7SEG_PIN * pin_arr_ptr = NULL ;

#endif




#if MCU == AVR_ATMEGA32A
void _7SEG_VidInit(_7Seg* me)
{

	for(u8 i=0; i<8; i++)
	{
		DIO_VidSetPinDirection(me->pins[i].port,me->pins[i].pin,1);
	}

}
#elif MCU == ARM_STM32F10XX
void _7SEG_VidInit(_7SEG_PIN pin_array[])
{
	pin_arr_ptr = pin_array ;
	for(u8 i=0; i<8 ; i++)
	{
		DIO_voidSetPinDirection(pin_array[i].port, pin_array[i].pin, OUTPUT_2MHZ_GPPP);
	}
}
#endif





void _7SEG_VidDisplayNum(_7Seg*me, u8 num)
{

#if MCU == AVR_ATMEGA32A

	u8 number=0;
	if(me->type==COM_ANODE)
	{
		number = seven_seg_digits[num%16];
	}
	else if(me->type==COM_CATHODE)
	{
		number = ~seven_seg_digits[num%16];
	}

	for(u8 i=0; i<8; i++)
	{
		DIO_VidSetPinValue(me->pins[i].port,me->pins[i].pin,(GET_BIT(number,i)));
	}


#elif MCU == ARM_STM32F10XX
		u8 number;
		if(_7SEG_TYPE == COM_ANODE)
		{
			number = ~seven_seg_digits[num%16];
		}
		else if(_7SEG_TYPE == COM_CATHODE)
		{
			number = seven_seg_digits[num%16];
		}

		for(u8 i=0; i<8 ; i++)
		{
			DIO_voidSetPinValue(pin_arr_ptr[i].port,pin_arr_ptr[i].pin, GET_BIT(number,i));
		}
#endif
}

void _7SEG_VidDisplayVal(u8 value)
{

#if MCU == AVR_ATMEGA32A
	#if _7SEG_TYPE == COM_ANODE

			DIO_VidSetPortValue(_7SEG_PORT,~(value));

	#elif _7SEG_TYPE == COM_CATHODE

			DIO_VidSetPortValue(_7SEG_PORT,(value));
	#endif
#elif MCU == ARM_STM32F10XX
		for(u8 i=0; i<8 ; i++)
		{
			DIO_voidSetPinValue(pin_arr_ptr[i].port,pin_arr_ptr[i].pin, GET_BIT(value,i));
		}
#endif


}

void _7SEG_VidDisplayOff(_7Seg* me)
{
	u8 number=0;
		if(me->type==COM_ANODE)
		{
			number = 0x00;
		}
		else if(me->type==COM_CATHODE)
		{
			number = 0xff;
		}

		for(u8 i=0; i<8; i++)
		{
			DIO_VidSetPinValue(me->pins[i].port,me->pins[i].pin,(GET_BIT(number,i)));
		}

}




