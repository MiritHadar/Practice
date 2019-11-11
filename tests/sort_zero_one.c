
#include <stddef.h>
#include <string.h>
#include <stdio.h>

void SortZeroOne(int *arr, size_t n);

int main()
{
    size_t size = 13;
    int arr[] = {1,0,0,0,1,1,0,0,0,0,1,1,0};
    size_t i = 0;

    SortZeroOne(arr, size);
    for (i = 0; i < size; ++i)
    {
        printf("%d ", arr[i]);
    }

    puts("\n");

    return 0;
}

void SortZeroOne(int *arr, size_t n)
{
    size_t i = 0;
    size_t sumOfOnes = 0;

    for (i = 0; i < n; ++i)
    {
        sumOfOnes += arr[i];
    }

    printf("%lu\n", sumOfOnes);

    memset(arr, 0, (n - sumOfOnes) * sizeof(int));

    for(i = (n - sumOfOnes); i < n; ++i)
    {
        arr[i] = 1;
    }
}