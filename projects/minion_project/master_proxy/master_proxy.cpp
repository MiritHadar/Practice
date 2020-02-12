/******************************************************************************/
/* author: 		Mirit Hadar											  	      */
/* Reviewer: 					       										  */
/* version: 	Final			  		                                      */
/* Last update: 06-11-2019					                                  */
/******************************************************************************/

#include "master_proxy.hpp"		//	Header file	

/*************************Helper functions*************************************/

/******************************************************************************/

namespace ilrd
{

MasterProxy::MasterProxy(uint32_t port_)
    : m_server(port_)
{
    ;
}

Request MasterProxy::ProduceRequest()
{
    Request request;

    m_server.Receive(request.GetData(), PACKET_SIZE);

    return request;
}

void MasterProxy::Respond(Response &response_)
{
	m_server.Send(response_.GetPacket().GetCPtr, PACKET_SIZE);
}

int MasterProxy::GetFD()
{
	m_server.GetSocketFD();
}

}//namespace ilrd
