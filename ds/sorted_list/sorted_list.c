/*******************************************************************************
*	Description: sorted_linked_list							   		           *
*	Author: Mirit Hadar									  	 	       		   *
*	Reviewer: Itay Kahalani									 	 	           *
*	Status:										 	  	         		       *
*	Last Update: 										  	         	       *
*******************************************************************************/

#include <stdio.h>      /*   printf   */
#include <stdlib.h>     /*foreachmalloc, free*/
#include <assert.h>     /*   assert   */
#include "doubly_linked_list.h"
#include "sorted_list.h"

#define UNUSED_VAR(x) (void)(x)


#ifndef NDEBUG
	#define PUTS(x) puts(x)
#else
	#define PUTS(x)
#endif

/*##########Macro For Casting#########*/
#define SOL_ITR(x) (struct sorted_list_info*)x
#define DLL_ITR(x) (dlist_itr_t)x.info

struct sorted_list
{
	dlist_t *dlist;
	is_before_t sort_func;
	void *param;
};

static int PrintData(void *data, void *param);

static sorted_list_itr_t FindLastPlace(sorted_list_t *list,
          sorted_list_itr_t from, sorted_list_itr_t to, const void *to_compare);
          
static sorted_list_itr_t FindFirstPlace(sorted_list_t *list,
          sorted_list_itr_t from, sorted_list_itr_t to, const void *to_compare);
          
/*Create*/
sorted_list_t *SOLCreate(is_before_t sort_func, void *param)
{
    sorted_list_t *list = malloc(sizeof(sorted_list_t));
    
    assert(sort_func);
    
    if (NULL == list)
    {
        return NULL;
    }
    
    list->dlist = DLLCreate();
    list->sort_func = sort_func;
    list->param = param;
    
    return list;
}

/*Destroy*/
void SOLDestroy(sorted_list_t *list)
{
    DLLDestroy(list->dlist);
    list->sort_func = NULL;
    list->param = NULL;
    
    free(list);
}

/*Insert*/
sorted_list_itr_t SOLInsert(sorted_list_t *list, void *data)
{
	sorted_list_itr_t where = {NULL};
		
	assert(list);
		
	/*proceed untill right location is fount and then insert there*/
	where = FindLastPlace(list, SOLBegin(list), SOLEnd(list), data);
	
	where.info = SOL_ITR(DLLInsert(DLL_ITR(where), data, list->dlist));
    
    return where;
}


sorted_list_itr_t SOLErase(sorted_list_itr_t who)
{    
    sorted_list_itr_t next_who = SOLNext(who);
    
    who.info = SOL_ITR(DLLErase(DLL_ITR(who)));
    
    return next_who;
}

int SOLIsSame(sorted_list_itr_t itr1, sorted_list_itr_t itr2)
{
    return DLLIsSame(DLL_ITR(itr1), DLL_ITR(itr2));
}

int SOLIsEmpty(const sorted_list_t *list)
{
    return DLLIsEmpty(list->dlist);
}

size_t SOLSize(const sorted_list_t *list)
{
    return DLLSize(list->dlist);
}

int SOLForEach(sorted_list_itr_t from, sorted_list_itr_t to,
						   void *param, act_func_t act_func)
{
    return DLLForEach(DLL_ITR(from), DLL_ITR(to), param, act_func);
}

/* Merges two sorted lists */
/* User's responsability to free the lists on the test file */
void SOLMerge(sorted_list_t *dest, sorted_list_t *src)
{
	sorted_list_itr_t where = {NULL};
	sorted_list_itr_t from = {NULL};
	sorted_list_itr_t to = {NULL};
    sorted_list_itr_t end_src = {NULL};
    
	assert(NULL != dest);
	assert(NULL != src);

    end_src = SOLEnd(src);
	from = SOLBegin(src);
	to = end_src;
    
    /*loop as long as src didn't end*/
	while (1 != SOLIsSame(from, end_src))
	{
	   /*"where" gets the first position that IsBigger then from(in this case)*/ 
		where = FindLastPlace(dest, SOLBegin(dest), SOLEnd(dest),
                                                            SOLGetData(from));
        
        /*if src didn't end - find next position*/
		if (1 != SOLIsSame(where, SOLEnd(dest)))
		{
			to = FindFirstPlace(src, from, end_src, SOLGetData(where));
		}
        
        /*commit splice*/
		DLLSplice(DLL_ITR(where), DLL_ITR(from), DLL_ITR(to));

        /*next starting point*/
		from = to;
		to = end_src;
	}
}

/*      Returns the address of a node containing requested data    */
/* Searching astrategy by sort func of the sorted list sent to func*/
sorted_list_itr_t SOLFind(sorted_list_t *list, sorted_list_itr_t from, 
							  sorted_list_itr_t to, const void *to_compare)
{
    from = FindFirstPlace(list, from, to, to_compare);
        
    /*    if to_compare can't be before "from" and "from" can't be before  */
    /* to_compare - Find succeded - return "from". for failuer return "to" */
    
    if(1 != SOLIsSame(from, to) &&
        1 == list->sort_func(to_compare, SOLGetData(from), list->param))
    {
        return to;
    }
    
    return from;
}
								 
/* Returns an iterator of a element containing data from to_compare */
/*          regular find by any match func sent                     */
sorted_list_itr_t SOLFindIf(sorted_list_itr_t from, sorted_list_itr_t to,
	   						const void *to_compare, void *param,
							is_match_t is_match_func)
{
    
    from.info = SOL_ITR(DLLFind(to_compare, DLL_ITR(from), DLL_ITR(to),
                                is_match_func, param));
    return from;
}

/* Remove an item from the back of the sorted list 	*/						   
void *SOLPopBack(sorted_list_t *list)
{
   return DLLPopBack(list->dlist);
}

/* Remove an item from the front of the sorted list */
void *SOLPopFront(sorted_list_t *list)
{
   return DLLPopFront(list->dlist);
}

/* Returns the address of the first valid member of the list */
sorted_list_itr_t SOLBegin(const sorted_list_t *list)
{
    sorted_list_itr_t s_itr = {NULL};
    
    assert(list);
    
    s_itr.info = SOL_ITR(DLLBegin(list->dlist));
    
    return s_itr;
}

/* Returns the tail of the list */
sorted_list_itr_t SOLEnd(const sorted_list_t *list)
{
    sorted_list_itr_t s_itr = {NULL};
    
    assert(list);
    
    s_itr.info = SOL_ITR(DLLEnd(list->dlist));
    
    return s_itr;
}

/* Returns the next member of the list */
sorted_list_itr_t SOLNext(sorted_list_itr_t itr)
{
    
    itr.info = SOL_ITR(DLLNext(DLL_ITR(itr)));
    
    return itr;
}

/* Returns the previous member of the list */
sorted_list_itr_t SOLPrev(sorted_list_itr_t itr)
{
   
    itr.info = SOL_ITR(DLLPrev(DLL_ITR(itr)));
    
    return itr;
}

/* Returns a data requested on specific iterator */
void *SOLGetData(sorted_list_itr_t itr)
{    
    return DLLGetData(DLL_ITR(itr));
}

/*********************************Inner Funcs**********************************/

#ifndef NDEBUG
    #define __NDEBUG__
void PrintList(const sorted_list_t *list)
{
    DLLForEach(DLLBegin(list->dlist), DLLEnd(list->dlist), NULL, PrintData);
    
    puts("\n");
}

static int PrintData(void *data, void *param)
{
    UNUSED_VAR(param);
    
    printf("%d ", *(int*)data);
    
    return 0;
}


#endif

/*finds the *last* suitable position*/
static sorted_list_itr_t FindLastPlace(sorted_list_t *list,
           sorted_list_itr_t from, sorted_list_itr_t to, const void *to_compare)
{
    while (1 != SOLIsSame(from, to) &&
                1 != list->sort_func(to_compare, SOLGetData(from), list->param))
    {
        /*proceed while "from" isn't bigger then to_compare*/
        from = SOLNext(from);
    }
    /*if sort_func didn't find location - return end of section*/
    return from;
}

/*finds the *first* suitable position*/
static sorted_list_itr_t FindFirstPlace(sorted_list_t *list,
           sorted_list_itr_t from, sorted_list_itr_t to, const void *to_compare)
{
    while (1 != SOLIsSame(from, to) &&
                1 == list->sort_func(SOLGetData(from), to_compare, list->param))
    {
        /*proceed while "from" is smaller then to_compare*/
        from = SOLNext(from);
    }
    /*if sort_func didn't find location - return end of section*/
    return from;
}
























