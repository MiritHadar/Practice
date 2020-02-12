/******************************************************************************/
/* author: 		Mirit Hadar											  	      */
/* Reviewer: 					       										  */
/* version: 	Final			  		                                      */
/* Last update: 06-10-2019					                                  */
/******************************************************************************/

#ifndef ILRD_RD6768_SERVER
#define ILRD_RD6768_SERVER

#if __cplusplus < 201103L
#define nullptr NULL
#define noexcept throw()
#endif

#include <iostream>
#include <stdint.h>          //uint32
#include <netdb.h>          //struct addrinfo
#include <cstdlib>

namespace ilrd
{

class UDPServer
{
public:
    UDPServer(uint32_t port_ = 1234);
    ~UDPServer();

    //member functions
    void Send(const char *msg_, uint32_t msgSize_);
    void Receive(char *msg_, uint32_t msgSize_);
	uint32_t GetPort() const;
    int GetSocketFD();

private:
    uint32_t m_port;
    int m_socketFD;
    socklen_t m_serverAddrSize;
    socklen_t m_clientAddrSize;
    sockaddr_in m_serverAddr;
    sockaddr_in m_clientAddr;
};

class SocketFDCreationException : public std::runtime_error
{
public:
	explicit SocketFDCreationException(const std::string &s_ = "")
        : runtime_error(s_ )
    {

    }

private:
};

class BindException : public std::runtime_error
{
public:
	explicit BindException(const std::string &s_ = "")
        : runtime_error(s_ )
    {

    }

private:
};

class SendException : public std::runtime_error
{
public:
	explicit SendException(const std::string &s_ = "")
        : runtime_error(s_ )
    {

    }

private:
};

class ReceiveException : public std::runtime_error
{
public:
	explicit ReceiveException(const std::string &s_ = "")
        : runtime_error(s_ )
    {

    }

private:
};

}//namespace ilrd



#endif  //ILRD_RD6768_SERVER
