/******************************************************************************/
/* author: 		Ori Michaeli											  	  */
/* Reviewer: 					       										  */
/* version: 	Draft			  		                                      */
/* Last update: 07-10-2019					                                  */
/******************************************************************************/

#ifndef ILRD_RD6768_RESPONSE
#define ILRD_RD6768_RESPONSE

#if __cplusplus < 201103L
#define nullptr NULL
#define noexcept throw()
#endif

#include "packet.hpp"	// Packet header, uint32_t, uint64_t

namespace ilrd
{

class Response
{
public:
    //Constructors
    explicit Response(uint32_t size_ = 0);
    // Response(const Response &other_) = default;
    // ~Response() = default;

    //member functions
    void SetActionType(char actionType_);
    void SetUID(uint64_t uid_);
    void SetStatus(char status_);
    void SetData(const char *data_);
    Packet GetPacket();
    void SetSize(uint32_t size_);
    uint32_t GetSize();

private:
    //Member variables
    Packet m_packet;
    uint32_t m_size;
};

}//namespace ilrd

#endif  //ILRD_RD6768_RESPONSE
