
#ifndef __OL67_heap
#define __OL67_heap

#include <stddef.h>	/* size_t	*/

typedef struct heap heap_t;

#ifndef IS_BEFORE_FUNC
#define IS_BEFORE_FUNC

typedef int (*is_before_t)(const void *d1, const void *d2, void *param);

#endif	/* is before type	*/


typedef int (*is_match_t)(const void *data1, const void *data2, void *param);

/* Creates a Heapueue and returnes a Pointer. */
heap_t *HeapCreate(size_t item_size, is_before_t is_before, void *param);

/* destroy the Heapueue. */
void HeapDestroy(heap_t *heap);

/* Adds an element to a Heapueue and returns 0 on success, other on failure. */
int HeapPush(heap_t *heap, const void *data);

/* Removes the first element from a Heapueue and returns pointer to data. */
int HeapPop(heap_t *heap);

/* Peeks on first element in Heapueue and returns pointer to data. */
void *HeapPeek(const heap_t *heap);

/* Checks if the Heapueue is empty. */
int HeapIsEmpty(const heap_t *heap);

/* Checks for Heapueue size. */
size_t HeapSize(const heap_t *heap);

/* Erase an element from the Heapueue. */
int HeapRemove(heap_t *heap, is_match_t is_match, const void *to_match, void *args);

#endif /* __OL67_heap */
