/*
********************************************************************************

Developer : Mirit Hadar
Reviewer :
Last Update : 
Status :

********************************************************************************
*/

#include "fd_listener.hpp"
#include <vector>           // vector
#include <sys/select.h>     // select
#include <stdexcept>        // runtime_error
#include <cerrno>           // errno
#include <cstring>          // strerror  
#include <algorithm>        // for_each
#include "fd_listener.hpp"  // fdListener

namespace ilrd
{

static void ResetFdArr(fd_set *fdArrForSelect_);
static timeval InitTimeOut(long timeoutSec_);
static FdListener::Fd MaxFdPlusOneAndFdSet(FdListener::FdVector fdsToListenTo_);

NoFdReady::NoFdReady(const std::string &what_)
    : runtime_error(what_)
{
    ;
}

FdListener::FdVector FdListener::operator()(FdListener::FdVector fdsToListenTo_, long timeOutSec_)
{
    fd_set fdArrForSelect[NUM_OF_MODES] = {0};
    timeval timeout = InitTimeOut(timeOutSec_);
    Fd maxFd = MaxFdPlusOneAndFdSet(fdsToListenTo_);
    ResetFdArr(fdArrForSelect);

    std::for_each(fdsToListenTo_.begin(), fdsToListenTo_.end(), SetFd(fdArrForSelect));

    int numOfReadyFd = select(maxFd,
                        &fdArrForSelect[READ],
                        &fdArrForSelect[WRITE],
                        &fdArrForSelect[EXCEPT],
                        &timeout);

    if ((numOfReadyFd < 0) && (timeOutSec_ > 0))
    {
        logger.Log(Logger::SDEBUG, "Logger : no FD ready");
        throw NoFdReady(std::string("No FD ready"));
    }

    FdVector activeFds;

    for(size_t i = 0; i < fdsToListenTo_.size(); ++i)
    {
        if(FD_ISSET(fdsToListenTo_[i].first, &fdArrForSelect[fdsToListenTo_[i].second]))
        {
            activeFds.push_back(fdsToListenTo_[i]);
        }
    }

    return activeFds;
}

static void ResetFdArr(fd_set *fdArrForSelect_)
{
    for(size_t i = 0; i < FdListener::NUM_OF_MODES; ++i)
    {
        FD_ZERO(fdArrForSelect_ + i);
    }
}

static timeval InitTimeOut(long timeoutSec_)
{
    timeval timeout = {0};
    timeout.tv_sec = timeoutSec_;
    timeout.tv_usec = 0;

    return timeout;
}

static FdListener::Fd MaxFdPlusOneAndFdSet(FdListener::FdVector fdsToListenTo_)
{
    FdListener::Fd maxFd = 0;
    std::for_each(fdsToListenTo_.begin(), fdsToListenTo_.end(), FindMaxFd(maxFd));

    return maxFd + 1;
}

} // namespace ilrd
