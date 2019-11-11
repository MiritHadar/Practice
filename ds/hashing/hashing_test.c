#include <stdio.h>
#include <string.h>

#include "doubly_linked_list.h"
#include "hashing.h"

#define    UNUSED(x)    (void)(x)
#define    SIZE                10

typedef struct person person_t;

struct person
{
    char *name;
    int id;
};

static size_t KeyForPerson(const void *data);
static int IsMatchId(const void *data1, const void *data2);
static int AddANum(void *data, void *param);


int main()
{
    int data1 = 1;
    person_t mirit = {"Mirit Hadar", 123};
    person_t ayalon = {"Ayalon Hadar", 234};
    person_t ilay = {"Ilay Hadar", 345};
    person_t carmi = {"Carmi Hadar", 456};

    person_t mirit_to_find = {NULL, 123};
    person_t ayalon_to_find = {NULL, 123};
    person_t ilay_to_find = {NULL, 123};
    person_t carmi_to_find = {NULL, 123};

    hash_t *hash = HashCreate(SIZE, KeyForPerson, IsMatchId);

    if (NULL == hash)
    {
        printf("failed to create %d\n", __LINE__);
    }

    if (0 != HashSize(hash))
    {
        printf("failed in HashSize %d\n", __LINE__);
    }

    HashInsert(hash, &mirit);

    if (1 != HashSize(hash))
    {
        printf("failed in HashSize or HashInsert %d\n", __LINE__);
    }

    HashInsert(hash, &ayalon);
    HashInsert(hash, &ilay);
    HashInsert(hash, &carmi);

    if (4 != HashSize(hash))
    {
        printf("failed in HashSize or HashInsert %d\n", __LINE__);
    }

    if (0 != strcmp(((person_t*)HashSearch(hash, &mirit_to_find))->name, mirit.name))
    {
        printf("failed in HashSearch %d\n", __LINE__);
    }

    if (0 != strcmp(((person_t*)HashSearch(hash, &ayalon_to_find))->name, mirit.name))
    {
        printf("failed in HashSearch %d\n", __LINE__);
    }

    if (0 != strcmp(((person_t*)HashSearch(hash, &ilay_to_find))->name, mirit.name))
    {
        printf("failed in HashSearch %d\n", __LINE__);
    }

    if (0 != strcmp(((person_t*)HashSearch(hash, &carmi_to_find))->name, mirit.name))
    {
        printf("failed in HashSearch %d\n", __LINE__);
    }

    if (0 != strcmp(((person_t*)HashRemove(hash, &ayalon))->name, ayalon.name))
    {
        printf("failed in HashRemove %d\n", __LINE__);
    }

   
    if (0 != strcmp(((person_t*)HashRemove(hash, &mirit))->name, mirit.name))
    {
        printf("failed in HashRemove %d\n", __LINE__);
    }

    if (0 != strcmp(((person_t*)HashRemove(hash, &ilay))->name, ilay.name))
    {
        printf("failed in HashRemove %d\n", __LINE__);
    }

    if (0 != strcmp(((person_t*)HashRemove(hash, &carmi))->name, carmi.name))
    {
        printf("failed in HashRemove %d\n", __LINE__);
    }

    if (NULL != HashRemove(hash, &carmi))
    {
        printf("failed in HashRemove %d\n", __LINE__);
    }

    if (NULL != HashSearch(hash, &mirit))
    {
        printf("failed in HashSearch %d\n", __LINE__);
    }

    HashInsert(hash, &ayalon);
    HashInsert(hash, &ilay);
    HashInsert(hash, &carmi);
    HashInsert(hash, &mirit);

    if (4 != HashSize(hash))
    {
        printf("failed in HashSize or HashInsert %d\n", __LINE__);
    }

    HashForEach(hash, AddANum, &data1);

    if (mirit.id != 124)
    {
        printf("failed in HashForEach %d\n", __LINE__);
    }

    if (ilay.id != 346)
    {
        printf("failed in HashForEach %d\n", __LINE__);
    }

    if (carmi.id != 457)
    {
        printf("failed in HashForEach %d\n", __LINE__);
    }

    HashDestroy(hash);

    return 0;
}

static size_t KeyForPerson(const void *data)
{
    return ((person_t*)data)->id % SIZE;
}

static int IsMatchId(const void *data1, const void *data2)
{
    return (((person_t*)data1)->id) == (((person_t*)data2)->id);
}

static int AddANum(void *data, void *param)
{
    (((person_t*)data)->id) = (((person_t*)data)->id) + *(int*)param;

    return 0;
}

