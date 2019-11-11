
#include <cassert>        // assert
#include <cstddef>	      // size_t
#include <bits/stdc++.h>  // INT_MIN
#include <iostream>       // cout

using namespace std;

int FindMax(int *src, size_t n);
size_t FindLargestSubArr(int *src, size_t n);
size_t FindFirstPosIndx(int *src, size_t n);
int FindLargestSubArrNegAllowed(int *src, size_t n);
int BursaFunc(int *src, size_t n, int **start, int **end);

void FindMaxTest();
void FindLargestSubArrTest();
void FindLargestSubArrNegAllowedTest();
void BursaFuncTest();

int main()
{
    //FindMaxTest();
    //FindLargestSubArrTest();
    //FindLargestSubArrNegAllowedTest();
    BursaFuncTest();

    return 0;
}

void FindMaxTest()
{
    int src[] = {-1,0,1,2,0,-1};
    size_t sizeSrc = 6;

    if (2 != FindMax(src, sizeSrc))
    {
        cout << __LINE__ << endl;
    }

    int src1[] = {-1,0,-100,-2,0,-1};
    size_t sizeSrc1 = 6;

    if (0 != FindMax(src1, sizeSrc1))
    {
        cout << __LINE__ << endl;
    }
}

void FindLargestSubArrTest()
{
    int srcPos[] = {0,0,2,2,0,3,5,0,10};
    size_t sizeSrcPos = sizeof(srcPos) / sizeof(srcPos[0]);
    cout << FindLargestSubArr(srcPos, sizeSrcPos) << endl;

    int srcMixed[] = {-1,-5,0,-7,0,-1};
    size_t sizeSrcMixed = sizeof(srcMixed) / sizeof(srcMixed[0]);
    cout << FindLargestSubArr(srcMixed, sizeSrcMixed) << endl;
}

void FindLargestSubArrNegAllowedTest()
{
    //Only negatives
    int srcNeg[] = {-1,-3,-10,-7};
    size_t sizeSrcNeg = sizeof(srcNeg) / sizeof(srcNeg[0]);
    if (-1 != FindLargestSubArrNegAllowed(srcNeg, sizeSrcNeg))
    {
        cout << "error in line: " << __LINE__ << endl;
    }

    int srcNeg1[] = {-10,-3,-10,-9};
    size_t sizeSrcNeg1 = sizeof(srcNeg1) / sizeof(srcNeg1[0]);
    if (-3 != FindLargestSubArrNegAllowed(srcNeg1, sizeSrcNeg1))
    {
        cout << "error in line: " << __LINE__ << endl;
    }

    //Negative and positive
    int srcNeg2[] = {-10,3,10,-9,-1,14};
    size_t sizeSrcNeg2 = sizeof(srcNeg2) / sizeof(srcNeg2[0]);
    if (17 != FindLargestSubArrNegAllowed(srcNeg2, sizeSrcNeg2))
    {
        cout << "error in line: " << __LINE__ << endl;
    }
    

    int srcNeg3[] = {-10,-3,-10,-9,-1,-4};
    size_t sizeSrcNeg3 = sizeof(srcNeg3) / sizeof(srcNeg3[0]);
    if (-1 != FindLargestSubArrNegAllowed(srcNeg3, sizeSrcNeg3))
    {
        cout << "error in line: " << __LINE__ << endl;
    }

    int srcNeg4[] = {-10,3,10,-9,-1,-14};
    size_t sizeSrcNeg4 = sizeof(srcNeg4) / sizeof(srcNeg4[0]);
    if (13 != FindLargestSubArrNegAllowed(srcNeg4, sizeSrcNeg4))
    {
        cout << "error in line: " << __LINE__ << endl;
    }

    int srcNeg5[] = {-10,3,10,-15,1,14,-5,4};
    size_t sizeSrcNeg5 = sizeof(srcNeg5) / sizeof(srcNeg5[0]);
    if (15 != FindLargestSubArrNegAllowed(srcNeg5, sizeSrcNeg5))
    {
        cout << "error in line: " << __LINE__ << endl;
    }

    int srcNeg6[] = {-10,3,10,-15,1,4,-5,4};
    size_t sizeSrcNeg6 = sizeof(srcNeg6) / sizeof(srcNeg6[0]);
    if (13 != FindLargestSubArrNegAllowed(srcNeg6, sizeSrcNeg6))
    {
        cout << "error in line: " << __LINE__ << endl;
    }
}

void BursaFuncTest()
{
    int **start = NULL;
    int **end = NULL;
    int srcNeg[] = {-7,-3,-10,-1};
    size_t sizeSrcNeg = sizeof(srcNeg) / sizeof(srcNeg[0]);
    if (-1 != BursaFunc(srcNeg, sizeSrcNeg, start, end))
    {
        cout << "error in line: " << __LINE__ << endl;
    }
    //cout << **start << endl;
    cout << /* **end << */ endl << endl;

    int srcNeg1[] = {-1,-3,-10,-7};
    size_t sizeSrcNeg1 = sizeof(srcNeg1) / sizeof(srcNeg1[0]);
    if (-1 != BursaFunc(srcNeg1, sizeSrcNeg1, start, end))
    {
        cout << "error in line: " << __LINE__ << endl;
    }
    cout << **start << endl;
    cout << **end << endl << endl;
}

int FindMax(int *src, size_t n)
{
    assert(src);

    int max = *src;

    for (size_t i = 1; i < n; ++i)
    {
       if (src[i] > max)
       {
           max = src[i];
       }
    }

    return max;
}

//necessarily containes at list one positive num, inclusive of zero
size_t FindLargestSubArr(int *src, size_t n)
{
    assert(src);

    size_t i = FindFirstPosIndx(src, n);
    size_t tmpSum = src[i];
    size_t sum = 0;
    ++i;
    cout << "n = " << n << endl;
    while (i < n)
    {
        cout << "tmpSum = " << tmpSum << endl;

        if (src[i] > 0)
        {
            tmpSum += src[i];
        }
        else
        {
            if (tmpSum > sum)
            {
                sum = tmpSum;
            }

            tmpSum = 0;
        }

        ++i;
    }

    return (tmpSum > sum)? tmpSum : sum;
}

int FindLargestSubArrNegAllowed(int *src, size_t n)
{
    assert(src);
    int tmpSum = src[0];
    int finalSum = tmpSum;

    for (size_t i = 1; i < n; ++i)
    {
        // cout << "tmpSum = " << tmpSum << '\t';
        // cout << "finalSum = " << finalSum << endl;

        if ((tmpSum < 0) && (src[i] > tmpSum))
        {
            tmpSum = src[i];
        }
        else
        {
            tmpSum += src[i];
        }

        if (tmpSum > finalSum)
        {
            finalSum = tmpSum;
        }
    }

    return finalSum;
}

size_t FindFirstPosIndx(int *src, size_t n)
{
    size_t i = 0;

    while (src[i] < 0)
    {
        i++;
    }

    return i;
}

int BursaFunc(int *src, size_t n, int **start, int **end)
{
    assert(src);
    int tmpSum = src[0];
    int finalSum = tmpSum;
    start = &src;
    end = &src;
    int **tmpStart = start;
    ++src;

    for (size_t i = 1; i < n; ++i)
    {
        cout << "i = " << i << endl;
        cout << "tmpSum = " << tmpSum << '\t';
        cout << "finalSum = " << finalSum << endl;
        cout << "start = " << **start << endl;
        cout << "end = " << **end << endl;

        if ((tmpSum < 0) && (*src > tmpSum))
        {
            tmpSum = *src;
            tmpStart = &src;
        }
        else
        {
            tmpSum += *src;
        }

        if (tmpSum > finalSum)
        {
            finalSum = tmpSum;
            start = tmpStart;
            end = &src;
        }
        ++src;
    }

    return finalSum;
}
