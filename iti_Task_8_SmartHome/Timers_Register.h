/*
 * Timers_Registers.h
 *
 *  Created on: Jun 29, 2020
 *      Author: mazen
 */

#ifndef TIMERS_REGISTER_H_
#define TIMERS_REGISTER_H_

/************** TIMER/COUNTER 0 Registers ************/

/* TIMER/COUNTER 0 control register*/
#define TCCR0  *((volatile u8*)(0x53))

/* Timer/counter 0 Register*/
#define TCNT0  *((volatile u8*)(0x52))

/* Output compare 0 register*/
#define OCR0  *((volatile u8*)(0x5C))


/*************** TIMER/COUNTER 1 Control regs*************************/
#define TCCR1A  *((volatile u8*)(0x4F))

#define TCCR1B  *((volatile u8*)(0x4E))

#define TCNT1L  *((volatile u8*)(0x4C))

#define TCNT1H  *((volatile u8*)(0x4D))

#define TCNT1   *((volatile u8*)(0x4C))

#define OCR1AH  *((volatile u8*)(0x4B))

#define OCR1AL  *((volatile u8*)(0x4A))

#define OCR1A   *((volatile u8*)(0x4A))

#define OCR1BL  *((volatile u8*)(0x48))

#define OCR1BH  *((volatile u8*)(0x49))

#define OCR1B   *((volatile u8*)(0x48))

#define ICR1H   *((volatile u8*)(0x47))

#define ICR1L   *((volatile u8*)(0x46))

#define ICR1    *((volatile u8*)(0x46))

/**************** 	TIMER/COUNTER 2 control regs*************************/

#define TCCR2   *((volatile u8*)(0x45))

#define TCNT2   *((volatile u8*)(0x44))

#define OCR2    *((volatile u8*)(0x43))

/***********************************************************/

/* Timer/counter  INterrupt mask register   */
#define TIMSK  *((volatile u8*)(0x59))

/*  Timer/counter  INterrupt Flag register  */
#define TIFR   *((volatile u8*)(0x58))

/*  Special Function I/O register  */
#define SFIOR  *((volatile u8*)(0x50))

void __vector_10(void) __attribute__((signal));
void __vector_11(void) __attribute__((signal));






/*********** TIMER0 REGISTER bits***********/
/*TCCR0 bits*/

#define FOC0 7
#define WGM00 6
#define WGM01 3

/* Timer/counter 0 MODES of operation */
#define TCNT0_NORMAL   0
#define TCNT0_PWM      1
#define TCNT0_CTC      2
#define TCNT0_FAST_PWM 3


#define COM00 4
#define COM01 5

#define NORMAL_OC0_DISCONN     (0x00<<4)
#define TOG_OC0                (0x01<<4)

#define CLR_OC0				   (0x02<<4)
#define CLR_OC0_UPCOUNT		   (0x02<<4)
#define CLR_OC0_NON_INV		   (0x02<<4)

#define SET_OC0				   (0x03<<4)
#define SET_OC0_UPCOUNT		   (0x03<<4)
#define SET_OC0_INV		       (0x03<<4)



#define NO_CLK           (0x00)
#define IO_PS_1          (0x01)
#define IO_PS_8          (0x02)
#define IO_PS_64         (0x03)
#define IO_PS_256        (0x04)
#define IO_PS_1024       (0x05)
#define XT_FALLING_EDGE  (0x06)
#define XT_RISING_EDGE   (0x07)

/***************** Timer/counter 1 register bits ****************/

/************ Timer/counter 1 operating modes *********/
/* the difference between similarly named modes is the value of TOP
 * the TOP value is the maximum value that the timer/counter triggers when it
 * reaches it.
 * _OC : means TOP value is determined by the value inside OCR1A
 * _IC : means TOP value is determined by the value inside ICR1
 * for any other setting: the value of the TOP is written below
 *
 * FOR MORE INFO: see DATASHEET: Section: Timer/Counter 1,
 * 								 Subsection: Register Description
 * 								 Table 17-5 WGM1[3:0] modes
 * 								                             */

#define TCNT1_NORMAL       				0   // TOP = 0xFFFF (= MAX )
#define TCNT1_PWM_8bit     				1   // TOP = 0x00FF
#define TCNT1_PWM_9bit     				2   // TOP = 0x01FF
#define TCNT1_PWM_10bit    				3   // TOP = 0x03FF
#define TCNT1_CTC_OC         			4
#define TCNT1_FASTPWM_8bit 				5  // TOP = 0x00FF
#define TCNT1_FASTPWM_9bit 				6  // TOP = 0x01FF
#define TCNT1_FASTPWM_10bit				7  // TOP = 0x03FF
#define TCNT1_PWM_PH_F_CORRECT_IC		8
#define TCNT1_PWM_PH_F_CORRECT_OC		9
#define TCNT1_PWM_PH_CORRECT_IC			10
#define TCNT1_PWM_PH_CORRECT_OC			11
#define TCNT1_CTC_IC					12
///////////RESERVED///////////          13
#define TCNT1_FASTPWM_IC				14
#define TCNT1_FASTPWM_OC				15


/**** Compare output mode A & B settings ***/

#define NORMAL_OC1AB_DISCONN   (0x00)
#define TOG_OC1AB			   (0x01)
#define TOG_OC1A			   (0x01)
#define CLR_OC1AB			   (0x02)
#define CLR_OC1AB_UP_COUNT	   (0x02)
#define CLR_OC1AB_NON_INV	   (0x02)
#define SET_OC1AB			   (0x03)
#define SET_OC1AB_UP_COUNT     (0x03)
#define SET_OC1AB_INV		   (0x03)

#define FOC1A    3
#define FOC1B    2



/*TIMSK bits*/
// Timer/counter 0
#define OCIE0   1
#define TOIE0   0

//Timer/counter 1
#define TOIE1   2
#define OCIE1B  3
#define OCIE1A  4
#define TICIE1  5

//Timer/counter 2
#define TOIE2  6
#define OCIE2  7

/*TIFR bits*/
#define OCF0 1
#define TOV0 0


/* SFIOR bit*/
#define PSR10  0

/* Call back options  */
#define CB_TCNT0_OVF  1
#define CB_TCNT0_CTC  0



#endif /* TIMERS_REGISTER_H_ */
