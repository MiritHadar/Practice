/*
********************************************************************************

Developer : Mirit Hadar
Reviewer :
Last Update : 
Status :

********************************************************************************
*/

#include "counter.hpp"

size_t StaticCounter::s_Cntr = 0;

StaticCounter::StaticCounter()
    :m_id(++s_Cntr)
{
    ;
}

size_t StaticCounter::GetId()
{
    std::cout << this->m_id <<std::endl;
    return m_id;
}

void StaticCounter::Print()
{
    std::cout << s_Cntr <<std::endl;
}





