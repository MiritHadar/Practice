/*
********************************************************************************

Developer : Mirit Hadar
Reviewer :
Last Update : 
Status :

********************************************************************************
*/

#include "thread_pool.hpp"

namespace ilrd
{

ThreadPool::ThreadPool(size_t numThreads_)
    : m_numThreads(numThreads_),
      m_isShutDown(false),
      m_runAllFuncs(*this)
{
    for (size_t i = 0; i < numThreads_; ++i)
    {
        m_threads.push_back(SharedPtr<Thread>(new Thread(m_runAllFuncs)));
    }
}

ThreadPool::~ThreadPool()
{
    this->ShutDown();
}


void ThreadPool::ShutDown()
{
   if (!m_isShutDown)
   {
        m_isShutDown = true;

        for (size_t i = 0; i < m_numThreads; ++i)
        {
            SharedPtr<details::GenericBase> g = new (details::Dummy);
            AddTask(g);
        }

        for (size_t i = 0; i < m_numThreads; ++i)
        {
            m_threads[i]->Join();
        }
   }
}

void ThreadPool::AddTask(SharedPtr<details::GenericBase> task_)
{
    m_tasks.Push(task_);
}

ThreadPool::RunAllTasks::RunAllTasks(ThreadPool& pool_)
    : m_pool(pool_)
{
    ;
}

void ThreadPool::RunAllTasks::operator()()
{
    while(!(m_pool.m_isShutDown))
    {
        SharedPtr<details::GenericBase> task;
        m_pool.m_tasks.Pop(task);
        (*task)();
    }
}

} // namespace ilrd




