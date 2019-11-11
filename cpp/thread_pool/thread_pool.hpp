/*
********************************************************************************

Developer : Mirit Hadar
Reviewer :
Last Update : 
Status :

********************************************************************************
*/

#ifndef __OL67_THREAD_POOL
#define __OL67_THREAD_POOL

#include <cstddef>      //size_t
#include <queue>        //queue 
#include <iostream>     //cout

#include "uncopyable.hpp"       //uncopyable class
#include "waitable_queue.hpp"   //waitable queue class
#include "thread.hpp"           //thread class
#include "shared_ptr.hpp"       //sharedPtr

/* #if __cplusplus < 201103L
    #define nullptr NULL
    #define noexcept throw()
#endif */

namespace details
{

class GenericBase
{
public:
    virtual void operator()() = 0;
    virtual ~GenericBase() {}
};

class Dummy : public GenericBase
{
public:
    void operator()() {}
};

} // namespace details

namespace ilrd
{

class ThreadPool : private Uncopyable
{
public:
    explicit ThreadPool (size_t numThreads_ = 4);
    ~ThreadPool();

    //template<typename FUNC>
    //void AddTask(const FUNC &functor_);
    void AddTask(SharedPtr<details::GenericBase> task_);
    void ShutDown();

private:
    class RunAllTasks
    {
    public:
        explicit RunAllTasks(ThreadPool& pool_);
        void operator()();
    private:
        ThreadPool &m_pool;
    };

    size_t m_numThreads;
    std::vector<SharedPtr<Thread> > m_threads;
    WaitableQueue<std::queue<SharedPtr<details::GenericBase> > >m_tasks;
    boost::atomic<bool> m_isShutDown;
    RunAllTasks m_runAllFuncs;
};

/* template<typename FUNC>
void ThreadPool::AddTask(const FUNC &functor_)
{
    
} */

} // namespace ilrd


#endif /* __OL67_THREAD_POOL */


