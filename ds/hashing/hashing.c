
#include <stdlib.h>     /*malloc*/
#include <stdio.h>      /*printf*/
#include <assert.h>     /*assert*/

#include "doubly_linked_list.h"
#include "hashing.h"

#define    UNUSED(x)    (void)(x)

struct hash_table
{
    hash_func_t hash_func;
    is_match_t match_func;
    dlist_t **table;
    size_t table_size;
};


static int IsMatchRapper(const void *data1, const void *data2, void *hash);

hash_t *HashCreate(size_t table_size, hash_func_t hash_func, is_match_t match_func)
{
    hash_t *hash = NULL;
    dlist_t **hash_end = NULL;
    dlist_t **hash_run = NULL;

    assert(match_func);
    assert(hash_func);

    hash = malloc(sizeof(hash_t));

    if (NULL == hash)
    {
        return NULL;
    }

    hash->table = malloc(table_size * sizeof(dlist_t*));

    if (NULL == hash->table)
    {
        free(hash);

        return NULL;
    }

    hash->match_func = match_func;
    hash->hash_func = hash_func;
    hash->table_size = table_size;

    hash_end = hash->table + table_size;

    for (hash_run = hash->table; hash_run < hash_end; ++hash_run)
    {
        *hash_run = DLLCreate();

        if (NULL == hash_run)
        {
            HashDestroy(hash);

            return NULL;
        }
    }

    return hash;
}


void HashDestroy(hash_t *hash)
{
    size_t i = 0;

    assert(hash);

    for (i = 0; i < hash->table_size; ++i)
    {
        DLLDestroy(hash->table[i]);
    }

    free(hash->table);
    free(hash);
}


int HashInsert(hash_t *hash, const void *data)
{
    size_t index = 0;
	dlist_itr_t new_node = NULL;
    dlist_t *list = NULL;

    assert(hash);
    assert(data);

    index = hash->hash_func(data);
    list = hash->table[index];

    new_node = DLLInsert(DLLEnd(list), (void*)data, list);
    
    return (DLLIsSame(new_node, DLLEnd(list)));
}

size_t HashSize(const hash_t *hash)
{
    size_t i = 0;
    size_t counter = 0;

    assert(hash);

    for (i = 0; i < hash->table_size; ++i)
    {
        counter += DLLSize(hash->table[i]);
    }

    return counter;
}

void *HashSearch(const hash_t *hash, const void *data)
{
    size_t i = 0;
    dlist_itr_t result = NULL;
    void *tmp_data = NULL;

    assert(hash);
    assert(data);

    i = hash->hash_func(data);

    result = DLLFind(data, DLLBegin(hash->table[i]), DLLEnd(hash->table[i]), IsMatchRapper, (hash_t*)hash);

    if(DLLIsSame(result, DLLEnd(hash->table[i])))
    {
        return NULL;
    }

    tmp_data = DLLGetData(result);
    DLLErase(result);
    DLLPushFront(hash->table[i], tmp_data);

    return tmp_data;
}

void *HashRemove(hash_t *hash, const void *data)
{
    size_t i = 0;
    dlist_itr_t itr_to_remove = NULL;
    void *data_to_remove = NULL;

    assert(hash);
    assert(data);

    i = hash->hash_func(data);

    itr_to_remove = DLLFind(data, DLLBegin(hash->table[i]), DLLEnd(hash->table[i]), IsMatchRapper, (void*)hash);

    if(DLLIsSame(itr_to_remove, DLLEnd(hash->table[i])))
    {
        return NULL;
    }

    data_to_remove = DLLGetData(itr_to_remove);
    DLLErase(itr_to_remove);

    return data_to_remove;
}

int HashForEach(const hash_t *hash, act_func_t act_func, void *param)
{
    size_t i = 0;
    int status = 0;

    assert(hash);
    assert(act_func);

    while (0 == status && i < hash->table_size)
    {
        status = DLLForEach(DLLBegin(hash->table[i]), DLLEnd(hash->table[i]), param, act_func);
        ++i;
    }

    return status;
}

static int IsMatchRapper(const void *data1, const void *data2, void *hash)
{
    return ((hash_t*)hash)->match_func(data1, data2);
}
