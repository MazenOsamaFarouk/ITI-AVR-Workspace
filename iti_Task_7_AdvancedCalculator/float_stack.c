#include "float_stack.h"

void FloatStack_Init(FloatStack*me, TYPE2*data, int size)
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
void FloatStack_Push(FloatStack*me, TYPE2 data)
{
    	/* check if valid */
    if(me != NULL)
    {
            /* check if full */
        if(FloatStack_IsFull(me) != fFULL)
        {
            /* move data in array */
            me->data[me->top]=data;
            me->top = (me->top+1)%(me->size);
            me->count++;
        }
    }
}
TYPE2 FloatStack_Pop(FloatStack*me)
{
    TYPE2 destination=0;
    /* check if valid */
	if (me != NULL)
	{
		/* check if empty */
		if (FloatStack_IsEmpty(me) != fEMPTY )
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
TYPE2 FloatStack_Peek(FloatStack*me)
{
    TYPE2 destination=0;
    /* check if valid */
	if (me != NULL)
	{
		/* check if empty */
		if (FloatStack_IsEmpty(me) != fEMPTY )
		{
			/* return top element in destination if user wants (i.e. destination is not null)*/
			destination = me->data[me->top];
			// /* decrement top */
			// me->top = ( me->top>0 ? (me->top-1):(me->top) ) ;
			// me->count-- ;
		}
	}	
return destination;

}
int FloatStack_GetCount(FloatStack*me)
{
    return me->count;
}
void FloatStack_Clear(FloatStack*me)
{
    me->top=0;
    me->count = 0;
}
fStackStatus FloatStack_IsEmpty(FloatStack*me)
{
    /* check if valid */
	if (me != NULL)
	{
		return (me->top==0 ? fEMPTY:fNOT_FULL) ;	
	}
	else
	{
		return fNOT_INIT;	
	}	

}
fStackStatus FloatStack_IsFull(FloatStack*me)
{
    if (me != NULL)
	{
		return (me->top==(me->size-1) ? fFULL:fNOT_FULL ) ;
	}
	else
	{
		return fNOT_INIT;
	}
}
