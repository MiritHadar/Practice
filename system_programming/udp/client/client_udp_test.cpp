/*
********************************************************************************

Developer : Mirit Hadar
Reviewer :
Last Update : 
Status :

********************************************************************************
*/

#include "client_udp.hpp"

using namespace ilrd;

//first argument sent is port number
//second one is num of runs wanted
int main(int argc, char *argv[])
{
	uint16_t port = 1234;
	size_t numOfSends = 3;
	if (argc > 1)
	{
		port = atoi(argv[1]);
	}
	if (argc > 2)
	{
		numOfSends = atoi(argv[2]);
	}

	RunUDPClient(port, numOfSends);

	return EXIT_SUCCESS;
}