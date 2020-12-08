/*
 * GIF_Interface.h
 *
 *  Created on: Jun 19, 2020
 *      Author: mazen
 */

#ifndef GIE_INTERFACE_H_
#define GIE_INTERFACE_H_


/*   Global Interrupt Enable/disable from SREG register*/
/*  done by either setting/clearing the I-bit  */


void GIE_enable(void);
void GIE_disable(void);

#endif /* GIE_INTERFACE_H_ */
