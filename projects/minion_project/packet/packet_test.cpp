/******************************************************************************/
/* author: 		Ori Michaeli											  	  */
/* Reviewer: 					       										  */
/* version: 	Draft			  		                                      */
/* Last update: 07-10-2019					                                  */
/******************************************************************************/

#include <iostream>			//	cout 	
#include <cstring>			//	memcpy

#include "packet.hpp"		//	Header file		

using namespace ilrd;
using namespace std;

int main()
{
	char str[PACKET_SIZE];
	memset(str, 'a', PACKET_SIZE);

	Packet packet1(str);
	for (size_t i = 0; i < PACKET_SIZE; ++i)
	{
		if ('a' != packet1.GetCPtr()[i])
		{
			cout << "ERROR IN LINE " << __LINE__ << endl;
		}
	}

	Packet packet2(packet1);

	for (size_t i = 0; i < PACKET_SIZE; ++i)
	{
		if (packet1.GetCPtr()[i] != packet2.GetCPtr()[i])
		{
			cout << "ERROR IN LINE " << __LINE__ << endl;
		}
	}

	return 0;
}
