/*
 * queue_buffer.c
 *
 *  Created on: Dec 24, 2020
 *      Author: mazen
 */


#include "../LIB/STD_TYPES.h"
#include "queue_buffer.h"

// Circular queue using arrays
void queue_Init( queue_type* me, u32 buffer_size, DATATYPE* data)
{
	if (me != NULL)
	{
		me->buf_size = buffer_size;
		me->front = 0;
		me->back = 0;
		me->count =0 ;
		me->data=data ;
	}
}
void queue_Push( queue_type* me, DATATYPE data)
{
	/* check if valid */
	if (me != NULL)
	{
		 if (queue_isFull(me) != FULL	)
		{
				/* move data in array */
			me->data[me->back]=data;
			me->back=(me->back+1)%me->buf_size;
			me->count++;
		}
	}

}
int queue_Pop( queue_type* me)
{
	int pop = 0;
	/* check if valid */
	if (me != NULL)
	{
		/* check if empty */
		if (queue_isEmpty(me) != EMPTY)
		{
			pop = me->data[me->front];
			/* increment front */
			me->front = (me->front+1)%(me->buf_size) ;
			me->count--;
		}
	}
	return pop;
}
int queue_Peek( queue_type* me)
{
	int peek = 0;
	/* check if valid */
	if (me != NULL)
	{
		/* check if empty */
		if (queue_isEmpty(me) != EMPTY)
		{
			peek = me->data[me->front];
		}
	}
	return peek;
}
u32 queue_GetCount(queue_type* me)
{
	return me->count;
}
void queue_Clear(queue_type* me)
{
	/* check if valid */
	if (me != NULL)
	{
		me->front = me->back = me->count = 0 ;
	}
}

BUF_STATUS queue_isEmpty( queue_type* me)
{
	/* check if valid */
	if (me != NULL)
	{
		return (me->count == 0)? EMPTY:NOT_EMPTY;
		//return (me->front==me->back ? EMPTY:NOT_EMPTY);
	}
	else
	{
		return NOT_INIT;
	}
}
BUF_STATUS queue_isFull( queue_type* me)
{
	/* check if valid */
	if (me != NULL)
	{
		return (me->count == me->buf_size)? FULL:NOT_FULL ;
		//return (me->back+1)==me->front ? FULL:NOT_FULL ;
	}
	else
	{
		return NOT_INIT;
	}
}

