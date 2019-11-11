/*
********************************************************************************

Developer : Mirit Hadar
Reviewer :
Last Update : 
Status :

********************************************************************************
*/

#ifndef __OL67_reactor
#define __OL67_reactor

#include <boost/function.hpp>   // boost::function
#include <boost/bind/bind.hpp>  // boost::bind
#include <map>                  // map
#include "logging.hpp"          // logger
#include "uncopyable.hpp"       // Uncopyable
#include "fd_listener.hpp"      // FdListener

#if __cplusplus < 201103L
#define nullptr NULL
#define noexcept throw()
#endif

namespace ilrd
{
    
class Reactor : private Uncopyable
{
public:
    explicit Reactor(long timeoutSec_ = 5);
    ~Reactor() noexcept;

    typedef boost::function<void()> Action;
    /* Function cannot throw an exception. Allows override to key*/

    void AddFd(FdListener::Fd fd_, FdListener::FdMode mode_ , Action action_);
    void RemoveFd(FdListener::Fd fd_, FdListener::FdMode mode_);
    void Run();
    void Stop();

    static const int MAX_FD = 1024;
    static const int MIN_FD = 0;

    std::map<FdListener::FdPair, Action> m_fdToAction;    

private:
    FdListener::FdVector CreateFDsForFdListener();
    long m_timeoutSec;
    bool m_isRunning;
};

struct FdOutOfRange : public std::runtime_error
{
    public:
        explicit FdOutOfRange(const std::string &what_);  
};

struct WrongFd : public std::runtime_error
{
    public:
        explicit WrongFd(const std::string &what_);
};

} // namespace ilrd
#endif /* __OL67_reactor */


