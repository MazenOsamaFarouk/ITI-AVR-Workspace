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
#include "BUTTON/BUTTON_Interface.h"
#include "LCD/LCD_Interface.h"



#include "custom_chars.h"

#include <util/delay.h>


#define REFRESH_RATE 200
#define ball 				0
#define left_bat 			1
#define left_bat_w_ball 	2
#define right_bat 			3
#define right_bat_w_ball 	4

#define UP   0
#define DOWN 1

#define BAT_LEFT  1
#define BAT_RIGHT 14

#define BALL_LEFT  1
#define BALL_RIGHT 0

#define BTN_LEFT  0
#define BTN_RIGHT 1
#define BTN_KICK  2


typedef struct
{
	u8 pos;
	u8 side;
	u8 score;
	u8 symbol;
	u8 hasball;
}player_type;

typedef struct
{
	u8 x;
	u8 y;
	u8 dir;
	u8 symbol;
}ball_type;

const u8 custom_chars[][8] = {BALL,LEFT_BAT,LEFT_BAT_W_BALL,RIGHT_BAT,RIGHT_BAT_W_BALL};


player_type p_left = {UP,BAT_LEFT,0,left_bat,1}; // left player starts with the ball
player_type p_right = {UP,BAT_RIGHT,0,right_bat,0};
ball_type the_ball = {7,0,BALL_LEFT,ball}; //ball starts in the middle of the screen



Button_Type b_arr[3];




void move_player(player_type*p, u8 dir)
{
	if(p->pos != dir)
	{
		p->pos = dir;
	}


	LCD_VidSetCursorPosition(p->side,p->pos);

	if(p->hasball == 1)
		{
			if(p->side == BAT_RIGHT)
			{
				p->symbol = right_bat_w_ball;
			}
			else if(p->side == BAT_LEFT)
			{
				p->symbol = left_bat_w_ball;
			}
		}
		else
		{
			if(p->side == BAT_RIGHT)
			{
				p->symbol = right_bat;
			}
			else if(p->side == BAT_LEFT)
			{
				p->symbol = left_bat;
			}

		}
		LCD_VidPrintCustomChar(p->symbol);
}


void move_ball(ball_type*b, u8 dx, u8 dy)
{
	if(b->dir == BALL_RIGHT)
	{
		if(b->x < BAT_RIGHT+1)
		{
			b->x+=dx;
		}

		if(b->y < 2)
		{
			b->y+=dy;
		}

	}
	else if(b->dir == BALL_LEFT)
	{
		if(b->x != BAT_LEFT-1)
		{
			b->x-=dx;
		}
		if(b->y != 0)
		{
			b->y-=dy;
		}
	}
	LCD_VidSetCursorPosition(b->x,b->y);
	LCD_VidPrintCustomChar(b->symbol);
}



void update_display(void)
{
	// clear screen
	LCD_VidSendCommand(CLEAR_DISPLAY);
	// move then draw


	move_ball(&the_ball,0,0);
	if(the_ball.x != BAT_RIGHT-1 || the_ball.x != BAT_LEFT+1)
	{
		draw_ball(&the_ball);
	}
	move_player(&p_left,p_left.pos);
	move_player(&p_right,p_right.pos);

	// delay
	_delay_ms(REFRESH_RATE);
}

void display_greeting(void)
{
	LCD_VidSendCommand(CLEAR_DISPLAY);
	LCD_VidSetCursorPosition(0,0);
	LCD_VidPrintString("  >>>Goal<<<  ",100);
	LCD_VidSetCursorPosition(0,1);
	LCD_VidPrintString("L= ",0);
	LCD_VidPrintNum(p_left.score);
	LCD_VidPrintString("     R= ",0);
	LCD_VidPrintNum(p_right.score);
	_delay_ms(3000);
}


int main(void)
{

	for(u8 i=0; i<3; i++)
	{
		b_arr[i] = BUTTON_Init(PORTD,i,NO,20,1);
	}
	Button_Type b_left = b_arr[0];
	Button_Type b_right = b_arr[1];
	Button_Type b_kick = b_arr[2];
	//init..
	LCD_VidInit();


	//load all custom charahcters into CGRAM
	for(int i=0; i<5 ; i++)
	{
		LCD_VidSaveCustomChar(custom_chars[i],i);
	}
	u8 is_goal= 0;

	while(1)
	{
		is_goal= 0;
		u8 current_player_pos= UP;
		update_display();

		do //wait for  player to start the game
		{
			BUTTON_IsPressed(&b_arr[BTN_KICK]);
		}while(b_arr[BTN_KICK].state == RELEASED);
		b_arr[BTN_KICK].state = RELEASED; //reset the  state
		//		the_ball.x=p_left.side;


		while(1)
		{


			if(p_right.hasball == 1)
			{
				p_left.hasball = 0;
				current_player_pos = p_right.pos;
				// check for kick
				do
				{
					BUTTON_IsPressed(&b_kick);
					BUTTON_IsPressed(&b_right);
					BUTTON_IsPressed(&b_left);

					if(b_right.state == PRESSED)
					{
						b_right.state = RELEASED;
						if(p_right.pos == UP)
						{
							move_player(&p_right,DOWN);
							move_ball(&the_ball,p_right.side,current_player_pos);
						}
						else if(p_right.pos==DOWN)
						{
							move_player(&p_right,UP);
							move_ball(&the_ball,p_right.side,current_player_pos);
						}
						update_display();
					}

					if(b_left.state == PRESSED)
					{
						b_left.state = RELEASED;
						if(p_left.pos == UP)
						{
							move_player(&p_left,DOWN);
						}
						else if(p_left.pos==DOWN)
						{
							move_player(&p_left,UP);
						}
						update_display();
					}

				}while(b_kick.state == PRESSED);
				b_kick.state = RELEASED;
			}
			else if(p_left.hasball == 1)
			{
				p_right.hasball = 0;
				current_player_pos = p_left.pos;
				// check for kick
				do
				{
					BUTTON_IsPressed(&b_kick);

					BUTTON_IsPressed(&b_right);
					BUTTON_IsPressed(&b_left);

					if(b_right.state == PRESSED)
					{
						b_right.state = RELEASED;
						if(p_right.pos == UP)
						{
							move_player(&p_right,DOWN);
						}
						else if(p_right.pos==DOWN)
						{
							move_player(&p_right,UP);
						}
						update_display();
					}

					if(b_left.state == PRESSED)
					{
						b_left.state = RELEASED;
						if(p_left.pos == UP)
						{
							move_player(&p_left,DOWN);
							move_ball(&the_ball,p_left.side,current_player_pos);
						}
						else if(p_left.pos==DOWN)
						{
							move_player(&p_left,UP);
							move_ball(&the_ball,p_left.side,current_player_pos);
						}
						update_display();
					}

				}while(b_kick.state == PRESSED);
				b_kick.state = RELEASED;
			}



			do
			{
				BUTTON_IsPressed(&b_right);
				BUTTON_IsPressed(&b_left);

				if(b_right.state == PRESSED)
				{
					b_right.state = RELEASED;
					if(p_right.pos == UP)
					{
						move_player(&p_right,DOWN);
					}
					else if(p_right.pos==DOWN)
					{
						move_player(&p_right,UP);
					}
				}
				if(b_left.state == PRESSED)
				{
					b_left.state = RELEASED;
					if(p_left.pos == UP)
					{
						move_player(&p_left,DOWN);
					}
					else if(p_left.pos==DOWN)
					{
						move_player(&p_left,UP);
					}

				}

				// dertermine ball direcion and initial position
				if(p_right.hasball == 1)
				{
					current_player_pos = p_right.pos;
					the_ball.dir = BALL_LEFT;
					move_ball(&the_ball,1,current_player_pos);
				}
				else if(p_left.hasball == 1)
				{
					current_player_pos = p_left.pos;
					the_ball.dir = BALL_RIGHT;
					move_ball(&the_ball,1,current_player_pos);
				}

				update_display();

				if(the_ball.x == p_right.side && the_ball.y == p_right.pos)
				{
					p_right.hasball = 1;
					p_left.hasball = 0 ;
					b_kick.state = RELEASED;
					break;
				}
				else if(the_ball.x == p_left.side && the_ball.y == p_left.pos)
				{
					p_left.hasball = 1;
					p_right.hasball = 0;
					b_kick.state = RELEASED;
					break;
				}
				else if(the_ball.x > p_right.side)
				{
					is_goal = 1;
					p_left.score += 1;
					b_kick.state = RELEASED;
				}
				else if(the_ball.x < p_left.side)
				{
					is_goal = 1;
					p_right.score += 1;
					b_kick.state = RELEASED;
				}


			}while(is_goal == 0);



			if(is_goal == 1)
			{
				display_greeting();
				the_ball.x=7;
				the_ball.y=UP;
				p_left.pos = UP;
				p_right.pos = UP;
				p_left.hasball = 1;
				p_right.hasball = 0;
				break;
			}


		}


	}
	return 0 ;

}
