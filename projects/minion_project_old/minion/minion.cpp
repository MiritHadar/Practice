/*
********************************************************************************

Developer : Mirit Hadar
Reviewer :
Last Update : 
Status :

********************************************************************************
*/
/* #include <cstdio>       //perror
#include <cstdlib>      //exit
#include <signal.h>     //pthread_kill
#include <pthread.h>    //pthread_create
#include <iostream>     //cout */

#include "minion.hpp"

using namespace std;

namespace ilrd
{
class Receiver
{
public:
	Receiver(UDPServer& server_, Request &request_, bool &isReceive_)
		: m_server(server_),
          m_request(request_),
          m_isReceive(isReceive_)
	{
		;
	}

	void operator()()
	{	
        m_server.Receive(reinterpret_cast<char*>(m_request.GetPacket().GetBuffer()), INFO_LEN);
		logger.Log(Logger::SDEBUG, "packet received\n"); 
        std::cout << "index number " << m_request.GetIndex() << std::endl;
        m_isReceive = true;
	}

private:
	UDPServer &m_server;
    Request &m_request;
    bool &m_isReceive;
};

class Sender
{
public:
	Sender(UDPServer& server_, RequestHandler &handlerRequest_, Request &request_, bool &isReceive_)
		:m_server(server_), m_handler(handlerRequest_), m_request(request_), m_isReceive(isReceive_)
	{
		;
	}

	void operator()()
	{	
        if (m_isReceive)
        {
            Response response;
			response = m_handler.Handle(m_request);
 		cout << response.GetSize() << endl;

            m_server.Send(reinterpret_cast<char*>(response.GetPacket().GetBuffer()), response.GetSize());
 		cout << response.GetSize() << endl;
            m_isReceive = false;
        }
	}

private:
	UDPServer &m_server;
    RequestHandler &m_handler;
    Request &m_request;
    bool &m_isReceive;
};

class StopReactor
{
public:
	explicit StopReactor(Reactor &reactor_)
		: m_reactor(reactor_)
	{
		;
	}

	void operator()()
	{	
		std::string command;
        std::cin >> command;

		Logger::Severity severity = logger.GetSeverity();

		if ("stop" == command)
		{
			m_reactor.Stop();
			exit(1);
		}

		if ("+" == command && severity < Logger::ERROR)
		{
			severity = static_cast<Logger::Severity>(static_cast<int>(severity) + 1);
			logger.SetOutputSeverity(severity);
		}

		if ("-" == command && severity > Logger::SDEBUG)
		{
			severity = static_cast<Logger::Severity>(static_cast<int>(severity) - 1);
			logger.SetOutputSeverity(severity);
		}

		if ("ping" == command || "Ping" == command)
		{
			std::cout << "Pong" << std::endl;
		}
	}

private:
	Reactor &m_reactor;
};

Minion::Minion()
    : m_storage(),
      m_factory(),
      m_server(),
      m_handler(m_storage, m_factory)
{
    m_factory.Learn(0, &ReadAction::Create);
	m_factory.Learn(1, &WriteAction::Create);
	cout << "ctor minion" << endl;
}

void Minion::Run()
{
	Request request;
    bool isReceive = false;
    Receiver receiveFunctor(m_server, request, isReceive);
    Sender sendFunctor(m_server, m_handler, request, isReceive);

    Reactor reactor;
    reactor.AddFd(m_server.GetFd(), FdListener::READ, receiveFunctor);
	cout << "AddFd1" << endl;

    reactor.AddFd(m_server.GetFd(), FdListener::WRITE, sendFunctor);
	cout << "AddFd2" << endl;

    reactor.AddFd(0, FdListener::READ, StopReactor(reactor));
	cout << "AddFd3" << endl;

    reactor.Run();
}

} // namespace ilrd
