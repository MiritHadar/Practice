/******************************************************************************/
/* author: 		Mirit Hadar											  	  */
/* Reviewer: 					       										  */
/* version: 	Draft			  		                                      */
/* Last update: 23-10-2019					                                  */
/******************************************************************************/

#include <exception>			//	logic_error

#include "reactor.hpp"			//	Header file	

#include "loggerST.hpp"


namespace ilrd
{

/*************************Helper functions*************************************/
static bool IsValidFileDescriptor(FDListener::FD fd_)
{
    return ((fd_ <= Reactor::MAX_FD) && (fd_ >= 0));    
}

static LoggerMT *logger = GetSOInstance();
/******************************************************************************/

class FunctionActivator
{
public:
    FunctionActivator(Reactor::FDMap &FDToFunctionMap_)
        : m_FDToFunctionMap(FDToFunctionMap_)
    {}

    void operator()(FDListener::FDPair key_)
    {
        m_FDToFunctionMap[key_]();
    }
private:
    Reactor::FDMap &m_FDToFunctionMap;
};

Reactor::Reactor()
	: m_fdToFunction(), m_isRunning(true)
{
	logger->SetOutputSeverity(LoggerMT::SDEBUG);
}

void Reactor::AddFD(FDListener::FD fd_, 
					FDListener::FDMode mode_, 								ReactorFunction action_)
{
	if(!IsValidFileDescriptor(fd_))
	{	
		logger->Log(ilrd::LoggerMT::ERROR, "ERROR: Invalid FD in Reactor Add 					function");
		throw InvalidFDException("ERROR: Invalid FD in Reactor Add function");
	}

	m_fdToFunction[std::pair<FDListener::FD, FDListener::FDMode>(fd_, mode_)]
				  = action_;

	logger->Log(ilrd::LoggerMT::SDEBUG, "Reactor Add function worked!");
}		

void Reactor::RemoveFD(FDListener::FD fd_, FDListener::FDMode mode_)
{
	if(!IsValidFileDescriptor(fd_))
	{	
		logger->Log(ilrd::LoggerMT::ERROR, "ERROR: Invalid FD in Reactor Remove 					function");
		throw InvalidFDException("ERROR: Invalid FD in Reactor Add function");
	}

	if (m_fdToFunction.find(std::pair<FDListener::FD, FDListener::FDMode>
						   (fd_, mode_)) == m_fdToFunction.end())
	{
		logger->Log(ilrd::LoggerMT::ERROR, "ERROR: Key doesn't exist in Reactor 				Remove function");
		throw KeyNotExistException("ERROR: Key doesn't exist");
	}

	m_fdToFunction.erase(std::pair<FDListener::FD, FDListener::FDMode>
						(fd_, mode_));

	logger->Log(ilrd::LoggerMT::SDEBUG, "Reactor Remove function worked!");
}

void Reactor::Run()
{
	logger->Log(ilrd::LoggerMT::SDEBUG, "Reactor Run function started");

	while (m_isRunning)
	{
		FDListener::FDVector fdsToListen;
		FDListener listener;

		FDMap::iterator itr = m_fdToFunction.begin();

		while (itr != m_fdToFunction.end())
		{
			fdsToListen.push_back(std::pair<FDListener::FD, FDListener::FDMode>						 (itr->first.first, itr->first.second));
			++itr;
		}

		FDListener::FDVector activeFds = listener(fdsToListen, 5);
        FunctionActivator activator(m_fdToFunction);
        
        std::for_each(activeFds.begin(), activeFds.end(), activator);
	}
}

void Reactor::Stop()
{
	logger->Log(ilrd::LoggerMT::SDEBUG, "Reactor Stop function called");

	m_isRunning = false;
}


InvalidFDException::InvalidFDException(const std::string &errorString_)
	: runtime_error(errorString_)
{
	;
}

KeyNotExistException::KeyNotExistException(const std::string &errorString_)
	: runtime_error(errorString_)
{
	;
}

}//namespace ilrd
