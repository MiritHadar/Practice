/*
********************************************************************************

Developer : Mirit Hadar
Reviewer :
Last Update : 
Status :

********************************************************************************
*/

#include <cstddef>		 // size_t 
#include <assert.h>      // assert 
#include <cstring>	     // memcpy
#include <algorithm>	 // copy
#include <cctype>        // isspace 
#include "crack.hpp"

using namespace std;

namespace mirit
{

static bool IsEvenLenPol(string str);
static bool IsOddLenPol(string str);
static void Copy(string &str, size_t i);
size_t g_lettersLut[256] = {0};

const size_t CHARS = 256;

bool IsAllStrUnique(const char *str)
{
    assert(str);
    int lutOfLetters[CHARS] = {0};
    char c = *str;

    while ('\0' != c)
    {
        // cout << "c = " << c << endl;
        // cout << lutOfLetters[static_cast<int>(c)] << endl;
        if (lutOfLetters[static_cast<int>(c)] > 0)
        {
            return false;
        }
        else
        {
            ++lutOfLetters[static_cast<int>(c)];
        }
        c = *(++str);
    }

    return true;
}

bool IsAllStrUniqueNoDs(string str)
{
    for (size_t i = 0; i < str.length(); ++i)
    {
        for (size_t j = i + 1; j < str.length(); ++j)
        {
            if (str[i] == str[j])
            {
                return false;
            }
        }
    }

    return true;
}


size_t HowManyCharsInStr(const char* str)
{
    size_t numOfChars = 0;
    while ('\0' != *str)
    {
        ++numOfChars;
        ++str;
    }

    return numOfChars;
}

void ReplaceSpaces(string &str)
{
    //remove_if(str.begin(), str.end(), isspace(str));
}

bool IsPolindrome(string str)
{
    if ((str.length() % 2) == 0)
    {
        return IsEvenLenPol(str);
    }
    
    return IsOddLenPol(str);
}

static bool IsEvenLenPol(string str)
{
    for (size_t i = 0; i < str.length(); ++i)
    {
        ++g_lettersLut[static_cast<int>(str[i])];
    }

    for (size_t i = 0; i < 256; ++i)
    {
        if (0 != (g_lettersLut[i] % 2))
        {
            return false;
        }
    }

    return true;
}

static bool IsOddLenPol(string str)
{
    int oddAppearFound = 0;
    for (size_t i = 0; i < str.length(); ++i)
    {
        ++g_lettersLut[static_cast<int>(str[i])];
        cout << str[i] << endl;
    }

    for (size_t i = 0; i < 256; ++i)
    {
        if (0 != (g_lettersLut[i] % 2))
        {
            ++oddAppearFound;
        }
    }

    return (oddAppearFound <= 1);
}

// supportes sequential spaces
void RemoveSpacesInplace(string &str)
{
    assert(!(str.empty()));
    size_t i = 0;

    while ('\0' != str[i])
    {
        cout << "RemoveSpacesInplace : " << i << endl;

        if (' ' == str[i])
        {
            Copy(str, i);
        }
        // in case of copying spaces
        if (' ' != str[i])
        {
            ++i;
        }
    }
}

static void Copy(string &str, size_t i)
{
    while ('\0' != str[i])
    {
        cout << "Copy : " << i << endl;
        str[i] = str[i + 1];
        ++i;
    }
}

int Fibonacci(int n)
{
    
}



} //namespace mirit



