/*
********************************************************************************

Developer : Mirit Hadar
Reviewer :
Last Update : 
Status :

********************************************************************************
*/

#ifndef ILRD_RD6768_SERVER
#define ILRD_RD6768_SERVER

#include <iostream>	
#include <stdint.h>          //uint32
#include <netdb.h>          //struct addrinfo
#include <cstdlib>

#include "logging.hpp"

/* #if __cplusplus < 201103L
#define nullptr NULL
#define noexcept throw()
#endif */

extern ilrd::Logger MyLogger;
extern ilrd::Logger::Severity loggerSeverity;
// int RunServer(size_t udpPort);

namespace ilrd
{

class UDPServer
{
public:
    UDPServer(uint32_t port = 1234);
    ~UDPServer();

    //member functions
    void Send(const char *msg_, uint32_t msgSize_);
    void Receive(char *msg_, uint32_t msgSize_);
    int GetFd() const;

private:
    size_t m_port;
    int m_socketFd;
    sockaddr_in m_serverAddr;
    sockaddr_in m_clientAddr;
    socklen_t m_LenClientAddr;
};

}//namespace ilrd


#endif  /*ILRD_RD6768_SERVER*/
