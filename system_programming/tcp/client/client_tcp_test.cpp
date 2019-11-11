
/*
********************************************************************************

Developer : Mirit Hadar
Reviewer :
Last Update : 
Status :

********************************************************************************
*/

#include <cstdlib>           //exit, atoi
#include <cstdio>             //perror 
#include "client_tcp.hpp"

int main(int argc, char *argv[])
{
    int port = 2345;            //default port
    size_t numOfSends = 10;     //default num of loops for chating
    if (argc > 1)
    {
        port = atoi(argv[1]);
    }
    if (argc > 2)
    {
        numOfSends = atoi(argv[2]);
    }

    RunTCPClient(port, numOfSends);

    return 0;
}