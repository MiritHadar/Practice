
#include <string.h>      /* memcpy */
#include <assert.h>      /* assert */

#include "heapify.h"

static size_t GetParent(size_t index);
static size_t GoToLeftChild(size_t index);
static size_t GoToRightChild(size_t index);

/* moves the elem indexed as "last" to its right place in the heap */
void HeapifyUp(void *heap, size_t elem_size, size_t index, is_before_t cmp_func, void *tmp_item)
{
    void *ptr_inx = NULL;

    assert(heap);
    assert(cmp_func);

    ptr_inx = (char*)heap + index * elem_size;
    memcpy(tmp_item, ptr_inx, elem_size);
    
    while (index > 0 && cmp_func(tmp_item, (char*)heap + (GetParent(index) * elem_size), NULL))
    {
        memcpy(ptr_inx, (char*)heap + (GetParent(index) * elem_size), elem_size);
        index = GetParent(index);
        ptr_inx = (char*)heap + index * elem_size;
    }

    memcpy(ptr_inx, tmp_item, elem_size);
}

void HeapifyDown(void *heap, size_t elem_size, size_t index, is_before_t cmp_func, void *tmp_item, size_t n)
{
    size_t first = index;
    size_t left = 0;
    size_t right = 0;

    memcpy(tmp_item, (char*)heap + (index * elem_size), elem_size);

    do
    {
        index = first;
        left = GoToLeftChild(index);
        right = GoToRightChild(index);
    
        if (left < n && cmp_func((char*)heap + (left * elem_size), tmp_item, NULL))
        {
            first = left;
        }

        if (right < n && cmp_func((char*)heap + (first * elem_size), (char*)heap + (right * elem_size), NULL))
        {
            first = right;
        }
        
        memmove((char*)heap + (index * elem_size), (char*)heap + (first * elem_size), elem_size);
         

    } while (first != index);

    memcpy((char*)heap + (index * elem_size), tmp_item, elem_size);

}

/* returns pointer to the parent of "last"*/
static size_t GetParent(size_t index)
{
    return ((index - 1) / 2);
}

static size_t GoToLeftChild(size_t index)
{
    return (1 + index * 2);
}

static size_t GoToRightChild(size_t index)
{
    return (2 + index * 2);
}



/* #include <string.h>  
#include <assert.h>  
#include "heapify.h"  

#define UNUSED(X) (void)X

static size_t Parent(size_t index);
static size_t ChildLeft(size_t index);
static size_t ChildRight(size_t index);


void HeapifyUp(void *heap, size_t item_size, size_t index, is_before_t is_before, void *temp_item)
{
    assert(heap);
    assert(temp_item);

    memcpy(temp_item, (char *)heap + item_size * index, item_size);

    while (0 != index && is_before(temp_item, (char *)heap + Parent(index) * item_size, NULL))
    {
        memcpy((char *)heap + index * item_size, (char *)heap + Parent(index) * item_size, item_size);
        index = Parent(index);
    }

    memcpy((char *)heap + index * item_size, temp_item, item_size);
}

void HeapifyDown(void *heap, size_t item_size, size_t index, is_before_t is_before, void *temp_item, size_t nmemb)
{
    size_t biggest = 0;

    assert(heap);
    assert(temp_item);

    memcpy(temp_item, (char *)heap + item_size * index, item_size);

    do 
    {
        index = biggest;

        if(ChildLeft(index) < nmemb && is_before((char *)heap + ChildLeft(index) * item_size, temp_item, NULL))
        {
            biggest = ChildLeft(index);
        }

        if(ChildRight(index) < nmemb  && ChildLeft(index) < nmemb
           && is_before((char *)heap + ChildRight(index) * item_size, (char *)heap + ChildLeft(index) * item_size, NULL) 
           && is_before((char *)heap + ChildRight(index) * item_size, temp_item, NULL))
        {
            biggest = ChildRight(index);
        }

        memmove((char *)heap + index * item_size, (char *)heap + biggest * item_size, item_size);

    } while (index != biggest);

    memcpy((char *)heap + index * item_size, temp_item, item_size);
}

static size_t Parent(size_t index)
{
    return (index - 1) / 2;
}

static size_t ChildLeft(size_t index)
{
    return 2 * index + 1;
}

static size_t ChildRight(size_t index)
{
    return 2 * index + 2;
} */

