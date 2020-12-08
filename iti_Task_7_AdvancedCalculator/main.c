/*
 * main.c
 *
 *  Created on: Nov 29, 2020
 *      Author: mazen
 *  Description: Task 7 for ITI-AVR course
 *
 */


//#include <avr/io.h>

#include "LIB/STD_TYPES.h"
#include "LIB/BIT_MAN.h"

#include "DIO/DIO_Interface.h"
#include "LCD/LCD_Interface.h"
#include "KEYPAD/KEYPAD.h"

#include "custom_stack.h"
#include "float_stack.h"


#include <util/delay.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

const char* char_key_map[] = {"","1","4","7", \
							  "L","2","5","8", \
							  "0","3","6","9", \
							  "R","+-","*/^.","()","="};

/*************** Global variables *************/
u8 current_x = 0;
u8 ans_flag = 0 ;
int err_no=0;
char user_input_string[15] = {'\0'};

TYPE lifo[16]={0};
CustomStack op_stack;



/*************** Function defintions *************/

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



void get_user_input(void)
{
	LCD_VidSendCommand(CLEAR_DISPLAY);
	LCD_VidSetCursorPosition(0,0);
	LCD_VidSetCursorPosition(current_x,0);
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
				user_input_string[current_x] = '\0';
				dec_current_x();
				LCD_VidSetCursorPosition(current_x,0);
				break; //go back one spot
			case 12:
				user_input_string[current_x] = char_to_display;
				user_input_string[current_x+1] = '\0';
				inc_current_x();
				LCD_VidSetCursorPosition(current_x,0);
				break; //go forward one spot
			case 16: flag_done = 1; break; //press entrer key to finish
			default:

		char_to_display = get_char_to_display(key_press,char_key_map);
			LCD_VidSendChar(char_to_display);
			LCD_VidSetCursorPosition(current_x,0);
			break;
			}
		}


		}
		user_input_string[current_x] = char_to_display;
		user_input_string[current_x+1] = '\0';

}


void display_message(char * the_message)
{
	LCD_VidSetCursorPosition(0,1);
	LCD_VidPrintString(the_message,0);
	LCD_VidSetCursorPosition(0,1);
	_delay_ms(2000);
	LCD_VidPrintString("               ",0);
	LCD_VidSetCursorPosition(current_x,0);
}




void LCD_PrintFloat(float f)
{
     long    l, rem;

	l = ( long)f;
	f -= (float)l;
	rem = (long)(f * 1e5);

	LCD_VidPrintNum(l);
	LCD_VidSendChar('.');
	LCD_VidPrintNum(rem);
}

void display_ans(float ans)
{
	LCD_VidSetCursorPosition(0,1);
	LCD_VidPrintString("        ",0); //to clear the second row
	LCD_VidSetCursorPosition(0,1);
	LCD_VidPrintString("= ",0);

	LCD_PrintFloat(ans);
}

int is_operator(char c)
{
   return strchr("+-*/^", c) == NULL ? 0 : 1;
}

int precedence(char op)
{
    int pr=0;
    switch(op)
    {
        case '^': pr=3; break;

        case '*':
        case '/': pr=2; break;

        case '+':
        case '-': pr=1; break;
    }

    return pr;
}

int my_pow(int base,int exponent)
{
    int res = 1;

    for (int i = 0; i < exponent; i++)
    {
        res *=base;
    }
    return res;
}




float f_calc(float B,char op,float A)
{
    float ans = 0;
      //everything is fine...until it isnt :D
    switch(op)
    {
        case '+': ans=B+A; break;
        case '-': ans=B-A; break;
        case '*': ans=B*A; break;
        case '/':
            if(A==0)
            {
                err_no=1;  // div by zero error
                ans = 0;
            }
            else
            {
                ans = B/A;
            }
            break;
        case '^': ans=my_pow((int)B,(int)A); break;
    }
    return ans;
}


void syntax_check(char modified_infix[])
{
	err_no = 0;
	char * check_ptr;
	const char * check_strs[]={"**","//","^^","..","*/","/*",
							   "*^","^*","/^","^/","*.",".*",
							   "/.","./","^.",".^"};
	for (int i = 0; i < 16; i++)
	{
		check_ptr = strstr(modified_infix,check_strs[i]);
		if (check_ptr != NULL)
		{
			err_no=5;  // INVALID SYNTAX
			break;
		}

	}
}


void strip(char str[])
{
	while(*str!='\0')
	{
		if(is_operator(*str) || *str=='(' || *str==')')
		{
			*str=' ';
		}
		str++;
	}
}


void get_floats(FloatStack* fstack, char stripped_infix_exp[])
{
	double temp_double;
	char * endptr1;
	char *endptr2;
	FloatStack_Clear(fstack);
	temp_double = strtod(stripped_infix_exp,&endptr1);
	endptr2 = endptr1;
	FloatStack_Push(fstack,temp_double);

	for (; ;)
	{
		temp_double = strtod(endptr1,&endptr2);
		if ((endptr1-endptr2)==0)
		{
			break;
		}

		FloatStack_Push(fstack,temp_double);
		endptr1 = endptr2;
	}

}

void modified_infix(CustomStack*s, char infix_exp[])
{
	CustomStack_Clear(s);
	while (*infix_exp != '\0')
	{
		if (is_operator(*infix_exp) || *infix_exp=='(' || *infix_exp==')')
		{
			CustomStack_Push(s,*infix_exp);
		}
		else if (isdigit(*infix_exp) || *infix_exp=='.')
		{
			if (CustomStack_Peek(s) != 'N' )
			{
				CustomStack_Push(s,'N');
			}
		}
		infix_exp++;
	}
	CustomStack_Push(s,'\0');
}


void compensate_unary(CustomStack*s, char modified_infix[])
{
	int i=0;
	char c,c1;
	int nBrackets = 0;
	CustomStack_Clear(s);
	CustomStack_Push(s,'\0');
	CustomStack_Clear(s);

	c = modified_infix[0];
	while (c!='\0')
	{
		c=modified_infix[i];

		if (c=='+' || c=='-')
		{
			c1 = CustomStack_Peek(s);
			if (c1=='N' || c1==')' )
			{
				CustomStack_Push(s,c);
				i++;
				continue;
			}
			else
			{
				CustomStack_Push(s,'(');
				CustomStack_Push(s,'0');
				CustomStack_Push(s,c);
				i++;
				nBrackets++;
				continue;
			}
		}
		else if (is_operator(c))
		{
			CustomStack_Push(s,c);
			i++;
			continue;
		}
		else
		{
			CustomStack_Push(s,c);

			while (nBrackets > 0)
			{
				CustomStack_Push(s,')');
				nBrackets--;
			}
			nBrackets = 0;

			i++;
			continue;
		}


	}

	CustomStack_Push(s,'\0');

}



void InfixToPostfix(char infix_exp[], char postfix_exp[])
{
	int i, j;
	char item;
	char x;
    CustomStack_Push(&op_stack,(TYPE)'(');  //   push('(');                               /* push '(' onto stack */
	strcat(infix_exp,")");                  /* add ')' to infix expression */

	i=0;
	j=0;
	item=infix_exp[i];         /* initialize before loop*/

	while(item != '\0')        /* run loop till end of infix expression */
	{
		if(item == '(')
		{
			 CustomStack_Push(&op_stack,(TYPE)item);//push(item);
		}
		else if( isdigit(item) || isalpha(item))
		{
			postfix_exp[j] = item;              /* add operand symbol to postfix expr */
			j++;
		}
		else if(is_operator(item) == 1)        /* means symbol is operator */
		{
			x=CustomStack_Pop(&op_stack);   //x=pop();
			while(is_operator(x) == 1 && precedence(x)>= precedence(item))
			{
				postfix_exp[j] = x;                  /* so pop all higher precendence operator and */
				j++;
				x= CustomStack_Pop(&op_stack);  //x = pop();                       /* add them to postfix expresion */
			}
			CustomStack_Push(&op_stack,x); //push(x);
			/* because just above while loop will terminate we have
			popped one extra item
			for which condition fails and loop terminates, so that one*/

			CustomStack_Push(&op_stack,item);// push(item);                 /* push current oprerator symbol onto stack */
		}
		else if(item == ')')         /* if current symbol is ')' then */
		{
			x=CustomStack_Pop(&op_stack);//  x = pop();                   /* pop and keep popping until */
			while(x != '(')                /* '(' encounterd */
			{
				postfix_exp[j] = x;
				j++;
				x=CustomStack_Pop(&op_stack);//  x = pop();
			}
		}
		else
		{ /* if current symbol is neither operand not '(' nor ')' and nor
			operator */
			//printf("\nInvalid infix Expression.\n");        /* the it is illegeal  symbol */
			err_no = 5 ;  // INVALID SYNTAX
			// getchar();
			//exit(1);
		}
		i++;


		item = infix_exp[i]; /* go to next symbol of infix expression */
	} /* while loop ends here */
	if( CustomStack_GetCount(&op_stack)>0)
	{
		err_no = 5 ;  // INVALID SYNTAX
		// printf("\nInvalid infix Expression.\n");        /* the it is illegeal  symbol */
		// getchar();
		//exit(1);
	}

	postfix_exp[j] = '\0'; /* add sentinel else puts() fucntion */
	/* will print entire postfix[] array upto SIZE */

}



float postfix_Fevaluate(char postfix_exp[], int exp_size,float floats[],int fsize)
{
    float ans = 0.0f;
    float A=0.0f,B=0.0f,C=0.0f ;
	int fidx = 0;
	float fans[10];
	FloatStack fs;
	FloatStack_Init(&fs,fans,10);
    for (int i = 0; i < exp_size; i++)
    {
        if((postfix_exp[i]=='0') ||(postfix_exp[i]=='N') )
		{
			if (postfix_exp[i]=='0')
			{
				FloatStack_Push(&fs,0);
			}
			else if(postfix_exp[i]=='N')
			{
				C=floats[fidx]; fidx++;
				FloatStack_Push(&fs,C);
			}
		}
		else if(is_operator(postfix_exp[i])==1 )
		{

			A= FloatStack_Pop(&fs); //pop(&s);
			B= FloatStack_Pop(&fs); //pop(&s);
			ans=f_calc(B,postfix_exp[i],A);
			FloatStack_Push(&fs,ans); // push(&s,ans);
		}
    }
    ans = FloatStack_Pop(&fs);// pop(&s);

return ans;
}



int main(void)
{

	CustomStack_Init(&op_stack,lifo,16);
	char postfix[16];
	float ans = 0.0f;
	u8 key_press = 0;
	//inits
	LCD_VidInit();
	KEYPAD_VidInit();


	while(1)
	{

		get_user_input();
//		display_message(user_input_string);
		// 1. modified infix
		// 2. compensate for unary
		// 3. get_floats
		// 4. convert compensated infix to postfix
		// 5. evaluate postfix with floats
		char modinfix[16]={0};
		CustomStack s;
		CustomStack_Init(&s,modinfix,16);

		modified_infix(&s,user_input_string);

		syntax_check(modinfix);
//		display_message(modinfix);
		if (err_no == 5)
		{
			display_message("Syntax Error!!");
		}
		char u_comp[30];
		CustomStack_Init(&s,u_comp,30);

		compensate_unary(&s,modinfix);
//		display_message(u_comp);

		float nums[10]={0.0f};
		FloatStack fs;
		FloatStack_Init(&fs,nums,10);
		strip(user_input_string);
		get_floats(&fs,user_input_string);


		InfixToPostfix(u_comp,postfix);

//		display_message(postfix);


		if (err_no != 5)
		{
			ans = postfix_Fevaluate(postfix,strlen(postfix),nums, FloatStack_GetCount(&fs));

			if (err_no != 1)
			{
				display_ans(ans);
			}
			else
			{
				display_message("Math Error..");
			}
			// wait for key press ENTER (=)
			while(key_press != 16)
			{
				key_press = KEYPAD_u8GetPressedKey();
			}
			current_x = 0;
			key_press = 0;
			ans = 0.0f;
			CustomStack_Clear(&op_stack);
			CustomStack_Clear(&s);
			FloatStack_Clear(&fs);
		}
		else
		{
			display_message("Syntax Error..");
		}


	}
	return 0 ;

}
