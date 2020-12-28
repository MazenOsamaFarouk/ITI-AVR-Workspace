/*
 * UART_Interface.h
 *
 *  Created on: Jul 10, 2020
 *      Author: mazen
 */

#ifndef UART_INTERFACE_H_
#define UART_INTERFACE_H_

//#include "STD_TYPES.h"


#define CB_TX  0
#define CB_RX  1
#define CB_EMP 2


void UART_VidInit(void);
void UART_VidSendData(u8 data);
u16 UART_u16ReadData(void);
void UART_VidFlushBuffer(void);
void UART_VidSetBaudRate(u16 baud);
void UART_VidTXSetCallBack(void (*LOC_fptr)(void));
void UART_VidRXSetCallBack(void (*LOC_fptr)(u8));

 void UART_printf(char* string);
 void UART_scanf(char string[], u16 size);

/* buffered functions */
u8 UART_GetData(void);



#endif /* UART_INTERFACE_H_ */
