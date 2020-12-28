/*
 * TWI_Register.h
 *
 *  Created on: Jul 18, 2020
 *      Author: mazen
 */

#ifndef TWI_REGISTER_H_
#define TWI_REGISTER_H_


#define TWINT  		7
#define TWEA  		6
#define TWSTA		5
#define TWSTO		4
#define TWWC		3
#define TWEN 		2
////RESERVED////	1
#define TWIE		0




#define PS_1   0x00
#define PS_4   0x01
#define PS_16  0x02
#define PS_64  0x03


#define MASTER_TX_MODE	1
#define MASTER_RX_MODE	2
#define SLAVE_TX_MODE	3
#define SLAVE_RX_MODE	4

 /*         MATER TX_RX STATUS CODES        */
#define TWI_START_COND				0x08
#define TWI_REP_START				0x10
#define TWI_MTX_SLAW_ACK			0x18
#define TWI_MTX_SLAW_NACK			0x20
#define TWI_MTX_SLAR_ACK			0x40
#define TWI_MTX_SLAR_NACK			0x48
#define TWI_MTX_DATA_ACK			0x28
#define TWI_MTX_DATA_NACK			0x30
#define TWI_MRX_DATA_ACK			0x50
#define TWI_MRX_DATA_NACK			0x58
#define TWI_ARB_LOST				0x38


/*         SLAVE TX_RX STATUS CODES           */
#define SLAW_RX_ACK_TX				0x60
#define SLAR_RX_ACK_TX				0xA8
#define ARBIT_LOST_SLAW				0x68
#define ARBIT_LOST_SLAR				0xB0
#define GENREALCALL_RX_ACK_TX		0x70
#define ARBIT_LOST_GEN_CALL_RX		0x78
#define SELF_DATA_RX_ACK_TX			0x80
#define SELF_DATA_TX_ACK_RX			0xB8
#define SELF_DATA_RX_NACK_TX		0x88
#define SELF_DATA_TX_NACK_RX		0xC0
#define LAST_DATA_TX_ACK_RX			0xC8
#define GENCALL_DATA_RX_ACK_TX		0x90
#define GENCALL_DATA_RX_NACK_TX		0x98
#define TWI_STOP_COND				0xA0
#define REPEATED_START_COND			0xA0

/* 				OTHER STATES			 */
#define BUS_ERROR					0x00
#define NO_INFO						0xF8





#define TWCR (*(volatile u8 *)(0x56))
#define TWDR (*(volatile u8 *)(0x23))
#define TWAR (*(volatile u8 *)(0x22))
#define TWSR (*(volatile u8 *)(0x21))
#define TWBR (*(volatile u8 *)(0x20))




#endif /* TWI_REGISTER_H_ */
