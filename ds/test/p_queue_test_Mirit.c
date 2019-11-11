/*******************************************************************************
*	Description: p_queue							   		                   *
*	Author: Mirit Hadar									  	 	       		   *
*	Reviewer: Or Marziano								 	 	               *										  	         	       *
*******************************************************************************/

#include <stdio.h>		/*puts, printf*/
#include <stdlib.h>		/*malloc, free*/

#include "doubly_linked_list.h"
#include "sorted_list.h"
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
    /*sorted_list_itr_t s_itr = {NULL};*/
    
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

/*Sort func - returns 1 when the right location idetified and 0 when not*/
static int IsBigger(const void *before, const void *after, void *param)
{
    UNUSED_VAR(param);
    
    return (*(int*)before < *(int*)after);
    
}

/*Act Func*/
static int IsEqual(const void *data, const void *to_compare, void *args)
{                                      
    UNUSED_VAR(args);
    
    return (*(int*)data == *(int*)to_compare);
}









