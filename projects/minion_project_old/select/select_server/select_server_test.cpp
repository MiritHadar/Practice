/*
********************************************************************************

Developer : Mirit Hadar
Reviewer :
Last Update : 
Status :

********************************************************************************
*/

#include <cstdlib>              // system
#include <unistd.h>             // sleep  
#include "select_server.hpp"    // Server
#include "thread.hpp"           // Thread

using namespace ilrd;

int main()
{
    SelectServer server(1234, 2222, 3333, 60);
    server.Start();
    
    return 0;
}
