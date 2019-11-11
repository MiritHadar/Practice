
#include <stdlib.h>     /*malloc*/
#include <string.h>     /*memcpy*/
#include <assert.h>     /*assert*/

#include "heapify.h"        
#include "heap.h"
#include "dynamic_vector.h"

#define START_SIZE (100)

struct heap
{
    vector_t *arr;
    is_before_t is_before;
    size_t elem_size;
};


heap_t *HeapCreate(size_t item_size, is_before_t is_before, void *param)
{
    heap_t *heap = NULL;

    assert(is_before);
    assert(item_size);

    heap = malloc(sizeof(heap_t));

    if (NULL == heap)
    {
        return NULL;
    }

    heap->arr = DVCreate(item_size, START_SIZE);

    if (NULL == heap->arr)
    {
        free(heap);
        return NULL;
    }

    heap->is_before = is_before;
    heap->elem_size = item_size;

    return heap;
}

void HeapDestroy(heap_t *heap)
{
    assert(heap);
    
    DVDestroy(heap->arr);
    free(heap);
}

int HeapIsEmpty(const heap_t *heap)
{
    assert(heap);

    return (DVSize(heap->arr) == 0);
}


/* adds element with DATA to HEAP. Returns 0 on success and non-zero otherwise */
int HeapPush(heap_t *heap, const void *data)
{
    void *tmp_item = NULL;
    size_t status = 1;

    assert(heap);

    tmp_item = malloc(heap->elem_size);

    if (NULL != tmp_item && !DVPushBack(heap->arr, data))
    {
        HeapifyUp(DVItemAddress(heap->arr, 0), heap->elem_size, DVSize(heap->arr) - 1, heap->is_before, tmp_item);      
        status = 0;
    }

    free(tmp_item);
    return status;
}

/* Checks for Heapueue size */
size_t HeapSize(const heap_t *heap)
{
    assert(heap);

    return DVSize(heap->arr);
}

/* Removes the root element from a Heap and returns status - 1 for failure, 0 for success */
int HeapPop(heap_t *heap)
{
    void *tmp_item = NULL;
    void *last = NULL;
    void *root = NULL;
    size_t size = 0;
    int status = 1;

    assert(heap);

    tmp_item = malloc(heap->elem_size);

    if (NULL == tmp_item)
    {
        return status;
    }

    root = DVItemAddress(heap->arr, 0);
    last = DVItemAddress(heap->arr, DVSize(heap->arr) - 1);

    memmove(root, last, heap->elem_size);    
    status = DVPopBack(heap->arr);
    size = DVSize(heap->arr);

    if (0 != size && 1 != status)
    {
        HeapifyDown(DVItemAddress(heap->arr, 0), heap->elem_size, 0, heap->is_before, tmp_item, size);
    }

    free(tmp_item);

    return status;
}

 /* Returns the adress of the top item in HEAP. Undefined when HEAP is empty. */
void *HeapPeek(const heap_t *heap)
{
    assert(heap);

    return DVItemAddress(heap->arr, 0);
}

int HeapRemove(heap_t *heap, is_match_t is_match, const void *to_match, void *args)
{
    size_t i = 0;
    void *tmp_item = NULL;
    void *last = NULL;
    void *current = NULL;
    size_t size = 0;
    int status = 1;

    assert(heap && to_match && is_match);
    tmp_item = malloc(heap->elem_size);

    if (NULL == tmp_item)
    {
        return status;
    }

    for (i = 0; i < DVSize(heap->arr); ++i)
    {
        if(is_match(to_match, DVItemAddress(heap->arr, i), args))
        {
            current = DVItemAddress(heap->arr, i);
            last = DVItemAddress(heap->arr, DVSize(heap->arr) - 1);

            memmove(current, last, heap->elem_size);
            status = DVPopBack(heap->arr);

            if (DVSize(heap->arr) != 0 && 0 == status)
            {
                HeapifyUp(DVItemAddress(heap->arr, 0), heap->elem_size, i, heap->is_before, tmp_item);
                HeapifyDown(DVItemAddress(heap->arr, 0), heap->elem_size, i, heap->is_before, tmp_item, DVSize(heap->arr));
            }

            free(tmp_item);
            return status;
        }
    }

    free(tmp_item);
    return status;
}
