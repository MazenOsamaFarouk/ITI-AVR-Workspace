/*
 * ADC.c
 *
 *  Created on: Jun 20, 2020
 *      Author: mazen
 */


#include "STD_TYPES.h"
#include "BIT_CALC.h"
#include "DIO_Interface.h"
#include "ADC.h"

static void (*CallBackFuncPtr)(u16) = NULL ;


void ADC_VidInit(void)
{
	// 1. select reference voltage
	// these are bits 6,7  in ADMUX register
	// according to the following table ATmega32A datasheet-ADC register description section
	//--------------------------------
	// bit-7   |   bit-6  | selection
	// -------------------------------
	//   0     |     0    | AREF-external Voltage reference using the AREF pin
	//   0     |     1    | AVCC-internal VCC - 5v
	//   1     |     0    | reserved-DO NOT USE
	//   1     |     1    | internal 2.56v voltage reference
	// --------------------------------

#if  REF_VOLT_SELECT == AREF
	CLR_BIT(ADMUX,6);
	CLR_BIT(ADMUX,7);
#elif REF_VOLT_SELECT == AVCC
	SET_BIT(ADMUX,6);
	CLR_BIT(ADMUX,7);
#elif REF_VOLT_SELECT == INTERNAL_REF
	SET_BIT(ADMUX,6);
	SET_BIT(ADMUX,7);
#else
#error "ADC_init():reference voltage not selected"
#endif


	//2.Left or right adjust
	// bit-5 ADLAR bit in ADMUX controls left/right adjustment of the data
	// inside ADCH and ADCL , ADLAR = 0-> right adjusted
#if  DATA_ADJUST==RIGHT_ADJUST
	CLR_BIT(ADMUX,5);
#elif  DATA_ADJUST == LEFT_ADJUST
	SET_BIT(ADMUX,5);
#endif
	//3. auto trigger enable
	// if disabled, you have to manually start the conversion every time
	//  you want to start an analog conversion
	// if enabled, a selection must be made to the trigger source
	// that starts the conversion

	/////  3.a. enable or disable auto trigger ?

#if AUTO_TRIGGER == DISABLE
	CLR_BIT(ADCSRA,5);
#elif AUTO_TRIGGER == ENABLE
	SET_BIT(ADCSRA,5);

	/////  3.b. choose trigger source

	SFIOR = (SFIOR & 0x1F) | TRIGGER_SOURCE ;


#endif

	//4. clear interrupt flag
	// ADIF is cleared by writing a 1 to it
	SET_BIT(ADCSRA,ADIF);

	//5. enable/disable interrupts
#if ADC_INTERRUPT == DISABLE

	CLR_BIT(ADCSRA,ADIE);

#elif ADC_INTERRUPT == ENABLE

	SET_BIT(ADCSRA,ADIE);
#endif

	//6. select Prescaler value


	ADCSRA = (ADCSRA & 0xF8) | PRESCALER ;



	//7. Enable ADC
	SET_BIT(ADCSRA,ADEN);


}

void ADC_VidEnable(void)
{
	// Enable ADC
		SET_BIT(ADCSRA,ADEN);
}

void ADC_VidDisable(void)
{
	// disable ADC
		CLR_BIT(ADCSRA,ADEN);
}

void ADC_VidEnableInterrupt(void)
{
#if ADC_INTERRUPT == ENABLE

		SET_BIT(ADCSRA,ADIE);
#endif
}

void ADC_VidDisableInterrupt(void)
{
	/*NOTE: this function is here so that you can disable interrupts
	 *      EVEN IF interrupts are ENABLED */
#if ADC_INTERRUPT == ENABLE

		CLR_BIT(ADCSRA,ADIE);
#endif

}

u16  ADC_u16GetAnalogValue(u8 channel_select)
{
	//select active channel
		ADMUX = (ADMUX & 0xE0);
		ADMUX|=channel_select  ;

#if DATA_ADJUST == LEFT_ADJUST
	return ADCH;
#elif DATA_ADJUST == RIGHT_ADJUST
	return ADC_DATA ;
#endif
}


u16 ADC_u16AnalogRead(u8 channel_select)
{

	//select active channel
	ADMUX = (ADMUX & 0xE0);
	ADMUX|=channel_select  ;

	//start conversion
	SET_BIT(ADCSRA,ADSC);

	while(!GET_BIT(ADCSRA,ADIF)) //check ADIF flag
	{/*wait for conversion to complete */}

#if AUTO_TRIGGER == DISABLE
	SET_BIT(ADCSRA,ADIF); //clear ADIF
#endif

#if DATA_ADJUST == LEFT_ADJUST
	return ADCH;
#elif DATA_ADJUST == RIGHT_ADJUST
	return ADC_DATA ;
#endif
}

void ADC_VidAnalogRead_Batch(u8 input_channels_array[], u16 output_array[], u8 No_channels)
{
	if(No_channels > 8)
	{
		No_channels = 8;
	}
	else if(No_channels < 0)
	{
		No_channels = 0;
	}
	for(int i=0; i<No_channels; i++)
	{
		output_array[i] = ADC_u16AnalogRead(input_channels_array[i]);
	}

}

void ADC_VidStartConversion(u8 channel_select)
{
	//select active channel
		ADMUX = (ADMUX & 0xE0);
		ADMUX|=channel_select  ;

		//start conversion
		SET_BIT(ADCSRA,ADSC);
}

void ADC_VidSelectChannel(u8 channel_select)
{
	//select active channel
	ADMUX = (ADMUX & 0xE0);
	ADMUX|=channel_select  ;
}

void ADC_VidSetCallBack(void (*LOC_fptr)(u16)  )
{
	if(LOC_fptr != NULL )
	{
		CallBackFuncPtr = LOC_fptr ;
	}
}

#if ADC_INTERRUPT==ENABLE
	void __vector_16(void)   __attribute__((signal));
	void __vector_16(void)
	{
	if(CallBackFuncPtr != NULL )
	{
		CallBackFuncPtr(ADC_DATA);
	}

	}
#endif
