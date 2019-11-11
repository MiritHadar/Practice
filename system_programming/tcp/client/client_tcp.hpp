
/*
********************************************************************************

Developer : Mirit Hadar
Reviewer :
Last Update : 
Status :

********************************************************************************
*/

#include <cstdlib>            //exit, atoi
#include <netdb.h>            //sockaddr_in
#include <cstdio>             //perror 
#include <iostream>           //cout
#include <unistd.h>           //write
#include <string.h>           //strncmp
#include <arpa/inet.h>        //inet_addr
#include <cstddef>      //size_t

#ifndef __OL67_TCP_CLIENT
#define __OL67_TCP_CLIENT

#if __cplusplus < 201103L
    #define nullptr (NULL)
#endif

void RunTCPClient(int port, size_t numOfSends);
int CreateSocket();
void InitSocket(sockaddr_in& servaddr, int port);
void ConnectToServer(int sockfd, sockaddr_in& servaddr);
void ChatWithServer(int sockfd, size_t numOfSends);

#endif // __OL67_TCP_CLIENT
