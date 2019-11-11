/*
********************************************************************************

Developer : Mirit Hadar
Reviewer :
Last Update : 
Status :

********************************************************************************
*/

#ifndef __OL67_SCOPE_LOCK
#define __OL67_SCOPE_LOCK

namespace ilrd
{

template <typename T>
class ScopeLock
{
public:
    explicit ScopeLock(T& t);
    ~ScopeLock();

private:
    T& m_lock;
};


template <typename T>
ScopeLock<T>::ScopeLock(T& t_)
    : m_lock(t_)
{
    m_lock.lock();
}

template <typename T>
ScopeLock<T>::~ScopeLock()
{
    m_lock.unlock();
}

} //namespace ilrd

#endif /* __OL67_SCOPE_LOCK */


