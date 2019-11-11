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
#include <netdb.h>			//gethostbyname
#include "logging.hpp"

#ifndef __OL67_BROADCAST
#define __OL67_BROADCAST

void RunClientBroadcast(char *ip);
int CreateSocket();
void EnableBroadcast(int sockfd, sockaddr_in& servaddr, char* ip);
void ConnectToClient(int sockfd, sockaddr_in& servaddr);
void ChatWithServer(int sockfd, sockaddr_in& servaddr);

#endif /* __OL67_BROADCAST */

