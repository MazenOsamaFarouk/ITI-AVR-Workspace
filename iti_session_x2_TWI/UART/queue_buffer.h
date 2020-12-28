/*
 * queue_buffer.h
 *
 *  Created on: Dec 24, 2020
 *      Author: mazen
 */

#ifndef UART_QUEUE_BUFFER_H_
#define UART_QUEUE_BUFFER_H_


typedef char DATATYPE;


typedef enum
{
	EMPTY=0,
	FULL=!EMPTY,
	NOT_FULL,
	NOT_EMPTY,
	NOT_INIT /*error in case buffer is not initialized */
}BUF_STATUS;

typedef struct
{
	s32 front;
	s32 back;
	u32 buf_size;
	u32 count;
	DATATYPE* data;
}queue_type;


void queue_Init( queue_type* me, u32 buffer_size, DATATYPE* data);
void queue_Push( queue_type* me, DATATYPE data);
int queue_Pop( queue_type* me);
int queue_Peek( queue_type* me);
u32 queue_GetCount(queue_type* me);
void queue_Clear(queue_type* me);

BUF_STATUS queue_isEmpty( queue_type* me);
BUF_STATUS queue_isFull( queue_type* me);

#endif /* UART_QUEUE_BUFFER_H_ */
