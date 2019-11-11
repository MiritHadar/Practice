/******************************************************************************/
/* author: 		Ori Michaeli											  	  */
/* Reviewer: 					       										  */
/* version: 	Draft			  		                                      */
/* Last update: 27-10-2019					                                  */
/******************************************************************************/

#include "request_handler.hpp"		//	Header file	

/*************************Helper functions*************************************/

/******************************************************************************/

namespace ilrd
{

RequestHandler::RequestHandler(Storage &storage_, Factory<char, Action> &factory_)
    : m_storage(storage_), m_factory(factory_)
{
	;
}

Response RequestHandler::HandlerRequest(Request request_)
{
    char key = request_.GetActionType();
    SharedPtr<Action> actionPtr = m_factory.Create(key);

    return actionPtr->Do(m_storage, request_);
}

}//namespace ilrd
