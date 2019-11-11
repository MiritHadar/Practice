/*
********************************************************************************

Developer : Mirit Hadar
Reviewer :
Last Update : 
Status :

********************************************************************************
*/

#ifndef __OL67_packet
#define __OL67_packet

#include <stdint.h> //uint32_t
#include <stddef.h>  //size_t

namespace ilrd
{

const uint32_t BUFF_SIZE = (5 * 1024);
const uint32_t INFO_LEN = (4 * 1024) + 17;

typedef unsigned char ActType;
 
class Packet
{
public:
    explicit Packet();
    Packet(const unsigned char *other_);
    Packet(const Packet &other_);
    Packet& operator=(const Packet &other_);
    //~Packet() = default
    unsigned char *GetBuffer();

private:
    unsigned char m_buff[INFO_LEN];
};

} // namespace ilrd

#endif /* __OL67_packet */

