/*
********************************************************************************

Developer : Mirit Hadar
Reviewer :
Last Update : 
Status :

********************************************************************************
*/
#include "shared_ptr.hpp"
#include "action.hpp"
#include "uncopyable.hpp"

#ifndef __OL67_write_action
#define __OL67_write_action

extern "C"
{
	ilrd::SharedPtr<ilrd::Action> Create();
}

namespace ilrd
{

class WriteAction : public Action
{
public:
    //explicit WriteAction() = default
    // WriteAction(const WriteAction &other_) = default
    // ~WriteAction() = default
    static SharedPtr<Action> Create();
    Response Do(Storage& storage_, Request request_);
    static const size_t WRITE_RESPONSE_SIZE = 10;
    
private:

};

} // namespace ilrd

#endif /* __OL67_write_action */


