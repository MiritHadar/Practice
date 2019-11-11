/*
********************************************************************************

Developer : Mirit Hadar
Reviewer :
Last Update : 
Status :

********************************************************************************
*/

#include "server_tcp.hpp"

//port number sent as argument
int main(int argc, char* argv[])
{
    int port = 1234;
    if (argc > 1)
    {
        port = atoi(argv[1]);
    }

    RunTcpServer(port);

    return EXIT_SUCCESS;
}
