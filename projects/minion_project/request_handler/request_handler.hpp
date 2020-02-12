/******************************************************************************/
/* author: 		Mirit Hadar											  	      */
/* Reviewer: 					       										  */
/* version: 	Final			  		                                      */
/* Last update: 27-10-2019					                                  */
/******************************************************************************/

#ifndef ILRD_RD6768_REQUEST_HANDLER
#define ILRD_RD6768_REQUEST_HANDLER

#if __cplusplus < 201103L
#define nullptr NULL
#define noexcept throw()
#endif

#include "storage.hpp"
#include "uncopyable.hpp"
#include "factory.hpp"
#include "action.hpp"
#include "request.hpp"
#include "response.hpp"
#include "packet.hpp"

namespace ilrd
{

class RequestHandler
{
public:
    //Constructors
    explicit RequestHandler(Storage &storage_, Factory<char, Action> &factory_);
    // RequestHandler(const RequestHandler &other_) = default;
    //~RequestHandler() = default;

    //member function
    Response HandlerRequest(Request request_);

private:
    //Member variables
    Storage &m_storage;
    Factory<char, Action> &m_factory; 
};

}//namespace ilrd

#endif  //ILRD_RD6768_REQUEST_HANDLER
