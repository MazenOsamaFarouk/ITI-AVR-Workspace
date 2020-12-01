/*
 * dio.h
 *
 *  Created on: Nov 25, 2020
 *      Author: mazen
 */
#include <avr/io.h>
#include "../LIB/STD_TYPES.h"
#include "../LIB/BIT_CALC.h"



#ifndef DIO_DIO_H_
#define DIO_DIO_H_

#define HIGH 1
#define LOW  0

void DIO_SetPin(u8 LOC_u8Port, u8 LOC_u8Pin, u8 LOC_u8Value );

#endif /* DIO_DIO_H_ */
