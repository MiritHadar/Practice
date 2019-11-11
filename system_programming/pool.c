

/*******************************************************************************
*	Description : FSA							   		                       *
*	Author : Mirit Hadar                                                       *
*   Version : Psoudo Code									  	 	       	   *
*******************************************************************************/

#include <stdlib.h>     /*malloc,free*/
#include <assert.h>     /*   assert  */
#include "pool.h"

#define     META_DATA_SIZE  8
#define     META_DATA_BLOCK_SIZE  8  

/*admin struct*/
struct pool
{
    void *first_free;       /*the last cell that has been freed*/
    size_t num_of_blocks;   /*      all blocks in the pool     */
    size_t free_blocks;     /*how meny freed blocks do we have */
    size_t block_size;      /*      size of single block       */
};

size_t AllignAddress (size_t block_size);

pool_t *FSAInit(void *pool, size_t block_size, size_t amount)
{
    pool_t *new_pool = NULL;
    void **swim_through = NULL;
    void *last_block = NULL;

    assert(pool);

    new_pool = pool;
    new_pool->block_size = AllignAddress(block_size) + META_DATA_BLOCK_SIZE;
    
    /*set the first block after keeping room for admin struct and meta data*/
    new_pool->first_free = (char*)pool + sizeof(pool_t) + META_DATA_BLOCK_SIZE;
    
    new_pool->num_of_blocks = amount;
    
    new_pool->free_blocks = amount; 
    
    last_block = (char*)pool + amount * block_size;
    
    swim_through = new_pool->first_free;
    
    /*put in every cell pointer to meta data*/
    while (swim_through != last_block)
    {
        /*set each MD of block to point at main MD*/
        *(swim_through - 1) = new_pool;
        
        /*set each block to point at the next one*/
        *swim_through = swim_through + new_pool->block_size;
        
        /*proceed*/
        swim_through += new_pool->block_size;    /*TODO jump from MD of block to an other*/
    }
    
    /*set last block*/
    *(swim_through - 1) = new_pool;
    *swim_through = NULL;
    
    return new_pool;
}


void *FSAAlloc(pool_t *pool)
{
    void *prev_first_free;

    if (NULL != pool->first_free)
    {
        /*save previous first_free for returning it*/
        prev_first_free = pool->first_free;
        
        /*get next first free*/
        pool->first_free = *(char*)(pool->first_free);
        --pool->free_blocks;

        return prev_first_free;
    }

    /*if there's no place to alloc*/
    return NULL;
}



void FSAFree(void *block)
{
    /*set previous first_free to point at new freed block*/
    void *prev_first_free = *((char*)block - 1)->first_free;
    *prev_first_free = block;
    
    /*point "pool->first_free" at that new freed block*/
    *(block - 1) = block;
    
    ++(pool->free_blocks);
}


size_t FSAGetPoolSize(size_t block_size, size_t block_amount)
{
    return ((sizeof(pool_t) +
        (block_size + META_DATA_BLOCK_SIZE) * block_amount) + META_DATA_SIZE);
}


size_t FSAGetFreeBlocks(const pool_t *pool)
{
    return pool->free_blocks;
}


size_t AllignAddress (size_t block_size)
{
    size_t offset = (block_size % 8);
    return (block_size + (8 - offset));
}

















