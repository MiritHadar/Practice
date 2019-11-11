/*
********************************************************************************

Developer : Mirit Hadar
Reviewer :
Last Update : 
Status :

********************************************************************************
*/

#ifndef __OL67_request_handler
#define __OL67_request_handler


#include <iostream>	
#include "storage.hpp"
#include "uncopyable.hpp"
#include "factory.hpp"
#include "action.hpp"
#include "read_action.hpp"
#include "write_action.hpp"
#include "request.hpp"
#include "response.hpp"
#include "packet.hpp"
#include "shared_ptr.hpp"

#if __cplusplus < 201103L
#define nullptr NULL
#define noexcept throw()
#endif

namespace ilrd
{

class RequestHandler
{
public:
    explicit RequestHandler(Storage &storage_, Factory<char, Action> &factory_);
    // RequestHandler(const RequestHandler &other_) = default;
    //~RequestHandler() = default;

    Response Handle(Request request_);

private:
    Storage &m_storage;
    Factory<char, Action> &m_factory; 
};

}//namespace ilrd

#endif /* __OL67_request_handler */


