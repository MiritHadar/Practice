/*
********************************************************************************

Developer : Mirit Hadar
Reviewer :
Last Update : 
Status :

********************************************************************************
*/

#include <iostream>
#include "reactor.hpp"

namespace ilrd
{

static void CheckIfFdInRange(FdListener::Fd fd_);
static void CheckIfFdExistes(Reactor *this_, FdListener::Fd fd_, FdListener::FdMode mode_);

struct ActivateActions
{
public:
    explicit ActivateActions(std::map<FdListener::FdPair, Reactor::Action>& FdToAction_)
                            : m_FdToAction(FdToAction_) {}
                            
    void operator()(FdListener::FdPair fdToAction_)
    {
        m_FdToAction.at(fdToAction_)();
    }

private:
    std::map<FdListener::FdPair, Reactor::Action>& m_FdToAction;
};

FdOutOfRange::FdOutOfRange(const std::string &what_)
    : runtime_error(what_)
{
    ;
}

WrongFd::WrongFd(const std::string &what_)
    : runtime_error(what_)
{
    ;
}

Reactor::Reactor(long timeoutSec_)
    : m_timeoutSec(timeoutSec_),
      m_isRunning(true)
{
    ;
}

Reactor::~Reactor() noexcept
{
    m_fdToAction.clear();
    m_isRunning = false;
}

void Reactor::AddFd(FdListener::Fd fd_, FdListener::FdMode mode_ , Action action_)
{
    CheckIfFdInRange(fd_);

    m_fdToAction[FdListener::FdPair(fd_, mode_)] = action_;
}

void Reactor::RemoveFd(FdListener::Fd fd_, FdListener::FdMode mode_)
{
    CheckIfFdInRange(fd_);
    CheckIfFdExistes(this, fd_, mode_);

    m_fdToAction.erase(FdListener::FdPair(fd_, mode_));
}

static void CheckIfFdInRange(FdListener::Fd fd_)
{
    if (fd_ > Reactor::MAX_FD || fd_ < Reactor::MIN_FD)
    {
        logger.Log(Logger::ERROR, "Logger : Fd out of range");
        throw FdOutOfRange("Fd out of range");
    }
}

static void CheckIfFdExistes(Reactor *this_, FdListener::Fd fd_, FdListener::FdMode mode_)
{
    if (nullptr == this_->m_fdToAction[FdListener::FdPair(fd_, mode_)])
    {
        logger.Log(Logger::ERROR, "Logger : Fd doesn't exist");
        throw WrongFd("Fd doesn't exist");
    }
}

void Reactor::Run()
{
    //std::cout << "starting running" << std::endl;

    while (m_isRunning)
    {
        FdListener::FdVector fds = CreateFDsForFdListener();
        FdListener listen;
        FdListener::FdVector readyFds = listen(fds, m_timeoutSec);

        //std::cout << "readyFds:" << readyFds.size() << std::endl;
        /* if(readyFds.size() > 0)
        {
            for
            (std::vector<FdListener::FdPair >::iterator it = readyFds.begin();
            it != readyFds.end();
            it++)
            {
                std::cout << "first: " << (*it).first << std::endl;
                std::cout << "second: " << (*it).second << std::endl;
            }
        } */
        std::for_each(readyFds.begin(), readyFds.end(), ActivateActions(m_fdToAction));
    }

    std::cout << "done running" << std::endl;
}

void Reactor::Stop()
{
    std::cout << "Stop reactor" << std::endl;
    m_isRunning = false;
}

FdListener::FdVector Reactor::CreateFDsForFdListener()
{
    FdListener::FdVector fdsVecToReturn;
    std::map<FdListener::FdPair, Action>::iterator itr;

    for (itr = m_fdToAction.begin(); itr != m_fdToAction.end(); ++itr)
    {
        fdsVecToReturn.push_back(itr->first);
    }

    return fdsVecToReturn;
}

} // namespace ilrd



