/*
********************************************************************************

Developer : Mirit Hadar
Reviewer :
Last Update : 
Status :

********************************************************************************
*/

#ifndef __OL67_read_action
#define __OL67_read_action

#include "action.hpp"
#include "storage.hpp"
#include "shared_ptr.hpp"
#include "request.hpp"
#include "response.hpp"

extern "C"
{
    ilrd::SharedPtr<ilrd::Action> CreateReadAction();
}

namespace ilrd
{

#if __cplusplus < 201103L
    #define nullptr NULL
    #define noexcept throw()
#endif



class ReadAction : public Action
{
public:
    // explicit ReadAction() = default;
    // ReadAction(const ReadAction other_) = default;
    // ~ReadAction() = default;
    Response Do(Storage &storage_, Request request_);
    static SharedPtr<Action> Create();

    static const size_t READ_RESPONSE_SIZE = 1024 + 10;

private:

};

} // namespace ilrd

#endif /* __OL67_read_action */


