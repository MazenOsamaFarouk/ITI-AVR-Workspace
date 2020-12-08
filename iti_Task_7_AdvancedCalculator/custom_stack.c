#include "custom_stack.h"



void CustomStack_Init(CustomStack*me, TYPE*data, int size)
{
    if(me != NULL)
    {
        me->count=0;
        me->top=0;
        me->size=size;
        if(data!=NULL)
        {
          me->data=data;
        }
    }
}
void CustomStack_Push(CustomStack*me, TYPE data)
{
    	/* check if valid */
    if(me != NULL)
    {
            /* check if full */
        if(CustomStack_IsFull(me) != FULL)
        {
            /* move data in array */
            me->data[me->top]=data;
            me->top = (me->top+1)%(me->size);
            me->count++;
        }
    }
}
TYPE CustomStack_Pop(CustomStack*me)
{
    TYPE destination;
    /* check if valid */
	if (me != NULL)
	{
		/* check if empty */
		if (CustomStack_IsEmpty(me) != EMPTY )
		{
            /* decrement top */
			me->top = ( me->top>0 ? (me->top-1):(me->top) ) ;
			me->count-- ;
			/* return top element in destination if user wants (i.e. destination is not null)*/
			destination = me->data[me->top];
			
		}
	}	
return destination;
}
TYPE CustomStack_Peek(CustomStack*me)
{
    TYPE destination;
    /* check if valid */
	if (me != NULL)
	{
		/* check if empty */
		if (CustomStack_IsEmpty(me) != EMPTY )
		{
			/* return top element in destination if user wants (i.e. destination is not null)*/
			destination = me->data[me->top-1];
			// /* decrement top */
			// me->top = ( me->top>0 ? (me->top-1):(me->top) ) ;
			// me->count-- ;
		}
	}	
return destination;

}
int CustomStack_GetCount(CustomStack*me)
{
    return me->count;
}
void CustomStack_Clear(CustomStack*me)
{
    me->top=0;
    me->count = 0;
}
StackStatus CustomStack_IsEmpty(CustomStack*me)
{
    /* check if valid */
	if (me != NULL)
	{
		return (me->top==0 ? EMPTY:NOT_FULL) ;	
	}
	else
	{
		return NOT_INIT;	
	}	

}
StackStatus CustomStack_IsFull(CustomStack*me)
{
    if (me != NULL)
	{
		return (me->top==(me->size-1) ? FULL:NOT_FULL ) ;
	}
	else
	{
		return NOT_INIT;
	}
}
