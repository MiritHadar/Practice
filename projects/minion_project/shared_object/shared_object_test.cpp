/******************************************************************************/
/* author: 		Mirit Hadar											  	  */
/* Reviewer: 					       										  */
/* version: 	Draft			  		                                      */
/* Last update: 31-10-2019					                                  */
/******************************************************************************/

#include <iostream>				//	cout 	

#include "shared_object.hpp"	//	Header file		
#include "shared_ptr.hpp"
#include "action.hpp"

using namespace ilrd;

/*************************Test functions***************************************/

/******************************************************************************/

int main()
{
	SharedObject sharedObject("../read_action/read_action.so");

	SharedPtr<Action> (*Create)(void) = sharedObject.Load<SharedPtr<Action> (*)(void)>("Create");

 	Create();

	SharedObject sharedObject2("../write_action/write_action.so");

	SharedPtr<Action> (*Create2)(void) = sharedObject2.Load<SharedPtr<Action> (*)(void)>("Create");

 	Create2();

	return 0;
}

