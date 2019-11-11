/******************************************************************************/
/* author: 		Ori Michaeli											  	  */
/* Reviewer: 					       										  */
/* version: 	Draft			  		                                      */
/* Last update: 29-10-2019					                                  */
/******************************************************************************/

#include <sys/inotify.h>			// 	inotify API
#include <boost/bind.hpp>			//	bind to reactor
#include <dlfcn.h>					//	dlsym, dlopen, dlclose
#include <cstdlib>					//	malloc, free
#include <unistd.h>					//	read
#include <project_exceptions.hpp>	//	project exceptions

#include "dir_monitor.hpp"			//	Header file	
#include "loggerMT_singleton.hpp"	//	logger instance
#include "reactor.hpp"
#include "factory.hpp"
#include "action.hpp"

namespace ilrd
{
/*************************Helper functions*************************************/
static bool IsSO(const char* fileName_);
/******************************************************************************/

static const size_t MAX_PATH_LEN = 50;
static const size_t EVENT_SIZE = sizeof(inotify_event) + MAX_PATH_LEN + 1;

static LoggerMT *logger;

DirMonitor::DirMonitor(const std::string &path_, CallBack callBack_, 								   ServiceLocator<std::string> &serviceLocator_)
    : m_path(path_), m_inotifyFD(inotify_init()), m_callBack(callBack_), 		  m_serviceLocator(serviceLocator_), m_dlLoader()
{
    logger = GetSOInstance();
	logger->Log(LoggerMT::SDEBUG, "DirMonitor Ctor");
	
	if (m_inotifyFD < 0)
	{
		logger->Log(LoggerMT::ERROR, "inotify_init failed");
		throw InotifyInitException("inotify_init failed");
	}

	if (inotify_add_watch(m_inotifyFD, m_path.c_str(), IN_CREATE | IN_MODIFY) < 0)
	{
		logger->Log(LoggerMT::ERROR, "inotify_add_watch failed");
		throw InotifyInitException("inotify_add_watch failed");		
	}

	Reactor &reactor = m_serviceLocator.Get<Reactor>("reactor");
	reactor.AddFD(m_inotifyFD,FDListener::READ, 
				  boost::bind(&DirMonitor::ReactorFunc,this));

	logger->Log(LoggerMT::SDEBUG, "DirMonitor Ctor finished");
}

DirMonitor::FD DirMonitor::GetFD() const
{
	return m_inotifyFD;
}

void DirMonitor::ReactorFunc()
{
	unsigned char buffer[EVENT_SIZE] = {0};
    inotify_event* event = reinterpret_cast<inotify_event*>(buffer);

    if (read(m_inotifyFD, event, EVENT_SIZE) < 0)
	{
		logger->Log(LoggerMT::ERROR, "read failed");
		throw new ReadException("read failed");
	}

    if ((event->mask & IN_CREATE) && !(event->mask & IN_ISDIR)) 
    {
    	std::string fullPath = m_path;
    	fullPath += event->name;
        // m_callBack(fullPath);

		if (IsSO(fullPath.c_str()))
		{
            SharedPtr<SharedObject> sharedObject = 
											m_dlLoader.Open(fullPath);
			std::cout << "dir monitor open" << std::endl;
            SharedPtr<Action> (*createFunction)() = sharedObject->Load<SharedPtr<Action> (*)()>("Create");
            char (*getActionFunction)() = sharedObject->Load<char (*)()>("GetActionType");
            logger->Log(LoggerMT::INFO, fullPath);
            logger->Log(LoggerMT::INFO, "\n");
            Factory<char, Action> &factory =
					 m_serviceLocator.Get<Factory<char, Action> >("factory");
            factory.Learn(getActionFunction(), createFunction);
		}
    }
}

static bool IsSO(const char* fileName_)
{
    const char* soEnding = ".so";
    const size_t soLen = 3;
    size_t fileLen = strlen(fileName_);
    if (fileLen >= soLen) 
    {
        return (0 == strcmp(fileName_ + fileLen - soLen, soEnding));
    } 

    return false;
}

}//namespace ilrd
