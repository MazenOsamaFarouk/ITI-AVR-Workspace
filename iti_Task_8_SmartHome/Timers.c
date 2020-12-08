/*
 * Timers.c
 *
 *  Created on: Jun 27, 2020
 *      Author: mazen
 */
#include "STD_TYPES.h"
#include "BIT_CALC.h"
#include "DIO_Interface.h"
#include "Timers_Register.h"
#include "Timers_Config.h"



// array of call back function pointers
static void (*TCNT0_CallBackFptr[2])(void) = {NULL,NULL} ;

static void (*TCNT1_CallBackFptr)(void) = NULL ;
static void (*TCNT2_CallBackFptr)(void) = NULL ;



void TCNT_VidInit(u8 timer_no)
{


	switch(timer_no)
	{
	case 0:
		/* 1. choose wave generation mode*/
		#if TCNT0_OP_MODE == TCNT0_NORMAL
			CLR_BIT(TCCR0,WGM00);
			CLR_BIT(TCCR0,WGM01);
		#elif TCNT0_OP_MODE == TCNT0_PWM
			SET_BIT(TCCR0,WGM00);
			CLR_BIT(TCCR0,WGM01);
		#elif TCNT0_OP_MODE == TCNT0_CTC
			CLR_BIT(TCCR0,WGM00);
			SET_BIT(TCCR0,WGM01);
		#elif TCNT0_OP_MODE == TCNT0_FAST_PWM
			SET_BIT(TCCR0,WGM00);
			SET_BIT(TCCR0,WGM01);
		#endif

		/* 2. compare match mode select  */
		#ifdef COM0_NON_PWM
			TCCR0 = (TCCR0 & 0xCF) | COM0_NON_PWM ;
		#endif
		#ifdef COM0_PWM
			TCCR0 = (TCCR0 & 0xCF) | COM0_PWM ;
		#endif
		/* 3. choose prescaler */
			TCCR0 = (TCCR0 & 0xF8) | NO_CLK ; //start with timer off

			/* 5. Preload Timer */
				TCNT0 = TCNT0_PRELOAD ;

		/* 4. Overflow Interrupt*/
		#if TCNT0_OVF_Interrupt == ENABLE
			SET_BIT(TIMSK,TOIE0);
		#elif TCNT0_OVF_Interrupt == DISABLE
			CLR_BIT(TIMSK,TOIE0);
		#endif

		/*  6. output compare Interrupt*/
		#if OCM0_Interrupt == ENABLE
			SET_BIT(TIMSK,OCIE0);
		#elif OCM0_Interrupt == DISABLE
			CLR_BIT(TIMSK,OCIE0);
		#endif
			break ;
	case 1:
		/* 1. choose wave generation mode*/
		TCCR1A = (TCCR1A & 0xFC) | (TCNT1_OP_MODE & 0x03) ; //WGM11 and WGM10
		TCCR1B = (TCCR1B & 0xE7) | ((TCNT1_OP_MODE>>2)<<3); //WGM13 and WGM12

		/* 2. compare match mode select  */
#ifdef COM1B_NON_PWM
		TCCR1A = (TCCR1A & 0xCF) | (COM1B_NON_PWM<<4);
		TCCR1A = (TCCR1A & 0x3F) | (COM1A_NON_PWM<<6);

#endif

#ifdef COM1B_PWM
		TCCR1A = (TCCR1A & 0xCF) | (COM1B_PWM<<4);
		TCCR1A = (TCCR1A & 0x3F) | (COM1A_PWM<<6);
#endif
		/* 3. choose prescaler */
		TCCR1B = (TCCR1B & 0xF8) | NO_CLK ; //start with the timer off
		/* 5. Preload Timer */
		TCNT1 = TCNT1_PRELOAD ;
		/* 4. Overflow Interrupt*/
#if TCNT1_OVF_Interrupt == ENABLE
		SET_BIT(TIMSK,TOIE1);
#elif TCNT1_OVF_Interrupt == DISABLE
		CLR_BIT(TIMSK,TOIE1);
#endif

#if OCM1A_Interrupt == ENABLE
		SET_BIT(TIMSK,OCIE1A);
#elif OCM1A_Interrupt == DISABLE
		CLR_BIT(TIMSK,OCIE1A);
#endif

#if OCM1B_Interrupt == ENABLE
		SET_BIT(TIMSK,OCIE1B);
#elif OCM1B_Interrupt == DISABLE
		CLR_BIT(TIMSK,OCIE1B);
#endif

#if TCNT1_IC_Interrupt == ENABLE
		SET_BIT(TIMSK,TICIE1);
#elif TCNT1_IC_Interrupt == DISABLE
		CLR_BIT(TIMSK,TICIE1);
#endif
		break ;
	case 2: break ;
	}



}
void TCNT_VidStartTimer(u8 timer_no)
{
	//start the clock of the timer
	switch(timer_no)
	{
	case 0: TCCR0 = (TCCR0 & 0xF8) | TCNT0_CLK_SELECT ;  break ;
	case 1: TCCR1B = (TCCR1B & 0xF8) | TCNT1_CLK_SELECT ;  break ;
	case 2: break ;
	}


}
void TCNT_VidStopTimer(u8 timer_no)
{
	//start the clock of the timer
	switch(timer_no)
	{
	case 0: TCCR0 = (TCCR0 & 0xF8) | NO_CLK ;  break ;
	case 1: TCCR1B = (TCCR1B & 0xF8) | NO_CLK ; break ;
	case 2: break ;
	}
}

void TCNT_VidResetAllTimers(void)
{
	SET_BIT(SFIOR,PSR10);
}


void TCNT_VidLoadOCR(u8 value, u8 timer_no)
{
	switch(timer_no)
	{
	case 0: OCR0 = value ;   break;
	case 'A': OCR1A = value; break;
	case 'B': OCR1B = value; break;
	case 2: OCR2 = value;    break ;
	}
}

void TCNT_VidSetCallBack( u8 timer_no , void (*LOCfptr)(void))
{
	if(LOCfptr != NULL)
	{
		switch(timer_no)
		{
		case 0: TCNT0_CallBackFptr[TCNT0_CALL_BACK]=LOCfptr; break;
		case 1: TCNT1_CallBackFptr=LOCfptr; break;
		case 2: TCNT2_CallBackFptr=LOCfptr; break;
		}
	}

}



/* Timer/counter 0 - compare match ISR */
void __vector_10(void)
{
	if(TCNT0_CallBackFptr[0] != NULL)
	{
		TCNT0_CallBackFptr[0]();
	}
}

/* Timer/counter 0 - Overflow ISR */

void __vector_11(void)
{
	if(TCNT0_CallBackFptr[1] != NULL)
	{
		TCNT0_CallBackFptr[1]();
	}
}
