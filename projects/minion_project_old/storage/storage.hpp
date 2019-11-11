/*
********************************************************************************

Developer : Mirit Hadar
Reviewer :
Last Update : 
Status :

********************************************************************************
*/

#ifndef __OL67_STORAGE
#define __OL67_STORAGE

#include <cstddef>          //size_t
#include <map>              //map
#include <stdint.h>         //uint_32
#include "storage.hpp"
//#include "uncopyable.hpp"
#include <cstring>      //memcpy

namespace ilrd
{

const uint64_t DATA_BLOCK_SIZE = (1024 * 4);

class Storage //: private Uncopyable
{
public:
    //Storage() = default
    //~Storage() = default
    void Read(unsigned char *dest_, uint64_t blockIndx_);
    void Write(const unsigned char *src_, uint64_t blockIndx_);

private:
    struct Buffer
    {
    public:
        Buffer &operator=(const Buffer& other_);
        unsigned char m_data[DATA_BLOCK_SIZE];
    };

    std::map<uint64_t, Buffer> m_storeroom;
};

} // namespace ilrd

#endif /* __OL67_STORAGE */


