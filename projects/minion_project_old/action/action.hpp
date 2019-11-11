/*
********************************************************************************

Developer : Mirit Hadar
Reviewer :
Last Update : 
Status :

********************************************************************************
*/

#ifndef __OL67_Action
#define __OL67_Action

#include "storage.hpp"
#include "request.hpp"
#include "response.hpp"

namespace ilrd
{

class Action
{
public:
    //Action() = default
    //Action(const Action& other_) = default
    //Action& operator=(const Action& other_) = default
    virtual ~Action() = 0;
    virtual Response Do(Storage& storage_, Request request_) = 0;
    
private:

};

} // namespace ilrd

#endif /* __OL67_Action */


