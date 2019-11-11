
#ifndef OL67_POOL
#define OL67_POOL

#include <stddef.h>  /* size_t */

typedef struct pool pool_t;

/* Initialize memory pool block */
pool_t *FSAInit(void *pool, size_t block_size, size_t amount);

/* Allocate memory in pool block */
void *FSAAlloc(pool_t *pool);

/* free block */
void FSAFree(void *block);

/* return the pool size */
size_t FSAGetPoolSize(size_t block_size, size_t block_amount);

/* return amount of free blocks */
size_t FSAGetFreeBlocks(const pool_t *pool);

#endif /* OL67_POOL */

