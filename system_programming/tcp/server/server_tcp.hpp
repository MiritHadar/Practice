/*
********************************************************************************

Developer : Mirit Hadar
Reviewer :
Last Update : 
Status :

********************************************************************************
*/

#include <cstdlib>            //exit
#include <netdb.h>            //sockaddr_in
#include <cstdio>             //perror 
#include <iostream>           //cout
#include <unistd.h>           //write
#include <string.h>           //strncmp
#include <sys/types.h>        //listen
#include <cstddef>            //size_t

#ifndef __OL67_server_tcp
#define __OL67_server_tcp

void RunTcpServer(int port);

#endif /* __OL67_server_tcp */


