/******************************************************************************/
/* author: 		Mirit Hadar											  	      */
/* Reviewer: 					       										  */
/* version: 	Final			  		                                      */
/* Last update: 07-10-2019					                                  */
/******************************************************************************/

#ifndef ILRD_RD6768_PACKET
#define ILRD_RD6768_PACKET

#if __cplusplus < 201103L
#define nullptr NULL
#define noexcept throw()
#endif

#include <stdint.h>		// uint32_t

namespace ilrd
{
	
const uint32_t PACKET_SIZE = 4113;

class Packet
{
public:
    //Constructors
    explicit Packet();
    Packet(const char *other_);
    Packet(const Packet &other_);
    //~Packet() noexcept = default;
    
	//Operators
	//Packet &operator=(const Packet &other_) = default;

    //Functions
    char *GetCPtr();

private:
    //Member variables
    char m_cArray[PACKET_SIZE];
};

}//namespace ilrd

#endif  //ILRD_RD6768_PACKET
