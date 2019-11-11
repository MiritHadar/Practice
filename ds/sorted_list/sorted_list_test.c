/*******************************************************************************
*	Description: sorted_linked_list							   		           *
*	Author: Mirit Hadar									  	 	       		   *
*	Reviewer: Itay Kahalani									 	 	           *									  	         	       *
*******************************************************************************/

#include <stdio.h>		/*puts, printf*/
#include <assert.h>		/*  assert    */

#include "doubly_linked_list.h"
#include "sorted_list.h"

#define UNUSED_VAR(x) (void)(x)
#define SIZE_ARR1 8
#define SIZE_ARR2 9
#define SIZE_ARR3 17

#define dlist_node dlist_info    

#ifndef NDEBUG
	#define PUTS(x) puts(x)
#else
	#define PUTS(x)
#endif

static int IsBigger (const void *data1, const void *data2, void *param);
static int AddToInts(void *data, void *param);
static int DoesMatch(const void *data1,const void *to_compare,void *param);

int main()
{
    int arr1[SIZE_ARR1] = {1,3,4,4,8,8,8,9};
    int arr2[SIZE_ARR2] = {2,2,2,5,6,7,8,10,11};
    int merge[SIZE_ARR3] = {2,2,2,2,5,5,6,6,6,7,8,10,10,10,10,11,11};
    size_t i = 0;
    
    sorted_list_t *list1 = SOLCreate(IsBigger, NULL);
    sorted_list_t *list2 = SOLCreate(IsBigger, NULL);
   
    sorted_list_itr_t itr_to_erase = {0};
	sorted_list_itr_t itr_to_find = {0};
	sorted_list_itr_t itr_to_if_find = {0};
	sorted_list_itr_t elems_in_dest = {0};
    


 /*********************************All the rest*********************************/

    
    if (1 != SOLIsEmpty(list1))
    {
	    printf("%d - failed to report Is Empty for an empty list\n", __LINE__);
	}
	
	if (0 != SOLSize(list1))
    {
	    printf("%d - failed to report size for an empty list\n", __LINE__);
	}
	
	/*insert*/
	for (i = 0; i < SIZE_ARR1; ++i)
	{
	    SOLInsert(list1, &arr1[i]);
	}
   
    if (1 == SOLIsEmpty(list1))
    {
	    printf("%d - failed to report Is Empty for un empty list\n", __LINE__);
	}
	
	if (8 != SOLSize(list1))
    {
	    printf("%d - failed to report size for an empty list\n", __LINE__);
	}
	
	itr_to_erase = SOLFind(list1, SOLNext(SOLBegin(list1)),
                                            SOLPrev(SOLEnd(list1)), &arr1[4]);
    
	if (8 != *(int*)SOLGetData(itr_to_erase))
	{
	     printf("%d - failed in find\n", __LINE__);
	}
	
	if (8 != *(int*)(SOLGetData(SOLErase(itr_to_erase))))
	{
	     printf("%d - failed in erase\n", __LINE__);
	}
	
	if (7 != SOLSize(list1))
    {
	    printf("%d - failed to report size for an empty list\n", __LINE__);
	}
	
	SOLPopFront(list1);

	itr_to_find = SOLFind(list1, SOLBegin(list1), SOLEnd(list1), &arr1[0]);
	
    if (!SOLIsSame(SOLEnd(list1), itr_to_find))
    {
    	printf("%d - find - Beta failure\n", __LINE__);  
    }
    
	itr_to_if_find = SOLFindIf(SOLBegin(list1), SOLEnd(list1), &arr1[0],
                                                              NULL, DoesMatch);
    if (!SOLIsSame(SOLEnd(list1), itr_to_if_find))
    {
    	printf("%d - findif - Beta failure\n", __LINE__);  
    }
	
	itr_to_if_find = SOLFindIf(SOLBegin(list1), SOLEnd(list1), &arr1[2],
                                                              NULL, DoesMatch);
    if (4 != *(int*)SOLGetData(itr_to_if_find))
    {
    	printf("%d - find if - failure\n", __LINE__);  
    }
    
    SOLPopBack(list1);
    SOLPopFront(list1);
    
    if (4 != SOLSize(list1))
    {
	    printf("%d - failed to report size\n", __LINE__);
	}
	
	itr_to_find = SOLBegin(list1);
	itr_to_if_find = SOLBegin(list1);
	itr_to_find = SOLBegin(list1);
	
	SOLErase(itr_to_if_find);

    SOLDestroy(list1);
    
/*******************************ForEach & Merge********************************/

    list1 = SOLCreate(IsBigger, NULL);
    
    for (i = 0; i < SIZE_ARR1; ++i)
	{
	    SOLInsert(list1, &arr1[i]);
	}
	
    list2 = SOLCreate(IsBigger, NULL); 
    
    for (i = 0; i < SIZE_ARR2; ++i)
	{
	    SOLInsert(list2, &arr2[i]);
	}
    
	SOLForEach(SOLBegin(list1), SOLEnd(list1), &arr1[0], AddToInts);
	
	if (2 != *(int*)(SOLGetData(SOLBegin(list1))))
	{
    	printf("%d - for each - failure\n", __LINE__);  	    
	}
	
	SOLMerge(list1, list2);
	
	elems_in_dest = SOLBegin(list1);

	for (i = 0; !SOLIsSame(elems_in_dest, SOLEnd(list1)); ++i)
	{
	    if (merge[i] != *(int*)(SOLGetData(elems_in_dest)))
	    {
    	    printf("%d - merge - failure\n", __LINE__);  	    
	    }
	    
	    elems_in_dest = SOLNext(elems_in_dest);
	}
	
    SOLDestroy(list1);
    SOLDestroy(list2);
 
    return 0;
}    
/*Sort func - returns 1 when the right location idetified and 0 when not*/
static int IsBigger(const void *before, const void *after, void *param)
{
    assert(before);
    assert(after);
    
    UNUSED_VAR(param);
    
    return (*(int*)before < *(int*)after);
    
}

/*action func*/
static int AddToInts(void *data, void *param)
{
    *(int *)data = *(int *)data + *(int *)param;
    
    return 0;
}

/*match func*/
static int DoesMatch(const void *data1,const void *to_compare,void *param)
{
    UNUSED_VAR(param);
    
    return *(int*)data1 == *(int*)to_compare;
}










