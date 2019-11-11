
#include <stdio.h>     /*size_t*/
#include <stdlib.h>     /*malloc*/
#include <string.h>     /*memcpy*/
#include <assert.h>     /*assert*/
#include <math.h>       /* sqrt */
#include <sys/types.h>  /*ssize_t*/

#include "sort.h"
#include "heapify.h"


#define         NIBBLE        4
#define  OPTIONS_OF_NIBBLE   16
#define     BITS_IN_BYTE      8
#define     BLOCK(x)     (size_t)sqrt(x)


static void Swap(void *data1, void *data2, size_t element_size);
static size_t NibbleToIndex(const void *elem, const void *args);
static size_t Partition(void *arr, size_t high, size_t elem_size, compare_t cmp_func);
static int Merge(char *base1, size_t n1, char *base2, size_t n2, size_t elem_size, compare_t cmp_func);

typedef struct
{
    to_index_t element_to_index;
    const void *args;
    size_t current_nibble;
}nibble_t;

void InsertionSort(void *base, size_t num_element, size_t elem_size, compare_t compare_func)
{
    size_t i, j = 0;
    char *c_base = (char*)base;

    if (num_element < 2)
    {
        return;
    }

    for (i = elem_size; i < (num_element * elem_size); i += elem_size)
    {
        for (j = 0; j < i; j += elem_size)
        {
           if (compare_func(c_base + i, c_base + j, NULL))
           {
               Swap(c_base + j, c_base + i, elem_size);
           }
        }
    }
}

void BubbleSort(void *base, size_t num_element, size_t elem_size, compare_t compare_func)
{
    size_t i = 0;
    size_t swaps = 0;
    char *c_base = (char*)base;

    if (num_element < 2)
    {
        return;
    }
    do
    {
        swaps = 0;
        for (i = elem_size; i < (elem_size * num_element); i += elem_size)
        {
            if (compare_func(c_base + i, c_base + i-elem_size, NULL))
            {
                Swap(c_base + i, c_base + i-elem_size, elem_size);
                swaps = 1;
            }
        }
    } while (swaps != 0);
}


void SelectionSort(void *base, size_t num_element, size_t elem_size, compare_t is_before)
{
    size_t i, j = 0;
    char *before = NULL;
    char *c_base = (char*)base;

    if (num_element < 2)
    {
        return;
    }

    for (i = 0; i < (num_element * elem_size) - elem_size; i += elem_size)
    {
        before = c_base + i;

        for (j = i + elem_size; j < (num_element * elem_size); j += elem_size)
        {
            if (is_before(c_base + j, before, NULL))
            {
                before = c_base + j;
            }
        }
        
        Swap(before, c_base + i, elem_size);

    }
}


int CountingSort(void *base, size_t num_of_elements, size_t element_size, to_index_t element_to_index, const void *args, size_t range)
{
    size_t *base_index = NULL;
    void *base_sorted = NULL;
    int i = 0;
    size_t index = 0;
    size_t sum = 0;
    /*casting of bases*/
    char *c_sorted = NULL;
    char *c_base = NULL;

    assert(base);
    assert(element_to_index);

    c_base = (char*)base;
    base_index = calloc(range, sizeof(size_t));
    base_sorted = (void*)malloc(num_of_elements * element_size);

    if(NULL == base_sorted || NULL == base_index)
    {
        free(base_index);
        return 1;
    }

    c_sorted = (char*)base_sorted;

    /*set the index base*/
    for (i = 0; i < (int)(element_size * num_of_elements); i += element_size)
    {
        ++base_index[element_to_index((const void*)(c_base + i), args)];
    }

    /*set the index base with sums of appearances*/
    for (i = 0; i < (int)range; ++i)
    {
        sum += base_index[i];
        base_index[i] = sum;
    }

    /*set the sorted base*/
    for (i = (element_size * (num_of_elements - 1)); i >= 0; i -= element_size)
    {
        index = element_to_index((const void*)(c_base + i), args);

        --base_index[index];
        memcpy(c_sorted + (element_size * base_index[index]), (const void*)(c_base + i), element_size);
    }
    
    /*updaet the base*/
    memcpy(base, (const void*)base_sorted, element_size * num_of_elements);

    free(base_index);
    free(base_sorted);

    return 0;
}

int RadixSort(void *base, size_t num_of_element, size_t element_size, to_index_t element_to_index, const void *args, size_t num_of_bytes)
{
    nibble_t nibble_info = {NULL};
    int status = 0;

    assert(base);
    assert(element_to_index);

    nibble_info.element_to_index = element_to_index;
    nibble_info.args = args;
    nibble_info.current_nibble = 0;

    while ((1 != status) && (nibble_info.current_nibble < (num_of_bytes * BITS_IN_BYTE)))
    {
        status = CountingSort(base, num_of_element, element_size, NibbleToIndex, (const void*)&nibble_info, OPTIONS_OF_NIBBLE);
        nibble_info.current_nibble += NIBBLE;
    }

    return status;
}

static void Swap(void *data1, void *data2, size_t elem_size)
{
    size_t i = 0;

    if (data1 != data2)
    {
        for (i = 0; i < elem_size; ++i)
        {
            *((unsigned char*)data1 + i) ^= *((unsigned char*)data2 + i);
            *((unsigned char*)data2 + i) ^= *((unsigned char*)data1 + i);
            *((unsigned char*)data1 + i) ^= *((unsigned char*)data2 + i);
        }
    }
}

static size_t NibbleToIndex(const void *elem, const void *args)
{
    nibble_t *nibble_info = NULL;
    size_t key = 0;

    assert(elem);
    assert(args);

    nibble_info = (nibble_t*)args;
    key = nibble_info->element_to_index(elem, nibble_info->args);

    return (key >> nibble_info->current_nibble) & 0xF;
}

int MergeSort(void *base, size_t n, size_t elem_size, compare_t cmp_func)
{
    size_t n1 = 0;
    size_t n2 = 0;

    assert(base && cmp_func);

    if (n > 1)
    {
        n1 = n / 2;
        n2 = n - n1;

        if (-1 == MergeSort(base, n1, elem_size, cmp_func))
        {
            return -1;
        }

        if (-1 == MergeSort((char*)base + (n1 * elem_size), n2, elem_size, cmp_func))
        {
            return -1;
        }

        if (-1 == Merge((char*)base, n1, (char*)base + (n1 * elem_size), n2, elem_size, cmp_func))
        {
            return -1;
        }
    }

    return 0;
}

static int Merge(char *base1, size_t n1, char *base2, size_t n2, size_t elem_size, compare_t cmp_func)
{
    char *end1 = NULL;
    char *end2 = NULL;
    char *tmp_base = NULL;
    char *start = NULL;

    assert(cmp_func && base1 && base2);

    start = (char*)base1;

    end1 = base1 + n1 * elem_size;
    end2 = base2 + n2 * elem_size;

    tmp_base = malloc((n1 + n2) * elem_size);

    if (NULL == tmp_base)
    {
        return -1;
    }
    
    while ((base1 != end1) && (base2 != end2))
    {
        if (cmp_func(base1, base2, NULL))
        {
            memcpy(tmp_base, base1, elem_size);
            base1 += elem_size;
        }
        else
        {
            memcpy(tmp_base, base2, elem_size);
            base2 += elem_size;
        }

        tmp_base += elem_size;
    }

    if (base1 != end1)
    {
        memcpy(tmp_base, base1, end1 - base1);
        tmp_base += end1 - base1;
    }
    else if (base2 != end2)
    {
        memcpy(tmp_base, base2, end2 - base2);
        tmp_base += end2 - base2;
    }

    tmp_base -= (n1 + n2) * elem_size;
    memcpy(start, tmp_base, (n1 + n2) * elem_size);

    free(tmp_base);

    return 0;
}


void QuickSort(void *base, size_t num_elems, size_t elem_size, compare_t is_before)
{
    size_t pivot = 0;

    if (num_elems > 1)
    {
        pivot = Partition(base, num_elems - 1, elem_size, is_before);

        QuickSort(base, pivot, elem_size, is_before);
        QuickSort((char*)base + (pivot + 1) * elem_size, num_elems - pivot - 1, elem_size, is_before);
    }
}

static size_t Partition(void *base, size_t high, size_t elem_size, compare_t is_before)
{
    size_t r = 0;
    ssize_t l = -1 * elem_size;

    for (r = 0; r < (high * elem_size); r += elem_size)
    {
        if (is_before((char*)base + r, (char*)base + (elem_size * high), NULL))
        {
            l += elem_size;
            Swap((char*)base + r, (char*)base + l, elem_size);
        }
    }

    Swap((char*)base + l + elem_size, (char*)base + (elem_size * high), elem_size);

    return ((l + elem_size) / elem_size);
}

void *RecursiveBinarySearch(const void *base, size_t n, size_t elem_size, compare_t is_before, const void *key)
{
    size_t mid_inx = 0;
    char *c_base = (char*)base;

    if (n > 1)
    {
        mid_inx = n / 2;

        /*if mid is ***bigger*** then key*/
        if (is_before(key, c_base + (mid_inx * elem_size), NULL))
        {
            return RecursiveBinarySearch(base, mid_inx, elem_size, is_before, key);
        }
        /*if mid is ***smaller*** then key*/
        else if (is_before(c_base + (mid_inx * elem_size), key, NULL))
        {
            return RecursiveBinarySearch(c_base + (mid_inx + 1) * elem_size, n - (mid_inx + 1), elem_size, is_before, key);
        }
        /*key found*/
        else
        {
            return (c_base + (mid_inx * elem_size));
        }
    }
    if (is_before(key, base, NULL) || (is_before(base, key, NULL)))
    {
        return NULL;
    }

    return (void*)base;
}

void *IterativeBinarySearch(const void *base, size_t n, size_t elem_size, compare_t is_before, const void *key)
{
    char *m = NULL;

    assert(base);
    assert(is_before);

    while (n > 0)
    {
        n /= 2;
        
        m = (char*)base + (n * elem_size);
       
        if (is_before(m, key, NULL))
        {
            base = m + elem_size;
        }
        else if (!is_before(key, m, NULL))
        {
            return m;
        }
    }

    return NULL;
}

void *IterativeJumpSearch(const void *base, size_t n, size_t elem_size, compare_t cmp_func, const void *key)
{
    size_t step = BLOCK(n) * elem_size;
    char *m = NULL;
    char *c_base = NULL;
    char *end = NULL;
    int cmp_result = 0;

    assert(base && cmp_func);

    c_base = (char*)base;
    m = c_base + step;
    end = c_base + n * elem_size;

    while (m < end)
    {
        cmp_result = cmp_func(key, m, NULL);

        if (0 == cmp_result)
        {
            return m;
        }

        else if (cmp_result < 0)
        {
            while (m != c_base && cmp_func(key, c_base, NULL) > 0)
            {
                c_base += elem_size;
            }
            if (0 == cmp_func(key, c_base, NULL))
            {
                return c_base;
            }

            return NULL;
        }

        c_base = m + elem_size;
        m += step;
    }

    while (c_base < end)
    {
        if (0 == cmp_func(key, c_base, NULL))
        {
            return c_base;
        }
        c_base += elem_size;

    }

    return NULL;
}

void HeapSort(void *base, size_t num_elems, size_t elem_size, compare_t cmp_func)
{
    size_t i = 0;
    void *tmp_item = NULL;

    assert(base);
    assert(cmp_func);
 
    tmp_item = malloc(elem_size);

    if (NULL == tmp_item)
    {
        return;
    }

    for (i = 1; i < num_elems; ++i)
    {
        HeapifyUp(base, elem_size, i, cmp_func, tmp_item);
    }

    while (num_elems > 0)
    {
        Swap(base, (char*)base + (num_elems - 1) * elem_size, elem_size);
        --num_elems;
        HeapifyDown(base, elem_size, 0, cmp_func, tmp_item, num_elems);
    }

    free(tmp_item);
}


