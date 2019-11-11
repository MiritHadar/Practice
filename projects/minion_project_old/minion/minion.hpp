/*
********************************************************************************

Developer : Mirit Hadar
Reviewer :
Last Update : 
Status :

********************************************************************************
*/

#ifndef __RD67_MINION
#define __RD67_MINION

#include <stdint.h>         //uint_32
#include <iostream>	
#include "logging.hpp"
#include "storage.hpp"
#include "uncopyable.hpp"
#include "factory.hpp"
#include "action.hpp"
#include "read_action.hpp"
#include "write_action.hpp"
#include "request.hpp"
#include "response.hpp"
#include "packet.hpp"
#include "server.hpp"
#include "request_handler.hpp"
#include "reactor.hpp"
#include "fd_listener.hpp"

#if __cplusplus < 201103L
#define nullptr NULL
#define noexcept throw()
#endif

extern ilrd::Logger logger;

namespace ilrd
{

class Minion
{
public:
   explicit Minion();
   //Minion(const Minion &other_) = default
   //Minion& operator=(const Minion &other_) = default
   //~Minion() = default;
   void Run();

private:
   Storage m_storage;
   Factory<char, Action> m_factory;
   UDPServer m_server;
   RequestHandler m_handler;
};

}//namespace ilrd*/


#endif /* __RD67_MINION */


