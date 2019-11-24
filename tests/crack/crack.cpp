/*
********************************************************************************

Developer : Mirit Hadar
Reviewer :
Last Update : 
Status :

********************************************************************************
*/

#include <cstddef>		/* size_t */
#include <assert.h>      /* assert */
#include "crack.hpp"

namespace mirit
{

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

void ReplaceSpaces(string str)
{
    for (size_t i = 0; i < str.size(); ++i)
    {
        if (str[i] == ' ')
        {
            str[i] = '%';
        }
    }
}

} //namespace mirit



