/*
********************************************************************************

Developer : Mirit Hadar
Reviewer :
Last Update : 
Status :

********************************************************************************
*/

#include "server_udp.hpp"

using namespace ilrd;

//port number sent as argument
int main(int argc, char *argv[])
{
	uint16_t port = 1234;
	if (argc > 1)
	{
		port = atoi(argv[1]);
	}

	RunUdpServer(port);

	return EXIT_SUCCESS;
}


