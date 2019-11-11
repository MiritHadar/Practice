/*
********************************************************************************

Developer : Mirit Hadar
Reviewer :
Last Update : 
Status :

********************************************************************************
*/

#ifndef __OL67_histo
#define __OL67_histo

#include <cstddef>      /*     size_t   */

#include "str.hpp"

class Data
{
    public:
        //Ctors
        Data();
        Data(const Str str_);

        Data& operator++();
        friend std::ostream& operator<<(std::ostream& os_, const Data& data_);

        const Str GetStr() const;
        size_t GetCounter() const;
        
    private:
        const Str m_str;
        size_t m_cntr = 0;
};

bool operator==(const Data& d1_, const Data& d2_);

#endif /* __OL67_histo */


