/*
********************************************************************************

Developer : Mirit Hadar
Reviewer :
Last Update : 
Status :

********************************************************************************
*/

#include <cstring>      //memcpy
#include "packet.hpp"

namespace ilrd
{

Packet::Packet()
    :m_buff()
{
    ;
}

Packet::Packet(const unsigned char *other_)
{
    memcpy(m_buff, other_, INFO_LEN);
}

Packet::Packet(const Packet &other_)
{
    memcpy(m_buff, other_.m_buff, INFO_LEN);
}

Packet& Packet::operator=(const Packet &other_)
{
    memcpy(m_buff, other_.m_buff, INFO_LEN);

    return *this;
}

unsigned char *Packet::GetBuffer()
{
    return m_buff;
}

} // namespace ilrd



