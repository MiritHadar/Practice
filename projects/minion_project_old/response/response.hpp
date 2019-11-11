/*
********************************************************************************

Developer : Mirit Hadar
Reviewer :
Last Update : 
Status :

********************************************************************************
*/

#ifndef __OL67_Response
#define __OL67_Response

#include <cstddef>      //size_t
#include "packet.hpp"

namespace ilrd
{

typedef char Status;

class Response
{
public:
    explicit Response(uint32_t size_ = 0);
    //Response(const Response other_) = default
    //Response& operator=(const Response other_) = default
    //~Response() = default

    void SetActType(ActType actType_);
    void SetUid(uint64_t uid_);
    void SetStatus(Status status_);
    void SetData(unsigned char* data_);
    void SetSize(uint32_t size_);

    Packet GetPacket();
    uint32_t GetSize();

    static const size_t GO_TO_UID = 1;
    static const size_t GO_TO_STATUS = 9;
    static const size_t GO_TO_BUFF = 10;

private:
    Packet m_packet;
    uint32_t m_packetSize;
};

} // namespace ilrd

#endif /* __OL67_Response */

