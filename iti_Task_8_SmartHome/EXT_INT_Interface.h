/*
 * EXT_INT_Interface.h
 *
 *  Created on: Jun 19, 2020
 *      Author: mazen
 */

#ifndef EXT_INT_INTERFACE_H_
#define EXT_INT_INTERFACE_H_

/* general purpose enable/disable  defines*/
#define ENABLE  1
#define DISABLE 0

/* defines for trigger mode options */

#define FALLING_EDGE 0
#define RISING_EDGE 1
#define ON_CHANGE  2
#define LOW_LEVEL 3

/* enable pin numbers for each interrupt */
#define INT0_EN  6
#define INT1_EN  7
#define INT2_EN  5


/* ************Peripheral Options*************  */

/* 1. choose which interrupts to enable/disable  */
#define INT0  ENABLE    /*on pin PD2 */
#define INT1  ENABLE    /*on pin PD3 */
#define INT2  ENABLE    /*on pin PB2 */

/* 2. choose trigger mode for each enabled interrupt*/

#define INT0_TRIG_MODE FALLING_EDGE
#define INT1_TRIG_MODE FALLING_EDGE
#define INT2_TRIG_MODE FALLING_EDGE


void EXT_INT_init(void);
void EXT_INT_enable(u8 int_id);
void EXT_INT_disable(u8 int_id);


/* ********ISR definitions********* */

#define ISR_EXT_INT_0() \
	void __vector_1(void) __attribute__((signal)); \
	void __vector_1(void)

#define ISR_EXT_INT_1() \
	void __vector_2(void) __attribute__((signal)); \
	void __vector_2(void)

#define ISR_EXT_INT_2() \
	void __vector_3(void) __attribute__((signal)); \
	void __vector_3(void)


#endif /* EXT_INT_INTERFACE_H_ */
