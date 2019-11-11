

#ifndef __HEAPIFY_H__
#define __HEAPIFY_H__

#include <stddef.h>

#ifndef IS_BEFORE_FUNC
#define IS_BEFORE_FUNC

typedef int (*is_before_t)(const void *d1, const void *d2, void *param);

#endif	/* is before type	*/

void HeapifyUp(void *heap, size_t elem_size, size_t index, is_before_t cmp_func, void *tmp_item);
void HeapifyDown(void *heap, size_t elem_size, size_t index, is_before_t cmp_func, void *tmp_item, size_t n);

#endif /* heapify */
