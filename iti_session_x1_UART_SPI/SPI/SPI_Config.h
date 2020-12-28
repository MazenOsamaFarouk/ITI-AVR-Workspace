/*
 * spi_Config.h
 *
 *  Created on: Jul 17, 2020
 *      Author: mazen
 */

#ifndef SPI_CONFIG_H_
#define SPI_CONFIG_H_


/* SPI Module Options */
#define ENABLE  1
#define DISABLE 0

#define MSB_1st 0
#define LSB_1st 1

#define MASTER 1
#define SLAVE  0

// Avaiable prescalers

#define F_4  	0
#define F_16 	1
#define F_64 	2
#define F_128	3
#define F_2 	4
#define F_8		5
#define F_32	6


//avialable modes
#define MODE_0 0
#define MODE_1 1
#define MODE_2 2
#define MODE_3 3


/* SPI module configuration */

#define MASTER_OR_SLAVE				MASTER

#define PRESCALER					F_64


/* DATA MODES */
/* ---------- */
/* CPOL CPHA | MODE  */
/*   0    0  |  0    */
/*   0    1  |  1    */
/*   1    0  |  2    */
/*   1    1  |  3    */
#define DATA_MODE					MODE_0

#define SPI_Interrupt				DISABLE

#define DATA_ORDER 					LSB_1st





#endif /* SPI_CONFIG_H_ */
