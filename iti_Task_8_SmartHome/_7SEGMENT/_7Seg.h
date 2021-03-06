/*
 * _7Seg.h
 *
 *  Created on: Jun 5, 2020
 *      Author: mazen
 */

#ifndef _7SEG_H_
#define _7SEG_H_

#define ARM_STM32F10XX  1
#define AVR_ATMEGA32A	0


#define MCU  AVR_ATMEGA32A


#if MCU == AVR_ATMEGA32A
#define _7SEG_PORT PORTC
#endif


typedef enum
{
	COM_CATHODE,
	COM_ANODE
}_7SEG_TYPE;

typedef struct
{
	u8 port;
	u8 pin;
}_7SEG_PIN;



typedef struct
{
	_7SEG_PIN *pins;
	_7SEG_TYPE type;
}_7Seg;

///  Connections
///  PORTx:  bit-7 bit-6 bit-5 bit-4 bit-3 bit-2 bit-1 bit-0
///  7-SEG:   dot     G     F     E     D     C     B     A

#define ZERO  	0b00111111
#define ONE   	0b00000110
#define TWO   	0b01011011
#define THREE 	0b01001111
#define FOUR  	0b01100110
#define FIVE  	0b01101101
#define SIX   	0b01111101
#define SEVEN 	0b00000111
#define EIGHT 	0b01111111
#define NINE  	0b01101111
//hex digits
#define A 		0b01110111
#define b 		0b01111100
#define c 		0b01011100
#define d 		0b01011110
#define E 		0b01111001
#define F 		0b01110001

#define DOT   	0b10000000




extern const u8 seven_seg_digits[];
#if MCU == AVR_ATMEGA32A
void _7SEG_VidInit(_7Seg* me);
#elif MCU == ARM_STM32F10XX
void _7SEG_VidInit(_7SEG_PIN pin_array[]);
#endif
void _7SEG_VidDisplayNum(_7Seg* me,u8 num);
void _7SEG_VidDisplayVal(_7Seg* me,u8 value);
void _7SEG_VidDisplayOff(_7Seg* me);



#endif /* 7SEG_H_ */
