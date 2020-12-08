/*
 * EXT_INT_Interface.h
 *
 *  Created on: Jun 19, 2020
 *      Author: mazen
 */

#ifndef EXT_INT_INTERFACE_H_
#define EXT_INT_INTERFACE_H_


#include "../LIB/STD_TYPES.h"

/* general purpose enable/disable  defines*/
#ifndef ENABLE
#define ENABLE  1
#define DISABLE 0
#endif
/* defines for trigger mode options */

#define FALLING_EDGE 0
#define RISING_EDGE 1
#define ON_CHANGE  2
#define LOW_LEVEL 3

/* enable pin numbers for each interrupt */
#define INT0_EN  6
#define INT1_EN  7
#define INT2_EN  5


void EXTI_init(void);
void EXTI_enable(u8 int_id);
void EXTI_disable(u8 int_id);
void EXTI_SetCallBack(u8 int_id, void (*CBFunc)(void));



#endif /* EXT_INT_INTERFACE_H_ */
