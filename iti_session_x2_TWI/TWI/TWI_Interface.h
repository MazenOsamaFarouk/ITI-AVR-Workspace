/*
 * TWI_Interface.h
 *
 *  Created on: Dec 28, 2020
 *      Author: mazen
 */

#ifndef TWI_INTERFACE_H_
#define TWI_INTERFACE_H_

#include "../LIB/STD_TYPES.h"


#define TWI_READ  1
#define TWI_WRITE 0


#define TWI_TX_FAIL      0
#define TWI_TX_SUCCESS   1
#define TWI_RX_FAIL      0
#define TWI_RX_SUCCESS   1


#define TWI_CLR_INT_FLAG()	TWCR = (1<<TWINT)|(1<<TWEN)
#define TWI_START()			TWCR = (1<<TWINT)|(1<<TWSTA)|(1<<TWEN)
#define TWI_STOP()			TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWSTO)
#define TWI_ACK()			TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWEA)
#define TWI_NACK()			CLR_BIT(TWCR,BIT(TWEA))
#define TWI_CheckFlag()		GET_BIT(TWCR,TWINT)

u8 TWI_u8GetStatus(void);
u8 TWI_u8CheckIfBusy(void);
void TWI_VidEnableInterrupt(void);
void TWI_VidDisableInterrupt(void);
void TWI_VidSetBitRate(u32 bit_rate);
void TWI_VidInit(void);
u8 TWI_SendSlaveAddress(u8 slave_addr, u8 rw);
u8 TWI_SendData(u8 data);
u8 TWI_ReadData(void);
u8 TWI_Start_TRX(void);
u8 TWI_RepeatedStart_TRX(void);
u8 TWI_Stop_TRX(void);
u8 TWI_SendLast(void);
u8 TWI_Master_TX(u8 data, u8 slave_addr);
u8 TWI_Master_RX(u8 slave_addr);













#endif /* TWI_INTERFACE_H_ */
