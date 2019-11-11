/*
********************************************************************************

Developer : Mirit Hadar
Reviewer :
Last Update : 
Status :

********************************************************************************
*/

#include <iostream> 
#include <unistd.h>
#include <stdlib.h>		//exit

const size_t MSGSIZE = 5; 
const char* pingMsg = "ping"; 
const char* pongMsg = "pong"; 
  
int main() 
{
	int pingPipe[2] = {0};
	int pongPipe[2] = {0};

	if ((pipe(pingPipe) < 0) || (pipe(pongPipe) < 0))
	{
		perror("error in pipe command");

		exit(1);
	}
	char buffer[MSGSIZE];
	pid_t pid = fork();
	if (pid < 0)
	{
		exit(2);
	}

	while (1)
	{
		if (0 == pid)	//child
		{
			sleep(1);
			write(pingPipe[1], pingMsg, MSGSIZE);
			read(pongPipe[0], buffer, MSGSIZE);

			std::cout << buffer << std::endl;
		}
		else			//parent
		{	
			sleep(1);
			write(pongPipe[1], pongMsg, MSGSIZE);
			read(pingPipe[0], buffer, MSGSIZE);
			
			std::cout << buffer << std::endl;
		}
	}
	
    return 0; 
} 
