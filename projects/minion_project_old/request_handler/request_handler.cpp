/*
********************************************************************************

Developer : Mirit Hadar
Reviewer :
Last Update : 
Status :

********************************************************************************
*/

#include "request_handler.hpp"

namespace ilrd
{

RequestHandler::RequestHandler(Storage &storage_, Factory<char, Action> &factory_)
    : m_storage(storage_),
      m_factory(factory_)
{
    ;
}

Response RequestHandler::Handle(Request request_)
{
    char key = request_.GetActType();
    SharedPtr<Action> ptrToAct = m_factory.Create(key);
    Response responseToReturn = ptrToAct->Do(m_storage, request_);
    
    return responseToReturn;
}

} // namespace ilrd



