/*******************************************************************************
*	Description: Queue							   		          	           *
*	Author: Mirit Hadar									  	 	       		   *
*	Reviewer: Gil Kremer									 	 	           *
*	Status:										 	  	         		       *
*	Last Update: 										  	         	       *
*******************************************************************************/

#include <stdio.h>     /*printf*/
#include <stdlib.h>     /*malloc, free*/
#include <assert.h>     /*   assert   */
#include "queue.h"
#include "singly_linked_list.h"

#define UNUSED_VAR(x) (void)(x)
#define STUB    1     

#ifndef NDEBUG
	#define PUTS(x) puts(x)
#else
	#define PUTS(x)
#endif

struct queue
{
    slist_node_t *head;
    slist_node_t *tail;
};

/**********************************Create**************************************/
queue_t *QCreate(void)
{
    queue_t *queue = malloc(sizeof(queue_t));
    
    if (NULL == queue)
    {
        return NULL;
    }

    queue->head = SLLCreate(NULL, NULL);    /*create a stub at the beginning*/
    
    if (NULL == queue->head)
    {
        free(queue);
        return NULL;
    }
    
    queue->tail = queue->head;
    
    return queue;
}

/*********************************QEnqueue*************************************/
int QEnqueue(queue_t *queue, void *data)
{
    slist_node_t *new_node = NULL;
    
    assert(queue);
    
    new_node = SLLCreate(data, NULL);       /*create a node from data*/
    
    if (NULL == new_node)
    {
        return 1;
    }
    
    queue->tail = SLLInsertAfter(queue->tail, new_node);
    
    return 0;
}

/*********************************QDequeue*************************************/
void *QDequeue(queue_t *queue)
{
    slist_node_t *removed = NULL;
    void *data = NULL;
    
    assert(queue);
    
    if (queue->head == queue->tail)             /*  when queue empty     */
    {
        return NULL;
    }
    
    removed = SLLRemoveAfter(queue->head);
    
    if (NULL == queue->head->next)              /*  when 1 elem remaines */
    {                                           /*head & tail point at it*/
		queue->tail = queue->head;
    }
    
    data = removed->data;
    SLLFreeAll(removed);
    
    return data;
}

/*********************************QDestroy*************************************/
void QDestroy(queue_t *queue)
{
    assert(queue);
    
    SLLFreeAll(queue->head);
    free(queue);    queue = NULL;   /*free admin struct*/
}

/*********************************QIsEmpty*************************************/
int QIsEmpty(const queue_t *queue)
{
    assert(queue);
    
    return (queue->tail == queue->head); 
}

/***********************************QSize**************************************/
size_t QSize(const queue_t *queue)
{
    assert(queue);
   
    return SLLCount(queue->head) - STUB;
}

/***********************************QPeek**************************************/
void *QPeek(const queue_t *queue)
{
    assert(queue);
    
    if (1 == QIsEmpty(queue))
    {
        return NULL;
    }
    
    return queue->head->next->data;
}

/**********************************QAppend*************************************/
void QAppend(queue_t *to, queue_t *from)
{
    assert(to);
    assert(from);
    
    if (1 != QIsEmpty(from))                    /*      when "from" empty     */
    {
        to->tail->next = from->head->next;      /*          append            */
        to->tail = from->tail;                  /*set a new tail to appended Q*/
        from->tail = from->head;
        from->head->next = NULL;
    }
}

/****************************PrintQ-For Debug**********************************/
#ifndef NDEBUG
    #define __NDEBUG__
void PrintQ(queue_t *queue)
{
	size_t i = 1;
	
	slist_node_t *q_start = queue->head;
	
	if (queue->tail == queue->head)
	{
		puts("Queue is empty");
	}
	
	queue->head = queue->head->next;    /*skip the stub*/
	
	while (queue->head != NULL)
	{
		printf("Entry #%lu -> data = %d\n", i, *(int *)(queue->head->data));
		
		queue->head = queue->head->next;
		++i;
	}
	
	queue->head = q_start;
}
#endif


