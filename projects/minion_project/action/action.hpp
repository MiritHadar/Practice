/******************************************************************************/
/* author: 		Mirit Hadar											  	      */
/* Reviewer: 					       										  */
/* version: 	Final			  		                                      */
/* Last update: 07-10-2019					                                  */
/******************************************************************************/

#ifndef ILRD_RD6768_ACTION
#define ILRD_RD6768_ACTION

#if __cplusplus < 201103L
#define nullptr NULL
#define noexcept throw()
#endif

#include "storage.hpp"
#include "request.hpp"
#include "response.hpp"

namespace ilrd
{

class Action
{
public:
    //Constructors
    virtual ~Action() = 0;
    //Action(const Action& other_) = default;
    //~Action() noexcept = default;

    //Operators
    //Action& operator=(const Action& other_) = default;

    //Functions
    virtual Response Do(Storage &storage_, Request request_) = 0;
	
private:
    //Member variables

};

}//namespace ilrd

#endif  //ILRD_RD6768_ACTION
