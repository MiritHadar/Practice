/*
********************************************************************************

Developer : Mirit Hadar
Reviewer :
Last Update : 
Status :

********************************************************************************
*/

#ifndef __OL67_select_server
#define __OL67_select_server

#include <map>
#include <errno.h>
#include "fd_listener.hpp"      // FdListener
#include "uncopyable.hpp"       // Uncopyable
#include "shared_ptr.hpp"       // SharedPtr
#include "server.hpp"           // Server
//#include "server_udp.hpp"       // UDPServer

namespace ilrd 
{

class SelectServer : private Uncopyable
{
public:
    explicit SelectServer(unsigned int udpPortNum_, unsigned int tcpPortNum_, unsigned int broadcastPortNum_, unsigned int timeoutSeconds_);
    void Start();

private:
    typedef int (SelectServer::*Handler) (int fd_);
    typedef int fdNum;

    int HandleActiveUdpFd(int fd_);
    void ConfigFdVecForListen(FdListener::FdVector& fds_);

    FdListener m_fdListener;
    UDPServer m_udpSocket;

    std::map<int, Handler> m_activeSocketsHandlers;
    int m_timeoutSec;
    bool m_exit;
}; // class Server

} // namespace ilrd



#endif /* __OL67_select_server */


