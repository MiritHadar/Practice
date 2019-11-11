
#include <stdio.h>
#include <pthread.h>
#include <assert.h>
#include <unistd.h>


#define    SIZE      10
#define UNUSED(X)       (void)(x)

void *PushThreads(void *threads);

int main()
{
    size_t i = 0;
    pthread_t threads[SIZE] = {0};
    size_t indexes[SIZE] = {0};

    /*Create */
    for (i = 0; i < SIZE; ++i)
    {
        if (0 != pthread_create(&threads[i], NULL, PushThreads, (indexes + i)))
        {
            printf("%lu - failed create\n", i);

            return 1;
        }
    }

    /*Join */
    for (i = 0; i < SIZE; ++i)
    {
        if (0 != pthread_join(threads[i], NULL))
        {
            printf("%lu - failed join\n", i);

            return 1;
        }
    }

    /*Indexes */
    for (i = 0; i < SIZE; ++i)
    {
        if (indexes[i] != 1)
        {
            printf("%lu failed\n", i);

            return 1;
        }
    }

    return 0;
}

void *PushThreads(void *indexes)
{
    assert(indexes);

    *(int*)indexes = 1;
    
    return NULL;
}





