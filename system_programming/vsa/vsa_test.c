
/*******************************************************************************
*	Description : VSA							   		                       *
*	Author : Mirit Hadar                                                       *
*   Version : Code									  	 	       	           *
*******************************************************************************/

#include <stdio.h>
#include <stdlib.h>     /*malloc*/
#include <sys/types.h>  /*ssize_t*/


#include "vsa.h"

int main()
{
    vsa_t *pool = NULL;
    size_t buffer_size = 100;
    void *buffer = (vsa_t*)malloc(buffer_size);
    void *memory1 = NULL;
    void *memory2 = NULL;

    pool = VSAInit(buffer, buffer_size);

    if (NULL == pool)
    {
	    printf("%d - failed Init\n", __LINE__);
    }

    VSAPrint(pool);
    printf("Free Space : %lu\n", VSAFreeSpace(pool));

    /*allocate the whole pool*/
    memory1 = VSAAlloc(pool, 80);

    VSAPrint(pool);
    printf("Free Space : %lu\n", VSAFreeSpace(pool));

    /*Free all the pool*/
    puts("\n*******Free*******");
    VSAFree(memory1);
    VSAPrint(pool);
    printf("Free Space : %lu\n", VSAFreeSpace(pool));

    puts("\nalloc 5");
    memory1 = VSAAlloc(pool, 40);
    VSAPrint(pool);
    printf("Free Space : %lu\n", VSAFreeSpace(pool));

    puts("\nalloc 3");
    memory2 = VSAAlloc(pool, 24);
    VSAPrint(pool);
    printf("Free Space : %lu\n", VSAFreeSpace(pool));

    puts("\nfree two blocks");
    VSAFree(memory1);
    VSAFree(memory2);
    VSAPrint(pool);
    printf("Free Space : %lu\n", VSAFreeSpace(pool));

    puts("\n*******Merging*******");
    VSAAlloc(pool, 50);
    VSAPrint(pool);
    printf("Free Space : %lu\n", VSAFreeSpace(pool));

    VSAAlloc(pool, 100);
    VSAPrint(pool);
    printf("Free Space : %lu\n", VSAFreeSpace(pool));
    
    return 0;
}
