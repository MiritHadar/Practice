/*
********************************************************************************

Developer : Mirit Hadar
Reviewer :
Last Update : 
Status :

********************************************************************************
*/

#ifndef __OL67_fd_listener
#define __OL67_fd_listener

#include <vector>
#include <exception>
#include <sys/select.h>
#include "logging.hpp"
#include "uncopyable.hpp"

extern ilrd::Logger logger;

namespace ilrd
{

class FdListener : private Uncopyable
{
public:
    typedef int Fd;
    
    enum FdMode
    {
        READ = 0,
        WRITE = 1,
        EXCEPT = 2,
        NUM_OF_MODES = 3
    };

    typedef std::pair<FdListener::Fd, FdListener::FdMode> FdPair;
    typedef std::vector<FdPair> FdVector;
    
    // FdListener() = default;
    // ~FDListener() = default;

    FdVector operator()(FdVector fdsToListenTo_, long timeoutSec_);

private:

}; // class FdListener

struct NoFdReady : public std::runtime_error
{
    public:
        explicit NoFdReady(const std::string &what_);
};

struct FindMaxFd
{
    public:
        explicit FindMaxFd(FdListener::Fd& fd_) : m_max(fd_) {}
        void operator()(FdListener::FdPair ItrFdsToListenTo_)
        {
            m_max = std::max(m_max, ItrFdsToListenTo_.first);
        }
        
    private:
        FdListener::Fd& m_max;
};

struct SetFd
{
    public:
        SetFd(fd_set *fdArrForSelect_) : m_fdArr(fdArrForSelect_) {}
        void operator()(FdListener::FdPair pair_)
        {
            FD_SET(pair_.first, &m_fdArr[pair_.second]);
        }
    private:
        fd_set *m_fdArr;
};

} // namespace ilrd



#endif /* __OL67_fd_listener */


