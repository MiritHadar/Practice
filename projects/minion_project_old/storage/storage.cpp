/*
********************************************************************************

Developer : Mirit Hadar
Reviewer :
Last Update : 
Status :

********************************************************************************
*/

#include <iostream>
#include <cstring>      //memcpy
#include <cassert>      //assert
#include <algorithm>    //for_each
#include "storage.hpp"

namespace ilrd
{

Storage::Buffer &Storage::Buffer::operator=(const Buffer& other_)
{
    memcpy(m_data, other_.m_data, DATA_BLOCK_SIZE);

    return *this;
}

void Storage::Read(unsigned char *dest_, uint64_t blockIndx_)
{
    memcpy(dest_, m_storeroom[blockIndx_].m_data, DATA_BLOCK_SIZE);
}

void Storage::Write(const unsigned char *src_, uint64_t blockIndx_)
{
    Buffer tmpBuffer;
    memcpy(tmpBuffer.m_data, src_, DATA_BLOCK_SIZE);

    m_storeroom[blockIndx_] = tmpBuffer;
}

} // namespace ilrd





