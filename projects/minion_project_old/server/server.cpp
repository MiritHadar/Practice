/*
********************************************************************************

Developer : Mirit Hadar
Reviewer :
Last Update : 
Status :

********************************************************************************
*/
#include <unistd.h>       // close
#include <string>       
#include "server_udp.hpp"
#include "server.hpp"

using namespace std;
using namespace ilrd;

UDPServer::UDPServer(uint32_t port)
    : m_port(port),
      m_socketFd(socket(AF_INET, SOCK_DGRAM, 0)),
      m_LenClientAddr(sizeof(sockaddr_in))
{
    if (-1 == m_socketFd)
    {
        throw string("creating socket failed");
    }

    m_serverAddr.sin_family = AF_INET;
    m_serverAddr.sin_addr.s_addr = INADDR_ANY;
    m_serverAddr.sin_port = htons(port);

    if (-1 == bind(m_socketFd,
                   reinterpret_cast<sockaddr*>(&m_serverAddr),
                   sizeof(sockaddr_in)))
    {
        throw string("binding failed");
    }
}

UDPServer::~UDPServer()
{
    close(m_socketFd);
}

void UDPServer::Send(const char *msg_, uint32_t msgSize_)
{
    if (-1 == sendto(m_socketFd,
                     msg_,
                     msgSize_,
                     MSG_CONFIRM,
                     reinterpret_cast<const sockaddr*>(&m_clientAddr),
                     m_LenClientAddr))
    {
        throw string("sendto failed");
    }
}

void UDPServer::Receive(char *msg_, uint32_t msgSize_)
{
    if (-1 == recvfrom(m_socketFd,
                       msg_,
                       msgSize_,
                       MSG_WAITALL,
                       reinterpret_cast<sockaddr*>(&m_clientAddr),
                       &m_LenClientAddr))
    {
        throw string ("failed recvfrom");
    }
}

int UDPServer::GetFd() const
{
    return m_socketFd;
}


