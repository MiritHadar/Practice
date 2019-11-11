/*
********************************************************************************

Developer : Mirit Hadar
Reviewer :
Last Update : 
Status :

********************************************************************************
*/

#include "read_action.hpp" 

namespace ilrd
{

Response ReadAction::Do(Storage& storage_, Request request_)
{
    Response response;
    response.SetActType(request_.GetActType());
    response.SetUid(request_.GetUid());
    
    char status = 1;
    uint64_t index = request_.GetIndex();
    
    response.SetStatus(status);
    
    unsigned char buffer[BUFF_SIZE] = {0};
    storage_.Read(buffer, index);
    response.SetData(buffer);
    response.SetSize(4106);

    return response;
}

SharedPtr<Action> ReadAction::Create()
{
    SharedPtr<Action> ptrToReadAct(new ReadAction);

    return ptrToReadAct;
}


} // extern "C"

extern "C"
{

ilrd::SharedPtr<ilrd::Action> CreateReadAction()
{
    ilrd::SharedPtr<ilrd::Action> ptr(new ilrd::ReadAction);

    return ptr;
}

} // namespace ilrd




