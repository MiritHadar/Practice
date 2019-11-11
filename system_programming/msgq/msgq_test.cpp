/*
********************************************************************************

Developer : Mirit Hadar
Reviewer :
Last Update : 
Status :

********************************************************************************
*/

#include <stdio.h>
#include <iostream>
#include <fstream>		//open, close, remove
#include <sys/ipc.h> 
#include <sys/msg.h> 
#include <unistd.h>		//fork

struct msgInfo
{
	long msgType;
	char msgText[8];
};

const char* fileName = "file_msgQ";

int main(int argc, char** argv)
{
	msgInfo msg = {1, "ping "};
	
	//writing
	if (argc == 1)
	{	
		//std::ofstream msgHnadler;
		//msgHnadler.open(fileName);
		key_t key = ftok(fileName, 65); 
	
		int msgid = msgget(key, 0666 | IPC_CREAT);
		msgsnd(msgid, &msg, 8, 0);
		msgsnd(msgid, &msg, 8, 0); 
		msgsnd(msgid, &msg, 8, 0);
		
		//msgHnadler.close();
	}
	//reading
	else if (argc == 2)
	{
		key_t key = ftok(fileName, 65); 
		int msgid = msgget(key, 0666 | IPC_CREAT); 
		std::cout << msgrcv(msgid, &msg, 8, 0, 0) << std::endl; 
		std::cout << msg.msgText << std::endl; 
	}
	//killing
	else
	{
		key_t key = ftok(fileName, 65); 
		int msgid = msgget(key, 0666 | IPC_CREAT);
		msgctl(msgid, IPC_RMID, NULL); 
		remove(fileName);
	}
	
	
	return 0;
}

