
#include <stddef.h>     /*size_t*/
#include <stdlib.h>		/*malloc*/
#include <assert.h>		/*assert*/

#include "new_circular_buffer.h"

struct cb
{
    int *arr;
	int *read;
	int *write;  
	size_t capacity;
};

cb_t *CBCreate(size_t capacity)
{
    cb_t *cb = malloc(sizeof(cb_t) + capacity);
    int *arr = malloc(capacity * sizeof(int));
    if (NULL == cb || NULL == arr)
    {
        free(cb);
        free(arr);

        return NULL;
    }

    cb->capacity = capacity;

    /*point at the beginning of data*/
    cb->arr = arr;
    cb->read = arr;
    cb->write = arr;

    return cb;
}

void CBDestroy(cb_t *cb)
{
    assert(cb);

    free(cb->arr);
    free(cb);
}

int CBWrite(cb_t *cb, int num)
{
    assert(cb);

    *(cb->write) = num;

    if (cb->write == cb->arr + cb->capacity)
    {
        cb->write = cb->arr;
    }
    else
    {
        cb->write += 1;
    }

    return num;
}

int CBRead(cb_t *cb)
{
    int num_read = *(cb->read);

    assert(cb);

    if (cb->read == cb->arr + cb->capacity)
    {
        cb->read = cb->arr;
    }
    else
    {
        cb->read += 1;
    }

    return num_read;
}



