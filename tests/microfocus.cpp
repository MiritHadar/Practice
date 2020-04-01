
#include <iostream>
#include <limits.h>     // INT_MIN

using namespace std;

int FindSecondBiggest(int *arr, size_t numOfElems);
void FindNumsSumToZero(int *arr, size_t numOfElemsint);
void PrintMeny(string str, size_t times, size_t lenInLine);

int main()
{
    // int arr[] = {200, 300, 60, 90, 1, 89};
    // size_t arrSize = 6;
    // cout << FindSecondBiggest(arr, arrSize) << endl;
    

    // int arr1[] = {1, 300, 60, 300, 1, 89};
    // size_t arrSize1 = 6;
    // cout << FindSecondBiggest(arr1, arrSize1) << endl;

    // int arr2[] = {2000, 300, 60, 90, 1, 989};
    // size_t arrSize2 = 6;
    // cout << FindSecondBiggest(arr2, arrSize2) << endl;

    // int arr3[] = {0, -56, 50, 200, 817, 12, 56};
    // size_t arrSize3 = 7;
    // FindNumsSumToZero(arr3, arrSize3);

    // int arr4[] = {0, -56, 50, 200, 817, 12, 0};
    // size_t arrSize4 = 7;
    // FindNumsSumToZero(arr4, arrSize4);

    string name = "mirit";
    PrintMeny(name, 2, 4);

    return 0;
}

int FindSecondBiggest(int *arr, size_t numOfElems)
{
    int max = INT_MIN;
    int secondMax = arr[0];

    for (size_t i = 0; i < numOfElems; ++i)
    {
        if (arr[i] >= max)
        {
            secondMax = max;
            max = arr[i];
        }
        else if (arr[i] > secondMax)
        {
            secondMax = arr[i];
        }
    }

    return secondMax;
}

void FindNumsSumToZero(int *arr, size_t numOfElemsint)
{
    for (size_t leftIndx = 0; leftIndx < numOfElemsint - 1; ++leftIndx)
    {
        for (size_t rightIndx = leftIndx + 1; rightIndx < numOfElemsint; ++rightIndx)
        {
            if (0 == (arr[leftIndx] + arr[rightIndx]))
            {
                cout << "left = " << arr[leftIndx] << endl;
                cout << "right = " << arr[rightIndx] << endl;

                return;
            }
        }
    }
}

void PrintMeny(string str, size_t times, size_t lenInLine)
{
    string strToPrint = str;
    for (size_t i = 1; i < times; ++i)
    {
        strToPrint += str;
    }

    for (size_t i = 0; i < strToPrint.size(); i += lenInLine)
    {
        cout << strToPrint.substr(i, lenInLine) << endl;
    }
}
