/******************************************************************************/
/* author: 		Ori Michaeli											  	  */
/* Reviewer: 					       										  */
/* version: 	Draft			  		                                      */
/* Last update: 06-10-2019					                                  */
/******************************************************************************/

#include <cerrno>
#include <pthread.h>
#include <signal.h>			// pthread_kill
#include <cstdio>
#include <iostream>
#include <cstring>          //memcpy
#include <stdlib.h>         //exit 
#include <unistd.h>         //sleep
#include <stdint.h>
#include "loggerMT.hpp"
#include "loggerMT_singleton.hpp"

#include "server.hpp"	//	Header file	

/*************************Helper functions*************************************/

/******************************************************************************/

using namespace std;
using namespace ilrd;

static const uint32_t READ_OR_WRITE_FLAG = 1;
static const uint32_t UID = 8;
static const uint32_t BLOCK_INDEX = 8;
static const uint32_t BLOCK_SIZE = 4 * 1024;
static const uint32_t EXTRA_SPACE = 10;
static const uint32_t MAXLINE = READ_OR_WRITE_FLAG + UID + BLOCK_INDEX + BLOCK_SIZE + EXTRA_SPACE;

/**************************************************************************************************/

namespace ilrd
{
static LoggerMT *logger = GetSOInstance();

UDPServer::UDPServer(uint32_t port_)
    :   m_port(port_), 
        m_socketFD(socket(AF_INET, SOCK_DGRAM, 0)), 
        m_serverAddrSize(sizeof(m_serverAddr)),
        m_clientAddrSize(sizeof(m_clientAddr))
{
	logger->SetOutputSeverity(LoggerMT::SDEBUG);
	
    if (-1 == m_socketFD)
    {
        logger->Log(LoggerMT::ERROR, "socket creation failed\n");
        logger->Log(LoggerMT::ERROR, strerror(errno)); 

        throw SocketFDCreationException("failure in socket FD creation");
    }

    logger->Log(LoggerMT::SDEBUG, "UDP-Socket successfully created \n");

    m_serverAddr.sin_family    = AF_INET; // IPv4 
    m_serverAddr.sin_addr.s_addr = INADDR_ANY; 
    m_serverAddr.sin_port = htons(m_port);

    if (-1 == bind(
                    m_socketFD, 
                    reinterpret_cast<const sockaddr *>(&m_serverAddr), 
                    m_serverAddrSize
                  )) 
    {
        logger->Log(LoggerMT::ERROR, "socket bind failed\n");
        logger->Log(LoggerMT::ERROR, strerror(errno)); 

        throw BindException("failure in UDP bind");
    }

    logger->Log(LoggerMT::SDEBUG, "Socket bind created\n");
}

UDPServer::~UDPServer()
{
    close(m_socketFD);
}

void UDPServer::Send(const char *msg_, uint32_t msgSize_)
{
    int status = sendto(
                        m_socketFD, 
                        msg_, 
                        msgSize_, 
                        MSG_CONFIRM, 
                        reinterpret_cast<const sockaddr *>(&m_clientAddr), 
                        m_clientAddrSize
                       );

    if(-1 == status)
    {
        logger->Log(LoggerMT::ERROR, "Send failed\n");      
        logger->Log(LoggerMT::ERROR, strerror(errno));

        throw SendException("failure in UDP send");
    }
}

void UDPServer::Receive(char *msg_, uint32_t msgSize_)
{
    int status = recvfrom(
                            m_socketFD, 
                            msg_, 
                            msgSize_, 
                            MSG_WAITALL, 
                            reinterpret_cast<sockaddr *>(&m_clientAddr), 
                            &m_clientAddrSize
                         );

    if(-1 == status)
    {
        logger->Log(LoggerMT::ERROR, "Recieve failed\n");      
        logger->Log(LoggerMT::ERROR, strerror(errno));

        throw ReceiveException("failure in UDP Recieve");
    }

    // else if (0 == status) 
    // {
    //     logger.Log(Logger::ERROR, "client left\n");      
        
    //     throw exception("client left");
    // }
}

uint32_t UDPServer::GetPort() const
{
	return m_port;
}

int UDPServer::GetSocketFD()
{
    return m_socketFD;
}

}//namespace ilrd


