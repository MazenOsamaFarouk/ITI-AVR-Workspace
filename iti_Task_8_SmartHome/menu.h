/*
 * menu.h
 *
 *  Created on: Jul 2, 2020
 *      Author: mazen
 */

#ifndef MENU_H_
#define MENU_H_



typedef struct
{

	u8 x;
	u8 y;
	void (*CallBack)(void);
	char name[8];
}ITEM;

typedef struct
{
	u8 no_items ;
	ITEM *page_items;

}PAGE;




extern u8 current_x ;


void inc_current_x(void);
void dec_current_x(void);

void save_selection_arrow(u8 cgRAM_address);

void page_construct(PAGE * const me, ITEM items[], u8 no_items);
void page_display(PAGE *the_page);
void page_update(PAGE *the_page, u8 selected_idx);
void item_construct(ITEM *const me, char name[], u8 x, u8 y, u8 selected, void (*CallBack)(void) );



#endif /* MENU_H_ */
