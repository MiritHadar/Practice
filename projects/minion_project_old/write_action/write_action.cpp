/*
********************************************************************************

Developer : Mirit Hadar
Reviewer :
Last Update : 
Status :

********************************************************************************
*/

#include "write_action.hpp"

namespace ilrd
{

/* SharedPtr<Action> WriteAction::Create()
{
    SharedPtr<Action> prtToWriteAction (new WriteAction);
    
    return prtToWriteAction;
} */

Response WriteAction::Do(Storage& storage_, Request request_)
{
    LoggerMT *log = LoggerST::GetInstance();
    Response response;
    response.SetActType(request_.GetActType());
    response.SetUid(request_.GetUid());

    char status = 1;
    uint64_t index = request_.GetIndex();
    storage_.Write(request_.GetDataBlock(), index);
    response.SetStatus(status);
    response.SetSize(10); //TO DO

    return response;
}

} // namespace ilrd

extern "C" 
{
	ilrd::SharedPtr<ilrd::Action> Create()
	{
		ilrd::SharedPtr<ilrd::Action> ptr(new ilrd::WriteAction);

		return ptr;
	}
}





