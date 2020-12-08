/*
 * EXT_INT_Interface.c
 *
 *  Created on: Jun 19, 2020
 *      Author: mazen
 */
#include "STD_TYPES.h"
#include "BIT_CALC.h"
#include "EXT_INT_Register.h"
#include "EXT_INT_Interface.h"

#include "DIO_Interface.h"

void EXT_INT_init(void)
{
	// 1. select trigger mode in MCUCR
	// 2. set direction of DIO pin to input
	// 3. enable pull-up resistors

#if INT0 == ENABLE
		DIO_VidSetPinDirection(PORTD,PIN2,0); //set direction to input
		DIO_VidSetPinValue(PORTD,PIN2,1); //enable pull-up resistor

		#if INT0_TRIG_MODE == FALLING_EDGE

			CLR_BIT(MCUCR,0);
			SET_BIT(MCUCR,1);

		#elif  INT0_TRIG_MODE == RISING_EDGE

			SET_BIT(MCUCR,0);
			SET_BIT(MCUCR,1);

		#elif  INT0_TRIG_MODE == ON_CHANGE

			CLR_BIT(MCUCR,1);
			SET_BIT(MCUCR,0);

		#elif  INT0_TRIG_MODE == LOW_LEVEL

			CLR_BIT(MCUCR,0);
			CLR_BIT(MCUCR,1);
		#else
		#error "EXT_INT_ERROR: INT0->No Trigger Mode selected"
		#endif


#endif

#if INT1 == ENABLE
	DIO_VidSetPinDirection(PORTD,PIN3,0); //set direction to input
	DIO_VidSetPinValue(PORTD,PIN3,1); //enable pull-up resistor

		#if INT1_TRIG_MODE == FALLING_EDGE

			CLR_BIT(MCUCR,2);
			SET_BIT(MCUCR,3);

		#elif  INT1_TRIG_MODE == RISING_EDGE

			SET_BIT(MCUCR,2);
			SET_BIT(MCUCR,3);

		#elif  INT1_TRIG_MODE == ON_CHANGE

			CLR_BIT(MCUCR,3);
			SET_BIT(MCUCR,2);

		#elif  INT1_TRIG_MODE == LOW_LEVEL

			CLR_BIT(MCUCR,2);
			CLR_BIT(MCUCR,3);
		#else
		#error "EXT_INT_ERROR: INT1->No Trigger Mode selected"
		#endif

#endif

#if INT2 == ENABLE
	DIO_VidSetPinDirection(PORTB,PIN2,0); //set direction to input
	DIO_VidSetPinValue(PORTB,PIN2,1); //enable pull-up resistor

		#if INT2_TRIG_MODE == FALLING_EGDE
			CLR_BIT(MCUCSR,6);
		#elif INT2_TRIG_MODE == RISING_EGDE
			SET_BIT(MCUCSR,6);
		#else
		#error "EXT_INT_ERROR: INT2-> only choose rising or falling edge"
		#endif
#endif

#if INT0==DISABLE && INT1==DISABLE && INT2==DISABLE
#warning "EXT_INT_init(): NO Interrupt pins selected!!"
#endif


}


void EXT_INT_enable(u8 int_id)
{
	switch(int_id)
	{
	case 0: SET_BIT(GICR,INT0_EN); break;
	case 1: SET_BIT(GICR,INT1_EN); break;
	case 2: SET_BIT(GICR,INT2_EN); break;
	}
}



void EXT_INT_disable(u8 int_id)
{
	switch(int_id)
	{
	case 0: CLR_BIT(GICR,INT0_EN); break;
	case 1: CLR_BIT(GICR,INT1_EN); break;
	case 2: CLR_BIT(GICR,INT2_EN); break;
	}
}



