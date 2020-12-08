/*
 * EXT_INT_Register.h
 *
 *  Created on: Jun 19, 2020
 *      Author: mazen
 */

#ifndef EXT_INT_REGISTER_H_
#define EXT_INT_REGISTER_H_



#define MCUCR  *((volatile u8 *) (0x55))
#define MCUCSR *((volatile u8 *) (0x54))
#define GICR   *((volatile u8 *) (0x5b))
#define GIFR   *((volatile u8 *) (0x5a))



void __vector_1(void) __attribute__((signal)) ;

#endif /* EXT_INT_REGISTER_H_ */
