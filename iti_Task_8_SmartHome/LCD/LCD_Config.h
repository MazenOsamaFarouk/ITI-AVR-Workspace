/*
 * LCD_Config.h
 *
 *  Created on: Nov 30, 2020
 *      Author: mazen
 */

#ifndef LCD_LCD_CONFIG_H_
#define LCD_LCD_CONFIG_H_

/* LCD data length MODE select (type 8 for 8-bit mode, 4 for 4-bit mode  */
#define MODE 4

#define NO_LINES 2
#define NO_CHARS 16
/* LCD HW Pins */
#define RS PIN0
#define RW PIN1
#define EN  PIN2
#define LCD_CTRL_PORT PORTC
#define LCD_DATA_PORT PORTA


#define CURSOR_EN	0x01
#define CURSOR_ON   0x02
// Maximum number of digits for a number to display
#define BUFFER_SIZE 9  // 8 digits + '\0'


#endif /* LCD_LCD_CONFIG_H_ */
