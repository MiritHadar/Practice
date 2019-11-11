/*******************************************************************************
*	Description: Queue							   		          	           *
*	Author: Mirit Hadar									  	 	       		   *
*	Reviewer: Gil Kremer									 	 	           *
*	Status:										 	  	         		       *
*	Last Update: 										  	         	       *
*******************************************************************************/

#include <stdio.h>		/*puts, printf*/
#include <stdlib.h>		/*malloc, free*/

#include "queue.h"
#include "singly_linked_list.h"

#define UNUSED_VAR(x) (void)(x)

int main()
{
/*********************************First Queue**********************************/
	/*initializing vars*/
	int arr[10] = {0,1,2,3,4,5,6,7,8,9};
	int arr1[5] = {0,1,2,3,4};
	int i = 0;
	
    queue_t *removed = NULL;
	queue_t *queue = QCreate();
	queue_t *queue_to_append = QCreate();
	
	if (NULL == queue)
	{
	    printf("%d - failed to create an empty queue\n", __LINE__);    
	}
	puts("**********PUSH 10 ELEMENTS IN FIRST Q****************");
    
    
	for (i = 0; i < 10; ++i)            /*insert 10 elements to Q*/
	{
	    QEnqueue(queue, &arr[i]);
	    if (0 != *(int*)QPeek(queue))
	    {
	       printf("%d - failed to peek non empty queue\n", __LINE__);
	    }   
	}
	PrintQ(queue);
	
    puts("**********PUSH 5 ELEMENTS IN SECOND Q**************");
    for (i = 0; i < 5; ++i)            /*insert 5 elements to Q 2*/
	{
	    QEnqueue(queue_to_append, &arr1[i]);
	    printf("%d\n", *(int*)QPeek(queue_to_append));
	    if (0 != *(int*)QPeek(queue_to_append))
	    {
	       printf("%d - failed to peek second queue\n", __LINE__);
	    }   
	}
	
    if (10 != QSize(queue))
	{
	    printf("%d - failed to return size for 10 elements\n", __LINE__);    
	}
 
    puts("pop 5 ELEMENTS");
    
    for (i = 0; i < 5; ++i)             /*Pop 5 elements from Q 1*/
	{
        removed = QDequeue(queue);
	}
	
	if (4 != *(int*)removed)
	{
	    printf("%d - failed to return removed value\n", __LINE__);    
	}
	
	if (0 != QIsEmpty(queue))
	{
	    printf("%d - failed to report a non-empty queue\n", __LINE__);    
	}

    if (5 != QSize(queue))
	{
	    printf("%d - failed to return size for 4 elements\n", __LINE__);    
	}

	QAppend(queue, queue_to_append);        /**********APPEND*************/
	
	puts("appended");
	printf("peek %d\n", *(int*)QPeek(queue));
	printf("peek %d\n", *(int*)QPeek(queue_to_append));     /*peek empty*/
	
	QDestroy(queue_to_append);                              /*destroy old Q*/
	
    PrintQ(queue);
    
	for (i = 0; i < 10; ++i)             /*Pop and retain one in the Q*/
	{
        removed = QDequeue(queue);
        printf("%d remove - %d\n", i, *(int*)removed);
	}
	
    removed = QDequeue(queue);

	if (NULL != QPeek(queue))
	{
	    printf("%d - failed to return QPeek value NULL\n", __LINE__);    
	}
	
	if (NULL != removed)
	{
	    printf("%d - failed to return removed value NULL\n", __LINE__);    
	}
	
	removed = QDequeue(queue);          /********remove last******/
	
	if (NULL != removed)
	{
	    printf("%d - failed to return removed value\n", __LINE__);    
	}
	
	if (1 != QIsEmpty(queue))           /*IsEmpty when queue empty*/
	{
	    printf("%d - failed to report an empty queue\n", __LINE__);    
	}
	
	printf("size = %lu\n", QSize(queue));    /*check size for empty*/
	
	
	if (0 != QEnqueue(queue, &arr[9]))
	{
	    puts("QEnqueue to emptied out Q - failed");
	}
	    PrintQ(queue);
	
	/*printf("peek enqued to empty %d\n", *(int*)QPeek(queue));*/
	QDestroy(queue);
	
	return 0;
}

