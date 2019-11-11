/*
********************************************************************************

Developer : Mirit Hadar
Reviewer :
Last Update : 
Status :

********************************************************************************
*/

#include <iostream>
#include <dlfcn.h>		//dlopen, dlsym, dlclose
//#include "read_action.hpp"
#include "action.hpp"
#include "storage.hpp"
#include "shared_ptr.hpp"
#include "request.hpp"
#include "response.hpp"
#include "uncopyable.hpp"

using namespace std;
using namespace ilrd;

typedef SharedPtr<Action> (*Creator)();

void FirstTest();
void *DlTest();

int main()
{
	//FirstTest();
	dlclose(DlTest());

	return 0;
}

void FirstTest()
{
	// Storage storage;
	// unsigned char array1[BUFF_SIZE] = {0};
	// unsigned char array2[BUFF_SIZE] = {0};

	// memset(array1, 'a', BUFF_SIZE);

	// cout << BUFF_SIZE << endl;
	// for (size_t i = 0; i < BUFF_SIZE; ++i)
	// {
	// 	if ('a' != array1[i])
	// 	{
	// 		cout << "ERROR in line " << __LINE__ << endl;
	// 	}	
	// }
	
	// storage.Write(array1, 0x1FFFF);
	// storage.Read(array2, 0x1FFFF);
	
	// for (size_t i = 0; i < 4106; ++i)
	// {
	// 	if (array1[i] != array2[i])
	// 	{
	// 		cout << array2[i] << i << endl;
	// 	}	
	// }
 
	// Packet packet;
	// Request request(packet);

	// unsigned char *packetCptr = request.GetPacket().GetBuffer();
	
	// char type = 0;
	// *packetCptr = type;

	// if (0 != request.GetActType())
	// {
	// 	cout << "ERROR in line " << __LINE__ << endl;
	// }
	
	// uint64_t uid = 0x1234567890ABCDEF;
	// *(reinterpret_cast<uint64_t*>(packetCptr + 1)) = uid;

	// if (uid != request.GetUid())
	// {
	// 	cout << "ERROR in line " << __LINE__ << endl;
	// }

	// uint64_t index = 0x1FFFF;
	// *(reinterpret_cast<uint64_t*>(packetCptr + 9)) = index;
	// if (index != request.GetIndex())
	// {
	// 	cout << "ERROR in line " << __LINE__ << endl;
	// }

	// ReadAction readAction;
	// Response response = readAction.Do(storage, request);

	// packetCptr = response.GetPacket().GetBuffer();

	// if (0 != *packetCptr)
	// {
	// 	cout << "ERROR in line " << __LINE__ << endl;
	// }

	// if (0x1234567890ABCDEF != *(reinterpret_cast<uint64_t*>(packetCptr + 1)))
	// {
	// 	cout << "ERROR in line " << __LINE__ << endl;
	// }
}

void *DlTest()
{
	void *handler = dlopen("./read_action.so", RTLD_LAZY);
	if (nullptr == handler)
	{
		throw std::runtime_error(std::string("error in dlopen"));
	}

	Creator ptrFunc = reinterpret_cast<Creator>(dlsym(handler, "CreateReadAction"));

	if (nullptr == ptrFunc)
	{
		throw std::runtime_error(std::string("error in dlsym"));
	}

	SharedPtr<Action> ptr = ptrFunc();
	Storage storage;
	unsigned char array1[BUFF_SIZE] = {0};
	unsigned char array2[BUFF_SIZE] = {0};

	memset(array1, 'a', BUFF_SIZE);

	cout << BUFF_SIZE << endl;
	for (size_t i = 0; i < BUFF_SIZE; ++i)
	{
		if ('a' != array1[i])
		{
			cout << "ERROR in line " << __LINE__ << endl;
		}	
	}
	
	storage.Write(array1, 0x1FFFF);
	storage.Read(array2, 0x1FFFF);
	
	for (size_t i = 0; i < 4106; ++i)
	{
		if (array1[i] != array2[i])
		{
			cout << array2[i] << i << endl;
		}	
	}
 
	Packet packet;
	Request request(packet);

	unsigned char *packetCptr = request.GetPacket().GetBuffer();
	
	char type = 0;
	*packetCptr = type;

	if (0 != request.GetActType())
	{
		cout << "ERROR in line " << __LINE__ << endl;
	}
	
	uint64_t uid = 0x1234567890ABCDEF;
	*(reinterpret_cast<uint64_t*>(packetCptr + 1)) = uid;

	if (uid != request.GetUid())
	{
		cout << "ERROR in line " << __LINE__ << endl;
	}

	uint64_t index = 0x1FFFF;
	*(reinterpret_cast<uint64_t*>(packetCptr + 9)) = index;
	if (index != request.GetIndex())
	{
		cout << "ERROR in line " << __LINE__ << endl;
	}

	// ReadAction readAction;
	// Response response = readAction.Do(storage, request);

	// packetCptr = response.GetPacket().GetBuffer();

	// if (0 != *packetCptr)
	// {
	// 	cout << "ERROR in line " << __LINE__ << endl;
	// }

	// if (0x1234567890ABCDEF != *(reinterpret_cast<uint64_t*>(packetCptr + 1)))
	// {
	// 	cout << "ERROR in line " << __LINE__ << endl;
	// }

	return handler;
}
