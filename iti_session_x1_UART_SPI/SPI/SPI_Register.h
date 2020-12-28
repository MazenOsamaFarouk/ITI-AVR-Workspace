/*
 * spi_Register.h
 *
 *  Created on: Jul 17, 2020
 *      Author: mazen
 */

#ifndef SPI_REGISTER_H_
#define SPI_REGISTER_H_

#define SS		4
#define MOSI	5
#define MISO	6
#define SCK		7

#define SPIE 7  // interrupt enable bit
#define SPE  6	// spi module enable bit
#define DORD 5  //data order bit
#define MSTR 4  //Master slave select bit
#define CPOL 3  //clock polarity
#define CPHA 2  //cloack phase


#define SPIF 7  // SPI interrupt flag

#define WCOL 6  // Write COLlision Flag

#define SPI2X 0

#define SPCR *((volatile u8 *)(0x2D))

#define SPDR *((volatile u8 *)(0x2F))

#define SPSR *((volatile u8 *)(0x2E))

#endif /* SPI_REGISTER_H_ */
