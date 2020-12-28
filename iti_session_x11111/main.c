/*
 * main.c
 *
 *  Created on: Dec 22, 2020
 *      Author: mazen
 */

#include "LIB/STD_TYPES.h"
#include "LIB/BIT_MAN.h"

#include <stdio.h>
#include <util/delay.h>

#include "DIO/DIO_Interface.h"
#include "UART/UART_Interface.h"

// this function is called by printf as a stream handler
int usart_putchar_printf(char var, FILE *stream)
{
    UART_VidSendData((u8)var);
    return 0;
}

static FILE mystdout = FDEV_SETUP_STREAM(usart_putchar_printf, NULL, _FDEV_SETUP_WRITE);


int main(void)
{
	// setup our stdio stream
	stdout = &mystdout;


	UART_VidInit();


	for(int i=0; i<10; i++)
	{
		printf("this is the %d line\n",i+1);
		_delay_ms(1000);
	}

	while(1)
	{


	}

return 0;
}

