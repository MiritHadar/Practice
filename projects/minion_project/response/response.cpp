/******************************************************************************/
/* author: 		Ori Michaeli											  	  */
/* Reviewer: 					       										  */
/* version: 	Draft			  		                                      */
/* Last update: 07-10-2019					                                  */
/******************************************************************************/

#include <cstring>			//	memcpy

#include "response.hpp"		//	Header file	

static const uint32_t READ_OR_WRITE_FLAG = 1;
static const uint32_t UID = 8;
static const uint32_t STATUS = 1;
static const uint32_t BLOCK_SIZE = 4 * 1024;
static const uint32_t MAXLINE = READ_OR_WRITE_FLAG + UID + BLOCK_SIZE;

/******************************************************************************/

namespace ilrd
{

Response::Response(uint32_t size_)
    : m_packet(), m_size(size_)
{}

void Response::SetActionType(char actionType_)
{
    *m_packet.GetCPtr() = actionType_;
}

void Response::SetUID(uint64_t uid_)
{
    *(reinterpret_cast<size_t *>(m_packet.GetCPtr() + READ_OR_WRITE_FLAG)) = uid_;
}

void Response::SetStatus(char status_)
{
    *(reinterpret_cast<size_t *>(m_packet.GetCPtr() + READ_OR_WRITE_FLAG + UID)) = status_;
}

void Response::SetData(const char *data_)
{
    memcpy(m_packet.GetCPtr() + READ_OR_WRITE_FLAG + UID + STATUS, data_, BLOCK_SIZE);
}

Packet Response::GetPacket()
{
    return m_packet;
}

void Response::SetSize(uint32_t size_)
{
    m_size = size_;
}

uint32_t Response::GetSize()
{
    return m_size;
}


}//namespace ilrd
