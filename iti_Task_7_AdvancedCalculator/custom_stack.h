#ifndef _CUSTOM_STACK_H
#define _CUSTOM_STACK_H

#ifndef NULL
#define NULL ((void*)0)
#endif



// configs
typedef    char    TYPE;


typedef enum 
{
	EMPTY=0,
	FULL=!EMPTY,
	NOT_FULL,
	NOT_EMPTY,
	NOT_INIT /*error in case buffer is not initialized */
}StackStatus;

typedef struct 
{
    int top;
    int size;
    int count;
    TYPE* data;
}CustomStack;

void CustomStack_Init(CustomStack*me, TYPE*data, int size);
void CustomStack_Push(CustomStack*me, TYPE data);
TYPE CustomStack_Pop(CustomStack*me);
TYPE CustomStack_Peek(CustomStack*me);
int CustomStack_GetCount(CustomStack*me);
void CustomStack_Clear(CustomStack*me);
StackStatus CustomStack_IsEmpty(CustomStack*me);
StackStatus CustomStack_IsFull(CustomStack*me);


#endif //_CUSTOM_STACK_H