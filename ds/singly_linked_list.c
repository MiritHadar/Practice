/*******************************************************************************
*	Description: Singly List							   		          	   *
*	Author: Mirit Hadar									  	 	       		   *
*	Reviewer: Ori Michaeli									 	 	           *
*	Status:	Sent								 	  	         		       *
*	Last Update: 13.5.19									  	         	   *
*******************************************************************************/

#include <assert.h>     /*   assert   */
#include <stdlib.h>		/*malloc, free*/

#include "singly_linked_list.h"


/**********************************Create**************************************/

slist_node_t *SLLCreate(void *data, slist_node_t *next)
{
    slist_node_t *node = NULL;
    
    node = (slist_node_t*)malloc(sizeof(slist_node_t));
    
    if (NULL == node)
    {
        return NULL;
    }
    
    node->data = data;
    node->next = next;
    
    return node;
}
 
/**********************************FreeAll*************************************/

void SLLFreeAll(slist_node_t *head)
{
	slist_node_t *tmp = NULL;
    
    assert(head);
    
    while (NULL != head)
    {
        tmp = head;
        head = head->next;
        free(tmp);
    }
    
    free(head);
    head = NULL;
    tmp = NULL;
}


/********************************Insert After**********************************/
slist_node_t *SLLInsertAfter(slist_node_t *where, slist_node_t *new_node)
{
    assert(where);
    assert(new_node);
      
    new_node->next = where->next;
    where->next = new_node;                 /*point to new one*/

    return new_node;
}

/********************************Insert****************************************/
slist_node_t *SLLInsert(slist_node_t *where, slist_node_t *new_node)
{
    void *tmp = NULL;
    
    assert(where);
    assert(new_node);
    
    tmp = new_node->data;
    SLLInsertAfter(where, new_node);
    
    new_node->data = where->data;    /*exchange data*/
    where->data = tmp;
    
    tmp = NULL;
    
    return where;
}

/******************************Remove After************************************/
slist_node_t *SLLRemoveAfter(slist_node_t *node)
{
    slist_node_t *tmp = NULL;
    
    assert(node);
    
    if (NULL == node->next) /*if there's nothing to remove after*/
    {
        return NULL;
    }
    
    tmp = node->next;
    node->next = tmp->next;
    tmp->next = NULL;
    
    return tmp;
}

/********************************Remove****************************************/
slist_node_t *SLLRemove(slist_node_t *node)
{
	void *tmp_data = NULL;
	slist_node_t *removed_node = NULL;

	assert(node);

	removed_node = SLLRemoveAfter(node);

	tmp_data = removed_node->data;  /*exchange data*/
	removed_node->data = node->data;
	node->data = tmp_data;

	return removed_node;	
}
/********************************SLLCount**************************************/
size_t SLLCount(const slist_node_t *head)
{
    size_t num_of_nodes = 0;
    
    while (NULL != head)
    {
        head = head->next;
        ++num_of_nodes;
    }
    
    return num_of_nodes;
}

/*********************************SLLFind**************************************/
slist_node_t *SLLFind(const slist_node_t *head, const void *to_compare,
                                            is_match_func_t match_func)
{
    assert(head);
    assert(to_compare);
    assert(match_func);
    
    while (NULL != head && (0 == match_func(head->data, to_compare)))
    {
        head = head->next; 
    }
    
    return (slist_node_t *)head;
}

/*********************************SLLFlip**************************************/
slist_node_t *SLLFlip(slist_node_t *head)
{
	slist_node_t *previous = NULL;
	slist_node_t *next = NULL;
	
	assert(head);
	
	/* Reorder the pointers in the list while always keeping the previous node */
	while (NULL != head->next)
	{
		next = head->next;
		head->next = previous;
		previous = head;
		head = next;
	}
	
	/* Set the last node to point to previous */
	head->next = previous;	
	
	return head;
}

/*****************************SLLFlipRecursive********************************/
slist_node_t *SLLFlipRecursive(slist_node_t *head)
{
    slist_node_t *new_head = NULL;

    if (NULL == head->next)
    {
        return head;
    }
    else
    {
        new_head = SLLFlipRecursive(head->next);
        head->next->next = head;
        head->next = NULL;
        return new_head;
    }
    
}


/*********************************SLLForEach***********************************/
int SLLForEach(slist_node_t *head, action_func_t act_func, void *param)
{
    int status = 0;
    
    assert(head);
    assert(act_func);

    
    while (NULL != head && 0 == status)
    {
        status = act_func(head->data, param);
        
        head = head->next;
    }
    
    return 0;
}

/*******************************SLLHasLoop*************************************/
int SLLHasLoop(const slist_node_t *head)
{
	const slist_node_t *slower = NULL;
	const slist_node_t *faster = NULL;
	
	assert(head);
	
	/*for a list of a single node un-looped return false*/
	if (NULL == head->next)
	{
	    return 0;
	}
	
	/*for a list of a single node looped to it self return true*/
	if (head->next == head)
	{
	    return 0;
	}
	
	slower = head;
	faster = head->next;
	
	/*  set 2 pointers to the list, proceed the first by node, and the    */
	/*second by 2 nodes and check if they are pointing at the same address*/
	while ((slower != faster) && (NULL != faster)
                          && NULL != faster->next)
	{
		slower = slower->next;            /*proceed by 1*/
		faster = (faster->next)->next;          /*proceed by 2*/
	}
	
	return slower == faster;
}

/*****************************Find Intersection********************************/
slist_node_t *SLLFindIntersection(const slist_node_t *head1, 
							   const slist_node_t *head2)
{
    size_t count1 = 0;
    size_t count2 = 0;
    int delta = 0;
    
    assert(head1);
    assert(head2);
    
    count1 = SLLCount(head1);
    count2 = SLLCount(head2);
    delta = count1 - count2;
    
    while (delta > 0)
    {
        head1 = head1->next;
        --delta;
    }
    
    while (delta < 0)
    {
        head2 = head2->next;
        ++delta;
    }
    
    while (head1->next != head2->next && head1->next != NULL)
    {
        head1 = head1->next;
        head2 = head2->next;
    }
    
    return head1->next;
}





