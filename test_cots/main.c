/*
 * main.c
 *
 *  Created on: Nov 25, 2020
 *      Author: mazen
 */

//#include <avr/io.h>

#include "dio/dio.h"

#include <util/delay.h>


int main(void)
{

DIO_SetPin(PORTA,0,HIGH);

	return 0;
}
