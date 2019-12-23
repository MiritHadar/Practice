#ifndef OL67_DOUBLY_LINKED_LIST
#define OL67_DOUBLY_LINKED_LIST

#include <stddef.h>		/*	size_t	*/

/* Management Struct */
typedef struct dlist dlist_t;

/* itr defining */
typedef struct dlist_info* dlist_itr_t;

/* Function pointers typedefs */
typedef int (*is_match_func_t)(const void *data, const void *to_compare,
																   void *param);
typedef int (*action_func_t)(void *data, void *param);

/********************* DOUBLY LINKED LIST FUNCTIONS ***************************/

/* Create doubly linked list */
dlist_t *DLLCreate(void);

/* Destroy doubly linked list */
void DLLDestroy(dlist_t *dlist);

/* Insert */
dlist_itr_t DLLInsert(dlist_itr_t where, void *data, dlist_t *dlist);

/* Erase node and free it from memory. Return the next node */
dlist_itr_t DLLErase(dlist_itr_t who);

/* Return the number of elements in the dll */
size_t DLLSize(const dlist_t *dlist);

/* Returns the address of node containing the requested data */
dlist_itr_t DLLFind(const void *to_compare, dlist_itr_t from, dlist_itr_t to,
								      is_match_func_t match_func, void *param);

/* Perform an action on all nodes */
int DLLForEach(dlist_itr_t from, dlist_itr_t to, void *param,
								   action_func_t action_func);

/* Boolean is list empty */
int DLLIsEmpty(const dlist_t *dlist);

/* Return the next item in the dll */
dlist_itr_t DLLNext(dlist_itr_t itr);

/* Return the previous item in the dll */
dlist_itr_t DLLPrev(dlist_itr_t itr);

/* Return the first valid item in the dll */
dlist_itr_t DLLBegin(const dlist_t *dlist);

/* Return the tail (stub) of the dll */
dlist_itr_t DLLEnd(const dlist_t *dlist);

/* Get the data from specific node */
void *DLLGetData(dlist_itr_t itr);

/* Create and push a node to the front of the list */
dlist_itr_t DLLPushFront(dlist_t *dlist, void *data);

/* Remove a node from the front of the list */
void *DLLPopFront(dlist_t *dlist);

/* Create and push a node to the end of the list */
dlist_itr_t DLLPushBack(dlist_t *dlist, void *data);

/* Remove a node from the end of the list */
void *DLLPopBack(dlist_t *dlist);

/* Compare data of 2 nodes */
int DLLIsSame(dlist_itr_t itr1, dlist_itr_t itr2);

/* Combine two lists */
void DLLSplice(dlist_itr_t where, dlist_itr_t from, dlist_itr_t to);

/*Prints Dlist for DBUG*/
void PrintDList(dlist_t *dlist);

void RemoveDup(dlist_t *dlist);

#endif	/*	OL67_DOUBLY_LINKED_LIST	*/







