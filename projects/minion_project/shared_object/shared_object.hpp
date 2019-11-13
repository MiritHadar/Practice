/******************************************************************************/
/* author: 		Mirit Hadar											  	  */
/* Reviewer: 					       										  */
/* version: 	Draft			  		                                      */
/* Last update: 31-10-2019					                                  */
/******************************************************************************/

#ifndef ILRD_RD6768_SHARED_OBJECT
#define ILRD_RD6768_SHARED_OBJECT


#if __cplusplus < 201103L
#define nullptr NULL
#define noexcept throw()
#endif

#include <string>				 //	string
#include <dlfcn.h>				 //	dlsym, dlopen, dlclose

#include "uncopyable.hpp"		 //	For inaccessible CCtor and assign operator
#include "project_exceptions.hpp"//	exceptions

namespace ilrd
{

class SharedObject : private Uncopyable
{
public:
    //Constructors
    explicit SharedObject(const std::string &path_);
    ~SharedObject() noexcept;

    //Operators

    //Functions
    template <typename T>
	T Load(const std::string &symbol_);

private:
    //Member variables
	void *m_handle;
};

template <typename T>
T SharedObject::Load(const std::string &symbol_)
{
	T ptr = reinterpret_cast<T >(dlsym(m_handle, symbol_.c_str()));
	if (nullptr == ptr)
	{
		throw new DLSymException("dlsym failed!");
	}

	return ptr;
}

}//namespace ilrd

#endif  //ILRD_RD6768_SHARED_OBJECT
