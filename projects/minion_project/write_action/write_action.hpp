/******************************************************************************/
/* author: 		Mirit Hadar											  	      */
/* Reviewer: 					       										  */
/* version: 	Final			  		                                      */
/* Last update: 07-10-2019					                                  */
/******************************************************************************/

#ifndef ILRD_RD6768_WRITE_ACTION
#define ILRD_RD6768_WRITE_ACTION

#if __cplusplus < 201103L
#define nullptr NULL
#define noexcept throw()
#endif

#include "action.hpp"
#include "request.hpp"
#include "response.hpp"
#include "storage.hpp"
#include "shared_ptr.hpp"

extern "C"
{
	ilrd::SharedPtr<ilrd::Action> Create();
	char GetActionType();
}

namespace ilrd
{

class WriteAction : public Action
{
public:
    //Constructors
    // explicit WriteAction() = default;
    // WriteAction(const WriteAction &other_) = default;
    // ~WriteAction() = default;
    
    //member function
    Response Do(Storage &storage_, Request request_);

private:
    //Member variables

};

}//namespace ilrd

#endif  //ILRD_RD6768_WRITE_ACTION
