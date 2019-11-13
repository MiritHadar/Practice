/*
********************************************************************************

Developer : Mirit Hadar
Reviewer :
Last Update : 
Status :

********************************************************************************
*/

#ifndef __OL67_writer
#define __OL67_writer

#include <queue>        //queue
#include "logMsg.hpp"
#include "thread.hpp"
#include "waitable_queue.hpp"
#include "uncopyable.hpp"

namespace ilrd
{

class PopFunctor : public Uncopyable
{
public:
    explicit PopFunctor(WaitableQueue<queue <LogMsg> > &waitQ);
    void operator()();
    void SetIsStop();

private:
    WaitableQueue <queue<LogMsg> > &m_q;
    bool m_IsStop;
};

/*******************************************Writer*********************************************/
class Writer : public Uncopyable
{
public:
    explicit Writer();
    void PushMsg(LogMsg &msg_);
    ~Writer();

private:
    WaitableQueue<queue <LogMsg> > m_q;
    PopFunctor m_functor;
    Thread m_thread;
};

} // namespace ilrd

#endif /* __OL67_writer */


