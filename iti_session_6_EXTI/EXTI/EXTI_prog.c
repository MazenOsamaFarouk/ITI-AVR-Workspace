/*
 * EXT_INT_Interface.c
 *
 *  Created on: Jun 19, 2020
 *      Author: mazen
 */
#include "EXTI_Interface.h"

#include "../LIB/STD_TYPES.h"
#include "../LIB/BIT_CALC.h"
#include "../DIO/DIO_Interface.h"

#include "EXTI_Interface.h"
#include "EXTI_Register.h"
#include "EXTI_Config.h"


static void (*Global_INT0_CBFunc)(void)=NULL;
static void (*Global_INT1_CBFunc)(void)=NULL;
static void (*Global_INT2_CBFunc)(void)=NULL;



void EXTI_init(void)
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


void EXTI_enable(u8 int_id)
{
	switch(int_id)
	{
	case 0: SET_BIT(GICR,INT0_EN); break;
	case 1: SET_BIT(GICR,INT1_EN); break;
	case 2: SET_BIT(GICR,INT2_EN); break;
	}
}



void EXTI_disable(u8 int_id)
{
	switch(int_id)
	{
	case 0: CLR_BIT(GICR,INT0_EN); break;
	case 1: CLR_BIT(GICR,INT1_EN); break;
	case 2: CLR_BIT(GICR,INT2_EN); break;
	}
}

void EXTI_SetCallBack(u8 int_id, void (*CBFunc)(void))
{
	if(CBFunc != NULL)
	{
		switch(int_id)
		{
			case INT0_EN: Global_INT0_CBFunc=CBFunc;  break;
			case INT1_EN: Global_INT1_CBFunc=CBFunc;  break;
			case INT2_EN: Global_INT2_CBFunc=CBFunc;  break;
		}
	}
}


/* ********ISR definitions********* */
#if INT0==ENABLE
void __vector_1(void)
{
	if(Global_INT0_CBFunc != NULL)
	{
		Global_INT0_CBFunc();
	}
}
#endif

#if INT1==ENABLE
void __vector_2(void)
{
	if(Global_INT1_CBFunc != NULL)
	{
		Global_INT1_CBFunc();
	}
}
#endif

#if INT2==ENABLE
void __vector_3(void)
{
	if(Global_INT2_CBFunc != NULL)
	{
		Global_INT2_CBFunc();
	}

}
#endif




