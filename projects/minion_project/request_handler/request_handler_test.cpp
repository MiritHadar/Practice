/******************************************************************************/
/* author: 		Mirit Hadar											  	      */
/* Reviewer: 					       										  */
/* version: 	Final			  		                                      */
/* Last update: 27-10-2019					                                  */
/******************************************************************************/

#include <iostream>					//	cout 
#include <cstring>					//	memcpy
#include <dlfcn.h>					//	dlsym, dlopen, dlclose

#include "request_handler.hpp"		//	Header file		

using namespace std;
using namespace ilrd;

static const uint32_t READ_OR_WRITE_FLAG = 1;
static const uint32_t UID = 8;
static const uint32_t INDEX = 8;
static const uint32_t STATUS = 1;
static const uint32_t BLOCK_SIZE = 4 * 1024;
static const uint32_t MAXLINE = READ_OR_WRITE_FLAG + UID + BLOCK_SIZE;
void *readHandler = nullptr;
void *writeHandler = nullptr;

void TeachFactory(Factory<char, Action> &factory_);
void TestWriteRequest(RequestHandler &requestHandler, Storage &storage);
void CreateWriteRequest(Request &writeRequest);
void TestReadRequest(RequestHandler &requestHandler, Storage &storage);
void CreateReadRequest(Request &readRequest);

typedef SharedPtr<Action> (*Create_CType)(void);

/******************************************************************************/

int main()
{
	Factory<char, Action> factory;
	TeachFactory(factory);

	Storage storage;
	RequestHandler requestHandler(storage, factory);

	TestWriteRequest(requestHandler, storage);
	TestReadRequest(requestHandler, storage);

	dlclose(readHandler);
	dlclose(writeHandler);

	return 0;
}

void TeachFactory(Factory<char, Action> &factory_)
{
	readHandler = dlopen("../read_action/read_action.so", RTLD_LAZY);

	if(NULL == readHandler)
	{
		throw std::logic_error(std::string("ilrd:ERROR in dlopen"));
	}

	SharedPtr<Action> (*CreateRead)(void); 
	CreateRead = reinterpret_cast<Create_CType>(dlsym(readHandler, 															"Create"));
	if (NULL == CreateRead)
	{
		throw std::logic_error(std::string("ilrd:ERROR in dlsym"));
	}

	factory_.Learn(0, CreateRead);

	writeHandler = dlopen("../write_action/write_action.so", RTLD_LAZY);

	if(NULL == writeHandler)
	{
		throw std::logic_error(std::string("ilrd:ERROR in dlopen"));
	}

	SharedPtr<Action> (*CreateWrite)(void); 
	CreateWrite = reinterpret_cast<Create_CType>(dlsym(writeHandler, 														"Create"));
	if (NULL == CreateWrite)
	{
		throw std::logic_error(std::string("ilrd:ERROR in dlsym"));
	}

	factory_.Learn(1, CreateWrite);
}

void TestWriteRequest(RequestHandler &requestHandler, Storage &storage)
{
	Request writeRequest;	
	CreateWriteRequest(writeRequest);

	Response response = requestHandler.HandlerRequest(writeRequest);

	char *packetCptr = response.GetPacket().GetCPtr();
	char array[4200] = {0};
	
	if (1 != *packetCptr)
	{
		cout << "ERROR in line " << __LINE__ << endl;
	}

	if (0x1234567890ABCDEF != *(reinterpret_cast<uint64_t*>(packetCptr + 1)))
	{
		cout << "ERROR in line " << __LINE__ << endl;
	}

	if (1 != *(packetCptr + 9))
	{
		cout << "ERROR in line " << __LINE__ << endl;
	}

	uint64_t index = 0x1FFFF;
	storage.Read(array, index);

	for (size_t i = 0; i < BLOCK_SIZE; ++i)
	{
		if ('b' != array[i])
		{
			cout << "ERROR in line " << __LINE__ << endl;
		}	
	}
}

void CreateWriteRequest(Request &writeRequest)
{
	char *packetCptr = writeRequest.GetPacket().GetCPtr();

	char type = 1;
	*packetCptr = type;
	if (1 != writeRequest.GetActionType())
	{
		cout << "ERROR in line " << __LINE__ << endl;
	}

	uint64_t uid = 0x1234567890ABCDEF;
	*(reinterpret_cast<uint64_t*>(packetCptr + 1)) = uid;

	if (uid != writeRequest.GetUID())
	{
		cout << "ERROR in line " << __LINE__ << endl;
	}

	uint64_t index = 0x1FFFF;
	*(reinterpret_cast<uint64_t*>(packetCptr + 9)) = index;
	if (index != writeRequest.GetIndex())
	{
		cout << "ERROR in line " << __LINE__ << endl;
	}

	memset(packetCptr + 17, 'b', BLOCK_SIZE);
}

void TestReadRequest(RequestHandler &requestHandler, Storage &storage)
{
	Request readRequest;	
	CreateReadRequest(readRequest);

	Response response = requestHandler.HandlerRequest(readRequest);

	char *packetCptr = response.GetPacket().GetCPtr();

	if (0 != *packetCptr)
	{
		cout << "ERROR in line " << __LINE__ << endl;
	}

	if (0x1234567890ABCDEF != *(reinterpret_cast<uint64_t*>(packetCptr + 1)))
	{
		cout << "ERROR in line " << __LINE__ << endl;
	}

	if (1 != *(packetCptr + 9))
	{
		cout << "ERROR in line " << __LINE__ << endl;
	}

	for (size_t i = 0; i < BLOCK_SIZE; ++i)
	{
		if ('b' != *(response.GetPacket().GetCPtr() + READ_OR_WRITE_FLAG + UID + STATUS + i))
		{
			cout << "ERROR in line " << __LINE__ << endl;
		}	
	}
}

void CreateReadRequest(Request &readRequest)
{
	char *packetCptr = readRequest.GetPacket().GetCPtr();
	
	char type = 0;
	*packetCptr = type;
	if (0 != readRequest.GetActionType())
	{
		cout << "ERROR in line " << __LINE__ << endl;
	}
	
	uint64_t uid = 0x1234567890ABCDEF;
	*(reinterpret_cast<uint64_t*>(packetCptr + 1)) = uid;

	if (uid != readRequest.GetUID())
	{
		cout << "ERROR in line " << __LINE__ << endl;
	}

	uint64_t index = 0x1FFFF;
	*(reinterpret_cast<uint64_t*>(packetCptr + 9)) = index;
	if (index != readRequest.GetIndex())
	{
		cout << "ERROR in line " << __LINE__ << endl;
	}
}


