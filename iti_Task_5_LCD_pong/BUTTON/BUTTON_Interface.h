/*
 * BUTTON_Interface.h
 *
 *  Created on: Dec 1, 2020
 *      Author: mazen
 */

#ifndef BUTTON_BUTTON_INTERFACE_H_
#define BUTTON_BUTTON_INTERFACE_H_

#define NO 0
#define NC 1


typedef enum
{
	PRESSED,
	RELEASED
}Button_State;


typedef struct
{
	u8 port;
	u8 pin;
	u8 type;
	Button_State state;
	u32 debounce_delay;
}Button_Type;

Button_Type BUTTON_Init(u8 port, u8 pin,u8 type,u32 debounce_delay, u8 use_internal_pullup);
void BUTTON_SetDebounceDelay(Button_Type*me, u32 deb_delay);
void BUTTON_IsPressed(Button_Type* me);
void BUTTON_GetButtonArray(Button_Type b_arr[],u8 port ,u8 no_buttons);

#endif /* BUTTON_BUTTON_INTERFACE_H_ */
