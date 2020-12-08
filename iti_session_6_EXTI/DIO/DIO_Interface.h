/*
 * DIO_Interface.h
 *
 *  Created on: May 30, 2020
 *      Author: mazen
 */

#ifndef DIO_INTERFACE_H_
#define DIO_INTERFACE_H_


#include "../LIB/STD_TYPES.h"


// MERGE_8: merges two 4 bit numbers into one 8-bit number
// 	-msb: the 4 Most-significant bits
//  -lsb: the 4 Least-significant bits
#define MERGE_8(msb,lsb)   ((msb<<4)|(lsb))


/* Use GET_PORT macro to EXTRACT the PORT ID from
 * a given 8 bit number								*/
#define GET_PORT(num_8bit)  (num_8bit>>4)

/* Use GET_PIN macro to EXTRACT the PIN ID from
 * a given 8 bit number								*/
#define GET_PIN(num_8bit)	(num_8bit&0x0f)

// MERGE_4: merges two 2 bit numbers into one 4-bit number
// 	-msb: the 2 Most-significant bits
//  -lsb: the 2 Least-significant bits
#define MERGE_4(msb,lsb)   ((msb<<2)|lsb)


#define PIN0 0
#define PIN1 1
#define PIN2 2
#define PIN3 3
#define PIN4 4
#define PIN5 5
#define PIN6 6
#define PIN7 7


#define OUTPUT 1
#define INPUT 0

#define PORTA 0
#define PORTB 1
#define PORTC 2
#define PORTD 3

#define PA0 MERGE_8(PORTA,PIN0)





void DIO_VidSetPinDirection(u8 LOC_u8Port, u8 LOC_u8Pin, u8 LOC_u8Mode );
void DIO_VidSetPinValue(u8 LOC_u8Port, u8 LOC_u8Pin, u8 LOC_u8Value );
void DIO_VidTogPinValue(u8 LOC_u8Port, u8 LOC_u8Pin);



u8 DIO_u8GetPinValue(u8 LOC_u8Port, u8 LOC_u8Pin );

void DIO_VidSetPortDirection(u8 LOC_u8Port,  u8 LOC_u8Mode );
void DIO_VidSetPortValue(u8 LOC_u8Port, u8 LOC_u8Value );
void DIO_VidInsPortValue(u8 LOC_u8Port,u8 LOC_u8Value, u8 LOC_u8No_bits, u8 LOC_u8offset);

u8 DIO_u8GetPortValue(u8 LOC_u8Port);






#endif /* DIO_INTERFACE_H_ */
