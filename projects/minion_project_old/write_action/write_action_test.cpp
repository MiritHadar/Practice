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
#include "packet.hpp"
//#include "write_action.hpp"
#include "shared_ptr.hpp"
#include "action.hpp"
#include "uncopyable.hpp"

using namespace std;
using namespace ilrd;

void BasicTest();
void *DlTest();

typedef SharedPtr<Action> (*Creator)();

int main()
{
	BasicTest();
	dlclose(DlTest());

	return 0;
}

void BasicTest()
{	
	// Storage storage;
	// unsigned char array1[BUFF_SIZE] = {0};
	// unsigned char array2[BUFF_SIZE] = {0};
	// unsigned char array3[BUFF_SIZE] = {0};

	// memset(reinterpret_cast<void*>(array1), 'a', BUFF_SIZE);

	// for (size_t i = 0; i < BUFF_SIZE; ++i)
	// {
	// 	if ('a' != array1[i])
	// 	{
	// 		cout << "ERROR in line " << __LINE__ << endl;
	// 	}	
	// }
	
	// storage.Write(array1, 0x1FFFF);
	// storage.Read(array2, 0x1FFFF);

	// for (size_t i = 0; i < DATA_BLOCK_SIZE; ++i)
	// {
	// 	if (array1[i] != array2[i])
	// 	{
	// 		cout << "ERROR in line " << __LINE__ << endl;
	// 	}	
	// }

	// Request request;
	// unsigned char *packetCptr = request.GetPacket().GetBuffer();

	// char type = 1;
	// *packetCptr = type;
	// cout << request.GetActType() << endl;
	// if (1 != request.GetActType())
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

	// memset(packetCptr + 17, 'b', DATA_BLOCK_SIZE);

	// WriteAction writeaction;
	// Response response = writeaction.Do(storage, request);

	// packetCptr = response.GetPacket().GetBuffer();
	
	// if (1 != *packetCptr)
	// {
	// 	cout << "kkkk ERROR in line " << __LINE__ << endl;
	// }

	// if (0x1234567890ABCDEF != *(reinterpret_cast<uint64_t*>(packetCptr + 1)))
	// {
	// 	cout << "ccccc ERROR in line " << __LINE__ << endl;
	// }

	// cout << *(packetCptr + 9) << endl;
	
	// if (1 != *(packetCptr + 9))
	// {
	// 	cout << "dddd ERROR in line " << __LINE__ << endl;
	// }

	// storage.Read(array3, index);

	// for (size_t i = 0; i < DATA_BLOCK_SIZE; ++i)
	// {
	// 	if ('b' != array3[i])
	// 	{
	// 		//cout << "ERROR in line " << __LINE__ << endl;
	// 	}	
	// }
}

void *DlTest()
{
	void *handler = dlopen("./write_action.so", RTLD_LAZY);

	if (nullptr == handler)
	{
		throw std::runtime_error(std::string("dlopen failed"));
	}

	Creator ptrFunc;
	
	ptrFunc = reinterpret_cast<Creator>(dlsym(handler, "Create"));

	if (nullptr == ptrFunc)
	{
		throw std::runtime_error(std::string("dlsym failed"));
	}

	cout << "dlTest done" << endl;

	return handler;
}


