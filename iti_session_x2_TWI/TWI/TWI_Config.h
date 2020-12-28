/*
 * TWI_Config.h
 *
 *  Created on: Dec 28, 2020
 *      Author: mazen
 */

#ifndef TWI_CONFIG_H_
#define TWI_CONFIG_H_


#ifndef FCPU
#define FCPU 8000000
#endif

#define SCL_FREQ   400000


#define ENABLE  1
#define DISABLE 0



/*  			CONFIGS					 */


#define I2C_Enable   				ENABLE
#define I2C_Interrupt_Enable		DISABLE

#define PRESCALER   				PS_1




#endif /* I2C_CONFIG_H_ */
