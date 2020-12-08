/*
 * ADC_Config.h
 *
 *  Created on: Dec 7, 2020
 *      Author: mazen
 */

#ifndef ADC_ADC_CONFIG_H_
#define ADC_ADC_CONFIG_H_


/********ALL ADC INIT OPTIONS**********/

/* 1. Select Reference Voltage*/
/* Reference voltage Options */
/******************************
   {  AREF  AVCC  INTERNAL_REF  }
*/
#define REF_VOLT_SELECT    AVCC

/* 2. Data representation Left to Right*/
/* options
 * ***********/
/* {  LEFT_ADJUST RIGHT_ADJUST }
 */
#define DATA_ADJUST     RIGHT_ADJUST

/* 3. Auto Trigger modes and Enable/disable */
#define AUTO_TRIGGER      DISABLE

#if AUTO_TRIGGER==ENABLE
/*
 * TRIGGER SOURCE Options
 * ************************
 FREE_RUNNING
 ANALOG_COMP
 EXT_INT0
 TCNT0_CM
 TCNT0_OVF
 TCNT1_CMB
 TCNT1_OVF
 TCNT1_CE
*/
#define TRIGGER_SOURCE   TCNT0_CM
#endif

/* 4. Prescaler value selection */
/* Prescaler selection options  */
/********************************
 { PS_2  PS_4   PS_8  PS_16  PS_32  PS_64  PS_128 }
*/
#define PRESCALER          PS_64

/* 5. Enable/disable interrupts */
#define ADC_INTERRUPT     DISABLE


#endif /* ADC_ADC_CONFIG_H_ */
