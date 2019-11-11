/*******************************************************************************
*	Description: p_queue							   		                   *
*	Author: Mirit Hadar									  	 	       		   *
*	Reviewer: Or Marziano								 	 	               *										  	         	       *
*******************************************************************************/

#include <stdlib.h>     /*malloc, free*/
#include <assert.h>     /*   assert   */

#include "sorted_list.h"
#include "p_queue.h"

#define UNUSED_VAR(x) (void)(x)

#ifndef NDEBUG
	#define PUTS(x) puts(x)
#else
	#define PUTS(x)
#endif

struct pqueue
{
    sorted_list_t *q_head; 
};

pqueue_t *PQCreate(int (*is_before)(const void *d1, const void *d2,
                                                    void *param), void *param)
{
    pqueue_t *pqueue = malloc(sizeof(pqueue_t));
    
    if (NULL == pqueue)
    {
        return NULL;
    }
    
    pqueue->q_head = SOLCreate(is_before, param);
    
    if (NULL == pqueue->q_head)
    {
        free(pqueue);
        
        return NULL;
    }
	
	return pqueue;
}

void PQDestroy(pqueue_t *pq)
{
    assert(pq);
    
    SOLDestroy(pq->q_head);
    pq->q_head = NULL;
    free(pq);   pq = NULL;
}

int PQEnqueue(pqueue_t *pq, void *data)
{
    assert(pq);
    assert(data);
    
    return SOLIsSame(SOLInsert(pq->q_head, data), SOLEnd(pq->q_head));
}

/* 0 for success 1 for failure*/
void *PQDequeue(pqueue_t *pq)
{
    assert(pq);
    
    return SOLPopFront(pq->q_head);
}

void *PQPeek(const pqueue_t *pq)
{
    assert(pq);
    
    return SOLGetData(SOLBegin(pq->q_head));
}

int PQIsEmpty(const pqueue_t *pq)
{
    assert(pq);
    
    return SOLIsEmpty(pq->q_head);
}

size_t PQSize(const pqueue_t *pq)
{
    assert(pq);
    
    return SOLSize(pq->q_head);
}

void PQClear(pqueue_t *pq)
{
    assert(pq);
    
    while (1 != PQIsEmpty(pq))
    {
        PQDequeue(pq);
    }
}

void *PQErase(pqueue_t *pq, int (*match_func)
            (const void *data, const void *to_compare, void *args),
                                            const void *to_match, void *args)
{
    sorted_list_itr_t find_itr = {NULL};
    void *data_to_erase = NULL;
    
    assert(pq);
    assert(match_func);
    assert(to_match);
    
    find_itr = SOLFindIf(SOLBegin(pq->q_head),
                               SOLEnd(pq->q_head), to_match, args, match_func);
                               
    if (SOLIsSame(SOLEnd(pq->q_head), find_itr))
    {
        return NULL;
    }
    
    data_to_erase = SOLGetData(find_itr);
    
    SOLErase(find_itr);
    
    return data_to_erase;
}












