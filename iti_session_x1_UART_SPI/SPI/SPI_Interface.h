/*
 * spi_Interface.h
 *
 *  Created on: Jul 17, 2020
 *      Author: mazen
 */

#ifndef SPI_INTERFACE_H_
#define SPI_INTERFACE_H_

#include "STD_TYPES.h"


void SPI_VidInit(void);
void SPI_VidEnable(void);
void SPI_VidDisable(void);
u8 SPI_u8TRX(u8 data);
void SPI_VidSetCallBack( void (*LOCfptr)(u8));

#endif /* SPI_INTERFACE_H_ */
