/******************************************************************************/
/* author: 		Mirit Hadar											  	      */
/* Reviewer: 					       										  */
/* version: 	Final			  		                                      */
/* Last update: 06-10-2019					                                  */
/******************************************************************************/

#include <iostream>			//	cout 	
#include <cstdlib>			//	atoi
#include <cstring>			//	memcpy

#include "server.hpp"		//	Header file		

using namespace ilrd;

void FirstTest(size_t udpPort);

int main(int argc, const char *argv[])
{
    size_t udpPort;

    switch (argc)
    {
        case 2:
        {
            udpPort = atoi(argv[1]);
            break;
        } 
       
        default:
        {   
            udpPort = 1234;
            break;
        }
    }

    FirstTest(udpPort);

	return 0;
}

void FirstTest(size_t udpPort)
{
    UDPServer server(udpPort);

    char pong[] = {'p', 'o', 'n', 'g', '\0'};
    char msg[10] = {'\0'};

    while(true)
    {
        server.Receive(msg, 10);

        std::cout << msg << std::endl;
        memcpy(msg, pong, 4);

        server.Send(msg, 10);
    }
}

