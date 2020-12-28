/*
 * spi.c
 *
 *  Created on: Jul 17, 2020
 *      Author: mazen
 */


#include "../LIB/STD_TYPES.h"
#include "../LIB/BIT_CALC.h"
#include "../DIO/DIO_Interface.h"
#include "SPI_Config.h"
#include "SPI_Register.h"

static void (*CallBackFptr)(u8) = NULL;

void SPI_VidInit(void)
{

	// set mosi as output
	DIO_VidSetPinDirection(PORTB,MOSI,1);
	//set MISO as input
	DIO_VidSetPinDirection(PORTB,MISO,0);
	DIO_VidSetPinValue(PORTB,MISO,1); //for pull up resisitors
	//set SCK as output
	DIO_VidSetPinDirection(PORTB,SCK,1);
	DIO_VidSetPinDirection(PORTB,SS,1);



u8 SPCR_setting = 0 ;
//master or slave
SPCR_setting |= (MASTER_OR_SLAVE<<MSTR);

//interuupt enable/disable
SPCR_setting |= (SPI_Interrupt<<SPIE);

//data order
SPCR_setting |= (DATA_ORDER<<DORD) ;

#if PRESCALER == F_2 || PRESCALER == F_8 || PRESCALER == F_32

// prescaler
SPCR_setting = (SPCR_setting & 0xFC) | (PRESCALER&0x02);
SET_BIT(SPSR,SPI2X);

#else
// prescaler
SPCR_setting = (SPCR_setting & 0b11111100) | (PRESCALER);
CLR_BIT(SPSR,SPI2X);
#endif





#if DATA_MODE == MODE_0

CLR_BIT(SPCR_setting,CPOL);
CLR_BIT(SPCR_setting,CPHA);

#elif DATA_MODE == MODE_1

CLR_BIT(SPCR_setting,CPOL);
SET_BIT(SPCR_setting,CPHA);

#elif DATA_MODE == MODE_2

SET_BIT(SPCR_setting,CPOL);
CLR_BIT(SPCR_setting,CPHA);

#elif DATA_MODE == MODE_3

SET_BIT(SPCR_setting,CPOL);
SET_BIT(SPCR_setting,CPHA);

#endif



//enable SPI module
SET_BIT(SPCR_setting,SPE);

SPCR = SPCR_setting ;

}

void SPI_VidEnable(void)
{
	//enable SPI module
	SET_BIT(SPCR,SPE);
}

void SPI_VidDisable(void)
{
	//disable SPI module
	CLR_BIT(SPCR,SPE);
}



u8 SPI_u8TRX(u8 data)
{

	u8 dummy ;

	SPDR = data ;

	while(  GET_BIT(SPSR,SPIF) == 0 )
	{/*wait for transmission flag */}

	 //read SPSR to clear th flag

	dummy = SPSR ;
	dummy = SPDR ;

	return dummy ;
}


void SPI_VidSetCallBack( void (*LOCfptr)(u8))
{
	if(LOCfptr!=NULL)
	{
		CallBackFptr=LOCfptr;
	}
}


void __vector_12(void) __attribute__((signal));
void __vector_12(void)
{
	if(CallBackFptr != NULL)
	{
		CallBackFptr(SPDR);
	}
}





