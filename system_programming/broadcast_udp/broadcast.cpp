/*
********************************************************************************

Developer : Mirit Hadar
Reviewer :
Last Update : 
Status :

********************************************************************************
*/

#include "broadcast.hpp"

const size_t MAX = 10;
const char* msgToServer = "ping";
const uint16_t PORT = 2222;

using namespace std;

void RunClientBroadcast(char *ip)
{
	int sockfd = CreateSocket();
	sockaddr_in servaddr = {0};
	EnableBroadcast(sockfd, servaddr, ip);
	ChatWithServer(sockfd, servaddr);
}


int CreateSocket()
{
	int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	if (-1 == sockfd)
	{
		perror("client failed socket");
		exit(EXIT_FAILURE);
	}

	return sockfd;
}

void EnableBroadcast(int sockfd, sockaddr_in& servaddr, char* ip)
{
	int broadcastOption = 1;
	hostent *hostData = gethostbyname(ip);
	if (NULL == hostData)
	{
		perror("client: failed get host by name");
		exit(EXIT_FAILURE);
	}

	if (-1 == setsockopt(sockfd, SOL_SOCKET, SO_BROADCAST, &broadcastOption,
															sizeof(broadcastOption)))
	{
		perror("client: failed setsockopt");
		exit(EXIT_FAILURE);
	}

	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(PORT);
	servaddr.sin_addr = *((in_addr*)hostData->h_addr);
	bzero(&(servaddr.sin_zero), sizeof(servaddr.sin_zero));
}

void ChatWithServer(int sockfd, sockaddr_in& servaddr)
{
	socklen_t addrlen = sizeof(sockaddr);
	char buff[MAX] = {0};

	while(1)
	{
		int send_status = sendto(sockfd, msgToServer, strlen(msgToServer),
								MSG_CONFIRM, reinterpret_cast<const sockaddr*>(&servaddr), sizeof(servaddr));
		if (-1 == send_status)
		{
			perror("client failed sending");
			exit(EXIT_FAILURE);
		}

		//socklen_t addrlen = 0;
		int numOfBytesRcv = recvfrom(sockfd, buff, MAX, MSG_WAITALL,
										reinterpret_cast<sockaddr*>(&servaddr), &addrlen);
		if (-1 == numOfBytesRcv)
		{
			perror("client failed sending");
			exit(EXIT_FAILURE);
		}

		buff[numOfBytesRcv] = '\0';
		cout << buff << endl;
		sleep(1);
	}

	close(sockfd);
}