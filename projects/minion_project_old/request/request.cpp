/*
********************************************************************************

Developer : Mirit Hadar
Reviewer :
Last Update : 
Status :

********************************************************************************
*/

#include "request.hpp"

namespace ilrd
{

Request::Request()
    :m_packet()
{
    ;
}

Request::Request(Packet& packet_)
    :m_packet(packet_)
{
    ;
}

ActType Request::GetActType()
{
    //return static_cast<ActType>(m_packet.GetBuffer()[0]);
    return *m_packet.GetBuffer();
}

uint64_t Request::GetUid()
{
    return *reinterpret_cast<uint64_t*>(m_packet.GetBuffer() + GO_TO_UID);
}


uint64_t Request::GetIndex()
{
    return *reinterpret_cast<uint64_t*>(m_packet.GetBuffer() + GO_TO_INDX);
}

Packet& Request::GetPacket()
{
    return m_packet;
}

unsigned char *Request::GetDataBlock()
{
    return &m_packet.GetBuffer()[GO_TO_BUFF]; 
}

} // namespace ilrd



