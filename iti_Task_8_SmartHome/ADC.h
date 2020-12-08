/*
 * ADC.h
 *
 *  Created on: Jun 20, 2020
 *      Author: mazen
 */

#ifndef ADC_H_
#define ADC_H_

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


/********ALL ADC INIT OPTIONS**********/

/* 1. Select Reference Voltage*/
#define REF_VOLT_SELECT    AVCC

/* 2. Data representation Left to Right*/
#define DATA_ADJUST     RIGHT_ADJUST

/* 3. Auto Trigger modes and Enable/disable */
#define AUTO_TRIGGER      ENABLE

#if AUTO_TRIGGER==ENABLE
#define TRIGGER_SOURCE   TCNT0_CM
#endif

/* 4. Prescaler value selection */
#define PRESCALER          PS_64

/* 5. Enable/disable interrupts */
#define ADC_INTERRUPT     ENABLE









#define CLEAR_ADIF() SET_BIT(ADCSRA,ADIF)




void ADC_VidInit(void);

void ADC_VidEnable(void);

void ADC_VidDisable(void);

void ADC_VidEnableInterrupt(void);

void ADC_VidDisableInterrupt(void);


u16  ADC_u16GetAnalogValue(u8 channel_select);

u16 ADC_u16AnalogRead(u8 channel_select);

void ADC_VidAnalogRead_Batch(u8 input_channels_array[], u16 output_array[], u8 No_channels);


void ADC_VidStartConversion(u8 channel_select);

void ADC_VidSelectChannel(u8 channel_select);


void ADC_VidSetCallBack(  void (*LOC_fptr)(u16)  ) ;


#endif /* ADC_H_ */
