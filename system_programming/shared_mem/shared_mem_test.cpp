/*
********************************************************************************

Developer : Mirit Hadar
Reviewer :
Last Update : 
Status :

********************************************************************************
*/

#include <iostream>		// I/O
#include <sys/types.h>	//pid_t
#include <unistd.h>		//fork
#include <sys/types.h>	//ftok
#include <sys/wait.h>	//wait
#include <sys/ipc.h>
#include <sys/shm.h>
#include <cstring>
//#include <cstdio>

static void WriteMsg(int shmid);
static void Read1(int shmid);
static void Read2(int shmid);
static void Read3(int shmid);

const char* FILE_NAME = "shmaFileName";
const char* pingMsg = "ping ";
const char* pongMsg = "pong ";

int main(void)
{
	key_t key = ftok(FILE_NAME, 66);
	int shmid = shmget(key, 4096, 0666 | IPC_CREAT);

	WriteMsg(shmid);
	wait(NULL);

	pid_t pid1 = fork();
	if (0 == pid1)
	{
		Read1(shmid);
		return 0;
	}

	pid_t pid2 = fork();
	if (0 == pid2)
	{
		Read2(shmid);
		return 0;
	}

	pid_t pid3 = fork();
	if (0 == pid3)
	{
		Read3(shmid);
		return 0;
	}

	return 0;
}

static void WriteMsg(int shmid)
{
	//1
	char *msg = (char*)shmat(shmid, NULL, 0);
	memcpy(msg, "Ping ", 6);
	shmdt(msg);
	//2
	msg = (char*)shmat(shmid, NULL, 0);
	memcpy(msg + 6, "Pong ", 6);
	shmdt(msg);
	//3
	msg = (char*)shmat(shmid, NULL, 0);
	memcpy(msg + 12, "Done ", 6);
	shmdt(msg);
}

static void Read1(int shmid)
{
	char *receiver = (char*)shmat(shmid, NULL, 0);
	std::cout << "Read1: " << receiver << std::endl;
	shmdt(receiver);
}

static void Read2(int shmid)
{
	char *receiver = (char*)shmat(shmid, NULL, 0);
	std::cout << "Read2: " << receiver + 6 << std::endl;
	shmdt(receiver);
}

static void Read3(int shmid)
{
	char *receiver = (char*)shmat(shmid, NULL, 0);
	std::cout << "Read3: " << receiver + 12 << std::endl;
	shmdt(receiver);
}