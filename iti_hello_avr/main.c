/*
 * main.c
 *
 *  Created on: Nov 25, 2020
 *      Author: mazen
 */

#include <avr/io.h>
#include <util/delay.h>





inline void D1US(uint8_t _c)
{
	__asm__ volatile("ldi r16,%0\n\t"     /* 1 cyc */
					 "again:dec r16\n\t" /* 1 cyc */
					 "brne again\n"      /* 2 cyc or 1 cyc*/
				:
				: "M" ((uint8_t)_c));

}

inline void OUTER_DELAY(uint16_t _co,uint8_t _ci )
{
	uint8_t low = _co>>8;
	uint8_t high= (uint8_t)_co;
	__asm__ volatile("ldi r23,%0\n\t"
					 "ldi r24,%1\n\t"
					 "ldi r16,%2\n\t"     /* 1 cyc */
					 "again: dec r16\n\t" /* 1 cyc */
					 "brne again\n\t"      /* 2 cyc or 1 cyc*/
					 "sbiw r24:r23,1\n\t"
					 "brne again\n"
					:
					:"M" (low),
					"M" (high),
					"M" (_ci));
}

#define delay_count (8000000UL/10000)

void delay(uint8_t ms)
{
uint16_t cnt;
		asm volatile(
		"\n"
		"L_dl1%=:" "\n\t"
		"mov %A0, %A2" "\n\t"
		"mov %B0, %B2" "\n"
		"L_dl2%=:" "\n\t"
		"sbiw %A0, 1" "\n\t"
		"brne L_dl2%=" "\n\t"
		"dec %1" "\n\t"
		"brne L_dl1%=" "\n\t"
		: "=&w" (cnt)
		: "r" (ms), "r" (delay_count)
		);
}

void delay_Bret(void)
{
	// Assembly code auto-generated
	// by utility from Bret Mulvey
	// Delay 8 000 cycles
	// 1ms at 8.0 MHz

	asm volatile (
	"    ldi  r18, 11	\n"
	"    ldi  r19, 99	\n"
	"1:  dec  r19	\n"
	"    brne 1b	\n"
	"    dec  r18	\n"
	"    brne 1b	\n"
	);

}

int main(void)
{

	DDRA |= (1<<0); //set port A 0 to output


	while(1)
	{
		PORTA ^= (1<<0);  // toggle pin A 0
//		_delay_ms(1000);
//		OUTER_DELAY(100,1);
//		delay(2);
		delay_Bret();
	}

	return 0;
}
