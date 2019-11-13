/******************************************************************************/
/* author: 		Mirit Hadar											  	  */
/* Reviewer: 					       										  */
/* version: 	Draft			  		                                      */
/* Last update: 07-10-2019					                                  */
/******************************************************************************/

#include <dlfcn.h>				//	dlsym, dlopen, dlclose

#include "read_action.hpp"		//	Header file	
#include "loggerMT.hpp"			//	LoggerMT
#include "loggerST.hpp"

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

Response ReadAction::Do(Storage &storage_, Request request_)
{
	LoggerMT *logger = GetSOInstance();
    logger->Log(ilrd::LoggerMT::ERROR, "ReadAction has received a packet");

    Response response;
    response.SetActionType(request_.GetActionType());
    response.SetUID(request_.GetUID());
    
    char status = 1;
    uint64_t index = request_.GetIndex();
/*     if (index > storage_.GetMaxSize())
    {
        response.SetStatus(0); 
        response.SetSize(READ_OR_WRITE_FLAG + UID + STATUS + BLOCK_SIZE);
   
        char buffer[4200] = {0};
        response.SetData(buffer);

        return response;

        // status = 0;
        // index = storage_.GetMaxSize();
    } */
    
    response.SetStatus(status);
    
    char buffer[4200] = {0};
    storage_.Read(buffer, index);
    response.SetData(buffer);
    response.SetSize(READ_OR_WRITE_FLAG + UID + BLOCK_SIZE + STATUS);

    return response;
}

}//namespace ilrd

extern "C"
{
	ilrd::SharedPtr<ilrd::Action> Create()
	{
		ilrd::SharedPtr<ilrd::Action> ptr(new ilrd::ReadAction);

		return ptr;
	}

	char GetActionType()
	{
		return 0;
	}
}