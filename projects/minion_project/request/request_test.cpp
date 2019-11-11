/******************************************************************************/
/* author: 		Ori Michaeli											  	  */
/* Reviewer: 					       										  */
/* version: 	Draft			  		                                      */
/* Last update: 07-10-2019					                                  */
/******************************************************************************/

#include <iostream>			//	cout 	
#include <cstring>			//	memcpy

#include "request.hpp"		//	Header file		

using namespace ilrd;
using namespace std;

int main()
{
	char data[4200] = {0};

	memset(data, 1, 1);
	
	if (1 != data[0])
	{
		cout << "ERROR in line " << __LINE__ << endl;
	}

	memset(data + 1, 1, 1);

	if (1 != *reinterpret_cast<size_t*>(&data[1]))
	{
		cout << "ERROR in line " << __LINE__ << endl;
	}

	memset(data + 9, 2, 1);

	if (2 != *reinterpret_cast<size_t*>(&data[9]))
	{
		cout << "ERROR in line " << __LINE__ << endl;
	}

	memset(data + 17, 3, 1);

	if (2 != *reinterpret_cast<size_t*>(&data[9]))
	{
		cout << "ERROR in line " << __LINE__ << endl;
	}

	Packet packet(data);
	Request request(packet);

	if (1 != request.GetUID())
	{
		cout << "ERROR in line " << __LINE__ << endl;
	}

	if (2 != request.GetIndex())
	{
		cout << "ERROR in line " << __LINE__ << endl;
	}

	if (3 != *request.GetData())
	{
		cout << "ERROR in line " << __LINE__ << endl;
	}

	return 0;
}
