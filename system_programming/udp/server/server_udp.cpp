/*
********************************************************************************

Developer : Mirit Hadar
Reviewer :
Last Update : 
Status :

********************************************************************************
*/

#include "server_udp.hpp"

namespace ilrd
{

const size_t MAX = 11;
char msgUdpToClient[MAX] = "pong ";

static int CreateSocket();
static void InitSocket(sockaddr_in& servaddr, int port);
static void BindToClient(int sockfd, sockaddr_in& servaddr);
static void ChatWithClient(int sockfd);

using namespace std;

void RunUdpServer(int port)
{
	int sockfd = CreateSocket();
	struct sockaddr_in servaddr = {0};
	InitSocket(servaddr, port);
    BindToClient(sockfd, servaddr);
    ChatWithClient(sockfd);
}

static int CreateSocket()
{
	int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	if (-1 == sockfd)
	{
		//myLogger.Log(Logger::ERROR, "server failed socket");
		exit(EXIT_FAILURE);
	}

    return sockfd;
}

static void InitSocket(sockaddr_in& servaddr, int port)
{
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(port);
	servaddr.sin_addr.s_addr = INADDR_ANY;
}

static void BindToClient(int sockfd, sockaddr_in& servaddr)
{
	if (-1 == bind(sockfd, reinterpret_cast<const struct sockaddr*>(&servaddr),
																sizeof(servaddr)))
	{
		perror("server failed bind");
		exit(EXIT_FAILURE);
	}
}

static void ChatWithClient(int sockfd)
{
	char buff[MAX] = {0};
	struct sockaddr_in clientAdrr = {0};
	socklen_t addrLen = sizeof(clientAdrr);

	while(1)
	{
		int numOfBytesRcv = recvfrom(sockfd, buff, MAX, MSG_WAITALL,
								reinterpret_cast<sockaddr*>(&clientAdrr), &addrLen);
		if (-1 == numOfBytesRcv)
		{
			perror("server failed recvfrom");
			exit(EXIT_FAILURE);
		}
		buff[numOfBytesRcv] = '\0'; 
		cout << buff << endl;
		strncpy(msgUdpToClient + 5, buff + 5, 6);
		sleep(1);
		int send_status = sendto(sockfd, msgUdpToClient, strlen(msgUdpToClient), MSG_CONFIRM,
									reinterpret_cast<sockaddr*>(&clientAdrr), addrLen);
		if (-1 == send_status)
		{
			perror("server failed sending");
			exit(EXIT_FAILURE);
		}
		sleep(1);
	}
}

} //namespace ilrd

