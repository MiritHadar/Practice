/*
********************************************************************************

Developer : Mirit Hadar
Reviewer :
Last Update : 
Status :

********************************************************************************
*/

#include <iostream>
#include <dlfcn.h> 		//dlopen, dlsym, dlclose
//#include "loggerST.hpp"
#include "loggerMT.hpp"

using namespace ilrd;
using namespace std;

typedef LoggerMT (*Creator)();

void FirstTest();
void *TestSharedObject();

struct InstanseLogError : public std::runtime_error
{
	public:
		explicit InstanseLogError(std::string what_);
};

InstanseLogError::InstanseLogError(std::string what_)
	: runtime_error(what_)
{
	;
}

int main()
{
	FirstTest();
	dlclose(TestSharedObject());

	return 0;
}

void FirstTest()
{
	// LoggerMT *logMt = LoggerST::GetInstance();
	// if (nullptr == logMt)
	// {
	// 	throw InstanseLogError("failed to get logger");
	// }
	// LoggerMT *dummyLog = LoggerST::GetInstance();
	// if (logMt != dummyLog)
	// {
	// 	throw InstanseLogError("failed to create no more then one logger");
	// }
}

void *TestSharedObject()
{
	void *handler = dlopen("./loggerST.so", RTLD_LAZY);

	if (nullptr == handler)
	{
		throw std::runtime_error(std::string("dlopen failed"));
	}

	Creator ptrFunc;
	ptrFunc = reinterpret_cast<Creator>(dlsym(handler, "GetSOInstance"));

	if (nullptr == ptrFunc)
	{
		throw std::runtime_error(std::string("dlsym failed"));
	}

	Creator ptrDummy;
	ptrDummy = reinterpret_cast<Creator>(dlsym(handler, "GetSOInstance"));

	if (ptrFunc != ptrDummy)
	{
		throw std::runtime_error(std::string("failed to limit instances to one"));
	}

	return handler;
}
