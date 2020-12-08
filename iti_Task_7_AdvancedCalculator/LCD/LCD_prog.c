/*
 * LCD.c
 *
 *  Created on: Jun 5, 2020
 *      Author: mazen
 */
#include <string.h>
#include <util/delay.h>

#include "../DIO/DIO_Interface.h"
#include "LCD_Interface.h"
#include "LCD_Config.h"


// helping functions
void my_reverse(char s[])
 {
     s32 i, j;
     char c;

     for (i = 0, j = strlen(s)-1; i<j; i++, j--) {
         c = s[i];
         s[i] = s[j];
         s[j] = c;
     }
 }

 void itoa(s32 n, char s[])
 {
     s32 i, sign;

     if ((sign = n) < 0)  /* record sign */
         n = -n;          /* make n positive */
     i = 0;
     do {       /* generate digits in reverse order */
         s[i++] = n % 10 + '0';   /* get next digit */
     } while ((n /= 10) > 0);     /* delete it */
     if (sign < 0)
         s[i++] = '-';
     s[i] = '\0';
     my_reverse(s);
 }






void LCD_VidPulseEnable(void)
{
	DIO_VidSetPinValue(LCD_CTRL_PORT,EN,1); /* Enable LCD E=1 */
	_delay_ms(1);
	DIO_VidSetPinValue(LCD_CTRL_PORT,EN,0); /* disable LCD E=0 */
	_delay_ms(1);
}


void LCD_VidSendCommand(u8 LOC_u8command)
{
	u8 mode = MODE;

	if(mode == 8)
	{
		DIO_VidSetPinValue(LCD_CTRL_PORT,RS,0); /* Instruction Mode RS=0 */
		DIO_VidSetPinValue(LCD_CTRL_PORT,RW,0);/* write data to LCD so RW=0 */
		_delay_ms(1);

		DIO_VidSetPortValue(LCD_DATA_PORT,LOC_u8command); /* out the required command to the data bus D0 --> D7 */
		_delay_ms(1);

		LCD_VidPulseEnable();
	}
	else if(mode == 4)
	{
		DIO_VidSetPinValue(LCD_CTRL_PORT,RS,0); /* Instruction Mode RS=0 */
		DIO_VidSetPinValue(LCD_CTRL_PORT,RW,0);/* write data to LCD so RW=0 */
		_delay_ms(1);

		//send MOST SIGNIFICANT 4-bits
		DIO_VidInsPortValue(LCD_DATA_PORT,LOC_u8command>>4,4,4); /* out the required command to the data bus D0 --> D7 */
		_delay_ms(1);
		LCD_VidPulseEnable();

		//send LEAST SIGNIFICANT 4-bits
		DIO_VidInsPortValue(LCD_DATA_PORT,LOC_u8command,4,4); /* out the required command to the data bus D0 --> D7 */
		_delay_ms(1);
		LCD_VidPulseEnable();
	}



}

void LCD_VidSendChar(u8 LOC_u8data)
{
	u8 mode = MODE;

		if(mode == 8)
		{
			DIO_VidSetPinValue(LCD_CTRL_PORT,RS,1); /* Instruction Mode RS=0 */
			DIO_VidSetPinValue(LCD_CTRL_PORT,RW,0);/* write data to LCD so RW=0 */
			_delay_ms(1);

			DIO_VidSetPortValue(LCD_DATA_PORT,LOC_u8data); /* out the required command to the data bus D0 --> D7 */
			_delay_ms(1);

			LCD_VidPulseEnable();
		}
		else if(mode == 4)
		{
			DIO_VidSetPinValue(LCD_CTRL_PORT,RS,1); /* Instruction Mode RS=0 */
			DIO_VidSetPinValue(LCD_CTRL_PORT,RW,0);/* write data to LCD so RW=0 */
			_delay_ms(1);

			//send MOST SIGNIFICANT 4-bits
			DIO_VidInsPortValue(LCD_DATA_PORT,LOC_u8data>>4,4,4); /* out the required command to the data bus D0 --> D7 */
			_delay_ms(1);
			LCD_VidPulseEnable();

			//send LEAST SIGNIFICANT 4-bits
			DIO_VidInsPortValue(LCD_DATA_PORT,LOC_u8data,4,4); /* out the required command to the data bus D0 --> D7 */
			_delay_ms(1);
			LCD_VidPulseEnable();
}



}

void LCD_VidInit(void)
{
	u8 mode = MODE ;
	_delay_ms(50) ;
	 /* Configure the control pins(E,RS,RW) as output pins */
	DIO_VidSetPinDirection(LCD_CTRL_PORT,RS,1);
	DIO_VidSetPinDirection(LCD_CTRL_PORT,RW,1);
	DIO_VidSetPinDirection(LCD_CTRL_PORT,EN,1);

	_delay_ms(1);

	if(mode == 8)
	{
		DIO_VidSetPortDirection(LCD_DATA_PORT,0xFF); /* Configure the data port as output port */
		LCD_VidSendCommand(TWO_LINE_LCD_Eight_BIT_MODE); /* use 2-line lcd + 8-bit Data Mode + 5*7 dot display Mode */
		_delay_ms(1);
		LCD_VidSendCommand((DIPLAY_ON|CURSOR_EN)); /* cursor off */
		_delay_ms(1);
		LCD_VidSendCommand(0x06); //Entry mode set-see page(17)
		LCD_VidSendCommand(CLEAR_DISPLAY); /* clear LCD at the beginning */
		_delay_ms(1);
		LCD_VidSendCommand(0x03); //return home
		_delay_ms(2);

	}
	else if(mode == 4)
	{
		// set only PORT 4~7 pins as outputs
		 /* Configure the data port as output port */

			DIO_VidSetPinDirection(LCD_DATA_PORT,4,1);
			DIO_VidSetPinDirection(LCD_DATA_PORT,5,1);
			DIO_VidSetPinDirection(LCD_DATA_PORT,6,1);
			DIO_VidSetPinDirection(LCD_DATA_PORT,7,1);


		/* FUNCTION SET */
		//send 0010 twice with delay in between
		LCD_VidSendCommand(0x02);

		//send N,F flags
		LCD_VidSendCommand(0x28);
		//_delay_ms(1);
		/* END OF FUNCTION SET */


		/* DISPLAY ON/OFF */
		//send 0000 once with a delay, then send 1(D)(C)(B) flags
		LCD_VidSendCommand(0x0C|CURSOR_ON);
		//_delay_ms(1);
		/* END OF DISPLAY ON/OFF*/



		/* ENTRY MODE SET*/
		LCD_VidSendCommand(0x06);
		//_delay_ms(1);
		/* END OF ENTRY MODE SET*/

		LCD_VidSendCommand(0x80);

		/* DISPLAY CLEAR */
		LCD_VidSendCommand(CLEAR_DISPLAY);
		_delay_ms(2);
		/* END OF DISPLAY CLEAR */


	}




}

void LCD_VidPrintString(char* the_string, u32 delay)
{

	while((*the_string) != '\0')
	{
		LCD_VidSendChar(*the_string) ;
		the_string++;
		if(delay != 0)
		{
			_delay_ms(delay);
		}
	}
}

void LCD_VidPrintNum(s32 num)
{
//	u32 buffer_size = snprintf(NULL,0,"%d",(int)num);
//	char buffer[buffer_size+1];
//	snprintf(buffer,sizeof(buffer),"%d",(int)num);
	char buffer[BUFFER_SIZE]={0};
	itoa(num,buffer);
	LCD_VidPrintString(buffer,0);
}

void LCD_VidSetCursorPosition(u8 line_pos, u8 line_no)
{
	if((line_no%NO_LINES) == 0)
	{
		LCD_VidSendCommand(DISPLAY_ORG + (line_pos%NO_CHARS) );
	}
	else
	{
		LCD_VidSendCommand(DISPLAY_ORG + (line_pos%NO_CHARS) + 64 );
	}
}


void LCD_VidScrollDisplay(u8 amount ,u8 right_left, u32 delay)
{
	if(right_left == RIGHT)
	{
		for(int i=0; i<amount; i++)
		{
			LCD_VidSendCommand(SCROLL_RIGHT);

			if(delay != 0)
			{
				_delay_ms(delay);
			}

		}
	}
	else if(right_left == LEFT)
	{
		for(int i=0; i<amount; i++)
		{
			LCD_VidSendCommand(SCROLL_LEFT);

			if(delay != 0)
			{
				_delay_ms(delay);
			}
		}
	}
}

void LCD_VidSaveCustomChar(const u8 byte_array[], u8 cgRAM_address)
{
	LCD_VidSendCommand(CGRAM_BASE+(cgRAM_address*8)); //set CGRAM address command

	//send custom character bitmap
	for(int i=0; i<8 ; i++)
	{
		LCD_VidSendChar(byte_array[i]);
	}

	LCD_VidSendCommand(0x80); //set reading to be from DDRAM again
}

void LCD_VidSaveCustomCharArray(u8 no_chars,const u8 char_array[][8])
{
	for(int i=0; i<no_chars ; i++)
	{
		LCD_VidSaveCustomChar(char_array[i],i);
	}
}


void LCD_VidPrintCustomChar(u8 cgRAM_address)
{
	LCD_VidSendChar(cgRAM_address);
}

void LCD_VidScanLines() //scans LCD lines to know the position of each charachter in the given LCd
{						//its a helping function intended to be used for debugging
	for(int i=0; i<80 ; i++)
	{
		LCD_VidSendCommand(DISPLAY_ORG + (i) ); //set cursor position
		LCD_VidPrintNum(i); //display char
		_delay_ms(250);
		LCD_VidSendCommand(DISPLAY_ORG + (i) ); //go back
		LCD_VidSendChar(' '); // display a space instead to erase the charachter
		//repeat until u scan all lines
	}
}



