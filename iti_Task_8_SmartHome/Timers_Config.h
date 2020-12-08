/*
 * Timers_Config.h
 *
 *  Created on: Jun 29, 2020
 *      Author: mazen
 */

#ifndef TIMERS_CONFIG_H_
#define TIMERS_CONFIG_H_


/*  general purpose Enable/Disable defines*/
#define ENABLE  1
#define DISABLE 0



/* Configuration settings for Timer 0 */

#ifndef F_CPU
	#define F_CPU 8000000   //Default for IMT-hardware Kit is 8 MHz crystal
#endif

/********* Timer/counter 0 config settings ************/
#define TCNT0_OP_MODE           TCNT0_CTC
#define TCNT0_CLK_SELECT        IO_PS_1024
#define OCM0_Interrupt          DISABLE
#define TCNT0_OVF_Interrupt     DISABLE
#define TCNT0_PRELOAD			0

#if TCNT0_OP_MODE==TCNT0_NORMAL || TCNT0_OP_MODE==TCNT0_CTC

#define COM0_NON_PWM       NORMAL_OC0_DISCONN

#elif TCNT0_OP_MODE==TCNT0_PWM || TCNT0_OP_MODE==TCNT0_FAST_PWM

#define COM0_PWM		   NORMAL_OC0_DISCONN

#endif

#if TCNT0_OVF_Interrupt==ENABLE && OCM0_Interrupt==DISABLE
	#define TCNT0_CALL_BACK  CB_TCNT0_OVF
#elif TCNT0_OVF_Interrupt==DISABLE && OCM0_Interrupt==ENABLE
	#define TCNT0_CALL_BACK  CB_TCNT0_CTC
#else
	#define TCNT0_CALL_BACK  2

#endif

/**********************************************************/

/****************** Timer/counter 1 config settings ********************/
#define TCNT1_OP_MODE          TCNT1_NORMAL
#define TCNT1_CLK_SELECT        IO_PS_256
#define OCM1A_Interrupt         DISABLE
#define OCM1B_Interrupt         DISABLE
#define TCNT1_IC_Interrupt		DISABLE
#define TCNT1_OVF_Interrupt		DISABLE
#define TCNT1_PRELOAD				0

#if TCNT1_OP_MODE==TCNT1_NORMAL || TCNT1_OP_MODE==TCNT1_CTC

#define COM1A_NON_PWM       NORMAL_OC1AB_DISCONN
#define COM1B_NON_PWM       NORMAL_OC1AB_DISCONN


#else

#define COM1A_PWM		    NORMAL_OC1AB_DISCONN
#define COM1B_PWM		    NORMAL_OC1AB_DISCONN

#endif


#endif /* TIMERS_CONFIG_H_ */
