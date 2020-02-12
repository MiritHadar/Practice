/******************************************************************************/
/* author: 		Mirit Hadar											  	      */
/* Reviewer: 					       										  */
/* version: 	Final			  		                                      */
/* Last update: 07-10-2019					                                  */
/******************************************************************************/

#include <cstring>			//	memcpy

#include "packet.hpp"		//	Header file

static const uint32_t READ_OR_WRITE_FLAG = 1;
static const uint32_t UID = 8;
static const uint32_t INDEX = 8;
static const uint32_t STATUS = 1;
static const uint32_t BLOCK_SIZE = 4 * 1024;
static const uint32_t MAXLINE = READ_OR_WRITE_FLAG + UID + INDEX + BLOCK_SIZE;

/******************************************************************************/

namespace ilrd
{

Packet::Packet()
    : m_cArray()
{}

Packet::Packet(const char *other_)
{
    memcpy(m_cArray, other_, MAXLINE);
}

Packet::Packet(const Packet &other_)
{
    memcpy(m_cArray, other_.m_cArray, MAXLINE);
}

char *Packet::GetCPtr()
{
    return m_cArray;
}

}//namespace ilrd

