/******************************************************************************/
/* author: 		Mirit Hadar											  	  */
/* Reviewer: 					       										  */
/* version: 	Draft			  		                                      */
/* Last update: 31-10-2019					                                  */
/******************************************************************************/

#include "shared_object.hpp"		//	Header file	
#include "loggerST.hpp"	//	logger


/*************************Helper functions*************************************/

/******************************************************************************/

namespace ilrd
{

static LoggerMT *logger = GetSOInstance();

static void* Open(const std::string &path_)
{
	sleep(1);
    void* handle = dlopen(path_.c_str(), RTLD_NOW); 

    if(nullptr == handle)
	{
		logger->Log(ilrd::LoggerMT::ERROR, "dlopen failed!");
		std::cout << dlerror() << std::endl;
		throw new DLOpenException("dlopen failed!");
	} 

    return handle; 
}

SharedObject::SharedObject(const std::string &path_)
    : m_handle(Open(path_))
{
	logger->Log(LoggerMT::INFO, "dlopen succeeded");
}

SharedObject::~SharedObject() noexcept
{
    //dlclose(m_handle);
}

}//namespace ilrd
