/*
 * KEYPAD.h
 *
 *  Created on: Jun 12, 2020
 *      Author: mazen
 */

#ifndef KEYPAD_H_
#define KEYPAD_H_

#define KEYPAD_PORT PORTB
#define DEBOUNCE_DELAY 10
#define COLS 4
#define ROWS 4



void KEYPAD_VidInit(void);

u8 KEYPAD_u8GetPressedKey(void);


#endif /* KEYPAD_H_ */
