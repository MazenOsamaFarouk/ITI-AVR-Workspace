/*
 * EXTI_Config.h
 *
 *  Created on: Dec 6, 2020
 *      Author: mazen
 */

#ifndef EXTI_EXTI_CONFIG_H_
#define EXTI_EXTI_CONFIG_H_

/* ************Peripheral Options*************  */

/* 1. choose which interrupts to enable/disable  */
#define INT0  DISABLE    /*on pin PD2 */
#define INT1  ENABLE    /*on pin PD3 */
#define INT2  DISABLE    /*on pin PB2 */

/* 2. choose trigger mode for each enabled interrupt*/

#define INT0_TRIG_MODE FALLING_EDGE
#define INT1_TRIG_MODE FALLING_EDGE
#define INT2_TRIG_MODE FALLING_EDGE


#endif /* EXTI_EXTI_CONFIG_H_ */
