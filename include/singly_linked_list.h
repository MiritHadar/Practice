/*******************************************************************************
*	Description: Singly List							   		          	   *
*	Author: Mirit Hadar									  	 	       		   *
*	Reviewer: Evgeny Chernov									 	 	       *
*	Status:										 	  	         		       *
*	Last Update: 										  	         	   *
*******************************************************************************/

#ifndef OL67_SINGLY_LINKED_LIST
#define OL67_SINGLY_LINKED_LIST


typedef struct node slist_node_t;

typedef int (*is_match_func_t)(const void *data, const void *to_compare);
typedef int (*action_func_t)(void *data, void *param);

struct node
{
	void *data;
	slist_node_t *next; 
};

/********************* SINGLY LINKED LIST FUNCTIONS ***************************/

#include <stddef.h>		/*	size_t	*/

slist_node_t *SLLCreate(void *data, slist_node_t *next);

void SLLFreeAll(slist_node_t *head);

/* returns pointer to new_node */
slist_node_t *SLLInsertAfter(slist_node_t *where, slist_node_t *new_node);

/* returns pointer to new_node */
/* WILL EXCHANGE DATA BETWEEN NODE SENT AND NODE ADDRESS*/
slist_node_t *SLLInsert(slist_node_t *where, slist_node_t *new_node);

/*	returns pointer to the removed node */
slist_node_t *SLLRemoveAfter(slist_node_t *node);

/*	returns pointer to the removed node */
/* CAN'T OPERATE ON THE LAST ELEMENT OF LIST */
slist_node_t *SLLRemove(slist_node_t *node);

size_t SLLCount(const slist_node_t *head);

slist_node_t *SLLFind(const slist_node_t *head, const void *to_compare, 
				is_match_func_t match_func);

slist_node_t *SLLFlip(slist_node_t *head);

int SLLForEach(slist_node_t *head, action_func_t act_func, void *param);

int SLLHasLoop(const slist_node_t *head);

slist_node_t *SLLFindIntersection(const slist_node_t *head1, 
							   const slist_node_t *head2);

slist_node_t *SLLFlipRecursive(slist_node_t *head);


#endif	/*	OL67_SINGLY_LINKED_LIST	*/


