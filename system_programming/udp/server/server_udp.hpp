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
#include "logging.hpp"

#ifndef __OL67_server
#define __OL67_server

namespace ilrd
{
    extern ilrd::Logger myLogger;
    void RunUdpServer(int port);
}

#endif /* __OL67_server */


