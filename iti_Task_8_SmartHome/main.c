/*
 * main.c
 *
 *  Created on: Jul 1, 2020
 *      Author: mazen
 */

//#define DEBUG


//LIB
#include "STD_TYPES.h"
#include "BIT_CALC.h"
#include <string.h>
//MCAL
#include "DIO_Interface.h"
#include "GIE_Interface.h"
#include "ADC.h"
#include "Timers_Interface.h"
#include <util/delay.h>
//HAL
#include "LCD/LCD_Interface.h"
#include "custom_chars.h"
#include "KEYPAD.h"

//APP
#include "security_module.h"
#include "menu.h"


#define NO_ELM(array)   (sizeof(array)/sizeof(array[0]))

#define MOTOR_ON  1
#define MOTOR_OFF 0

#define LED_OFF 0
#define LED_ON  1

#define MAX_TEMP 82
#define MIN_LIGHT 355

#define OUTPUT_PORT   PORTD
#define LED_PIN       PIN3
#define BUZ_PIN       PIN4
#define MOTOR_PIN     PIN6
#define LED2_PIN	  PIN5


u8 flag_log_out = 0 ;


const u8 loading_animation_chars[][8] = {LOADING1,LOADING2,LOADING3,LOADING4,\
										LOADING5, LOADING6 } ;

char temp_reading_string[8] = "";
char LDR_reading_string[8] = "";

u16  temp_reading = 0 ;
u16  LDR_reading = 0 ;


char *motor_states[] = {"OFF","ON"};
u8 current_motor_state = MOTOR_OFF;


char *led_states[] = {"LED OFF","LED ON "};
u8 current_led_state = LED_OFF;


u8 channel = 0 ;


void pulse_buzzer(u16 delay_amount,u8 no_pulses);
void press_any_key(void);
void loading_animation(void);


void temp_page(void);
void LDR_page(void);
void motor_page(void);
void home_page(void);
void logout(void);


//motor functions
void change_motor_state(void);


//led functions
void change_led_State(void);


void ADC_IntHandler(u16);

void update_analog_readings(void);
void safety_check(void);

ITEM items_home[4] = {
		              {1,0,temp_page,"Temp."},
					  {1,1,motor_page,"Motor"},
					  {8,0,LDR_page,"Light"},
					  {9,1,logout,"Logout"}
};


ITEM items_temp[] = { {1,0,NULL,"T= "},
					  {4,0,NULL,""},
					  {12,1,home_page,"back"}
};

ITEM items_LDR[] = { {1,0,NULL,"L= "},
					 {4,0,NULL,""},
					 {1,1,NULL,""},
					 {12,1,home_page,"back"}
};

ITEM items_motor[] = { {1,0,change_motor_state,"motor= "},
					  {8,0,NULL,"OFF"},
					  {12,1,home_page,"back"}
};

PAGE home ;
PAGE temp;
PAGE LDR;
PAGE motor;

PAGE *current_page;

int main(void)
{
	LCD_VidInit();
	KEYPAD_VidInit();
	GIE_enable();
	ADC_VidInit();
	ADC_VidSetCallBack(ADC_IntHandler);

	TCNT_VidInit(TIMER0);
	TCNT_VidLoadOCR(250,TIMER0);
	TCNT_VidStartTimer(TIMER0);





	//define all outputs
	DIO_VidSetPinDirection(OUTPUT_PORT,LED_PIN,1);
	DIO_VidSetPinDirection(OUTPUT_PORT,LED2_PIN,1);
	DIO_VidSetPinDirection(OUTPUT_PORT,BUZ_PIN,1);
	DIO_VidSetPinDirection(OUTPUT_PORT,MOTOR_PIN,1);


	 page_construct(&home,items_home,NO_ELM(items_home));
	 page_construct(&temp,items_temp,NO_ELM(items_temp));
	 page_construct(&LDR,items_LDR,NO_ELM(items_LDR));
	 page_construct(&motor,items_motor,NO_ELM(items_motor));




while(1)
{

ADC_VidStartConversion(channel);


LCD_VidSendCommand(CLEAR_DISPLAY);

flag_log_out = 0;

	u8 user_found = 0;
	u8 pass_correct = 0 ;
	u8 selected = 0;
	u8 key_press = 0;


#ifndef DEBUG
	current_page = &home ;
#endif

	current_page = &home ;


	do{

		press_any_key();
		loading_animation();

#ifdef DEBUG
		user_found = 1;
		pass_correct = 1;
#endif

#ifndef DEBUG

		user_found = verify_user();
		if(user_found == 0)
		{
			continue ;
		}
		else
		{
			pass_correct = verify_Pass();

			if(pass_correct == 0)
			{
				continue;
			}
			else
			{
				break ;
			}
		}
#endif

	}while( pass_correct==0 || user_found==0 );

	save_selection_arrow(0);
	LCD_VidSendCommand(CLEAR_DISPLAY);

page_display(current_page);



while(flag_log_out == 0)
{
	update_analog_readings();
	safety_check();
	key_press = KEYPAD_u8GetPressedKey();
	if(key_press != 0)
	{
		switch(key_press)
		{
/*UP*/	    case 16:
			LCD_VidSetCursorPosition(current_page->page_items[selected].x-1,current_page->page_items[selected].y);
			LCD_VidSendChar(' ');
			selected = (selected+1)%(current_page->no_items);
			LCD_VidSetCursorPosition(current_page->page_items[selected].x-1,current_page->page_items[selected].y);
			LCD_VidPrintCustomChar(0);

			page_display(current_page);

			break;
/*DOWN*/
			case 15:
			LCD_VidSetCursorPosition(current_page->page_items[selected].x-1,current_page->page_items[selected].y);
			LCD_VidSendChar(' ');
			selected = (selected-1)%(current_page->no_items);
			LCD_VidSetCursorPosition(current_page->page_items[selected].x-1,current_page->page_items[selected].y);
			LCD_VidPrintCustomChar(0);


			page_display(current_page);

			break;
/*ENTER*/
			case 14:
				LCD_VidSetCursorPosition(current_page->page_items[selected].x-1,current_page->page_items[selected].y);
				LCD_VidSendChar(' ');

				if(current_page->page_items[selected].CallBack != NULL)
				{
					current_page->page_items[selected].CallBack();

					LCD_VidSetCursorPosition(current_page->page_items[selected].x-1,current_page->page_items[selected].y);

					LCD_VidPrintCustomChar(0);

					LCD_VidSendCommand(CLEAR_DISPLAY);


					page_display(current_page);
				}
				break ;
		}
	}
	else
	{
		if(current_page== (&temp) ||  current_page==(&LDR))
		{
			page_update(current_page,1);
		}


	}

}

}

	return 0;
}

// function defs

void pulse_buzzer(u16 delay_amount,u8 no_pulses)
{
	for(int i=0; i< no_pulses; i++)
	{
		DIO_VidSetPinValue(OUTPUT_PORT,BUZ_PIN,1);
		DIO_VidSetPinValue(OUTPUT_PORT,LED2_PIN,1);
		_delay_ms(delay_amount);
		DIO_VidSetPinValue(OUTPUT_PORT,BUZ_PIN,0);
		DIO_VidSetPinValue(OUTPUT_PORT,LED2_PIN,0);

		_delay_ms(delay_amount);
	}

}

void temp_page(void)
{
	current_page = &temp ;
}

void LDR_page(void)
{
 current_page = &LDR ;
}

void motor_page(void)
{
 current_page = &motor;
}

void home_page(void)
{
 current_page = &home ;
}

void logout(void)
{
	flag_log_out = 1 ;
}


void press_any_key(void)
{
	LCD_VidSetCursorPosition(0,1);
	LCD_VidPrintString("Press Any Key",0);
	u8 key_press = 0 ;
	while(key_press == 0)
	{
		key_press = KEYPAD_u8GetPressedKey();
	}
	LCD_VidSendCommand(CLEAR_DISPLAY);
	LCD_VidSetCursorPosition(0,0);

}

void loading_animation(void)
{
	LCD_VidSaveCustomCharArray(6,loading_animation_chars);
	LCD_VidSetCursorPosition(0,2);
	LCD_VidPrintString("Loading...",0);
	LCD_VidSetCursorPosition(7,1);
	for(int j=0; j<2 ; j++)
	{
		for(int i=0; i<6; i++)
			{
				LCD_VidPrintCustomChar(i);
				LCD_VidSetCursorPosition(7,1);
				_delay_ms(100);
			}
	}
	LCD_VidSendCommand(CLEAR_DISPLAY);
	LCD_VidSetCursorPosition(0,0);
	pulse_buzzer(500,1);
}

void change_led_State(void)
{
	if(current_led_state == LED_OFF)
	{
		current_led_state = LED_ON;
	}
	else
	{
		current_led_state = LED_OFF;
	}
	strcpy(items_LDR[1].name,led_states[current_led_state]);

	DIO_VidSetPinValue(OUTPUT_PORT,LED_PIN,current_led_state);

}



void change_motor_state(void)
{
	if(current_motor_state == MOTOR_OFF)
	{
		current_motor_state = MOTOR_ON ;
	}
	else
	{
		current_motor_state = MOTOR_OFF ;
	}
	strcpy(items_motor[1].name,motor_states[current_motor_state]);

	DIO_VidSetPinValue(OUTPUT_PORT,MOTOR_PIN,current_motor_state);
}



void main_reverse(char s[])
 {
     int i, j;
     char c;

     for (i = 0, j = strlen(s)-1; i<j; i++, j--) {
         c = s[i];
         s[i] = s[j];
         s[j] = c;
     }
 }



void main_itoa(u16 n, char s[])
 {
     int i ;
	 u16 sign;

     if ((sign = n) < 0)  /* record sign */
         n = -n;          /* make n positive */
     i = 0;
     do {       /* generate digits in main_reverse order */
         s[i++] = n % 10 + '0';   /* get next digit */
     } while ((n /= 10) > 0);     /* delete it */
     if (sign < 0)
         s[i++] = '-';
     s[i] = '\0';
     main_reverse(s);
 }

void update_analog_readings(void)
{
	//generate display strings

	/***** 1. temp reading *****/
	u16 temp = (temp_reading*500UL)>>10 ; // (temp in mV) = (reading*5000)/(ADC_resoultion);
												// each 10 mv is 1 degC
											// T = (temp in mV)/10
	main_itoa(temp,temp_reading_string);
	strcat(temp_reading_string," C");

	/***** 2. LDR reading  *****/

	// min experimental value of LDR -> 350
	// max experimental value of LDR -> 990
	// NOTE: these numbers vary according to each LDR sensor
	//       so an experiment must be made to determine these values
	//       for a specific LDR
	//
	// to map values y={0->100} to values x={0->1024}
	//  y = m*x + c ,
	// calculated to be:
	// m= (25/256); -> a VERY NICE number because the denom. is 2^n
	// c= 0;
	u16 ldr = ((25*LDR_reading)>>8)  ;

	main_itoa(ldr,LDR_reading_string);
	if(ldr < 10)
	{
	 strcat(LDR_reading_string," ");
	}
	strcat(LDR_reading_string,"%");
	//update display strings
	strcpy(items_temp[1].name,temp_reading_string);
	strcpy(items_LDR[1].name, LDR_reading_string);
}



void safety_check(void)
{
	if(LDR_reading < MIN_LIGHT)
	{
		strcpy(items_LDR[2].name,led_states[LED_ON]);

		DIO_VidSetPinValue(OUTPUT_PORT,LED_PIN,LED_ON);
	}
	else
	{
		strcpy(items_LDR[2].name,led_states[LED_OFF]);

		DIO_VidSetPinValue(OUTPUT_PORT,LED_PIN,LED_OFF);

	}
	//check if temp reading has exceeded MAX_TEMP
	if(temp_reading >= MAX_TEMP)
	{
		while(temp_reading >= MAX_TEMP)
		{
			update_analog_readings();
			LCD_VidSendCommand(CLEAR_DISPLAY);
			page_display(&temp);
			pulse_buzzer(250,3);
		}
		LCD_VidSendCommand(CLEAR_DISPLAY);

	}
	page_display(current_page);


}




void ADC_IntHandler(u16 copy_of_ADC_DATA)
{
	switch(channel)
	{
	case 0:
		LDR_reading = copy_of_ADC_DATA ;
		channel = 1;
		break;
	case 1:
		temp_reading = copy_of_ADC_DATA ;
		channel = 0 ;
		break ;
	}
	ADC_VidSelectChannel(channel);
	ADC_VidStartConversion(channel);  //start next conversion

}

