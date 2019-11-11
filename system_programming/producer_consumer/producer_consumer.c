

#include <stdio.h>                   /*    I / O    */
#include <pthread.h>                 /*  threads    */
#include <semaphore.h>               /*  semaphore  */
#include <unistd.h>                  /*    sleep    */ 

#include "doubly_linked_list.h"        /*  DLL    */
#include "new_circular_buffer.h"       /*   CB    */

#define     SIZE        5
#define     SEM_SIZE    10
#define     BER_SIZE    3

/*variables*/
static volatile int full = 0;
static size_t counter = 0;
static pthread_mutex_t mutex = {{0}};
static pthread_mutex_t read_mut = {{0}};
static pthread_mutex_t write_mut = {{0}};
static sem_t sem = {{0}};
static sem_t sem_read = {{0}};
static sem_t sem_write = {{0}};
static pthread_cond_t cond_glob = PTHREAD_COND_INITIALIZER;

typedef struct person
{
    char *name;
    int id;
}person_t;

typedef struct cond_info
{
    pthread_mutex_t mut_cond; /* Protects access to value  */
    pthread_cond_t cond;      /* Signals change to value   */
}cond_t;

/*functions*/
void BusyWait(void);
void *ProduceWrite(void *person);
void *ConsumeRead(void *person);

void MutexBusyWait(void);
void *ProduceInsert(void *dlist);
void *ConsumeRemove(void *dlist);

void MutexSemaphore(void);
void *SemProduceInsert(void *dlist);
void *SemConsumeRemove(void *dlist);

void CircularBufferOneMut(void);
void *WriteToCBOneMut(void *cb);
void *RedaFromCBOneMut(void *cb);

void CircularBufferTwoMut(void);
void *WriteToCBTwoMut(void *cb);
void *RedaFromCBTwoMut(void *cb);

void CondVarDemo(void);
void *CVWrite(void *args);
void *CVRead(void *args);

void Berrier(void);
void *BerWrite(void *args);
void *BerRead(void *args);

int main()
{
/*         BusyWait();
     MutexBusyWait();
     MutexSemaphore();
     CircularBufferOneMut();
     CircularBufferTwoMut();
     CondVarDemo();*/
     Berrier();
 
    return 0;
}

void BusyWait(void)
{
    pthread_t write = {0};
    pthread_t read = {0};
    person_t person;

    /*Create the threads*/
    if (pthread_create(&write, NULL, ProduceWrite, &person))
    {
        puts("failed create read");
        return;
    }
    
    if (pthread_create(&read, NULL, ConsumeRead, &person))
    {
        puts("failed create write");
        return;
    }

    /*assure there done running*/
    if (pthread_join(read, NULL))
    {
        puts("failed join read");
    }

    if (pthread_join(write, NULL))
    {
        puts("failed join write");
    }
}

/*write*/
void *ProduceWrite(void *person)
{
    size_t i = 0;
    person_t *p = (person_t*)person;

    while (i < SIZE)
    {
        pthread_mutex_lock(&mutex);

        if (!full)
        {
            p->name = "mirit";
            p->id = 123456 + i;

            ++i;
            full = 1;
        }

        pthread_mutex_unlock(&mutex);
    }

    return NULL;
}

/*read*/
void *ConsumeRead(void *person)
{
    size_t i = 0;
    person_t *p = (person_t*)person;

    while (i < SIZE)
    {
        pthread_mutex_lock(&mutex);

        if (full)
        {
            printf("%s\n", p->name);
            printf("%d\n", p->id);

            ++i;
            full = 0;
        }

        pthread_mutex_unlock(&mutex);
    }

    return NULL;
}

/*BuzyWait*/
void MutexBusyWait(void)
{
    size_t i = 0;
    dlist_t *dlist =  DLLCreate();
    pthread_t threads[SEM_SIZE] = {0};
    
    if (NULL == dlist)
    {
        puts("failed dlist");
        return;
    }

    for (i = 0; i < SEM_SIZE; i += 2)
    {
        if (pthread_create(threads + i, NULL, ProduceInsert, dlist))
        {
            printf("failed ProduceInsert num %lu\n", i);
        }
        if (pthread_create(threads + i + 1, NULL, ConsumeRemove, dlist))
        {
            printf("failed ConsumeRemove num %lu\n", i);
        }
    }

    /*assure there done running*/
    for (i = 0; i < SEM_SIZE; ++i)
    {
        if (pthread_join(threads[i], NULL))
        {
            printf("failed join num %lu\n", i);
        }
    }

    DLLDestroy(dlist);
}

void *ProduceInsert(void *dlist)
{
    dlist_t *d = (dlist_t*)dlist;

    while (counter < SEM_SIZE * 5)
    {
        pthread_mutex_lock(&mutex);

        DLLPushFront(d, (void*)counter);
        ++counter;

        printf("push - %lu\n", counter);
        pthread_mutex_unlock(&mutex);
    }

    return NULL;
}

void *ConsumeRemove(void *dlist)
{
    dlist_t *d = (dlist_t*)dlist;

    while (counter < SEM_SIZE * 5)
    {
        pthread_mutex_lock(&mutex);

        if (!DLLIsEmpty(d))
        {
            printf("pop - %lu\n", (size_t)DLLPopBack(d));
            ++counter;
        }

        pthread_mutex_unlock(&mutex);
    }

    return NULL;
}

/*Semaphore*/
void MutexSemaphore(void)
{
    size_t i = 0;
    dlist_t *dlist =  DLLCreate();
    pthread_t threads[SEM_SIZE] = {0};

    if (NULL == dlist)
    {
        return;
    }

    counter = 0;

    sem_init(&sem, 0, 0);

    for (i = 0; i < SEM_SIZE; i += 2)
    {
        if (pthread_create(threads + i, NULL, SemProduceInsert, dlist))
        {
            printf("failed create %lu\n", i);
            sem_destroy(&sem);
            DLLDestroy(dlist);

            return;
        }
        if (pthread_create(threads + (i + 1), NULL, SemConsumeRemove, dlist))
        {
            printf("failed create %lu\n", i);
            sem_destroy(&sem);
            DLLDestroy(dlist);

            return;
        }
    }

    /*assure there done running*/
    for (i = 0; i < SEM_SIZE; ++i)
    {
        if (pthread_join(threads[i], NULL))
        {
            printf("failed join num %lu\n", i);
        }
    }

    sem_destroy(&sem);
    DLLDestroy(dlist);
}

void *SemProduceInsert(void *dlist)
{
    dlist_t *d = (dlist_t*)dlist;

    while (counter < (SEM_SIZE * 10))
    {
        pthread_mutex_lock(&mutex);

        DLLPushFront(d, (void*)counter);
        ++counter;

        printf("push - %lu\n", counter);
        sem_post(&sem);
        pthread_mutex_unlock(&mutex);
    }

    return NULL;
}

void *SemConsumeRemove(void *dlist)
{
    dlist_t *d = (dlist_t*)dlist;

    while (counter < (SEM_SIZE * 10))
    {
        sem_wait(&sem);
        pthread_mutex_lock(&mutex);

        printf("pop - %lu\n", (size_t)DLLPopBack(d));
        ++counter;

        pthread_mutex_unlock(&mutex);
    }

    return NULL;
}

void CircularBufferOneMut()
{
    size_t i = 0;
    pthread_t threads[SEM_SIZE] = {0};
    cb_t *cb = CBCreate(SEM_SIZE);
    if (NULL == cb)
    {
        return;
    }

    counter = 0;

    /* forbid reading and allow writing */
    if (0 != sem_init(&sem_read, 0, 0) || 0 != sem_init(&sem_write, 0, SEM_SIZE))
    {
            sem_destroy(&sem_read);
            sem_destroy(&sem_write);
            CBDestroy(cb);

            return;
    }

    for (i = 0; i < SEM_SIZE; i += 2)
    {
        if (pthread_create(threads + i, NULL, WriteToCBOneMut, cb) || pthread_create(threads + (i + 1), NULL, RedaFromCBOneMut, cb))
        {
            printf("failed create %lu\n", i);
            sem_destroy(&sem_read);
            sem_destroy(&sem_write);
            CBDestroy(cb);

            return;
        }
    }

    for (i = 0; i < SEM_SIZE; ++i)
    {
        if (pthread_join(threads[i], NULL))
        {
            printf("failed join num %lu\n", i);
        }
    }

    sem_destroy(&sem_read);
    sem_destroy(&sem_write);
    CBDestroy(cb);
}

void *WriteToCBOneMut(void *cb)
{
    while (1)
    {
        sem_wait(&sem_write);
        pthread_mutex_lock(&mutex);

        CBWrite((cb_t*)cb, (int)counter);
        printf("write - %lu\n", counter);
        ++counter;

        sem_post(&sem_read);
        pthread_mutex_unlock(&mutex);
    }

    return NULL;
}

void *RedaFromCBOneMut(void *cb)
{
    while (1)
    {
        sem_wait(&sem_read);
        pthread_mutex_lock(&mutex);

        printf("read - %d\n", CBRead((cb_t*)cb));

        sem_post(&sem_write);
        pthread_mutex_unlock(&mutex);
    }

    return NULL;
}

void CircularBufferTwoMut()
{
    size_t i = 0;
    pthread_t threads[SEM_SIZE] = {0};
    cb_t *cb = CBCreate(SEM_SIZE);
    if (NULL == cb)
    {
        return;
    }

    counter = 0;

    /* forbid reading and allow writing */
    if (0 != sem_init(&sem_read, 0, 0) || 0 != sem_init(&sem_write, 0, SEM_SIZE))
    {
            sem_destroy(&sem_read);
            sem_destroy(&sem_write);
            CBDestroy(cb);

            return;
    }

    for (i = 0; i < SEM_SIZE; i += 2)
    {
        if (pthread_create(threads + i, NULL, WriteToCBTwoMut, cb) || pthread_create(threads + (i + 1), NULL, RedaFromCBTwoMut, cb))
        {
            printf("failed create %lu\n", i);
            sem_destroy(&sem_read);
            sem_destroy(&sem_write);
            CBDestroy(cb);

            return;
        }
    }

    for (i = 0; i < SEM_SIZE; ++i)
    {
        if (pthread_join(threads[i], NULL))
        {
            printf("failed join num %lu\n", i);
        }
    }

    sem_destroy(&sem_read);
    sem_destroy(&sem_write);
    CBDestroy(cb);
}

void *WriteToCBTwoMut(void *cb)
{
    
    while (1)
    {
        sem_wait(&sem_write);
        pthread_mutex_lock(&write_mut);

        CBWrite((cb_t*)cb, (int)counter);
        printf("write - %lu\n", counter);
        ++counter;

        pthread_mutex_unlock(&write_mut);
        sem_post(&sem_read);
    }

    return NULL;
}

void *RedaFromCBTwoMut(void *cb)
{
    while (1)
    {
        sem_wait(&sem_read);
        pthread_mutex_lock(&read_mut);

        printf("read - %d\n", CBRead((cb_t*)cb));
        pthread_mutex_unlock(&read_mut);

        sem_post(&sem_write);
    }

    return NULL;
}

void CondVarDemo(void)
{
    size_t i = 0;
    pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
    cond_t cond_info;
    pthread_t threads[SEM_SIZE] = {0};

    if (pthread_cond_init (&cond, NULL))
    {
        puts("condition init failed!");
        pthread_cond_destroy(&cond);

        return;
    }

    for (i = 0; i < 5; ++i)
    {
        if (pthread_create(threads + i, NULL, CVRead, (void*)&cond_info))
        {
            printf("failed create %lu\n", i);
            pthread_cond_destroy(&cond);

            return;
        }
    }

    if (pthread_create(threads + i, NULL, CVWrite, (void*)&cond_info))
    {
        printf("failed create %lu\n", i);
        pthread_cond_destroy(&cond);

        return;
    }

    for (i = 0; i < 6; ++i)
    {
        if (pthread_join(threads[i], NULL))
        {
            printf("failed join num %lu\n", i);
        }
    }

    pthread_cond_destroy(&cond_info.cond);
    pthread_mutex_destroy(&cond_info.mut_cond);
 
}

void *CVWrite(void *args)
{
    cond_t *cond_info = (cond_t*)args;

    while (1)
    {
        sleep(1);
        pthread_mutex_lock(&cond_info->mut_cond);
        printf("%lu - writing\n", counter);
        ++counter;
        pthread_mutex_unlock(&cond_info->mut_cond);
        full = 1;
        pthread_cond_signal(&cond_info->cond);
    }

    return NULL;
}

void *CVRead(void *args)
{
    cond_t *cond_info = (cond_t*)args;

    while (1)
    {
        pthread_mutex_lock(&cond_info->mut_cond);
        printf("%lu - read before waiting\n", counter);

        while (full == 0)
        {
            pthread_cond_wait(&cond_info->cond, &cond_info->mut_cond);
        }
    
        printf("%lu - read after waiting\n", counter);
        full = 0;
        pthread_mutex_unlock(&cond_info->mut_cond);
    }

    return NULL;

}


void Berrier(void)
{
    size_t i = 0;
    int tmp = 0;
    pthread_t thread_write = 0;
    pthread_t thread_read[BER_SIZE] = {0};

    full = 0;

    if (pthread_mutex_init(&mutex, NULL))
    {
        return;
    }

    if (sem_init(&sem, 0, BER_SIZE))
    {
        return;
    }

    if (pthread_create(&thread_write, NULL, BerWrite, (void*)&tmp))
    {
        sem_destroy(&sem);

        return;
    }

    for (i = 0; i < BER_SIZE; ++i)
    {
        if (pthread_create(thread_read + i, NULL, BerRead, (void*)&tmp))
        {
            sem_destroy(&sem);

            return;
        }
    }

    for (i = 0; i < BER_SIZE; ++i)
    {
        if (pthread_join(thread_read[i], NULL))
        {
            printf("failed join read num %lu\n", i);
        }
    }

    if (pthread_join(thread_write, NULL))
    {
        printf("failed join write\n");
    }

    sem_destroy(&sem);
    pthread_cond_destroy(&cond_glob);
    pthread_mutex_destroy(&mutex);

}

void *BerWrite(void *args)
{
    size_t i = 0;

    while (1)
    {
        for (i = 0; i < BER_SIZE; ++i)
        {
            sem_wait(&sem);
        }

        *(int*)args = ++counter;
        printf("\n%d\n", *(int*)args);

        pthread_mutex_lock(&mutex);
        full = 3;
        pthread_cond_broadcast(&cond_glob);

        pthread_mutex_unlock(&mutex);

    }

    return NULL;

}

void *BerRead(void *args)
{
    size_t i = 0;

    while (1)
    {
        pthread_mutex_lock(&mutex);
        sem_post(&sem);

        while (full == 0)
        {
            pthread_cond_wait(&cond_glob, &mutex);
        }

        --full;
        ++i;
                printf("read - %d. thread - %lu. run num - %lu.\n", *(int*)args, pthread_self(), i);

        pthread_mutex_unlock(&mutex);

    }

    return NULL;

}



