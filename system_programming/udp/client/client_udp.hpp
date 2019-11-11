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

#ifndef __OL67_client
#define __OL67_client

namespace ilrd
{

void RunUDPClient(int port, size_t numOfSends);
int CreateSocket();
void InitSocket(sockaddr_in& servaddr, int port);
void ConnectToClient(int sockfd, sockaddr_in& servaddr);
void ChatWithServer(int sockfd, size_t numOfSends, sockaddr_in& servaddr);

} // namespace ilrd

#endif /* __OL67_client */


