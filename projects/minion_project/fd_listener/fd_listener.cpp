/******************************************************************************/
/* author: 		Mirit Hadar											  	  */
/* Reviewer: 					       										  */
/* version: 	Draft			  		                                      */
/* Last update: 20-10-2019					                                  */
/******************************************************************************/

#include <map>              // 	map
#include <sys/select.h>     // 	select, fd_set
#include <stdexcept>        // 	runtime_error
#include <cerrno>           // 	errno
#include <cstring>          //	strerror 

#include "fd_listener.hpp"	//	Header file	
#include "loggerMT.hpp"
#include "loggerMT_singleton.hpp"

namespace ilrd
{

FDListener::FDVector FDListener::operator()(FDListener::FDVector fdsToListen_,												long timeOutSeconds_)
{
    int maxFd = 0;
    
    fd_set readFd; 
    fd_set writeFd; 
    fd_set exceptFd;

    std::map<FDMode, fd_set*> fdSets;
    fdSets[READ] = &readFd;
    fdSets[WRITE] = &writeFd;
    fdSets[EXCEPT] = &exceptFd;

    FD_ZERO(&readFd);
    FD_ZERO(&writeFd);
    FD_ZERO(&exceptFd);

    timeval timeout;
    timeout.tv_sec = timeOutSeconds_;
    timeout.tv_usec = 0;

	size_t size = fdsToListen_.size();
    for(size_t i = 0; i < size; ++i)
    {
        maxFd = std::max(maxFd, fdsToListen_[i].first);
        FD_SET(fdsToListen_[i].first, fdSets[fdsToListen_[i].second]);
    }

    int status = select(maxFd + 1, 
						fdSets[READ], 
						fdSets[WRITE], 
						fdSets[EXCEPT], 
						&timeout);

	LoggerMT *logger = GetSOInstance();
    if (status < 0)
    {
		logger->Log(ilrd::LoggerMT::ERROR, std::string("ERROR in select function 				in FDListner operator") + std::string(strerror(errno)));

		throw FDListenerOperatorException(std::string("ERROR in select function 				in FDListner operator") + std::string(strerror(errno)));
    }
	//logger->Log(ilrd::LoggerMT::SDEBUG, std::string("Select worked!"));

    FDVector activeFds;
	size = fdsToListen_.size();

    for(size_t i = 0; i < size; ++i)
    {
        if (FD_ISSET(fdsToListen_[i].first, fdSets[fdsToListen_[i].second]))
        {
            activeFds.push_back(fdsToListen_[i]);
        }
    }

    return activeFds;
}

FDListenerOperatorException::FDListenerOperatorException(const std::string &s_ )
        : runtime_error(s_ )
{

}

}//namespace ilrd
