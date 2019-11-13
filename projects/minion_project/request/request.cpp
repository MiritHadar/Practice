/******************************************************************************/
/* author: 		Mirit Hadar											  	  */
/* Reviewer: 					       										  */
/* version: 	Draft			  		                                      */
/* Last update: 07-10-2019					                                  */
/******************************************************************************/

#include "request.hpp"		//	Header file	

/*************************Helper functions*************************************/

/******************************************************************************/

namespace ilrd
{

Request::Request()
{
	;
}

Request::Request(Packet packet_)
    : m_packet(packet_)
{}

char Request::GetActionType()
{
    return *m_packet.GetCPtr();
}

uint64_t Request::GetUID()
{
    return *reinterpret_cast<uint64_t*>(m_packet.GetCPtr() + 1);
}

uint64_t Request::GetIndex()
{
    return *reinterpret_cast<uint64_t*>(m_packet.GetCPtr() + 9); 
}

char *Request::GetData()
{
    return &m_packet.GetCPtr()[17]; 
}

Packet &Request::GetPacket()
{
    return m_packet;
}

}//namespace ilrd
