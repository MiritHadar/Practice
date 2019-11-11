/*
********************************************************************************

Developer : Mirit Hadar
Reviewer :
Last Update : 
Status :

********************************************************************************
*/

#include "writer.hpp"

namespace ilrd
{

Writer::Writer()
	: m_q(), m_functor(m_q), m_thread(m_functor)
{
	;
}

void Writer::PushMsg(LogMsg &msg_)
{
	m_q.Push(msg_);
}

Writer::~Writer()
{
    m_functor.SetIsStop();
    m_thread.Join();
}

/***************************************Functor*********************************************/

PopFunctor::PopFunctor(WaitableQueue<queue <LogMsg> > &waitQ)
    : m_q(waitQ), m_IsStop(false)
{
    ;
}

void PopFunctor::operator()()
{
    while(!m_IsStop)
    {
        cout << "functor running" << endl;
        LogMsg logOut;
        if (m_q.Pop(logOut, static_cast<boost::chrono::milliseconds>(1000)))
        {
            FuncPrintLogMsg()(logOut);  //prints msg to ostream
        }
    }

    //delete &m_q;
}

void PopFunctor::SetIsStop()
{
    m_IsStop = true;
}

} // namespace ilrd
