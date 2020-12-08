/*
 * LCD.h
 *
 *  Created on: Jun 5, 2020
 *      Author: mazen
 */

#ifndef LCD_H_
#define LCD_H_




/* LCD Commands */
#define CLEAR_DISPLAY 0x01
#define TWO_LINE_LCD_Eight_BIT_MODE 0x38
#define DIPLAY_ON 0b00001110
#define DISPLAY_ORG 0x80
#define LINE_OFFSET 30
#define SCROLL_LEFT    0b00011000
#define SCROLL_RIGHT   0b00011100
#define RIGHT  1
#define LEFT   0

#define CGRAM_BASE 0x40

/* custom chars  */

#define HEART {0x00, 0x00, 0x1B, 0x1F, 0x1F, 0x0E, 0x04, 0x00}
#define STICK_FIG {0x0E,0x0E,0x04,0x0E,0x15,0x04,0x0A,0x11}
#define STICK_FIG_RUN {0x07,0x07,0x02,0x0E,0x0B,0x02,0x05,0x09}
//#define BALL {0x00,0x00,0x00,0x00,0x00,0x03,0x03,0x00}


 /* functions  */
void LCD_VidPulseEnable(void);

void LCD_VidSendCommand(u8 LOC_u8command);

void LCD_VidSendChar(u8 LOC_u8data);

void LCD_VidInit(void);

void LCD_VidPrintString(char* the_string, u32 delay);

void LCD_VidPrintNum(s32 num);

void LCD_VidSetCursorPosition(u8 line_pos, u8 line_no);

void LCD_VidScrollDisplay(u8 amount ,u8 right_left, u32 delay);

void LCD_VidSaveCustomChar(const u8 byte_array[], u8 cgRAM_address);

void LCD_VidSaveCustomCharArray(u8 no_chars,const u8 char_array[][no_chars]);

void LCD_VidPrintCustomChar(u8 cgRAM_address);

void LCD_VidScanLines();


#endif /* LCD_H_ */
