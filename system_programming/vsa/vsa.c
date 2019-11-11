
/*******************************************************************************
*	Description : VSA							   		                       *
*	Author : Mirit Hadar                                                       *
*   Version : Code									  	 	       	           *
*******************************************************************************/

#include <stdio.h>     
#include <stdlib.h>      /* abs  */
#include <assert.h>
#include <sys/types.h>  /*ssize_t*/

#include "vsa.h"

#define    POOL_MD_SIZE     1   /*8 bytes*/
#define    ELEM_MD_SIZE     1   /*8 bytes*/

static size_t AllignUpToEight (size_t num);
static size_t AllignDownToEight (size_t num);

struct vsa
{
    /* point at the end of the pool */
    size_t *pool_end;
};

struct element
{
    /* (-) for size of free blocks (+) for size of occupied blocks */
    ssize_t elem_size;
};

vsa_t *VSAInit (void *buffer, size_t buffer_size)
{
    vsa_t *pool = buffer;
    vsa_t *base_vsa = pool;
    element_t *element = {NULL};

    assert(buffer);
    /*at least 16 bytes malloced*/
    assert(buffer_size >= (8 * (POOL_MD_SIZE + ELEM_MD_SIZE)));

    /*initial main meta data*/
    pool->pool_end = (size_t*)pool + AllignDownToEight(buffer_size);

    /*initial element meta data at the beginning of empty space*/
    element = (element_t*)pool + POOL_MD_SIZE;
    element->elem_size = (size_t*)element - pool->pool_end + ELEM_MD_SIZE;

    return base_vsa;
}


void *VSAAlloc(vsa_t *pool, size_t element_size)
{
    element_t *itr = NULL;
    element_t *itr_base = NULL;
    size_t old_element_size = 0;
    size_t seq_space = 0;

    assert(pool);

    element_size = AllignUpToEight(element_size);

    itr = (element_t*)pool + POOL_MD_SIZE;

    while (itr < (element_t*)pool->pool_end)
    {
        if (itr->elem_size > 0)
        {
            itr += itr->elem_size + ELEM_MD_SIZE;
        }
        else
        {
            /*if there's a block large enough for new element*/
            if (abs(itr->elem_size) >= abs(element_size))
            {
                old_element_size = itr->elem_size;
                itr_base = itr;
                itr->elem_size = element_size;

                if(element_size < old_element_size)
                {
                    itr += itr->elem_size + ELEM_MD_SIZE;
                    itr->elem_size = old_element_size + element_size + ELEM_MD_SIZE;
                }

                return itr_base + ELEM_MD_SIZE;
            }
            
            /*merging*/
            old_element_size = itr->elem_size;
            itr_base = itr;

            while((itr != (element_t*)pool->pool_end) && (itr->elem_size <= 0))
            {
                seq_space += abs(itr->elem_size) + ELEM_MD_SIZE;
                
                if ((seq_space - ELEM_MD_SIZE) >= element_size)
                {
                    itr_base->elem_size = element_size;
                    itr += element_size + old_element_size;
                    itr->elem_size = element_size - seq_space;

                    return itr_base + ELEM_MD_SIZE;
                }

                itr += abs(itr->elem_size) + ELEM_MD_SIZE;
            }
            seq_space = 0;
            itr += itr->elem_size + ELEM_MD_SIZE;
        }
    }
    /*when no location has been found*/
    return NULL;

}

void VSAFree(void *memory_element)
{
    element_t *elem_to_free = NULL;

    assert(memory_element);

    elem_to_free = (element_t*)memory_element - ELEM_MD_SIZE;
    elem_to_free->elem_size = -1 * abs(elem_to_free->elem_size);
}

/*allign up for blocks*/
static size_t AllignUpToEight (size_t num)
{
    size_t offset = num & 0x7;
    
    if (offset > 0)
    {
        return ((num + (8 - offset)) / 8);
    }
    
    return num / 8;
}

/*allign down for blocks*/
static size_t AllignDownToEight (size_t num)
{
    size_t offset = num & 0x7;
    
    return (num - offset) / 8;
}

/*for test
size_t VSAFreeSpace(vsa_t *pool)
{
    ssize_t free_bytes = 0;
    element_t *element = (element_t*)pool + POOL_MD_SIZE;

    assert(pool);
    
    while (element < (element_t*)pool->pool_end)
    {
        if (element->elem_size < 0)
        {
            free_bytes += (-1)*element->elem_size;
        }

        element += abs(element->elem_size) + ELEM_MD_SIZE;

    }

    return free_bytes; 
}*/

/*for my test*/
size_t VSAFreeSpace(vsa_t *pool)
{
    ssize_t free_bytes = 0;
    element_t *element = (element_t*)pool + POOL_MD_SIZE;

    assert(pool);
    
    while (element < (element_t*)pool->pool_end)
    {
        if (element->elem_size <= 0)
        {
            free_bytes += (-1)*element->elem_size + ELEM_MD_SIZE;
        }
        
        element += abs(element->elem_size) + ELEM_MD_SIZE;
    }
    /*take off first header*/
    if (free_bytes != 0)
    {
        free_bytes -= ELEM_MD_SIZE;
    }
    return free_bytes; 
}

void VSAPrint(vsa_t *pool)
{
	element_t *current_elem = NULL;
    size_t i = 0;

	assert(pool);

	current_elem = (element_t*)pool + POOL_MD_SIZE;

	while (current_elem < (element_t*)pool->pool_end)
	{
		printf("block %lu : %li\n", i, current_elem->elem_size);

		current_elem += abs(current_elem->elem_size) + ELEM_MD_SIZE;
        ++i;
	}
}
