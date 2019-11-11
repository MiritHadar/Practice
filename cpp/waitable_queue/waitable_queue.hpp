/*
********************************************************************************

Developer : Mirit Hadar
Reviewer :
Last Update : 
Status :

********************************************************************************
*/

#ifndef __OL67_waitable_queue
#define __OL67_waitable_queue

#include <boost/chrono.hpp> // boost chrono
#include <boost/thread.hpp> // boost mutex, condition variable
#include <iostream>         // cout
#include "uncopyable.hpp"

using namespace std;

namespace ilrd
{

#if __cplusplus < 201103L
    #define nullptr NULL
    #define noexcept throw()
#endif

template <class Q>
class WaitableQueue : private Uncopyable
{
public:
	//Ctors
	//explicit WaitableQueue() = default
	//~WaitableQueue()noexcept = default

	//Functions
	void Push(typename Q::value_type &data_);
	void Pop(typename Q::value_type &out_);
	bool Pop(typename Q::value_type &out_, boost::chrono::milliseconds timeout_);

private:
	//Member variables
	Q m_q;
	typedef boost::unique_lock<boost::mutex> Lock;

	boost::condition_variable m_cond;
	boost::mutex m_mutex;
};

template <class Q>
void WaitableQueue<Q>::Push(typename Q::value_type &data_)
{
    //scope for lock and unlock
    {
        Lock lock(m_mutex);
        m_q.push(data_);
    }

    //cout << "Push: " << data_ << endl;
    m_cond.notify_one();
}

template <class Q>
void WaitableQueue<Q>::Pop(typename Q::value_type &out_)
{
    Lock lock(m_mutex);

    while (m_q.empty())
    {
        m_cond.wait(lock);
    }

    out_ = m_q.front();
    m_q.pop();
    //cout << "Pop: " << out_ << endl;
}

template <class Q>
bool WaitableQueue<Q>::Pop(typename Q::value_type &out_, boost::chrono::milliseconds timeout_)
{
    Lock lock(m_mutex);

    while (m_q.empty())
    {
        if (boost::cv_status::timeout == m_cond.wait_for(lock, timeout_))
        {
            return false;
        }
    }

    out_ = m_q.front();
    m_q.pop();

    return true;
}

} //namespace ilrd

#endif /* __OL67_waitable_queue */


