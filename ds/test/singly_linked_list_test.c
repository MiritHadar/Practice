/*******************************************************************************
*	Description: Singly List							   		          	   *
*	Author: Mirit Hadar									  	 	       		   *
*	Reviewer: Evgeny Chernov									 	 	       *
*	Status:										 	  	         		       *
*	Last Update: 										  	         	       *
*******************************************************************************/

#include <stdio.h>		/*puts, printf*/
#include <stdlib.h>		/*malloc, free*/

#include "singly_linked_list.h"

#define UNUSED_VAR(x) (void)(x)

#ifndef NDEBUG
    #define __NDEBUG__
static void PrintNodes(slist_node_t *node);
#endif
static int CmpInts(const void *data, const void *to_compare);
static int AddToInts(void *data, void *param);

int main()
{
	int data1 = 1;
    int data2 = 2;
    int data3 = 3;
    int data4 = 4;
    int data5 = 5;

    slist_node_t *node1 = SLLCreate(&data1, NULL);    /*Create with*/
    slist_node_t *node2 = SLLCreate(&data2, node1);   /* two nodes */
    slist_node_t *node3 = SLLCreate(&data3, NULL);    /*Create single node*/
    slist_node_t *node4 = SLLCreate(&data4, NULL);    /*Create single node*/
    slist_node_t *node5 = SLLCreate(&data5, NULL);  /*Create single node*/
    slist_node_t *removed_node = NULL;
    
    if (NULL == node1)
    {
        puts("1 Create with one node failed");
    }
  
    if (NULL == node2)
    {
        puts("2 Create with two nodes failed");
    }
    
    if (NULL == node3)
    {
        puts("3 Create with one node failed");
    }
    
/********************************Insert After**********************************/
    if (node3 != SLLInsertAfter(node2, node3))           /*Insert After*/
    {
        puts("Insert After failed to return the added node");
    }
    

        
    if (node2->next != node3)
    {
        puts("1 Insert After once failed");
    }
    
    if (node3->next != node1)
    {
        puts("2 Insert After once failed");
    }
    

/********************************Insert****************************************/
    if(node3 != SLLInsert(node3, node4))                /*  Insert    */
    {
        puts("Insert failed to return the added node");
    }
    

                        
    if (node2->next != node3)
    {
        puts("Insert once failed");
    }
    
    if (node3->next != node4)
    {
        puts("Insert once failed");
    }
    
    if (node4->next != node1)
    {
        puts("Insert once failed");
    }
    
   
    
/*****************************Remove After*************************************/    
    removed_node = SLLRemoveAfter(node2);                       /*Remove After*/
    SLLFreeAll(removed_node);
    
    

    
    if (node2->next != node4)
    {
        puts("1 Remove After once failed");
    }
    
    if (node4->next != node1)
    {
        puts("2 Remove After once failed");
    }
    
    SLLRemoveAfter(node4);                /*Remove After - last*/
    
    /*SLLFreeAll(removed_node);*/
    
    if (node3->next != NULL)
    {
        puts("Remove After for last once failed");
    }
    

    
/********************************Remove****************************************/       
    SLLInsertAfter(node2, node5);                   /*add after at the end*/
    SLLInsertAfter(node2, node1);                   

                            
    SLLRemove(node5);                         /*remove - middle*/
    /*SLLFreeAll(removed_node);*/

    
    SLLRemove(node2);                      /*remove - beginning*/
    /*SLLFreeAll(removed_node);*/

    
    if (node2->next != node5)
    {
        puts("1 Remove 3 times failed");
    }                                  
    /*TODO check the returns*/
    
/********************************SLLCount**************************************/
    
    if (2 != SLLCount(node2))
    {
        puts("SLL Count failed for 2 elements");
    }
    
    SLLRemove(node2);                      /*remove - beginning*/

    
    if (1 != SLLCount(node2))
    {
        puts("SLL Count failed for 1 element");
    }
    
    SLLInsertAfter(node2, node3);                   /*add-after at the middle*/
    SLLInsertAfter(node2, node4);
    
    
    /*SLLFreeAll(removed_node);*/
    
/***********************************Find***************************************/      

    
    data5 = 5;
    
    node1 = SLLFind(node2, &data5, CmpInts);
    
    if (NULL == node1)
    {
        puts("SLLFind failed");
    }
    
    SLLForEach(node2, AddToInts, &data1);


/*****************************Find Intersection********************************/

    
	return 0;
}

#ifndef NDEBUG
    #define __NDEBUG__
static void PrintNodes(slist_node_t *node)
{
    while (NULL != node)
    {
        printf("%d ", *(int*)node->data);
        node = node->next;
    }
    puts("");
}
#endif

static int CmpInts(const void *data, const void *to_compare)
{
    return (*(int*)data == *(int*)to_compare);
}

static int AddToInts(void *data, void *param)
{
    	*(int *)data = *(int *)data + *(int *)param;
    
    return 0;
}





