/******************************************************************************/
/* author: 		Mirit Hadar											  	      */
/* Reviewer: 					       										  */
/* version: 	Final			  		                                      */
/* Last update: 07-10-2019					                                  */
/******************************************************************************/

#include <iostream>					//	cout
#include <cstring>					//	memset
#include <dlfcn.h>					//	dlsym, dlopen, dlclose
#include "shared_ptr.hpp"
#include "action.hpp"

// #include "read_action.hpp"			//	Header file

using namespace ilrd;
using namespace std;

static const uint32_t READ_OR_WRITE_FLAG = 1;
static const uint32_t UID = 8;
static const uint32_t INDEX = 8;
static const uint32_t STATUS = 1;
static const uint32_t BLOCK_SIZE = 4 * 1024;
static const uint32_t MAXLINE = READ_OR_WRITE_FLAG + UID + BLOCK_SIZE;

typedef SharedPtr<Action> (*Create_CType)(void);

/******************************************************************************/

void FirstTest();
void* SecondTest();

int main()
{
	//FirstTest();
	dlclose(SecondTest());

	return 0;
}

// void FirstTest()
// {
// 	Storage storage;
// 	char array1[4200] = {0};
// 	char array2[4200] = {0};

// 	memset(array1, 'a', 4200);

// 	for (size_t i = 0; i < BLOCK_SIZE; ++i)
// 	{
// 		if ('a' != array1[i])
// 		{
// 			cout << "ERROR in line " << __LINE__ << endl;
// 		}	
// 	}
	
// 	storage.Write(array1, 0x1FFFF);
// 	storage.Read(array2, 0x1FFFF);
	
// 	for (size_t i = 0; i < BLOCK_SIZE; ++i)
// 	{
// 		if (array1[i] != array2[i])
// 		{
// 			cout << "ERROR in line " << __LINE__ << endl;
// 		}	
// 	}

// 	Request request;

// 	char *packetCptr = request.GetPacket().GetCPtr();
	
// 	char type = 0;
// 	*packetCptr = type;
// 	if (0 != request.GetActionType())
// 	{
// 		cout << "ERROR in line " << __LINE__ << endl;
// 	}
	
// 	uint64_t uid = 0x1234567890ABCDEF;
// 	*(reinterpret_cast<uint64_t*>(packetCptr + 1)) = uid;

// 	if (uid != request.GetUID())
// 	{
// 		cout << "ERROR in line " << __LINE__ << endl;
// 	}

// 	uint64_t index = 0x1FFFF;
// 	*(reinterpret_cast<uint64_t*>(packetCptr + 9)) = index;
// 	if (index != request.GetIndex())
// 	{
// 		cout << "ERROR in line " << __LINE__ << endl;
// 	}

// 	ReadAction readAction;
// 	Response response = readAction.Do(storage, request);

// 	packetCptr = response.GetPacket().GetCPtr();

// 	if (0 != *packetCptr)
// 	{
// 		cout << "ERROR in line " << __LINE__ << endl;
// 	}

// 	if (0x1234567890ABCDEF != *(reinterpret_cast<uint64_t*>(packetCptr + 1)))
// 	{
// 		cout << "ERROR in line " << __LINE__ << endl;
// 	}

// 	if (1 != *(packetCptr + 9))
// 	{
// 		cout << "ERROR in line " << __LINE__ << endl;
// 	}

// 	for (size_t i = 0; i < BLOCK_SIZE; ++i)
// 	{
// 		if ('a' != *(response.GetPacket().GetCPtr() + READ_OR_WRITE_FLAG + UID + STATUS + i))
// 		{
// 			cout << "ERROR in line " << __LINE__ << endl;
// 		}	
// 	}
// }

void* SecondTest()
{
	void *handle = NULL;

	SharedPtr<Action> ptr;

	SharedPtr<Action> (*Create)(void); 

	handle = dlopen("./read_action.so", RTLD_LAZY);

	if(NULL == handle)
	{
		throw std::logic_error(std::string("ilrd:ERROR in dlopen"));
	}

	Create = reinterpret_cast<Create_CType>(dlsym(handle, "Create"));

	if (NULL == Create)
	{
		throw std::logic_error(std::string("ilrd:ERROR in dlsym"));
	}

	ptr = Create();

	Storage storage;
	char array1[4200] = {0};
	char array2[4200] = {0};

	memset(array1, 'a', 4200);

	for (size_t i = 0; i < BLOCK_SIZE; ++i)
	{
		if ('a' != array1[i])
		{
			cout << "ERROR in line " << __LINE__ << endl;
		}	
	}
	
	storage.Write(array1, 0x1FFFF);
	storage.Read(array2, 0x1FFFF);
	
	for (size_t i = 0; i < BLOCK_SIZE; ++i)
	{
		if (array1[i] != array2[i])
		{
			cout << "ERROR in line " << __LINE__ << endl;
		}	
	}

	Request request;
	char *packetCptr = request.GetPacket().GetCPtr();
	
	char type = 0;
	*packetCptr = type;
	if (0 != request.GetActionType())
	{
		cout << "ERROR in line " << __LINE__ << endl;
	}
	
	uint64_t uid = 0x1234567890ABCDEF;
	*(reinterpret_cast<uint64_t*>(packetCptr + 1)) = uid;

	if (uid != request.GetUID())
	{
		cout << "ERROR in line " << __LINE__ << endl;
	}

	uint64_t index = 0x1FFFF;
	*(reinterpret_cast<uint64_t*>(packetCptr + 9)) = index;
	if (index != request.GetIndex())
	{
		cout << "ERROR in line " << __LINE__ << endl;
	}

	Response response = ptr->Do(storage, request);

	packetCptr = response.GetPacket().GetCPtr();

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
		if ('a' != *(response.GetPacket().GetCPtr() + READ_OR_WRITE_FLAG + UID + STATUS + i))
		{
			cout << "ERROR in line " << __LINE__ << endl;
		}	
	}

	return handle;
}
