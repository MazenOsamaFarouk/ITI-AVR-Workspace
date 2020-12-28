/*
 * UART.c
 *
 *  Created on: Jul 10, 2020
 *      Author: mazen
 */

#include "../LIB/STD_TYPES.h"
#include "../LIB/BIT_CALC.h"
#include "../DIO/DIO_Interface.h"
#include "UART_Config.h"
#include "UART_Interface.h"
#include "UART_Register.h"

#include "queue_buffer.h"


DATATYPE buffer[BUFFERSIZE] = {0};
queue_type q;

static void (*TX_CallBackFptr)(void) = NULL;
static void (*RX_CallBackFptr)(u8)= NULL ;
static void (*UDR_EMP_CallBackFptr)(void) = NULL ;


void UART_VidInit(void)
{

#if TRANSMIT == ENABLE
	SET_BIT(UCSRB,TXEN);
	/* make the TX pin PD1 output*/
	DIO_VidSetPinDirection(PORTD,PIN1,1);
#elif TRANSMIT == DISABLE
	CLR_BIT(UCSRB,TXEN);
#endif

#if RECEIVE == ENABLE
	SET_BIT(UCSRB,RXEN);
	/* make the RX pin PD0 input*/
	DIO_VidSetPinDirection(PORTD,PIN0,0);
#elif RECEIVE == DISABLE
	CLR_BIT(UCSRB,RXEN);
#endif

#if	TX_INT	== ENABLE
	SET_BIT(UCSRB,TXCIE);
#elif TX_INT == DISABLE
	CLR_BIT(UCSRB,TXCIE);
#endif


#if RX_INT	== ENABLE
	SET_BIT(UCSRB,RXCIE);
#elif RX_INT == DISABLE
	CLR_BIT(UCSRB,RXCIE);
#endif

#if	UDR_EMPTY_INT == ENABLE
	SET_BIT(UCSRB,UDRIE);
#elif UDR_EMPTY_INT == DISABLE
	CLR_BIT(UCSRB,UDRIE);
#endif

u8 UCSRC_setting = 0 ;

#if MODE == ASYNC
CLR_BIT(UCSRC_setting,UMSEL);
#elif MODE == SYNC
SET_BIT(UCSRC_setting,UMSEL);
#endif

UCSRC_setting = (UCSRC_setting & 0xCF) | (PARITY<<UPM0);

UCSRC_setting = (UCSRC_setting & 0xF7) | ((STOP_BITS-1)<<USBS);

if(DATA_SIZE < 9)
{
	CLR_BIT(UCSRB,UCSZ2);
	UCSRC_setting = (UCSRC_setting & 0xF9) | ((DATA_SIZE-5)<<UCSZ0); //  00000110
}
else
{
	SET_BIT(UCSRB,UCSZ2);
	UCSRC_setting = (UCSRC_setting & 0xF9) | ((3)<<UCSZ0);
}

#if MODE == SYNC

	#if XCK_PIN_MODE == RISING_TX
	CLR_BIT(UCSRC_setting, UCPOL);
	#elif XCK_PIN_MODE == FALLING_TX
	SET_BIT(UCSRC_setting, UCPOL);
	#endif

#elif MODE == ASYNC
	CLR_BIT(UCSRC_setting, UCPOL);
#endif

SET_BIT(UCSRC_setting,URSEL);  // UCSRC Select bit

UCSRC =  UCSRC_setting ;

u8 UBRRH_setting = 0 ;
u16 UBRR = 0 ;
u32 DIV = FCPU/BAUD ;


#if DOUBLE_SPEED == DISABLE && MODE == ASYNC

UBRR = ((((u16)(DIV)))>>4)-1 ;

#elif DOUBLE_SPEED == ENABLE && MODE == ASYNC

UBRR = ((((u16)(DIV)))>>3)-1 ;


#elif MODE==SYNC

UBRR = ((((u16)(DIV)))>>1)-1 ;

#endif

UBRRH_setting = (u8)((UBRR>>8) & 0x0F ) ;

//CLR_BIT(UBRRH_setting,URSEL);

UBRRH = UBRRH_setting;

UBRRL = (u8)(UBRR) ;

#if DOUBLE_SPEED == ENABLE && MODE == ASYNC
	SET_BIT(UCSRA,U2X);
#endif

#if MULTI_PROC_MODE == ENABLE
	SET_BIT(UCSRA,MPCM);
#endif




#if USE_BUFFER==YES
	queue_Init(&q,BUFFERSIZE,buffer);
#endif

}
void UART_VidSendData(u8 data)
{
	while( !GET_BIT(UCSRA,UDRE))
	{ /* wait for empty trasnmit buffer */ }
	UDR = data ;
}


u8 UART_u8ReadData(void)
{
	while(!GET_BIT(UCSRA,RXC))
	{ /* wait for data to be received */ }

	return UDR;
}



void UART_VidFlushBuffer(void)
{
	u8 dummy = 0;
	while(GET_BIT(UCSRA,RXC))
		{ /* wait for data to be received */ }

	dummy = UDR;

}

void UART_VidSetBaudRate(u16 baud)
{
	u8 UBRRH_setting = 0 ;
	u16 UBRR = 0 ;
	u32 DIV = FCPU/(u32)baud ;


	#if DOUBLE_SPEED == DISABLE && MODE == ASYNC

	UBRR = ((((u16)(DIV)))>>4)-1 ;

	#elif DOUBLE_SPEED == ENABLE && MODE == ASYNC

	UBRR = ((((u16)(DIV)))>>3)-1 ;


	#elif MODE==SYNC

	UBRR = ((((u16)(DIV)))>>1)-1 ;

	#endif

	UBRRH_setting = (u8)(UBRR & 0xF0) ;

	CLR_BIT(UBRRH_setting,7);

	UBRRH = UBRRH_setting;

	UBRRL = (u8)(UBRR & 0x0F) ;

}



void UART_VidTXSetCallBack(void (*LOC_fptr)(void))
{
	if(LOC_fptr != NULL)
	{
		TX_CallBackFptr = LOC_fptr;
	}

}

void UART_VidRXSetCallBack(void (*LOC_fptr)(u8))
{
	if(LOC_fptr != NULL)
	{
		RX_CallBackFptr = LOC_fptr;
	}
}


void UART_printf(char string[])
{
	for(int i=0; string[i] != '\0'; i++)
	{
		UART_VidSendData(string[i]);
	}
}

void UART_scanf(char* string, u16 size)
{
	for(int i=0; i<size; i++)
	{
	string[i]=UART_u8ReadData();
	if(string[i] == '\n')
	{
		string[i]='\0';
		break ;
	}
	}
}

/* buffered functions */
u8 UART_GetData(void)
{
	 /* return the next data on the front of the queue */
	return queue_Pop(&q);
}


void __vector_13(void)
{
#if USE_BUFFER==YES
	/* here we push the value in the  buffer */
	/* as long as the buffer is not full, data won't be lost */
	queue_Push(&q,UDR);
#endif
	if(RX_CallBackFptr != NULL)
	{
		RX_CallBackFptr(UDR);
	}

}
void __vector_14(void)
{
	if(UDR_EMP_CallBackFptr != NULL)
	{
		UDR_EMP_CallBackFptr();
	}

}
void __vector_15(void)
{
	if(TX_CallBackFptr != NULL)
	{
		TX_CallBackFptr();
	}
}



