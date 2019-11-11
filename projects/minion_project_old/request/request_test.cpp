/*
********************************************************************************

Developer : Mirit Hadar
Reviewer :
Last Update : 
Status :

********************************************************************************
*/

#include <iostream>
#include "request.hpp"

using namespace std;
using namespace ilrd;

void RequestTest();

int main()
{
	RequestTest();

	return 0;
}


void RequestTest()
{
    unsigned char buff[BUFF_SIZE] = "this is my request";
    Packet packet(buff);
    Request request(packet);

    cout << request.GetPacket().GetBuffer() << endl;
    cout << request.GetActType() << endl;
}

