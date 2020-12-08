/*
 * ADC.h
 *
 *  Created on: Jun 20, 2020
 *      Author: mazen
 */

#ifndef ADC_H_
#define ADC_H_





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
