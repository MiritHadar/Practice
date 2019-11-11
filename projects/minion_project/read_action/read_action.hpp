/******************************************************************************/
/* author: 		Ori Michaeli											  	  */
/* Reviewer: 					       										  */
/* version: 	Draft			  		                                      */
/* Last update: 07-10-2019					                                  */
/******************************************************************************/

#ifndef ILRD_RD6768_READ_ACTION
#define ILRD_RD6768_READ_ACTION

#if __cplusplus < 201103L
#define nullptr NULL
#define noexcept throw()
#endif

#include "action.hpp"
#include "request.hpp"
#include "response.hpp"
#include "storage.hpp"
#include "sharedPtr.hpp"

extern "C" 
{
	ilrd::SharedPtr<ilrd::Action> Create();
	char GetActionType();
}

namespace ilrd
{

class ReadAction : public Action
{
public:
    //Constructors
    //explicit ReadAction();
    //ReadAction(const ReadAction& other_) = default;
    //~ReadAction() noexcept = default;

    //Operators
    //ReadAction& operator=(const ReadAction& other_) = default;

    //Functions
    Response Do(Storage &storage_, Request request_);  

private:
    //Member variables

};

}//namespace ilrd

#endif  //ILRD_RD6768_READ_ACTION
