/*
********************************************************************************

Developer : Mirit Hadar
Reviewer :
Last Update : 
Status :

********************************************************************************
*/

#include "crack_arrays.hpp"

using namespace std;

bool IsUnique(std::string str)
{
    char lut_abc[256] = {0};
    size_t str_len = str.size();
    cout << "str_len = " << str_len << endl;
    for (size_t i = 0; i < str_len; ++i)
    {
        if (0 != lut_abc[static_cast<int>(str[i])])
        {
            return 0;
        }

        lut_abc[static_cast<int>(str[i])]++;

    }

    return 1;
}




