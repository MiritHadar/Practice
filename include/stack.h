/*******************************************************************************
*	Description: Stack							   		            		   *
*	Author: Mirit Hadar									  	 	       		   *
*	Reviewer: Evgeny Chernov									 	 	       *
*	Status:	Sent									 	  	         		   *
*	Last Update: 6.5.19										  	         	   *
*******************************************************************************/

#ifndef OL67_STACK
#define OL67_STACK

#include <stddef.h>		/*size_t*/

typedef struct stack stack_t;


stack_t *StackCreate(size_t capacity, size_t element_size);
int StackPush(stack_t *s, const void *element);
void StackPop(stack_t *s);
void *StackPeek(stack_t *s);
size_t StackSize(const stack_t *s);
void StackDestroy(stack_t *s);
int IsStackFull(stack_t *s);
int IsStackEmpty(stack_t *s);
void SortStack(stack_t *s);


#endif	/*	OL67_STACK	*/
