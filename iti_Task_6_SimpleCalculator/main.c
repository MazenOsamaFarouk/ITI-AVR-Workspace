/*
 * main.c
 *
 *  Created on: Nov 29, 2020
 *      Author: mazen
 *  Description: Task 1_a for ITI-AVR course
 *  control 2 seven segment displays using 4 dip switches.
 *  use the dip switches to put the system in 1 of 3 modes:
 *  1. mode 1 -> count up on one of the seven segments
 *  2. mode 2 -> count down one the other seven segment
 *  3. mode 3 -> count to  99 using both seven segments
 */


//#include <avr/io.h>
//#include <util/delay.h>

#include "LIB/STD_TYPES.h"
#include "LIB/BIT_MAN.h"

#include "DIO/DIO_Interface.h"
#include "LCD/LCD_Interface.h"
#include "KEYPAD/KEYPAD.h"

#include <util/delay.h>
#include <string.h>
#include <ctype.h>

#define EQUAL_SIGN 0x3d
#define DIVISION_SIGN 0xfd


const char char_key_map[] = {'\0','1','4','7', \
		                      'B','2','5','8', \
							  '0','3','6','9', \
							  EQUAL_SIGN,'+','-','*',DIVISION_SIGN};
	u8 current_x = 0;
	u8 ans_flag = 0 ;

void display_message(char * the_message)
{
	LCD_VidSetCursorPosition(0,1);
	LCD_VidPrintString(the_message,0);
	LCD_VidSetCursorPosition(0,1);
	_delay_ms(2000);
	LCD_VidPrintString("               ",0);
	LCD_VidSetCursorPosition(current_x,0);
}

void display_ans(s32 ans)
{
	LCD_VidSetCursorPosition(0,1);
	LCD_VidPrintString("        ",0); //to clear the second row
	LCD_VidSetCursorPosition(0,1);
	LCD_VidPrintString("= ",0);

	LCD_VidPrintNum((u32)ans);
}


void inc_current_x(void)
{
	if(current_x == 15)
	{
		current_x = 0 ;
	}
	else
	{
		current_x++;
	}

	LCD_VidSetCursorPosition(current_x,0);
}


void dec_current_x(void)
{
	LCD_VidSetCursorPosition(current_x,0);
	LCD_VidSendChar(' ');
	if(current_x != 0)
	{
		current_x--;
	}

	LCD_VidSetCursorPosition(current_x,0);
}








u32 my_strtoi(char * aString)
{
	u32 result = 0;
	u8 No_digits = strlen(aString);

	for (u8 i = 0; (i < No_digits); ++i)
	{
		result = (result*10) + (aString[i]-'0');
	}

	return result;
}

void clear_operand_string_stack(char* stack)
{
	for (u8 i = 0; stack[i] != '\0'; ++i)
	{
		stack[i] = '\0';
	}
}

s32 parse_expression_string(char * exp)
{
	char operand_string_stack[8] = {'\0'}; u8 operand_string_stack_pointer = 0;
	char operation_stack[8] = {'\0'}; u8 operation_stack_pointer=0;

	u32 operand_number_stack[2] = {0}; u8 operand_number_stack_pointer=0;

	s32 ans = 0 ;

	for (u8 i = 0; exp[i] != '\0' ; ++i)
	{
		if (isdigit(exp[i]))
		{
			while(exp[i] !='\0' && isdigit(exp[i]) )
			{
				operand_string_stack[operand_string_stack_pointer++] = exp[i] ;
				++i;
			}

			operand_number_stack[operand_number_stack_pointer++] = my_strtoi(operand_string_stack);
			operand_string_stack_pointer = 0 ; //to begin again from the bottom the operand stack the next time you encounter a digit
			clear_operand_string_stack(operand_string_stack);
		}
		if (ispunct(exp[i]) || (exp[i]==DIVISION_SIGN))
		{
			operation_stack[operation_stack_pointer++] = exp[i];
		}
	}

	if ((exp[0]=='-'))
	{
		operand_number_stack[0] = -1*operand_number_stack[0];
	}



	if (operation_stack[2]=='-' )
	{
		operand_number_stack[1] = -1*operand_number_stack[1];
	}



	u8 switch_char = ispunct(exp[0])?operation_stack[1]:operation_stack[0];

	switch(switch_char)
	{
		case '+':  ans=operand_number_stack[0]+operand_number_stack[1]; ans_flag = 1; break ;
		case '-':  ans=operand_number_stack[0]-operand_number_stack[1]; ans_flag = 1; break ;
        case '*':  ans=operand_number_stack[0]*operand_number_stack[1]; ans_flag = 1; break ;
        case DIVISION_SIGN:
        if (operand_number_stack[1] != 0)
          {
          	ans=operand_number_stack[0]/operand_number_stack[1]; ans_flag = 1; break ;
          }
          else
          {
          	ans = 0; ans_flag = 2; break;
          }
	}


return ans;
}




int main(void)
{

	while(1)
	{
	//inits
	LCD_VidInit();
	KEYPAD_VidInit();


	char input_string_stack[15]={'\0'};
	u8 input_string_stack_pointer = 0;


	u8 digit_limit_counter = 0;
	//u8 operators_limit_counter = 0;
	s32 ans = 0;


	u8 key_press = 0 ;

	LCD_VidSendCommand(CLEAR_DISPLAY);
	LCD_VidSetCursorPosition(0,0);



	while(1)
	{


		key_press = KEYPAD_u8GetPressedKey();

		LCD_VidSetCursorPosition(current_x,0);


		if((key_press != 0))
		{
			if(key_press == 12) //equals sign
			{
				//show the typed char

				LCD_VidSendChar(char_key_map[key_press]);

				//if the last symbol entered is equals sign, i dont want to save it
				if(input_string_stack[input_string_stack_pointer-1] != EQUAL_SIGN)
				{
					//push equals sign in stack
					input_string_stack[input_string_stack_pointer++] = char_key_map[key_press];
				}
					display_message(input_string_stack);
				ans = parse_expression_string(input_string_stack);
			}
			else if(key_press == 4) //backspace or delete key
			{

				if(isdigit(input_string_stack[input_string_stack_pointer-1])&& (digit_limit_counter != 0) &&  (input_string_stack_pointer != 0) )
				{
					digit_limit_counter--;
				}

				//check if the stack pointer == 0
				if(input_string_stack_pointer != 0)
				{
					//pop the last element from the stack (make it equal to '\'
					input_string_stack[input_string_stack_pointer--] = '\0';
					dec_current_x();
				}

			}
			else
			{
				//check for max no digit
				if((digit_limit_counter != 4) && isdigit(char_key_map[key_press]))
				{
				digit_limit_counter++;
					//check stack pointer value

					if(input_string_stack_pointer != 14)
					{
						//show the typed char
						LCD_VidSendChar(char_key_map[key_press]);
						//push the number  symbol in the stack
						input_string_stack[input_string_stack_pointer++] = char_key_map[key_press];
						inc_current_x();
					}
					else
					{
						display_message("Max input!");
					}

				}
				else if(!isdigit(char_key_map[key_press]))
				{

					if(input_string_stack_pointer != 14)
					{
						//show the typed char
						LCD_VidSendChar(char_key_map[key_press]);
						//push the number  symbol in the stack
						input_string_stack[input_string_stack_pointer++] = char_key_map[key_press];
						inc_current_x();
						digit_limit_counter = 0; //reset the counter to indicate the end of an operand
					}
					else
					{
						display_message("Max input!");
					}
									}
				else
				{
					display_message("Max digits!");
				}
			}
		}
		//check for answer

		if(ans_flag == 1)
			{
				display_ans(ans);
				key_press = 0;

				//wait for enter key to continue
				while(1)
				{
					key_press = KEYPAD_u8GetPressedKey();
					if(key_press == 12)
					{
						break;
					}
				}
				current_x = 0;
				digit_limit_counter = 0;
				key_press = 0;
				 ans_flag = 0 ;
				 break ;
			}
			else if(ans_flag == 2)
			{
				display_message("Math Err!");
				key_press = 0; //to make the loop wait for a key press
				 ans_flag = 0 ;
			}
			else if(ans_flag == 3)
			{
				display_message("INVALID input!");
			}
	}


}


	return 0 ;

}
