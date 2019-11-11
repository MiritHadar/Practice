/******************************************************************************/
/* author: 		Ori Michaeli											  	  */
/* Reviewer: 					       										  */
/* version: 	Draft			  		                                      */
/* Last update: 07-10-2019					                                  */
/******************************************************************************/

#include "write_action.hpp"			//	Header file	
#include "loggerMT.hpp"				//	LoggerMT
#include "loggerMT_singleton.hpp"

static const uint32_t READ_OR_WRITE_FLAG = 1;
static const uint32_t UID = 8;
static const uint32_t BLOCK_INDEX = 8;
static const uint32_t BLOCK_SIZE = 4 * 1024;
static const uint32_t STATUS = 1;
static const uint32_t MAXLINE = READ_OR_WRITE_FLAG + UID + 
								BLOCK_INDEX + BLOCK_SIZE;

/******************************************************************************/

namespace ilrd
{

Response WriteAction::Do(Storage &storage_, Request request_)
{
	LoggerMT *logger = GetSOInstance();
    logger->Log(ilrd::LoggerMT::ERROR, "WriteAction Do function");
    Response response;
    response.SetActionType(request_.GetActionType());
    response.SetUID(request_.GetUID());

    char status = 1;
    uint64_t index = request_.GetIndex();
/*     if (index > storage_.GetMaxSize())
    {
        response.SetStatus(0); 
        response.SetSize(READ_OR_WRITE_FLAG + UID + STATUS);

        // index = storage_.GetMaxSize();
        // status = 0;
   
        return response;
    } */

    storage_.Write(request_.GetData(), index);
    response.SetStatus(status);
    response.SetSize(READ_OR_WRITE_FLAG + UID + STATUS);

    return response;
}

}//namespace ilrd

extern "C" 
{
	ilrd::SharedPtr<ilrd::Action> Create()
	{
		ilrd::SharedPtr<ilrd::Action> ptr(new ilrd::WriteAction);

		return ptr;
	}

	char GetActionType()
	{
		return 1;
	}
}