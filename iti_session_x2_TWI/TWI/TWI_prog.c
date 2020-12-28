/*
 * TWI_prog.c
 *
 *  Created on: Dec 28, 2020
 *      Author: mazen
 */


#include "../LIB/STD_TYPES.h"
#include "../LIB/BIT_MAN.h"
#include "../DIO/DIO_Interface.h"
#include "TWI_Config.h"
#include "TWI_Interface.h"
#include "TWI_Register.h"


u8 lastTransOK = 0 ;

u8 TWI_u8GetStatus(void)
{
	return (TWSR&0xF8) ;
}

u8 TWI_u8CheckIfBusy(void)
{

return 0 ;
}

void TWI_VidEnableInterrupt(void)
{
	SET_BIT(TWCR,BIT(TWEN)|BIT(TWINT));
}

void TWI_VidDisableInterrupt(void)
{
	CLR_BIT(TWCR,TWINT);
}




void TWI_VidSetBitRate(u32 bit_rate)
{
	u32 TWBR_VAL = 0 ;

	u32 DIV = FCPU/bit_rate ;

	TWBR_VAL = (DIV - 16)>>( (2*PRESCALER) +1 ) ;

	if(TWBR_VAL<10)
	{

	}
	TWBR = (u8)TWBR_VAL;
	TWBR = 32;


}




void TWI_VidInit(void)
{

/*  Enable of I2C Interrupt */

#if TWI_Interrupt_Enable == ENABLE
	SET_BIT(TWCR,TWIE );
#elif TWI_Interrupt_Enable == DISABLE
	CLR_BIT(TWCR,TWIE);
#endif
/* set bit rate */

	TWI_VidSetBitRate(SCL_FREQ);

/* Enable of I2C */


#if TWI_Enable == ENABLE
SET_BIT(TWCR , TWEN);

#elif TWI_Enable == DISABLE
CLR_BIT(TWCR , TWEN);

#endif


///TWDR = 0xFF ; //default value on bus (bec 1 is the recessive bit)

}

u8 TWI_SendSlaveAddress(u8 slave_addr, u8 rw)
{
	u8 status = 0;

	TWDR = (slave_addr<<1) | rw ; // OR with 0x00 for Write operation

		/* as soon as the flag is cleared transmission begins */
//		CLR_BIT(TWCR,BIT(TWSTA));
		TWI_CLR_INT_FLAG();
		//4. wait for flag to set
		/*wait for flag */
		while(TWI_CheckFlag() == 0)
		{/*wait for slave address to be sent */}
		status = TWI_u8GetStatus();
		return status ;
}

u8 TWI_SendData(u8 data)
{
	u8 status = 0;
	/*load data in TWDR */
	TWDR = data ;
	TWI_CLR_INT_FLAG();
	/*wait for flag */
	while(TWI_CheckFlag() == 0)
	{/*wait for data to be transmitted */}
	status = TWI_u8GetStatus();
	return status ;
}

u8 TWI_ReadData(void)
{
//	TWI_CLR_INT_FLAG();
	TWCR = (1<<TWINT);
	/*wait for flag */
	while(TWI_CheckFlag() == 0)
	{/*wait for data to be recieved */}

	/*read data from TWDR */
	return TWDR ;
}

u8 TWI_Start_TRX(void)
{
	u8 status = 0;
//send a start condition signal
	TWI_START();

	/*wait for flag */
	while(TWI_CheckFlag() == 0)
	{/*wait for start condition */}
	status = TWI_u8GetStatus();
	return status ;

}

u8 TWI_RepeatedStart_TRX(void)
{
	u8 status = 0;
//send a start condition signal
	TWI_START();

	/*wait for flag */
	while(TWI_CheckFlag() == 0)
	{/*wait for start condition */}
	status = TWI_u8GetStatus();
	return status ;
}


u8 TWI_Stop_TRX(void)
{
	u8 status = 0;
	TWI_STOP();
	status = TWI_u8GetStatus();
	return status ;
}

u8 TWI_SendLast(void)
{
	u8 status = 0;

	// if there was a problem sending the last
	// byte of data:
	//send a start condition signal
	TWI_START();
	/*wait for flag */
	while(TWI_CheckFlag() == 0)
	{/*wait for start condition */}

	status = TWI_u8GetStatus();
	return status ;
}


u8 TWI_Master_TX(u8 data, u8 slave_addr)
{
	u8 status = 0 ;

	// 1. start condition
	status = TWI_Start_TRX();
	// 2. wait for flag to set (this happens inside TWI_Start_TRX() )
	// 3. check TWSR, load SLA+W in TWDR , Send SLA+W
	if(status != TWI_START_COND){ return TWI_TX_FAIL; }

	status = TWI_SendSlaveAddress(slave_addr, 1); // rw = 1 -> write operation
	//4. wait for flag to set (this happens inside TWI_SlaveAddr() )
	//5. check TWSR, load data in TWDR, send data
	if(status != TWI_MTX_SLAW_ACK){ return TWI_TX_FAIL; }

	status = TWI_SendData(data);
	//6.wait for flag to set (this happens inside TWI_SendData() )
	//7. check TWSR , send STOP cond
	if(status != TWI_MTX_DATA_ACK){ return TWI_TX_FAIL; }

	TWI_Stop_TRX();

	lastTransOK = 1 ;
	return TWI_TX_SUCCESS;



}
u8 TWI_Master_RX(u8 slave_addr)
{
	u8 status = 0 ;
	u8 rx = 0 ;
	// 1. start condition
	status = TWI_Start_TRX();
	// 2. wait for flag to set (this happens inside TWI_Start_TRX() )
	// 3. check TWSR, load SLA+R in TWDR , Send SLA+R
	if(status != TWI_START_COND){ return TWI_TX_FAIL; }

	status = TWI_SendSlaveAddress(slave_addr, 0); // rw = 0 -> read operation
	//4. wait for flag to set (this happens inside TWI_SlaveAddr() )
	//5. check TWSR, read data in TWDR, send ACK to slave
	if(status != TWI_MTX_SLAR_ACK){ return TWI_TX_FAIL; }

	rx = TWI_ReadData();
	TWI_ACK();
	status = TWSR ;
	//6.wait for flag to set (this happens inside TWI_SendData() )
	//7. check TWSR , send STOP cond
	if(status != TWI_MRX_DATA_ACK){ return TWI_TX_FAIL; }

	TWI_STOP();


	return rx;

	return 0 ;
}
