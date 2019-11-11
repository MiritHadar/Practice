/*
********************************************************************************

Developer : Mirit Hadar
Reviewer :
Last Update : 
Status :

********************************************************************************
*/
#include <sys/types.h>          // recv, send
#include <sys/socket.h>         // recv, send
#include <sys/select.h>         // select
#include <vector>               // vector 
#include <map>                  // map
#include <stdexcept>            // runtime_error
#include <iostream>             // cout, endl      
#include <string>               // string   

#include "select_server.hpp"    // FdListener

namespace ilrd
{

const size_t MSG_SIZE = 100;
const char* MSG_TO_SEND = "pong";

//assign handlers to the vector
SelectServer::SelectServer(unsigned int udpPortNum_, unsigned int tcpPortNum_, unsigned int broadcastPortNum_, unsigned int timeoutSeconds_)
    :   m_udpSocket(udpPortNum_), 
        /* m_broadcastSocket(INADDR_BROADCAST, broadcastPortNum_, true), 
        m_tcpAcceptSocket(tcpPortNum_, INADDR_ANY),  */
        m_timeoutSec(timeoutSeconds_),
        m_exit(false)
{
    (void)broadcastPortNum_; // ?
    m_activeSocketsHandlers[m_udpSocket.GetFd()] = &SelectServer::HandleActiveUdpFd;
    /* m_activeSocketsHandlers[m_tcpAcceptSocket.GetFd()] = &SelectServer::HandleActiveTcpAccepterFd;
    m_activeSocketsHandlers[0] = &SelectServer::HandleActiveStdinFd; 
    m_activeSocketsHandlers[m_broadcastSocket.GetFd()] = &SelectServer::HandleActiveUdpFd;*/
}

//costumer use - find avilable fd and, dispach the matching handler and execute it
void SelectServer::Start()
{
    while (!m_exit)
    {
        FdListener::FdVector fds; 
        ConfigFdVecForListen(fds);
        
        fds = m_fdListener(fds, m_timeoutSec);
        
        for (size_t i = 0; i < fds.size(); ++i)
        {
            int fd = fds[i].first;
            Handler handler = m_activeSocketsHandlers[fd];
            (this->*handler)(fd);
        }
    }
}

void SelectServer::ConfigFdVecForListen(FdListener::FdVector& vec_)
{
    for (std::map<int, Handler>::iterator iter = m_activeSocketsHandlers.begin(); 
            iter != m_activeSocketsHandlers.end(); ++iter)
    {
        vec_.push_back(std::pair<int, FdListener::FdMode>(iter->first, FdListener::READ));
    }
}

int SelectServer::HandleActiveUdpFd(int fd_)
{
    (void)fd_;
    char buf[MSG_SIZE] = {0};
    
    m_udpSocket.Receive(buf, MSG_SIZE);
    std::cout << std::string(reinterpret_cast<char*>(buf)) << std::endl;
    m_udpSocket.Send(reinterpret_cast<const char*>(MSG_TO_SEND), 5);

    return 0;
}





} // namespace ilrd
