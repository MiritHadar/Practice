/*******************************************************************************
*	Description: p_queue							   		                   *
*	Author: Mirit Hadar									  	 	       		   *
*	Reviewer: Or Marziano								 	 	               *										  	         	       *
*******************************************************************************/
/*
#include <stdio.h>		puts, printf
#include <stdlib.h>		malloc, free

#include "p_queue.h"

#define ARR_SIZE1 10
#define UNUSED_VAR(x) (void)(x)

#define dlist_node dlist_info    

#ifndef NDEBUG
	#define PUTS(x) puts(x)
#else
	#define PUTS(x)
#endif

static int IsBigger (const void *data1, const void *data2, void *param);
static int IsEqual(const void *data, const void *to_compare, void *args);

int main()
{
    size_t i = 0;
    int data8 = 8;
    int data2 = 2;
    int arr1[ARR_SIZE1] = {2,3,3,3,6,7,8,9,10,14};
    
    pqueue_t *pq = PQCreate(*IsBigger, NULL);
    
     if (0 != PQSize(pq))
    {
	    printf("%d - failed Size\n", __LINE__);
    }
    
    if (1 != PQIsEmpty(pq))
    {
	    printf("%d - failed IsEmpty\n", __LINE__);
    }
    
    for (i = 0; i < ARR_SIZE1; ++i)
    {
        PQEnqueue(pq, &arr1[i]);
    }
    
    if (2 != *(int*)PQPeek(pq))
    {
	    printf("%d - failed to Peek\n", __LINE__);
    }
    
    if (0 != PQIsEmpty(pq))
    {
	    printf("%d - failed IsEmpty\n", __LINE__);
    }
    
    if (10 != PQSize(pq))
    {
	    printf("%d - failed Size\n", __LINE__);
    }
    printf("%d\n", *(int*)PQDequeue(pq));

    if (2 != *(int*)PQDequeue(pq))
    {
        printf("%d - failed to PQDequeue\n", __LINE__);
    }

    PQErase(pq, IsEqual, &data8, NULL);
    PQErase(pq, IsEqual, &data2, NULL);

    if (NULL != PQErase(pq, IsEqual, &data8, NULL))
    {
        printf("%d - failed to PQ Erase\n", __LINE__);
    }
    
    if (3 != *(int*)PQPeek(pq))
    {
	    printf("%d - failed to Peek\n", __LINE__);
    }
    
    if (8 != PQSize(pq))
    {
	    printf("%d - failed Size\n", __LINE__);
    }
          
    PQClear(pq);
    
    if (1 != PQIsEmpty(pq))
    {
	    printf("%d - failed IsEmpty\n", __LINE__);
    } 
    
    
    PQDestroy(pq); 
    
    return 0;
}

static int IsBigger(const void *before, const void *after, void *param)
{
    UNUSED_VAR(param);
    
    return (*(int*)before < *(int*)after);
    
}


static int IsEqual(const void *data, const void *to_compare, void *args)
{                                      
    UNUSED_VAR(args);
    
    return (*(int*)data == *(int*)to_compare);
}*/


#include <stdio.h>          /* puts */ 
#include "p_queue.h"        /* header file */

#define UNUSED_VAR(x) (void)(x)


void TestPQEnqueue();
void TestPQDequeue();
void TestPQSize();
void TestPQClear();
void TestPQErase();
		


int IsBefore(const void *data1, const void *data2, void *param);
int IsMatch(const void *data1, const void *data2, void *param);

int main()
{
	TestPQEnqueue();
	TestPQDequeue();
	TestPQSize();
	TestPQClear();
	/*TestPQErase(); */

	return 0;
}

int IsBefore(const void *before, const void *after, void *param)
{
	UNUSED_VAR(param);

	return *(size_t*)before < *(size_t*)after;
}

int IsMatch(const void *data1, const void *data2, void *param)
{
	UNUSED_VAR(param);

	return *(size_t*)data1 == *(size_t*)data2;
}


void TestPQEnqueue()
{
	int a = 2, b = 3;
	pqueue_t *pq = PQCreate(IsBefore, NULL);

	PQEnqueue(pq, &a);

	if (2 != *(int *)PQPeek(pq))
	{
		puts("Error in function PQEnqueue");
	}

	PQEnqueue(pq, &b);

	if (2 != *(int *)PQPeek(pq))
	{
		puts("Error in function PQEnqueue");
	}

	PQDestroy(pq);
}

void TestPQDequeue()
{
	int a = 2, b = 3;
	pqueue_t *pq = PQCreate(IsBefore, NULL);

	PQEnqueue(pq, &a);
	PQEnqueue(pq, &b);
	printf("%d\n", *(int*)PQDequeue(pq));

	if (2 != *(int *)PQDequeue(pq))
	{
		puts("Error in function PQDequeue");
	}
	printf("%d\n", *(int*)PQDequeue(pq));
	if (3 != *(int *)PQDequeue(pq))
	{
		puts("Error in function PQDequeue");
	}

	PQDestroy(pq);
}

void TestPQSize()
{
	int a = 2, b = 3;
	pqueue_t *pq = PQCreate(IsBefore, NULL);

	if (0 != PQSize(pq))
	{
		puts("Error in function PQSize");
	}

	PQEnqueue(pq, &a);
	
	if (1 != PQSize(pq))
	{
		puts("Error in function PQSize");
	}
	
	PQEnqueue(pq, &b);
	
	if (2 != PQSize(pq))
	{
		puts("Error in function PQSize");
	}

	PQDestroy(pq);
}

void TestPQClear()
{
	int a = 2, b = 3;
	pqueue_t *pq = PQCreate(IsBefore, NULL);

	if(1 != PQIsEmpty(pq))
	{
		puts("Error in function PQIsEmpty");
	}

	PQEnqueue(pq, &a);
	PQEnqueue(pq, &b);

	if(0 != PQIsEmpty(pq))
	{
		puts("Error in function PQIsEmpty");
	}

	PQClear(pq);

	if(1 != PQIsEmpty(pq))
	{
		puts("Error in function PQClear");
	}

	PQDestroy(pq);
}

/* void TestPQErase()
{
	int a = 2, b = 3, c = 5;
	int x = 4;
	pqueue_t *pq = PQCreate(IsBefore, NULL);

	PQEnqueue(pq, &a);
	PQEnqueue(pq, &b);
	PQEnqueue(pq, &c);

	if (3 != *(int *)PQErase(pq, IsMatch, &b, NULL))
	{
		puts("Error in function PQErase");
	}

	if (NULL != PQErase(pq, IsMatch, &x, NULL))
	{
		puts("Error in function PQErase");
	}

	PQDestroy(pq);
}
 */






