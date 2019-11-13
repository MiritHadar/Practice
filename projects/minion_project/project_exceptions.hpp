/******************************************************************************/
/* author: 		Mirit Hadar											  	  */
/* Reviewer: 					       										  */
/* version: 	Draft			  		                                      */
/* Last update: 29-09-2019					                                  */
/******************************************************************************/

#ifndef ILRD_RD6768_PROJECT_EXCEPTIONS
#define ILRD_RD6768_PROJECT_EXCEPTIONS

#if __cplusplus < 201103L
#define nullptr NULL
#define noexcept throw()
#endif

#include <stdexcept>		// 	runtime_error
#include <dlfcn.h>			//	dlerror
#include <cerrno>			//	errno
#include <cstring>			//	strerror

namespace ilrd
{

class DLOpenException : public std::runtime_error
{
public:
	explicit DLOpenException(const std::string &errorString_ = "")
        : runtime_error(errorString_ + dlerror())
    {

    }

private:
};

class DLSymException : public std::runtime_error
{
public:
	explicit DLSymException(const std::string &errorString_ = "")
        : runtime_error(errorString_ + dlerror())
    {

    }

private:
};

/******************************************************************************/
class InotifyInitException : public std::runtime_error
{
public:
	explicit InotifyInitException(const std::string &errorString_ = "")
		: runtime_error(errorString_ + strerror(errno))
	{
		;
	}
};

class ReadException : public std::runtime_error
{
public:
	explicit ReadException(const std::string &errorString_ = "")
		: runtime_error(errorString_ + strerror(errno))
	{
		;
	}
};

}//namespace ilrd

#endif  //ILRD_RD6768_PROJECT_EXCEPTIONS	