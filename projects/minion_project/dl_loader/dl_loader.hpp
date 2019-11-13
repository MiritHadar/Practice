/******************************************************************************/
/* author: 		Mirit Hadar											  	  */
/* Reviewer: 					       										  */
/* version: 	Draft			  		                                      */
/* Last update: 31-10-2019					                                  */
/******************************************************************************/

#ifndef ILRD_RD6768_DL_LOADER
#define ILRD_RD6768_DL_LOADER

#if __cplusplus < 201103L
#define nullptr NULL
#define noexcept throw()
#endif

#include <string>				// 	string
#include <map>					//	map

#include "uncopyable.hpp"		//	For inaccessible CCtor and assign operator
#include "shared_object.hpp"	//	SharedObject header
#include "shared_ptr.hpp"		//	SharedPointer

namespace ilrd
{

class DlLoader : private Uncopyable
{
public:
    //Constructors
    //explicit DlLoader() = default;
    //~DlLoader() noexcept = default;

    //Operators

    //Functions
    SharedPtr<SharedObject> Open(const std::string &path_);

private:
    //Member variables
	std::map<std::string, SharedPtr<SharedObject> > m_sharedObjects;
};

}//namespace ilrd

#endif  //ILRD_RD6768_DL_LOADER
