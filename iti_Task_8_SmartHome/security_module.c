/*
 * security_module.c
 *
 *  Created on: Jul 2, 2020
 *      Author: mazen
 */

#include <string.h>
#include <util/delay.h>
#include "STD_TYPES.h"
#include "DIO_Interface.h"
#include "LCD/LCD_Interface.h"
#include "KEYPAD.h"
#include "_7SEGMENT/_7Seg.h"
#include "menu.h"
#include "security_module.h"


	char user_id_string[15] = {'\0'};
	char pass_string[15] = {'\0'};

	_7SEG_PIN ss_pinarr[]=
	{
			{PORTC,PIN0},
			{PORTC,PIN1},
			{PORTC,PIN2},
			{PORTC,PIN3},
			{PORTC,PIN4},
			{PORTC,PIN5},
			{PORTC,PIN6},
			{PORTC,PIN7}
	};
	_7Seg ss = {ss_pinarr,COM_CATHODE};


	const char *T9_key_map[] = {"\0", /* 0 */
								"1",  /* 1 */
							   "4ghi", /* 2 */
							   "7pqrs", /* 3 */
							   "L", /* 4 */
							   "2abc", /* 5 */
							   "5jkl", /* 6 */
							   "8tuv", /* 7 */
							   "0", /* 8 */
							   "3def", /* 9 */
							   "6mnp", /* 10 */
							   "9wxyz",  /* 11 */
							   "R", /* 12 */
							   "B", /* 13 */
							   "E", /* 14 */
							   "U", /* 15 */
							   "D" /* 16 */
	};

u8 get_char_to_display(u8 key_press ,const char *key_map[])
{
	u8 disp_char = 0;
static	u8 current_string_idx  = 0 ;
static	u8 current_key_map_idx = 0 ;

	if(current_key_map_idx==key_press) //then we are pointing to the same string
	{
		if( key_map[current_key_map_idx][current_string_idx] != '\0')
		{
			disp_char = key_map[current_key_map_idx][current_string_idx];

			current_string_idx = (current_string_idx+1)%strlen(key_map[current_key_map_idx]);
		}
		else
		{
			current_string_idx = 0 ;
		}
	}
	else //then we are pointing to a different string
	{
		current_string_idx = 0 ;
		current_key_map_idx=key_press;
		disp_char = key_map[current_key_map_idx][current_string_idx];

	}


	return disp_char;
}

void get_user_id(void)
{
	_7SEG_VidInit(&ss);
	LCD_VidSendCommand(CLEAR_DISPLAY);
	LCD_VidSetCursorPosition(0,0);
	LCD_VidPrintString("User ID:",0);
	LCD_VidSetCursorPosition(current_x,1);
	u8 key_press = 0;
	u8 char_to_display = 0;
	u8 flag_done = 0 ;
		 //left arrow key (simulates BACK key)
		while(flag_done == 0)
		{
			key_press = KEYPAD_u8GetPressedKey();
		if(key_press != 0)
		{
			switch(key_press)
			{
			case 4:
				user_id_string[current_x] = '\0';
				dec_current_x();
				LCD_VidSetCursorPosition(current_x,1);
				break; //go back one spot
			case 12:
				user_id_string[current_x] = char_to_display;
				user_id_string[current_x+1] = '\0';
				inc_current_x();
				LCD_VidSetCursorPosition(current_x,1);
				break; //go forward one spot
			case 14: flag_done = 1; break; //press entrer key to finish
			case 13: case 15: case 16: break ; // do nothing for backspace,UP and DOWN buttons
			default:

		char_to_display = get_char_to_display(key_press,T9_key_map);
			LCD_VidSendChar(char_to_display);
			LCD_VidSetCursorPosition(current_x,1);
			break;
			}
		}


		}
		user_id_string[current_x] = char_to_display;
		user_id_string[current_x+1] = '\0';

}


void get_pass(void)
{
	LCD_VidSendCommand(CLEAR_DISPLAY);
		LCD_VidSetCursorPosition(0,0);
			LCD_VidPrintString("PASS :",0);
			LCD_VidSetCursorPosition(current_x,1);
			u8 key_press = 0;
			u8 char_to_display = 0;
			u8 flag_done = 0 ;
			 //left arrow key (simulates BACK key)
			while(flag_done == 0)
			{
				key_press = KEYPAD_u8GetPressedKey();
			if(key_press != 0)
			{
				switch(key_press)
				{
				case 4:
					pass_string[current_x] = '\0'; // "delete" it from the array
					LCD_VidSendChar(' '); // overwrite it with space
					dec_current_x();
					LCD_VidSetCursorPosition(current_x,1);
					break; //go back one spot
				case 12:
					pass_string[current_x] = char_to_display;
					pass_string[current_x+1] = '\0';
					LCD_VidSendChar('*');
					inc_current_x();
					LCD_VidSetCursorPosition(current_x,1);
					break; //go forward one spot
				case 14: flag_done = 1; break; //press entrer key to finish
				case 13: case 15: case 16: break ; // do nothing for backspace,UP and DOWN buttons
				default:

			char_to_display = get_char_to_display(key_press,T9_key_map);
				LCD_VidSendChar(char_to_display);
				LCD_VidSetCursorPosition(current_x,1);
				break;
				}
			}


			}
			pass_string[current_x] = char_to_display;
			pass_string[current_x+1] = '\0';


}

u8 verify_user(void)
{
	_7SEG_VidDisplayNum(&ss,NO_TRIALS);
	u8 flag_user_id_match =0 ;
	for(int i=0; i < NO_TRIALS; i++)
	{
		get_user_id();
		if((strcmp(ADMIN,user_id_string) == 0) || (strcmp(USR_MAZEN,user_id_string) == 0))
		{
			flag_user_id_match = 1;
			break ;
		}
		else
		{
			_7SEG_VidDisplayNum(&ss,3-i-1);
			flag_user_id_match = 0 ;
			LCD_VidSendCommand(CLEAR_DISPLAY);
			LCD_VidSetCursorPosition(0,0);
			LCD_VidPrintString("wrong user..",0);
			if(i != 2)
			{
			LCD_VidSetCursorPosition(0,1);
			LCD_VidPrintString("Try Again",0);
			LCD_VidSetCursorPosition(0,1);
			}
			current_x = 0 ;
			_delay_ms(1000);
		}

	}

	if(flag_user_id_match == 1)
	{
		_7SEG_VidDisplayOff(&ss);
		LCD_VidSendCommand(CLEAR_DISPLAY);
		LCD_VidSetCursorPosition(0,0);
		LCD_VidPrintString("***welcome***",0);
		LCD_VidSetCursorPosition(0,1);
		LCD_VidPrintString(user_id_string,0);
		_delay_ms(2000);
		LCD_VidSendCommand(CLEAR_DISPLAY);
	}
	else
	{
		LCD_VidSendCommand(CLEAR_DISPLAY);
		LCD_VidSetCursorPosition(0,0);
		LCD_VidPrintString("user: not found",0);
		_delay_ms(2000);
		LCD_VidSendCommand(CLEAR_DISPLAY);
	}
	current_x = 0 ;
	LCD_VidSetCursorPosition(current_x,0);
	_7SEG_VidDisplayNum(&ss,0);
	return flag_user_id_match;
}

u8 verify_Pass(void)
{
	_7SEG_VidDisplayNum(&ss,NO_TRIALS);
	u8 flag_pass_match =0 ;
		for(int i=0; i < NO_TRIALS; i++)
		{
			get_pass();
			if((strcmp(ADMIN_PASS,pass_string) == 0) || (strcmp(USR_MAZEN_PASS,pass_string) == 0))
			{
				flag_pass_match = 1;
				break ;
			}
			else
			{
				_7SEG_VidDisplayNum(&ss,3-i-1);
				flag_pass_match = 0 ;
				LCD_VidSendCommand(CLEAR_DISPLAY);
				LCD_VidSetCursorPosition(0,0);
				LCD_VidPrintString("wrong pass..",0);

				if(i != 2)
				{
				LCD_VidSetCursorPosition(0,1);
				LCD_VidPrintString("Try Again",0);
				LCD_VidSetCursorPosition(0,1);
				}
				current_x = 0 ;
				_delay_ms(1000);
			}

		}

		if(flag_pass_match == 1)
		{
			_7SEG_VidDisplayOff(&ss);
			LCD_VidSendCommand(CLEAR_DISPLAY);
			LCD_VidSetCursorPosition(0,0);
			LCD_VidPrintString("access Granted",0);

			_delay_ms(2000);
			LCD_VidSendCommand(CLEAR_DISPLAY);
		}
		else
		{
			LCD_VidSendCommand(CLEAR_DISPLAY);
			LCD_VidSetCursorPosition(0,0);
			LCD_VidPrintString("access Denied",0);

			_delay_ms(2000);
			LCD_VidSendCommand(CLEAR_DISPLAY);
		}
		current_x = 0 ;
		LCD_VidSetCursorPosition(current_x,0);
		return flag_pass_match;

}

