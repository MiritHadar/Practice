
/*
********************************************************************************

Developer : Mirit Hadar
Reviewer :
Last Update : 
Status :

********************************************************************************
*/

#include <cstdlib> 			//exit
#include <unistd.h>			//close
#include <cstring>			//strlen 
#include <iostream>			//cout
#include <arpa/inet.h>		//htons
#include <cstdio>			//perror   
#include <netinet/in.h>		//socket

const size_t MAX = 1024;
const char* msgToClient = "pong";
const uint16_t PORT = 2222;

using namespace std;

int CreateSocket();
void InitSocket(sockaddr_in& servaddr);
void BindToClient(int sockfd, sockaddr_in& servaddr);
void ChatWithClient(int sockfd);

int main(void)
{
	sockaddr_in servaddr = {0};

	int sockfd = CreateSocket();
	InitSocket(servaddr);
	BindToClient(sockfd, servaddr);
    ChatWithClient(sockfd);

	return EXIT_SUCCESS;
}


int CreateSocket()
{
	int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	if (-1 == sockfd)
	{
		perror("server failed socket");
		exit(EXIT_FAILURE);
	}

	return sockfd;
}

void InitSocket(sockaddr_in& servaddr)
{
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(PORT);
	servaddr.sin_addr.s_addr = INADDR_ANY;
}

void BindToClient(int sockfd, sockaddr_in& servaddr)
{
	if (-1 == bind(sockfd, (const struct sockaddr*)&servaddr, sizeof(servaddr)))
	{
		perror("server failed bind");
		exit(EXIT_FAILURE);
	}
}

void ChatWithClient(int sockfd)
{
	char buff[MAX] = {0};
	sockaddr_in clientAdrr = {0};
	socklen_t addrLen = sizeof(clientAdrr);

	while(1)
	{
		int numOfBytesRcv = recvfrom(sockfd, buff, MAX, MSG_WAITALL,
											(struct sockaddr*)&clientAdrr, &addrLen);

		if (-1 == numOfBytesRcv)
		{
			perror("server failed recvfrom");
			exit(EXIT_FAILURE);
		}
		buff[numOfBytesRcv] = '\0'; 
		cout << buff << endl;
		int send_status = sendto(sockfd, msgToClient, strlen(msgToClient), MSG_CONFIRM,
													(struct sockaddr*)&clientAdrr, addrLen);
		if (-1 == send_status)
		{
			perror("server failed sending");
			exit(EXIT_FAILURE);
		}
	}
}
