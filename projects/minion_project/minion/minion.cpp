/******************************************************************************/
/* author: 		Mirit Hadar											  	  */
/* Reviewer: 					       										  */
/* version: 	Draft			  		                                      */
/* Last update: 29-09-2019					                                  */
/******************************************************************************/

#include <iostream>
#include <sstream>
#include <dlfcn.h>

#include "minion.hpp"				//	Header file	
#include "loggerMT_singleton.hpp"

static const uint32_t READ_OR_WRITE_FLAG = 1;
static const uint32_t UID = 8;
static const uint32_t BLOCK_INDEX = 8;
static const uint32_t BLOCK_SIZE = 4 * 1024;
static const uint32_t MAXLINE = READ_OR_WRITE_FLAG + UID + 
								BLOCK_INDEX + BLOCK_SIZE;

/******************************************************************************/
namespace ilrd
{

/*************************Helper functions*************************************/
static void  CallBackFunction(std::string string_);
/******************************************************************************/

static LoggerMT *logger = GetSOInstance();

class ReceiveFunctor
{
public:
	ReceiveFunctor(UDPServer& server_, Request &request_, bool &isReceive_)
		:m_server(server_), m_request(request_), m_isReceive(isReceive_)
	{
		;
	}

	void operator()()
	{	
        m_server.Receive(m_request.GetPacket().GetCPtr(), MAXLINE);
		logger->Log(LoggerMT::SDEBUG, "packet have been received. Index number is: ");
		std::stringstream ss;
		ss << m_request.GetIndex();
		logger->Log(LoggerMT::SDEBUG, ss.str());
        // std::cout << "index number " << m_request.GetIndex() << std::endl;
        m_isReceive = true;
	}

private:
	UDPServer &m_server;
    Request &m_request;
    bool &m_isReceive;
};

class SendFunctor
{
public:
	SendFunctor(UDPServer& server_, RequestHandler &handlerRequest_, Request &request_, bool &isReceive_)
		:m_server(server_), m_handlerRequest(handlerRequest_), m_request(request_), m_isReceive(isReceive_)
	{
		;
	}

	void operator()()
	{	
        if (m_isReceive)
        {
            Response response = m_handlerRequest.HandlerRequest(m_request);
            m_server.Send(response.GetPacket().GetCPtr(), response.GetSize());

            m_isReceive = false;
        }
	}

private:
	UDPServer &m_server;
    RequestHandler &m_handlerRequest;
    Request &m_request;
    bool &m_isReceive;
};

class MinionConsole
{
public:
	explicit MinionConsole(Reactor &reactor_)
		:m_reactor(reactor_)
	{
		;
	}

	void operator()()
	{	
		std::string command;
		std::getline(std::cin, command);

		LoggerMT::Severity severity = logger->GetOutputSeverity();

		if ("stop" == command)
		{
			m_reactor.Stop();
			exit(1);
		}

		if ("+" == command && severity < LoggerMT::ERROR)
		{
			severity = static_cast<LoggerMT::Severity>(static_cast<int>(severity) + 1);
			logger->SetOutputSeverity(severity);
		}

		if ("-" == command && severity > LoggerMT::SDEBUG)
		{
			severity = static_cast<LoggerMT::Severity>(static_cast<int>(severity) - 1);
			logger->SetOutputSeverity(severity);
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
    : m_storage(), m_reactor(), m_factory(),
	  m_serviceLocator(InitServiceLocator()), 
	  m_dirMonitor("/home/student/Ori-Michaeli/projects/minion_project/add_ons/", CallBackFunction, m_serviceLocator), m_server(), m_requestHandler(m_storage, m_factory), m_sharedObjectPointers()
{
	logger->SetOutputSeverity(LoggerMT::INFO);
}

void Minion::Run()
{
    Request request;
    bool isReceive = false;
    ReceiveFunctor receiveFunctor(m_server, request, isReceive);
    SendFunctor sendFunctor(m_server, m_requestHandler, request, isReceive);

    m_reactor.AddFD(m_server.GetSocketFD(), FDListener::READ, receiveFunctor);
    m_reactor.AddFD(m_server.GetSocketFD(), FDListener::WRITE, sendFunctor);
    m_reactor.AddFD(0, FDListener::READ, MinionConsole(m_reactor));

    m_reactor.Run();
}

ServiceLocator<std::string> Minion::InitServiceLocator()
{
	ServiceLocator<std::string> sl_;

    sl_.Add(std::string("reactor"), m_reactor);
    sl_.Add(std::string("storage"), m_storage);
    sl_.Add(std::string("factory"), m_factory);
    sl_.Add(std::string("dir_monitor"), m_dirMonitor);
    sl_.Add(std::string("request_handler"), m_requestHandler);

	return sl_;
}

static void CallBackFunction(std::string fullPath_)
{
	// if (IsSO(fullPath_))
	// {
	//     DLLoader dlLoader;
	//     SharedPtr<SharedObject> sharedObject = dlLoader.Open(fullPath_);
	//     SharedPtr<Action> (*createFunction)() = sharedObject->Load<SharedPtr<Action> (*)()>(CREATE_OBJECT);
	//     ActionType (*getActionFunction)() = sharedObject->Load<ActionType (*)()>(GET_ACTION_TYPE);
	//     //m_minion.GetFactory().Learn(getActionFunction(), createFunction);
	// }
}

}//namespace ilrd
