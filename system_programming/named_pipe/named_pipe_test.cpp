/*
********************************************************************************

Developer : Mirit Hadar
Reviewer :
Last Update : 
Status :

********************************************************************************
*/
#include <iostream>
#include <stdio.h> 
#include <string.h> 
#include <fcntl.h> 
#include <sys/stat.h> 
#include <sys/types.h> 
#include <unistd.h> 
#include <stdlib.h>		//exit

const char* CHILD_WRITE_TO_ME = "child.txt";
const char* PARENT_WRITE_TO_ME = "parent.txt";
const size_t MSGSIZE = 5; 
const char* pingMsg = "ping "; 
const char* pongMsg = "pong ";

int main() 
{ 
    mkfifo(CHILD_WRITE_TO_ME, 0666);
    mkfifo(PARENT_WRITE_TO_ME, 0666);

	int childHandler;
	int parentHandler;

	char BufForReadingPong[MSGSIZE] = {0};
	char BufForReadingPing[MSGSIZE] = {0};

	pid_t pid = fork();
	if (pid < 0)
	{
		perror("fork failed");
		exit(1);
	}

	while (1)
	{
		if (0 == pid)	//child
		{
			childHandler = open(CHILD_WRITE_TO_ME, O_WRONLY);
			write(childHandler, pingMsg, MSGSIZE);
			close(childHandler);

			childHandler = open(PARENT_WRITE_TO_ME, O_RDONLY);
			read(childHandler, BufForReadingPong, MSGSIZE);
			write(STDOUT_FILENO, BufForReadingPong, MSGSIZE);

			//std::cout << BufForReadingPong << " ";
			close(childHandler);
			sleep(1);
		}
		else	//parent
		{
			parentHandler = open(CHILD_WRITE_TO_ME, O_RDONLY);
			read(parentHandler, BufForReadingPing, MSGSIZE);
			write(STDOUT_FILENO, BufForReadingPing, MSGSIZE);

			//std::cout << BufForReadingPing << " ";
			close(parentHandler);

			parentHandler = open(PARENT_WRITE_TO_ME, O_WRONLY);
			write(parentHandler, pongMsg, MSGSIZE);
			close(parentHandler);
		}
	}

    return 0; 
} 
