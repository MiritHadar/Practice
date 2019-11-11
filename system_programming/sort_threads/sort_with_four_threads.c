
#include <stdio.h>      /*       print      */
#include <stdlib.h>     /*  qsort, malloc   */
#include <assert.h>     /*      assert      */
#include <pthread.h>    /*      threads     */
#include <string.h>     /*      strcmp      */

#define     NUM_OF_THREADS          4   /* DO NOT CHANGE */
#define     UNUSED(x)       (void)(x)


typedef int (*cmp_t)(const void *s1, const void *s2);

typedef struct args
{
    char **start;
    size_t size;
}args_t;

static int IsBefore(const void *s1, const void *s2);
static void *SortThread(void *args);
static int MergeThread(args_t *part1, args_t *part2);
void AssignArrays(args_t *arr_args, char **ptrs_to_file, size_t num_of_lines);

int main(int argc, char *argv[])
{
    char **ptrs_to_file = NULL;
    FILE *fp = NULL;
    size_t i = 0;
    size_t buffer_size = 0;
    size_t num_of_lines = 0;
    pthread_t threads[NUM_OF_THREADS] = {0};
    char *buf = NULL;
    char *tmp_buf = NULL;
    args_t arr_args[NUM_OF_THREADS] = {{NULL}};

    if (argc < 2)
    {
        puts("No file name supplied");
        return 1;
    }

    fp = fopen(argv[1], "r");
    if (NULL == fp)
    {
        puts("can't open file");
        return 1;
    }

    /*copying the original file in to a buffer */
    fseek(fp, 0, SEEK_END);
    buffer_size = ftell(fp) - 1;

    buf = malloc(buffer_size * sizeof(char*));
    if (NULL == buf)
    {
        puts("failed malloc for buffer");
        return 1;
    }

    fseek(fp, 0, SEEK_SET);
    fread(buf, sizeof(char*), buffer_size, fp);

    buf[buffer_size] = '\0';
    fseek(fp, 0, SEEK_SET);

    /* swapping '\n' with '\0' */
    tmp_buf = strtok(buf, "\n");
    while (NULL != tmp_buf)
    {
        ++num_of_lines;
        tmp_buf = strtok(NULL, "\n");
    }
    
    fclose(fp);
/*     num_of_lines -= 1;
 */    
    /* allocate space for pointers to buffers */
    ptrs_to_file = malloc(num_of_lines * sizeof(char*));
    if (NULL == ptrs_to_file)
    {
        puts("failed malloc for arr of pointers to the buffer");
        return 1;
    }

    tmp_buf = buf;

    /* puting pointers to point at each new line */
    for (i = 0; i < num_of_lines; ++i)
    {
        ptrs_to_file[i] = tmp_buf;

        while ('\0' != *tmp_buf)
        {
            ++tmp_buf;
        }

        ++tmp_buf;
    }
    
    AssignArrays(arr_args, ptrs_to_file, num_of_lines);
    
    /* executing the threads */
    for (i = 0; i < NUM_OF_THREADS; ++i)
    {
        if (pthread_create(&threads[i], NULL, SortThread, &arr_args[i]))
        {
            printf("failed create num %lu\n", i);
            return 1;
        }
    }

    /* assure there done running */
    for (i = 0; i < NUM_OF_THREADS; ++i)
    {
        if (pthread_join(threads[i], NULL))
        {
            printf("failed join num %lu\n", i);
            return 1;
        }
    }

    /* Combine them */
    for (i = 0; i < NUM_OF_THREADS - 1; i += 2)
    {
        if (0 != MergeThread(&arr_args[i], &arr_args[i + 1]))
        {
            puts("failed merge");
        }
    }
   
    arr_args[0].size = num_of_lines / 2;
    arr_args[NUM_OF_THREADS / 2].start = ptrs_to_file + arr_args[0].size;
    arr_args[NUM_OF_THREADS / 2].size = num_of_lines - arr_args[0].size;

    if (0 != MergeThread(&arr_args[0], &arr_args[NUM_OF_THREADS / 2]))
    {
        puts("failed merge");
    }

    /* testing */
    for (i = 0; i < num_of_lines; ++i)
    {
        puts(ptrs_to_file[i]);
    }

    free(ptrs_to_file);
    free(buf);

    return 0;
}

void AssignArrays(args_t *arr_args, char **ptrs_to_file, size_t num_of_lines)
{
    arr_args[0].start = ptrs_to_file;
    arr_args[0].size = num_of_lines / NUM_OF_THREADS;
    arr_args[1].start = arr_args[0].start + arr_args[0].size;
    arr_args[1].size = num_of_lines / NUM_OF_THREADS;
    arr_args[2].start = arr_args[1].start + arr_args[1].size;
    arr_args[2].size = num_of_lines / NUM_OF_THREADS;
    arr_args[3].start = arr_args[2].start + arr_args[2].size;
    arr_args[3].size = num_of_lines - arr_args[0].size - arr_args[1].size - arr_args[2].size;
}

static int IsBefore(const void *s1, const void *s2)
{
    return strcmp(*(const char**)s1, *(const char**)s2);
}

static void *SortThread(void *args)
{
    args_t *sort_info = (args_t*)args;

    qsort(sort_info->start,
          sort_info->size,
          sizeof(char*),
          IsBefore);

    return NULL;

}

static int MergeThread(args_t *part1, args_t *part2)
{
    size_t total_size = 0;
    char **tmp_base = NULL;
    size_t i_part1 = 0;
    size_t i_part2 = 0;

    assert(part1 && part2);

    total_size = part1->size + part2->size;
    tmp_base = (char**)malloc(sizeof(char**) * total_size);

    if (NULL == tmp_base)
    {
        return 1;
    }

    while (i_part1 < part1->size && i_part2 < part2->size)
    {
        if(IsBefore(part1->start + i_part1, part2->start + i_part2) >= 0)
        {
            tmp_base[i_part1 + i_part2] = part2->start[i_part2];
            ++i_part2;
        }
        else
        {
            tmp_base[i_part1 + i_part2] = part1->start[i_part1];
            ++i_part1;
        }
    }

    while (i_part1 < part1->size)
    {
        tmp_base[i_part1 + i_part2] = part1->start[i_part1];
        ++i_part1;
    }

    while (i_part2 < part2->size)
    {
        tmp_base[i_part1 + i_part2] = part2->start[i_part2];
        ++i_part2;
    }

    memcpy(part1->start, tmp_base, sizeof(char**) * total_size);

    free(tmp_base);

    return 0;

}




    
