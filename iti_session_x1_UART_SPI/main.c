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
// this function is just a wrapper function to our
// custom UART function that can send one byte
// the reason for the wrapping is the required prototype
// for this function, this prototype is required
// by the FDEV_SETUP_STREAM function
int usart_putchar_printf(char var, FILE *stream)
{
    UART_VidSendData((u8)var);
    return 0;
}

// this function connects the stream handler functions
// to a the returned stream (mystdout in this case)
// it takes 3 arguments:
// 1. a function that outputs a byte to the stream
// 2. a function that can take a byte as input from the stream
// 3. the stream mode, read, write or both
// the function returns a stream (FILE type)
static FILE mystdout = FDEV_SETUP_STREAM(usart_putchar_printf, NULL, _FDEV_SETUP_WRITE);





int main(void)
{
	// Setup our stdio stream:
	// here we used the Stream we created (mystdout) and
	//  "replaced" the stdout stream with our stream
	// so that when printf gets called, it uses our stream
	// (mystdout) not the default stdout
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

