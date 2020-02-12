/******************************************************************************/
/* author: 		Mirit Hadar											  	      */
/* Reviewer: 					       										  */
/* version: 	Final			  		                                      */
/* Last update: 07-10-2019					                                  */
/******************************************************************************/

#ifndef ILRD_RD6768_REQUEST
#define ILRD_RD6768_REQUEST

#if __cplusplus < 201103L
#define nullptr NULL
#define noexcept throw()
#endif

#include "packet.hpp"	// Packet header, uint64_t

namespace ilrd
{

class Request
{
public:
    //Constructors
    explicit Request();
    explicit Request(Packet packet_);
    //Request(const Request &other_) = default;
    //~Request() = default;
    
    //member functions
    char GetActionType();
    uint64_t GetUID();
    uint64_t GetIndex();
    char * GetData();
    Packet &GetPacket();

private:
    //Member variables
    Packet m_packet;
};

}//namespace ilrd

#endif  //ILRD_RD6768_REQUEST


