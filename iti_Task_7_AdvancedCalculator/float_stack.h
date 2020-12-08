#ifndef _FLOAT_STACK_H
#define _FLOAT_STACK_H

#ifndef NULL
#define NULL ((void*)0)
#endif



// configs
typedef    float    TYPE2;


typedef enum 
{
	fEMPTY=0,
	fFULL=!fEMPTY,
	fNOT_FULL,
	fNOT_EMPTY,
	fNOT_INIT /*error in case buffer is not initialized */
}fStackStatus;

typedef struct 
{
    int top;
    int size;
    int count;
    TYPE2* data;
}FloatStack;

void FloatStack_Init(FloatStack*me, TYPE2*data, int size);
void FloatStack_Push(FloatStack*me, TYPE2 data);
TYPE2 FloatStack_Pop(FloatStack*me);
TYPE2 FloatStack_Peek(FloatStack*me);
int FloatStack_GetCount(FloatStack*me);
void FloatStack_Clear(FloatStack*me);
fStackStatus FloatStack_IsEmpty(FloatStack*me);
fStackStatus FloatStack_IsFull(FloatStack*me);


#endif //_FLOAT_STACK_H
