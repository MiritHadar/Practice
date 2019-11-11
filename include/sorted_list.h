#ifndef __OL67_SORTED_LIST
#define __OL67_SORTED_LIST

#include <stddef.h>			/*	size_t	*/

/*############################ Struct definitions ############################*/

typedef struct sorted_list sorted_list_t;

typedef struct
{
	struct sorted_list_info *info;
	
} sorted_list_itr_t;

/*############################################################################*/
/*############################# Function typedefs ############################*/

typedef int (*is_before_t)(const void *data1, const void *data2, void *param);
typedef int (*act_func_t)(void *data, void *param);
typedef int (*is_match_t)(const void *data1,const void *to_compare,void *param);

/*############################################################################*/

/* Creates the sorted linked list */
sorted_list_t *SOLCreate(is_before_t sort_func, void *param);

/* Removes the sorted linked list from memory */
void SOLDestroy(sorted_list_t *list);

/* Insert a new element according to sorting function */
sorted_list_itr_t SOLInsert(sorted_list_t *list, void *data);

/* Erase an element from the list */
sorted_list_itr_t SOLErase(sorted_list_itr_t who);

/* Boolean is list empty */
int SOLIsEmpty(const sorted_list_t *list);

/* Return the number of elements in the list */
size_t SOLSize(const sorted_list_t *list);

/* Performs an action on all list members */
int SOLForEach(sorted_list_itr_t from, sorted_list_itr_t to,
						   void *param, act_func_t act_func);

/* Merges two sorted lists */
void SOLMerge(sorted_list_t *dest, sorted_list_t *src);

/* Returns an iterator of element containing requested data */
sorted_list_itr_t SOLFind(sorted_list_t *sorted_list, sorted_list_itr_t from, 
								sorted_list_itr_t to, const void *to_compare);
								 
/* Returns an iterator of a element containing data from to_compare */
sorted_list_itr_t SOLFindIf(sorted_list_itr_t from, sorted_list_itr_t to,
	   				 const void *data, void *param, is_match_t is_match_func);

/* Remove an item from the back of the sorted list */							   
void *SOLPopBack(sorted_list_t *list);

/* Remove an item from the front of the sorted list */
void *SOLPopFront(sorted_list_t *list);

/* Returns the address of the first valid member of the list */
sorted_list_itr_t SOLBegin(const sorted_list_t *list);

/* Returns the tail of the list */
sorted_list_itr_t SOLEnd(const sorted_list_t *list);

/* Returns the next member of the list */
sorted_list_itr_t SOLNext(sorted_list_itr_t itr);

/* Returns the previous member of the list */
sorted_list_itr_t SOLPrev(sorted_list_itr_t itr);

/* Boolean function, returns true if both iterators are equivalent */
int SOLIsSame(sorted_list_itr_t itr1, sorted_list_itr_t itr2);

/* Returns a data requested on specific iterator */
void *SOLGetData(sorted_list_itr_t itr);

#endif /* __OL67_SORTED_LIST */







