/*
********************************************************************************

Developer : Mirit Hadar
Reviewer :
Last Update : 
Status :

********************************************************************************
*/

#include "histo.hpp"

Data::Data()
    : m_str(), m_cntr(0)
{
    ;
}

Data::Data(const Str str_)
    : m_str(str_), m_cntr(1)
{
    ;
}

Data& Data::operator++()
{
    ++m_cntr;

    return *this;
}

const Str Data::GetStr() const
{
    return m_str;
}

size_t Data::GetCounter() const
{
    return m_cntr;
}

/***********************************************************************************************/
std::ostream& operator<<(std::ostream& os_, const Data& data_)
{
    return os_ << data_.GetStr() << " x " << data_.GetCounter();
}

bool operator==(const Data& d1_, const Data& d2_)
{
    return d1_.GetStr() == d2_.GetStr();
}
