/*******************************************************************************
*	Description: doubly_linked_list							   		           *
*	Author: Mirit Hadar									  	 	       		   *
*	Reviewer: Nir Kirshbloom									 	 	       *
*	Status:										 	  	         		       *
*	Last Update: 										  	         	       *
*******************************************************************************/

#include <stdio.h>      /*   printf   */
#include <stdlib.h>     /*malloc, free*/
#include <assert.h>     /*   assert   */
#include "doubly_linked_list.h"

#define UNUSED_VAR(x) (void)(x)


#ifndef NDEBUG
	#define PUTS(x) puts(x)
#else
	#define PUTS(x)
#endif

/*########Macro For Casting########*/
#define dlist_node dlist_info

static dlist_itr_t DLLCreateItr(void *data);
static int CountItrs(void *data, void *param);

/*############ITR Struct###########*/
struct dlist_node
{
    void *data;
    struct dlist_node *next;
    struct dlist_node *prev;
};

/*##########Admin Struct###########*/
/******should use with "struct"*****/
struct dlist
{
    struct dlist_node head;
    struct dlist_node tail;
};

/************************************Create************************************/
dlist_t *DLLCreate(void)
{
    /*admin struct*/
    dlist_t *dlist = malloc(sizeof(dlist_t));
    
    if (NULL == dlist)
    {
        return NULL;
    }
    
    /*set stubs at head and tail*/
    dlist->head.prev = NULL;
    dlist->head.next = &(dlist->tail);
    dlist->head.data = NULL;

    dlist->tail.prev = &(dlist->head);
    dlist->tail.next = NULL;
    dlist->tail.data = NULL;
    
    return dlist;
}

/***********************************Destroy************************************/
void DLLDestroy(dlist_t *dlist)
{
    dlist_itr_t itr = NULL;
    dlist_itr_t tmp_itr = NULL;
    
    assert(dlist);
    
    itr = DLLBegin(dlist);
    
    while (!DLLIsSame(itr, DLLEnd(dlist)))
    {
        tmp_itr = itr;
        itr = DLLNext(itr);                            
        DLLErase(tmp_itr);
    } 
    
    free(dlist); dlist = NULL;
}

/***********************************Insert*************************************/
dlist_itr_t DLLInsert(dlist_itr_t where, void *data, dlist_t *dlist)
{
    dlist_itr_t itr = NULL;
    dlist_itr_t prev_where = NULL;
    
    assert(dlist);
    assert(where);

    prev_where = DLLPrev(where);
    
    /*create itr from data*/
    itr = DLLCreateItr(data);
    
    if (NULL != itr)
    {
        /*conect itr to dlist*/
        itr->next = where;
        itr->prev = prev_where;
        where->prev = itr;
        prev_where->next = itr;
        
        return itr;
    }
    
    return DLLEnd(dlist);
}

/*************************Static DLL Create Itr********************************/
static dlist_itr_t DLLCreateItr(void *data)
{
    dlist_itr_t itr = NULL;
    
    itr = malloc(sizeof(struct dlist_node));
    
    if (NULL == itr)
    {
        return NULL;
    }
    
    itr->data = data;
    itr->prev = NULL;
    itr->next = NULL;
    
    return itr;
}
/**********************************IS Empty************************************/
int DLLIsEmpty(const dlist_t *dlist)
{
    assert(dlist);
    
    return (DLLEnd(dlist) == DLLBegin(dlist));
}


/**********************************Is Same*************************************/
int DLLIsSame(dlist_itr_t itr1, dlist_itr_t itr2)
{
    assert(itr1);
    assert(itr2);
    
    return (itr1 == itr2);
}

/************************************Next**************************************/
dlist_itr_t DLLNext(dlist_itr_t itr)
{
    assert(itr);
    
    return itr->next;
}

/************************************Prev**************************************/
dlist_itr_t DLLPrev(dlist_itr_t itr)
{
    assert(itr);
    
    return itr->prev;
}

/************************************Begin*************************************/
/*returns first valid node*/
dlist_itr_t DLLBegin(const dlist_t *dlist)
{
    assert(dlist);
    
    return (dlist->head.next);
}

/************************************End***************************************/
/*returns tail of dlist*/
dlist_itr_t DLLEnd(const dlist_t *dlist)
{
    assert(dlist);
    
    return (dlist_itr_t)&(dlist->tail);
}

/**********************************Get Data************************************/
void *DLLGetData(dlist_itr_t itr)
{
    assert(itr);
    
    return itr->data;
}

/********************************Push Front************************************/
dlist_itr_t DLLPushFront(dlist_t *dlist, void *data)
{
    assert(dlist);
    
    return DLLInsert(DLLBegin(dlist), data, dlist);
}

/*********************************Pop Front************************************/
void *DLLPopFront(dlist_t *dlist)
{
    /*save data of first valid node*/
    void *tmp_data = DLLGetData(DLLBegin(dlist));
    
    DLLErase(DLLBegin(dlist));
    
    return tmp_data;
}

/*********************************Push Back************************************/
dlist_itr_t DLLPushBack(dlist_t *dlist, void *data)
{
    
    assert(dlist);
    
    return DLLInsert(DLLEnd(dlist), data, dlist); 
}

/*********************************Pop Back*************************************/
void *DLLPopBack(dlist_t *dlist)
{
    void *tmp_data = NULL;
    
    assert(dlist);
    
    tmp_data = DLLGetData(DLLPrev(DLLEnd(dlist)));
    
    DLLErase(DLLPrev(DLLEnd(dlist)));
    
    return tmp_data;
}

/***********************************Size***************************************/
static int CountItrs(void *data, void *param)
{
	assert(param);

	UNUSED_VAR(data);

	++*(int *)param;

	return 0;
}

/******************************************************************************/

size_t DLLSize(const dlist_t *dlist)
{
	size_t count = 0;

	DLLForEach(DLLBegin(dlist), DLLEnd(dlist), &count, CountItrs);

	return count;
}

/***********************************Erase**************************************/
dlist_itr_t DLLErase(dlist_itr_t who)
{
    dlist_itr_t next_who = NULL;
    dlist_itr_t tmp_who = NULL;
    
    assert(who);
   
    next_who = DLLNext(who);
    tmp_who = who;
    
    /*reconnection*/
    /*TODO*/
    DLLPrev(who)->next = next_who;
    next_who->prev = DLLPrev(who);
    free(tmp_who);
    
    return next_who;
}

/***********************************Find***************************************/
dlist_itr_t DLLFind(const void *to_compare, dlist_itr_t from, dlist_itr_t to,
								      is_match_func_t match_func, void *param)
{
    dlist_itr_t itr = NULL;
    
    assert(to);
    assert(from);
    assert(to_compare);
    assert(match_func);
    
    itr = from;

    /*while desired matching not found - loop*/                            
    while (!DLLIsSame(itr, to) && 0 == match_func(DLLGetData(itr), to_compare, param))                           
    {
        itr = DLLNext(itr);
    }
        
    return itr;
}

/********************************For Each**************************************/
int DLLForEach(dlist_itr_t from, dlist_itr_t to, void *param,
								   action_func_t action_func)
{
    dlist_itr_t itr = NULL;
    int status = 0;

    assert(to);
    assert(from);
    assert(action_func);
    
    itr = from;
       
    /*while action func hasn't failed - loop*/                                  
    while (0 ==  status && !DLLIsSame(itr, to))
    {
        status = action_func(itr->data, param);
        itr = DLLNext(itr);
    }
        
    return status;
}
								  								   
/********************************Splice****************************************/
void DLLSplice(dlist_itr_t where, dlist_itr_t from, dlist_itr_t to)
{    
    dlist_itr_t prev_where = NULL;
    dlist_itr_t prev_from = NULL;
    dlist_itr_t prev_to = NULL;
    
    assert(where);
    assert(to);
    assert(from);
    
    prev_where = DLLPrev(where);
    prev_from = DLLPrev(from);
    prev_to = DLLPrev(to);
    
    /*reconnect*/
    prev_where->next = from;
    from->prev = prev_where;
    
    prev_to->next = where;
    where->prev = prev_to;
    
    prev_from->next = to;
    to->prev = prev_from;
   
}


void RemoveDup(dlist_t *dlist)
{
    dlist_itr_t head = NULL;
    dlist_itr_t runner = NULL;

    assert(dlist);

    head = DLLBegin(dlist);

    while (head != DLLPrev(DLLEnd(dlist)) && head != DLLEnd(dlist))
    {
        runner = DLLNext(head);
        while (runner != DLLEnd(dlist))
        {
            if (DLLGetData(head) == DLLGetData(runner))
            {
                head = head->next;
                DLLErase(DLLPrev(head));
                runner = head->next;
            }
            else
            {
                runner = runner->next;
            }
        }
        head = head->next;
    }
}

/****************************Print DList Debug*********************************/
#ifndef NDEBUG
void PrintDList(dlist_t *dlist)
{
	dlist_itr_t itr = NULL;

	assert(NULL != dlist);

	for (itr = DLLBegin(dlist); !DLLIsSame(itr, DLLEnd(dlist));
                                            itr = DLLNext(itr))
	{
		printf("%d ", *(int *)itr->data);
	}

	puts("");
}


#endif











































