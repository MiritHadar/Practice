/*
********************************************************************************

Developer : Mirit Hadar
Reviewer :
Last Update : 
Status :

********************************************************************************
*/

#include "thread.hpp"
#include "signal.h"     //pthread_kill

#define     THREAD_FUNC(f)  reinterpret_cast<void*(*)(void*)>(f)

namespace ilrd
{

Thread::Thread(FuncT(f_))
    : m_thread(0), m_IsJoined(0)
{
    int status = pthread_create(&m_thread, nullptr, THREAD_FUNC(f_), nullptr);
    assert(EINVAL != status); //Invalid settings in attr

    if (0 != status)
    {
        throw Thread_error();
    }
}

void Thread::Join() const
{
    m_IsJoined = 1;
    pthread_join(m_thread, nullptr);
}

void Thread::Detach()
{
    pthread_detach(m_thread);
}

Thread::~Thread()noexcept
{
    if (!m_IsJoined)
    {
        pthread_join(m_thread, nullptr);
    }
}

}//namespace ilrd



