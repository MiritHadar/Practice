/******************************************************************************/
/* author: 		Mirit Hadar											  	      */
/* Reviewer: 					       										  */
/* version: 	Final			  		                                      */
/* Last update: 06-11-2019					                                  */
/******************************************************************************/

#ifndef ILRD_RD6768_MASTER_PROXY
#define ILRD_RD6768_MASTER_PROXY

#if __cplusplus < 201103L
#define nullptr NULL
#define noexcept throw()
#endif

#include "request.hpp"			//	Request header
#include "response.hpp"			//	Response header
#include "server.hpp"			//	server API
#include "uncopyable.hpp"		// 	For inaccessible CCtor and assign operator

namespace ilrd
{

class MasterProxy : private Uncopyable
{
public:
    //Constructors
    explicit MasterProxy(uint32_t port_);
    //~MasterProxy() noexcept = default;

    //Operators

    //Functions
    Request ProduceRequest();
    void Respond(Response& response_);
    int GetFD();

private:
    //Member variables
	UDPServer m_server;
};

}//namespace ilrd

#endif  //ILRD_RD6768_MASTER_PROXY
