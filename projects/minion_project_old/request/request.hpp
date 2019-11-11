/*
********************************************************************************

Developer : Mirit Hadar
Reviewer :
Last Update : 
Status :

********************************************************************************
*/

#include "packet.hpp"

#ifndef __OL67_Request
#define __OL67_Request

#include <cstddef>      //size

namespace ilrd
{

class Request
{
public:
    explicit Request();
    explicit Request(Packet& packet_);
    //Request(const Request other_) = default
    //Request& operator=(const Request other_) = default
    //~Request() = default
    ActType GetActType();
    uint64_t GetUid();
    uint64_t GetIndex();
    Packet &GetPacket();
    unsigned char *GetDataBlock();
    
    static const size_t GO_TO_UID = 1;
    static const size_t GO_TO_INDX = 9;
    static const size_t GO_TO_BUFF = 17;

private:
    Packet m_packet;
};

} // namespace ilrd

#endif /* __OL67_Request */

