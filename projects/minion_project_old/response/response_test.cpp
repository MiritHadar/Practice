/*
********************************************************************************

Developer : Mirit Hadar
Reviewer :
Last Update : 
Status :

********************************************************************************
*/

#include <iostream>
#include <cstdlib>		//atoi

#include "response.hpp"

using namespace ilrd;
using namespace std;

void BasicTest();
void SetTest();

int main()
{
	BasicTest();
	SetTest();

	return 0;
}

void BasicTest()
{
	/* unsigned char buff[] = "this is a response";
	Packet packet(buff);
	Response response(50);
	response = buff;
	cout << response.GetPacket().GetBuffer() << endl; */
}

void SetTest()
{
	Response response;
	//response.SetActType(1);
	unsigned char dataForResponse[] = "this is the answer";
	response.SetData(dataForResponse);
	//response.SetStatus(0);
	cout << response.GetPacket().GetBuffer() << endl;
}



