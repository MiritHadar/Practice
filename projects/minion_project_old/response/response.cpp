/*
********************************************************************************

Developer : Mirit Hadar
Reviewer :
Last Update : 
Status :

********************************************************************************
*/

#include <cstring>  //memcpy
#include "response.hpp"

namespace ilrd
{

Response::Response(uint32_t size_)
    : m_packet(),
     m_packetSize(size_)
{
    ;
}

void Response::SetActType(ActType actType_)
{
    *m_packet.GetBuffer() = actType_;
}

void Response::SetStatus(Status status_)
{
    Status *myStatus = reinterpret_cast<Status*>(this->GetPacket().GetBuffer() + GO_TO_STATUS);
    *myStatus = status_;
}

void Response::SetData(unsigned char* data_)
{
    memcpy(m_packet.GetBuffer() + GO_TO_BUFF, data_, 1024 * 4);
}

void Response::SetUid(uint64_t uid_)
{
    *(reinterpret_cast<size_t *>(m_packet.GetBuffer() + GO_TO_UID)) = uid_;
}

void Response::SetSize(uint32_t size_)
{
    m_packetSize = size_;
}

uint32_t Response::GetSize()
{
    return m_packetSize;
}

Packet Response::GetPacket()
{
    return m_packet;
}


} // namespace ilrd




