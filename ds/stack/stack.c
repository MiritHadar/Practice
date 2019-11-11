/*******************************************************************************
*	Description: Stack							   		            		   *
*	Author: Mirit Hadar									  	 	       		   *
*	Reviewer: Evgeny Chernov									 	 	       *
*	Status:	Sent									 	  	         		   *
*	Last Update: 6.5.19										  	         	   *
*******************************************************************************/

#include <stdio.h>		/*puts*/
#include <assert.h>		/*assert*/
#include <stdlib.h>		/*malloc*/
#include <string.h>		/*memcpy*/
#include "stack.h"

#define UNUSED_VAR(x) (void)(x)


struct stack
{
	void *end;
	void *current;
	size_t element_size;
	void *head;
};

static void PushToSorted(stack_t *s, int element);


stack_t *StackCreate(size_t capacity, size_t element_size)
{
	/*allocate memroy for the struct*/
	stack_t *s = (stack_t*) malloc(sizeof(stack_t));
	if (NULL == s)
	{
		puts("Malloc failed, Can't create a stack.");
		return NULL;
	}
	
	assert(capacity);
	assert(element_size);

	/*allocate memroy for the stack*/
	s->head = (void*)malloc(capacity * element_size); /*malloc for array*/

	if (NULL == s->head)
	{
		puts("Malloc failed, Can't create an array for the stack.");
		/*free(s);		s = NULL;*/
		return NULL;
	}
	
	/*place members of stack*/
	s->current = s->head;
	s->end = (char*)(s->head) + (capacity * element_size);
	s->element_size = element_size;
	
	return s;
}


int StackPush(stack_t *s, const void *element)
{
	assert(s);
	assert(element);

	if(1 == IsStackFull(s))	/*check if there's room to push to*/
	{
		return 1;
	}

	memcpy(s->current, element, s->element_size);  /*add new element*/
	*(char*)&s->current += s->element_size;		/*proceed current's pointer*/

	return 0;
}


void StackPop(stack_t *s)
{
	assert(s);

	if(1 == IsStackEmpty(s))		       /*check if there's room to push to*/
	{
		/*puts("underflow - nothing to pop");*/
		return;
	}
	else
	{
		*(char*)&s->current -= s->element_size;	/*move back current's pointer*/
	}
}

void *StackPeek(stack_t *s)
{
	/*assert(s);*/

	if(1 == IsStackEmpty(s))
	{
		/*puts("Stack empty - nothing to peek");*/
		return NULL;
	}
	else
	{
		return ((char*)(s->current) - s->element_size);
	}
}

size_t StackSize(const stack_t *s)
{
	assert(s);

	return ((*(char*)&(s->current) - *(char*)&(s->head))/s->element_size);
}

void StackDestroy(stack_t *s)
{
	assert(s);
	assert(s->head);

	free(s->head);		s->head = NULL;			/*free haed */
	s->end = NULL;		    					 /*free end */
	s->current = NULL;					     /*free current */
	free(s);		        s = NULL;		    /*free stack*/
}

int IsStackFull(stack_t *s)	/*return 1 if full*/
{
	assert(s);

	if(s->end == s->current)
	{
		return 1;
	}
	return 0;
}

int IsStackEmpty(stack_t *s)	/*return 1 if empty*/
{
	/* assert(s); */

	if(s->head == s->current)
	{
		return 1;
	}
	return 0;
}

/*void SortStack(stack_t *s)
{
	int tmp = 0;
	int tmp1 = 0;

	if (StackSize(s) > 1)
	{
		tmp = *(int*)StackPeek(s);
		StackPop(s);
		SortStack(s);
	}
	else
	{
		if (tmp != 0)
		{
			if (*(int*)StackPeek(s) < tmp)
			{
				StackPush(s, &tmp);
			}
			else
			{
				tmp1 = *(int*)StackPeek(s);
				StackPop(s);
				StackPush(s, &tmp);
			}

			SortStack(s);
		}
		else
		{
			if (tmp1 > 0)
			{
				StackPush(s, &tmp1);
				SortStack(s);
			}
		}
	}
}*/

void SortStack(stack_t *s)
{
	int element = 0;

	if (!IsStackEmpty(s))
	{
		element = *(int*)StackPeek(s);
		StackPop(s);
		SortStack(s);
		PushToSorted(s, element);
	}
}

static void PushToSorted(stack_t *s, int element)
{
	int tmp = 0;

	if (IsStackEmpty(s) || *(int*)(StackPeek(s)) < element)
	{
		StackPush(s, &element);
		return;
	}
	tmp = *(int*)StackPeek(s);
	StackPop(s);
	PushToSorted(s, element);
	StackPush(s, &tmp);
}







