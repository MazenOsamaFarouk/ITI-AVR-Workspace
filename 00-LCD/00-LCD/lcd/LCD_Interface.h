/*
 * LCD_Interface.h
 *
 *  Created on: Nov 30, 2020
 *      Author: neutr
 */

#ifndef LCD_INTERFACE_H_
#define LCD_INTERFACE_H_

#include "STD_Type.h"

void LCD_voidInit(void);

void LCD_voidSendData(u8 Copy_U8Data);


void LCD_voidSendCommand(u8 Copy_U8Command);
void LCD_VidSendString(u8 Copy_U8String);

#endif /* LCD_INTERFACE_H_ */
