
#include <string>   //string
#include <cstddef>  //size_t
#include <iostream>  //cout , endl

int EvenOdd (int srcNum);
size_t CountDigits(int srcNum);

int main()
{
    int num = 12345678;
    std::cout << num << std::endl;
    std::cout << EvenOdd(num) << std::endl;

    return 0;
}

//copies digits from the left section to the odd positions
//copies digits from the right section to the even positions
//returns the new number
int EvenOdd (int srcNum)
{
    size_t numOfDigits = CountDigits(srcNum);
    std::string srcStr = std::to_string(srcNum);
    std::string destStr = new char[numOfDigits];
    size_t halfNum = numOfDigits / 2;

    for (size_t i = 0; i < halfNum; ++i)
    {
        destStr[i * 2] = srcStr[i];
        destStr[i * 2 + 1] = srcStr[i + halfNum];
    }

    return stoi(destStr);
}

size_t CountDigits(int srcNum)
{
    size_t numOfDigits = 0;
    while (srcNum != 0)
    {
        ++numOfDigits;
        srcNum /= 10;
    }

    return numOfDigits;
}
