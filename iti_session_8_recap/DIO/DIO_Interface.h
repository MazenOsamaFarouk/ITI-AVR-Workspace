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


#define DIO_PIN0 0
#define DIO_PIN1 1
#define DIO_PIN2 2
#define DIO_PIN3 3
#define DIO_PIN4 4
#define DIO_PIN5 5
#define DIO_PIN6 6
#define DIO_PIN7 7


#define OUTPUT 1
#define INPUT 0

#define DIO_PORTA 0
#define DIO_PORTB 1
#define DIO_PORTC 2
#define DIO_PORTD 3

#define PA0 MERGE_8(DIO_PORTA,DIO_PIN0)
#define PA1 MERGE_8(DIO_PORTA,DIO_PIN1)
#define PA2 MERGE_8(DIO_PORTA,DIO_PIN2)
#define PA3 MERGE_8(DIO_PORTA,DIO_PIN3)
#define PA4 MERGE_8(DIO_PORTA,DIO_PIN4)
#define PA5 MERGE_8(DIO_PORTA,DIO_PIN5)
#define PA6 MERGE_8(DIO_PORTA,DIO_PIN6)
#define PA7 MERGE_8(DIO_PORTA,DIO_PIN7)

#define PB0 MERGE_8(DIO_PORTB,DIO_PIN0)
#define PB1 MERGE_8(DIO_PORTB,DIO_PIN1)
#define PB2 MERGE_8(DIO_PORTB,DIO_PIN2)
#define PB3 MERGE_8(DIO_PORTB,DIO_PIN3)
#define PB4 MERGE_8(DIO_PORTB,DIO_PIN4)
#define PB5 MERGE_8(DIO_PORTB,DIO_PIN5)
#define PB6 MERGE_8(DIO_PORTB,DIO_PIN6)
#define PB7 MERGE_8(DIO_PORTB,DIO_PIN7)

#define PC0 MERGE_8(DIO_PORTC,DIO_PIN0)
#define PC1 MERGE_8(DIO_PORTC,DIO_PIN1)
#define PC2 MERGE_8(DIO_PORTC,DIO_PIN2)
#define PC3 MERGE_8(DIO_PORTC,DIO_PIN3)
#define PC4 MERGE_8(DIO_PORTC,DIO_PIN4)
#define PC5 MERGE_8(DIO_PORTC,DIO_PIN5)
#define PC6 MERGE_8(DIO_PORTC,DIO_PIN6)
#define PC7 MERGE_8(DIO_PORTC,DIO_PIN7)

#define PD0 MERGE_8(DIO_PORTD,DIO_PIN0)
#define PD1 MERGE_8(DIO_PORTD,DIO_PIN1)
#define PD2 MERGE_8(DIO_PORTD,DIO_PIN2)
#define PD3 MERGE_8(DIO_PORTD,DIO_PIN3)
#define PD4 MERGE_8(DIO_PORTD,DIO_PIN4)
#define PD5 MERGE_8(DIO_PORTD,DIO_PIN5)
#define PD6 MERGE_8(DIO_PORTD,DIO_PIN6)
#define PD7 MERGE_8(DIO_PORTD,DIO_PIN7)




void DIO_VidSetPinDirection(u8 LOC_u8Port, u8 LOC_u8Pin, u8 LOC_u8Mode );
void DIO_VidSetPinValue(u8 LOC_u8Port, u8 LOC_u8Pin, u8 LOC_u8Value );
void DIO_VidTogPinValue(u8 LOC_u8Port, u8 LOC_u8Pin);
u8 DIO_u8GetPinValue(u8 LOC_u8Port, u8 LOC_u8Pin );


void DIO_SetPinDirection(u8 LOC_u8PortPin, u8 LOC_u8Mode );
void DIO_SetPinValue(u8 LOC_u8PortPin, u8 LOC_u8Value );
void DIO_TogPinValue(u8 LOC_u8PortPin);
u8 DIO_GetPinValue(u8 LOC_u8PortPin );



void DIO_VidSetPortDirection(u8 LOC_u8Port,  u8 LOC_u8Mode );
void DIO_VidSetPortValue(u8 LOC_u8Port, u8 LOC_u8Value );
void DIO_VidInsPortValue(u8 LOC_u8Port,u8 LOC_u8Value, u8 LOC_u8No_bits, u8 LOC_u8offset);

u8 DIO_u8GetPortValue(u8 LOC_u8Port);






#endif /* DIO_INTERFACE_H_ */
