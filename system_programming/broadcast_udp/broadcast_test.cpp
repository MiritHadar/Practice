
/*
********************************************************************************

Developer : Mirit Hadar
Reviewer :
Last Update : 
Status :

********************************************************************************
*/

#include "broadcast.hpp"

//host name sent as argument
int main(int argc, char *argv[])
{
	char *ip = 0;
	if (argc > 1)
	{
		ip = argv[1];
	}
	else
	{
		perror("no host name recieved");
		exit (EXIT_FAILURE);
	}

    RunClientBroadcast(ip);

	return EXIT_SUCCESS;
}