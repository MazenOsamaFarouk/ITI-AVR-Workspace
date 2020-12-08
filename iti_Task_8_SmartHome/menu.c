/*
 * menu.c
 *
 *  Created on: Jul 2, 2020
 *      Author: mazen
 */

#include <string.h>
#include "STD_TYPES.h"
#include "LCD/LCD_Interface.h"
#include "custom_chars.h"
#include "menu.h"

#include <util/delay.h>

//#define DEBUG

u8 current_x = 0;

u8 selection_arrow[] = ARROW;

void inc_current_x(void)
{
	if(current_x < 15)
	{
		current_x++;
	}
	else
	{
		current_x = 0;
	}
}

void dec_current_x(void)
{
	if(current_x > 0)
	{
		current_x--;
	}
	else
	{
		current_x = 0;
	}

}


void save_selection_arrow(u8 cgRAM_address)
{
	LCD_VidSaveCustomChar(selection_arrow,cgRAM_address);
}




void item_construct(ITEM *const me, char name[], u8 x, u8 y, u8 selected, void (*CallBack)(void) )
{
	strcpy(me->name, name);
	me->x = x;
	me->y = y;
	me->CallBack = CallBack ;
}


// page type constructor
void page_construct(PAGE * const me, ITEM* items, u8 no_items )
{
	me->no_items = no_items;

	me->page_items = items ;

}
void page_display(PAGE *the_page)
{


	for(int i=0; i<the_page->no_items; i++)
	{

		//display each item in its place on the LCD
		// 1. move cursor to desired location

		LCD_VidSetCursorPosition(the_page->page_items[i].x,the_page->page_items[i].y);

		// 2. print the item name

		LCD_VidPrintString(the_page->page_items[i].name,0);

		// 3. repeat
#ifdef DEBUG
		_delay_ms(1000);
#endif
	}


}
void page_update(PAGE *the_page,u8 selected_idx)
{
	//display each item in its place on the LCD
	// 1. move cursor to desired location

	LCD_VidSetCursorPosition(the_page->page_items[selected_idx].x,the_page->page_items[selected_idx].y);

	// 2. print the item name

	LCD_VidPrintString(the_page->page_items[selected_idx].name,0);


}
