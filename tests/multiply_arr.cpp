
#include <iostream>
#include <cstddef>  // size_t

int *MultAllNumsButMe(int *srcArr, size_t n);
int *MultAllNumsButMeBetter(int *srcArr, size_t n);

int main()
{
    int src[] = {1, 2, 3, 4};

    int *destArr = MultAllNumsButMe(src, sizeof(src)/ sizeof(src[0]));
    for (size_t i = 0; i < sizeof(src)/sizeof(src[0]); ++i)
    {
        std::cout << destArr[i] << std::endl;
    }

    std::cout << std::endl;
    int *destArrBetter = MultAllNumsButMeBetter(src, sizeof(src)/ sizeof(src[0]));
    for (size_t i = 0; i < sizeof(src)/sizeof(src[0]); ++i)
    {
        std::cout << destArrBetter[i] << std::endl;
    }

    delete[] destArr;
    delete[] destArrBetter;

    return 0;
}


int *MultAllNumsButMe(int *srcArr, size_t n)
{
    int multAllNums = 1;
    int *destArr = new int[n];
    
    for (size_t i = 0; i < n; ++i)
    {
        multAllNums *= srcArr[i];
    }

    for (size_t i = 0; i < n; ++i)
    {
        destArr[i] = multAllNums / srcArr[i];
    }

    return destArr;
}

int *MultAllNumsButMeBetter(int *srcArr, size_t n)
{
    int *left = new int[n];
    int *right = new int[n];
    for (size_t i = 0; i < n; ++i)
    {
        left[i] = 1;
        right[i] = 1;
    }

    for (size_t i = 0; i < n; ++i)
    {
        for (size_t j = 0; j < i; ++j)
        {
            left[i] *= srcArr[j];
        }

        for (size_t j = i + 1; j < n; ++j)
        {
            right[i] *= srcArr[j];
        }
    }

    for (size_t i = 0; i < n; ++i)
    {
        right[i] *= left[i];
    }

    delete[] left;
    
    return right;
}
