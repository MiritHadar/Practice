/*
********************************************************************************

Developer : Mirit Hadar
Reviewer :
Last Update : 
Status :

********************************************************************************
*/

#include "client_udp.hpp"
using namespace std;

namespace ilrd
{

const size_t MAX = 11;
char msgToServer[MAX] = "ping ";

void RunUDPClient(int port, size_t numOfSends)
{
	int sockfd = CreateSocket();
	sockaddr_in servaddr = {0};
	InitSocket(servaddr, port);
    ChatWithServer(sockfd, numOfSends, servaddr);
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

void InitSocket(sockaddr_in& servaddr, int port)
{
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(port);
	servaddr.sin_addr.s_addr = INADDR_ANY;
}

void ChatWithServer(int sockfd, size_t numOfSends, sockaddr_in& servaddr)
{
	char buff[MAX] = {0};
	char myPid[6] = {0};
	sprintf(myPid, "%d", getpid());
	strcat(msgToServer, myPid);
	
	while(numOfSends > 0)
	{
		int send_status = sendto(sockfd, msgToServer, strlen(msgToServer), MSG_CONFIRM,
						reinterpret_cast<const sockaddr*>(&servaddr), sizeof(servaddr));
		if (-1 == send_status)
		{
			perror("client failed sending");
			exit(EXIT_FAILURE);
		}

		socklen_t addrlen = 0;
		int numOfBytesRcv = recvfrom(sockfd, buff, MAX, MSG_WAITALL,
										reinterpret_cast<sockaddr*>(&servaddr), &addrlen);
		if (-1 == numOfBytesRcv)
		{
			perror("client failed sending");
			exit(EXIT_FAILURE);
		}

		buff[numOfBytesRcv] = '\0';
		cout << buff << endl;
		--numOfSends;
	}

	close(sockfd);
}

} // namespace ilrd
