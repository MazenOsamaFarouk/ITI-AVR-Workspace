/*
 * ADC_Register.h
 *
 *  Created on: Dec 7, 2020
 *      Author: mazen
 */

#ifndef ADC_ADC_REGISTER_H_
#define ADC_ADC_REGISTER_H_


/* Register definitions */
#define ADMUX   *((volatile u8*)(0x27))
#define ADCSRA  *((volatile u8*)(0x26))

#define ADCH    *((volatile u8*)(0x25))
#define ADCL    *((volatile u8*)(0x24))

#define ADC_DATA *((volatile u16*)(0x24)) //pointer to the LOW byte only
									     // its treated as u16 because they are
										//  two consecutive memory addresses
#define SFIOR   *((volatile u16*)(0x50))

/* END OF Register definitions */

/* Reference voltage selection */
#define AREF 0
#define AVCC 1
#define INTERNAL_REF 2


/*  data represenstion in ADCH and ADCL*/
#define LEFT_ADJUST 0
#define RIGHT_ADJUST 1

/* General purpose Enable or Disable macros */

#define ENABLE  1
#define DISABLE 0


/* Auto trigger modes    */
#define FREE_RUNNING (0x00<<5)
#define ANALOG_COMP  (0x01<<5)
#define EXT_INT0     (0x02<<5)
#define TCNT0_CM     (0x03<<5)
#define TCNT0_OVF    (0x04<<5)
#define TCNT1_CMB    (0x05<<5)
#define TCNT1_OVF    (0x06<<5)
#define TCNT1_CE     (0x07<<5)


#define ADIF 4  //ADC interrupt flag bit
#define ADIE 3  //ADC interrupt mode Enable bit

/* PRescaler selection  */

#define PS_2     0x01
#define PS_4     0x02
#define PS_8     0x03
#define PS_16    0x04
#define PS_32    0x05
#define PS_64    0x06
#define PS_128   0x07


/* ADC control bits*/

#define ADSC 6 //ADC start conversion bit
#define ADEN 7   //ADC peripheral enable bit

#define CLEAR_ADIF() SET_BIT(ADCSRA,ADIF)


#endif /* ADC_ADC_REGISTER_H_ */
