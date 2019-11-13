/******************************************************************************/
/* author: 		Mirit Hadar											  	  */
/* Reviewer: 					       										  */
/* version: 	Draft			  		                                      */
/* Last update: 29-09-2019					                                  */
/******************************************************************************/

#ifndef ILRD_RD6768_MINION
#define ILRD_RD6768_MINION

#if __cplusplus < 201103L
#define nullptr NULL
#define noexcept throw()
#endif

#include "storage.hpp"
#include "uncopyable.hpp"
#include "factory.hpp"
#include "action.hpp"
#include "request.hpp"
#include "response.hpp"
#include "packet.hpp"
#include "server.hpp"
#include "request_handler.hpp"
#include "reactor.hpp"
#include "fd_listener.hpp"
#include "dir_monitor.hpp"
#include "service_locator.hpp"
#include "project_exceptions.hpp"

namespace ilrd
{

typedef SharedPtr<Action> (*Create_CType)(void);

static const unsigned int MAX_FACTORY_OPTINS = 256;

namespace details
{
struct SharedObjectPointers
{
    void *m_sharedObjectFiles[ilrd::MAX_FACTORY_OPTINS];
};

}//namespace details

class Minion
{
public:
    enum State
    {
        READ = 0,
        WRITE = 1
    };

	typedef Factory<char, Action> ActionFactory;
  
    //Constructors
    explicit Minion();
    // Minion(const Minion &other_) = default;
    //~Minion() = default;

    //member function
    void Run();
	inline Reactor &GetReactor();
	inline ActionFactory &GetFactory();

private:
	ServiceLocator<std::string> InitServiceLocator();
    
	//Member variables
    Storage m_storage;
	Reactor m_reactor;
    ActionFactory m_factory;
	ServiceLocator<std::string> m_serviceLocator;
	DirMonitor m_dirMonitor;
    UDPServer m_server;
    RequestHandler m_requestHandler;
    details::SharedObjectPointers m_sharedObjectPointers;
};

Reactor &Minion::GetReactor() 
{
	return m_reactor;
}

Minion::ActionFactory &Minion::GetFactory()
{
	return m_factory;
}

}//namespace ilrd

#endif  //ILRD_RD6768_MINION
