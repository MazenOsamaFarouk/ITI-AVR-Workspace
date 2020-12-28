/*
 * UART_Config.h
 *
 *  Created on: Jul 10, 2020
 *      Author: mazen
 */

#ifndef UART_CONFIG_H_
#define UART_CONFIG_H_

#define ENABLE 1
#define DISABLE 0
#define YES 1
#define NO 0

#define EVEN  2
#define ODD   3

#define SYNC  1
#define ASYNC 0

#define RISING_TX  0
#define FALLING_TX 1

#ifndef FCPU
#define FCPU   8000000 //8 MHz is the cystral for IMT kit
#endif

/* ************ Configurations ************** */

/* MODE can be either: */
/* SYNC  -  ASYNC */
#define MODE  ASYNC


/* DATA SIZE can either be one of the following */
/* 5 - 6 - 7 - 8 - 9 */
#define DATA_SIZE   8

/* PARITY can either be : */
/* EVEN - ODD - DISABLE */
#define PARITY   DISABLE


/* STOP BITS can either be: */
/* 1  - 2 */
#define STOP_BITS   1

/* List of allowed BAUD rates in (bits/sec) */
/* 2400
 * 4800
 * 9600
 * 14400
 * 19200
 * 28800
 * 38400
 * 57600
 * 76800
 * 115200
 * 230400
 * 250000 */
#define BAUD    9600


#define TRANSMIT    ENABLE

#define RECEIVE     ENABLE

#define TX_INT		DISABLE

#define RX_INT		DISABLE

#define UDR_EMPTY_INT   DISABLE

#if RX_INT==ENABLE
	#define USE_BUFFER		YES
	#define BUFFERSIZE      20
#endif

/* *********** Special Configs ***************/
#define DOUBLE_SPEED    DISABLE

#define MULTI_PROC_MODE  DISABLE

/* for SYNC mode only */
/* can either be: */
/*
 * RISING_TX - FALLING_TX
 *
 * NOTE: rising edge on TX is Falling Eage on RX */
#define XCK_PIN_MODE  RISING_TX

#endif /* UART_CONFIG_H_ */
