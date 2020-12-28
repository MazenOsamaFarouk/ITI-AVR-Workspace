/*
 * main.c
 *
 *  Created on: Dec 28, 2020
 *      Author: mazen
 */

#include "LIB/STD_TYPES.h"
#include "LIB/BIT_MAN.h"
#include <util/delay.h>
#include "DIO/DIO_Interface.h"
#include "TWI/TWI_Interface.h"
#include "UART/UART_Interface.h"

#define EEPROM_ADDR  0b01010000

void EEPROM_WriteByte(u8 byte, u16 addr)
{
//	UART_printf("Write Byte Called");
	TWI_Start_TRX();
//	UART_printf("Start condition sent");
	TWI_SendSlaveAddress((EEPROM_ADDR|(0x03&(addr>>8))),TWI_WRITE);
//	UART_printf("Slave Address sent");
	TWI_SendData((u8)addr);
//	UART_printf("Data Sent\r\n");
	TWI_SendData(byte);
//	UART_printf("Data Sent\r\n");
	TWI_Stop_TRX();
	UART_printf("Write Byte Done");
}

u8 EEPROM_ReadByte(u16 addr)
{
//	UART_printf("Read Byte Called\r\n");
	u8 byte = 0;
	TWI_Start_TRX();
//	UART_printf("Start condition sent");
	TWI_SendSlaveAddress(0b01010000,TWI_WRITE);
//	UART_printf("Slave Address sent");
	TWI_SendData((u8)addr);
//	UART_printf("Data Sent\r\n");
	TWI_RepeatedStart_TRX();
//	UART_printf("Repeated Start condition sent");
	TWI_SendSlaveAddress(0b01010000,TWI_READ);
	UART_printf("Slave Address sent\r\n");
	byte = TWI_ReadData();
	UART_printf("byte reading done\r\n");
	TWI_Stop_TRX();
	UART_printf("READ byte done");
	return byte;
}


int main(void)
{
	u8 c1;
	u8 c2;
	UART_VidInit();
	TWI_VidInit();

	UART_printf("Enter a charachter:\r\n");
	c1=UART_u8ReadData();
	UART_printf("Charachter recieved\r\n");

	EEPROM_WriteByte(c1,2);
	_delay_ms(100);
	c2=EEPROM_ReadByte(2);

	if(c1==c2)
	{
		UART_printf("EEPROM Success Write and Read\r\n");
	}
	else
	{
		UART_printf("EEPROM Failed\r\n");
	}

	while(1)
	{


	}

return 0;
}

