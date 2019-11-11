/*******************************************************************************
*	Description: doubly_linked_list							   		           *
*	Author: Mirit Hadar									  	 	       		   *
*	Reviewer: Nir Kirshbloom									 	 	       *
*	Status:										 	  	         		       *
*	Last Update: 										  	         	       *
*******************************************************************************/

#include <stdio.h>		/*puts, printf*/
#include <stdlib.h>		/*malloc, free*/

#include "doubly_linked_list.h"


#define dlist_node dlist_info    

#ifndef NDEBUG
	#define PUTS(x) puts(x)
#else
	#define PUTS(x)
#endif

static int CmpInts(const void *data, const void *to_compare, void *param);
static int AddToInts(void *data, void *param);

int main()
{
    int data0 = 0;
    int data1 = 1;
    int data2 = 2;
    int data3 = 3;
    int data4 = 4;
    int data5 = 5;
    int data6 = 6;
    int status = 0;
    
    dlist_itr_t itr_insert = NULL;
    dlist_itr_t itr_found = NULL;
    
/**********************************First DLL***********************************/
	dlist_t *dlist = DLLCreate();
	dlist_t *dlist1 = DLLCreate();
	
	if (NULL == dlist)
	{
	    printf("%d - failed to create an empty dlist\n", __LINE__);
	}
	
	if (1 != DLLIsEmpty(dlist))
	{
	    printf("%d - failed to report an empty dlist\n", __LINE__);    
	}
	
	/*Insert 3 nodes to empty dlist*/
	itr_insert = DLLInsert(DLLEnd(dlist), &data1, dlist);
    itr_insert = DLLInsert(DLLEnd(dlist), &data2, dlist);
	itr_insert = DLLInsert(DLLEnd(dlist), &data3, dlist);

	
    /*check inserted data*/
	if (3 != *(int*)DLLGetData(itr_insert))
	{
	    printf("%d - failed to retrun insrted itr\n", __LINE__);
	}
	
	/*check dlist data after insert*/
	if (3 != *(int*)DLLGetData(DLLPrev(DLLEnd(dlist))))
	{
	    printf("%d - failed to insert itr\n", __LINE__);
	}
	
	/*Erase 3 nodes and empty dlist*/
	DLLErase(DLLBegin(dlist));
	DLLErase(DLLBegin(dlist));
	DLLErase(DLLBegin(dlist));

	itr_insert = NULL;
	DLLDestroy(dlist);
	
/**********************************Second DLL**********************************/
	
	dlist = DLLCreate();
	
	/*Insert 3 nodes to empty dlist*/
	DLLInsert(DLLEnd(dlist), &data1, dlist);
    DLLInsert(DLLEnd(dlist), &data2, dlist);
	DLLInsert(DLLEnd(dlist), &data3, dlist);
	
	/*Pop Front till empty the list*/
	DLLPopFront(dlist);
	DLLPopFront(dlist);
	DLLPopFront(dlist);
	
	DLLDestroy(dlist);
	
/**********************************Third DLL***********************************/
	
	dlist = DLLCreate();
	
	/*Insert 6 nodes to empty dlist*/
	DLLInsert(DLLEnd(dlist), &data1, dlist);
    DLLInsert(DLLEnd(dlist), &data2, dlist);
	DLLInsert(DLLEnd(dlist), &data3, dlist);
	
	DLLPushFront(dlist, &data4);
	DLLPushBack(dlist, &data0);
	
	/*find 1+2*/
	itr_found = DLLFind(&data1, DLLNext(DLLBegin(dlist)),
	DLLPrev(DLLEnd(dlist)), CmpInts, &data2);
	
	if (3 != *(int*)DLLGetData(itr_found))
	{
	    printf("%d - failed to find itr 1\n", __LINE__);
	}
	
	/*find something you can't*/
	itr_found = DLLFind(&data5, DLLBegin(dlist),
	            DLLPrev(DLLEnd(dlist)), CmpInts, &data5);
	
	if (DLLPrev(DLLEnd(dlist)) != itr_found)
	{
	    printf("%d - failed to find itr 2\n", __LINE__);
	}
	
	status = DLLForEach(DLLNext(DLLBegin(dlist)), DLLPrev(DLLEnd(dlist)),
	                                                  &data1, AddToInts);
	if (0 != status)
	{
	    printf("%d - failed to return right status\n", __LINE__);
	}
	
	if (0 != *(int*)DLLGetData(DLLPrev(DLLEnd(dlist))))
	{
	    printf("%d - failed to do for each\n", __LINE__);
	}
	
	if (5 != DLLSize(dlist))
	{
	    printf("%d - failed to return Size\n", __LINE__);
	}
	
	if (1 == DLLIsEmpty(dlist))
	{
	    printf("%d - failed to report an empty dlist\n", __LINE__);    
	}
	
	/*Pop back till empty*/ 
	DLLPopBack(dlist);
	DLLPopBack(dlist);
	DLLPopBack(dlist);
	DLLPopBack(dlist);
	DLLPopBack(dlist);
	
	if (0 != DLLSize(dlist))
	{
	    printf("%d - failed to return Size for empty list\n", __LINE__);
	}
	
	if (1 != DLLIsEmpty(dlist))
	{
	    printf("%d - failed to report an empty dlist\n", __LINE__);    
	}
    
	DLLDestroy(dlist);
	
/***********************************SPLISE*************************************/	
	dlist = DLLCreate();
	
	data0 = 0;
    data1 = 1;
    data2 = 2;
    data3 = 3;
    data4 = 4;
    data5 = 5;
    data6 = 6;
    
	DLLPushBack(dlist, &data0);
	DLLPushBack(dlist, &data1);
	DLLPushBack(dlist, &data2);
	DLLPushBack(dlist, &data6);
	
	DLLPushBack(dlist1, &data0);
	DLLPushBack(dlist1, &data3);
	DLLPushBack(dlist1, &data4);
	DLLPushBack(dlist1, &data5);
	DLLPushBack(dlist1, &data6);
	
	puts("befor splicing:");
	/*PrintDList(dlist);
	PrintDList(dlist1);*/
	
	DLLSplice(DLLPrev(DLLEnd(dlist)), DLLNext(DLLBegin(dlist1)),
	DLLPrev(DLLEnd(dlist1)));
	
	puts("after splicing:");
	/*PrintDList(dlist);
	PrintDList(dlist1);*/
	
	DLLDestroy(dlist);
	DLLDestroy(dlist1);
	
	return 0;
}

static int CmpInts(const void *data, const void *to_compare, void *param)
{
    int result = *(int*)to_compare + *(int*)param;
    
    return *(int*)data == result;
}

static int AddToInts(void *data, void *param)
{
    *(int *)data = *(int *)data + *(int *)param;
    
    return 0;
}

