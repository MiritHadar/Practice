/******************************************************************************/
/* author: 		Ori Michaeli											  	  */
/* Reviewer: 					       										  */
/* version: 	Draft			  		                                      */
/* Last update: 24-09-2019					                                  */
/******************************************************************************/

#ifndef ILRD_RD6768_WRITER
#define ILRD_RD6768_WRITER

#if __cplusplus < 201103L
#define nullptr NULL
#define noexcept throw()
#endif

#include <iostream>	//	Streams
#include <queue>	//	Queue funcs

#include "uncopyable.hpp"
#include "thread.hpp"
#include "waitable_queue.hpp"

namespace ilrd
{
template <typename MsgFunctor>
class WriteMsgFunctor;

template <typename MsgFunctor>
class Writer : private Uncopyable
{
public:
    //Constructors
    explicit Writer();
    ~Writer() noexcept;

    //Operators

    //Functions
    void WriteMsg(MsgFunctor msg_);

private:
    //Member variables
	WaitableQueue<std::queue<MsgFunctor> > m_waitQ;
	WriteMsgFunctor<MsgFunctor> m_writeMsgFunctor;
	Thread m_thread;
};

template <typename MsgFunctor>
Writer<MsgFunctor>::Writer()
	: m_waitQ(), m_writeMsgFunctor(m_waitQ), m_thread(m_writeMsgFunctor)
{
	;
}

template <typename MsgFunctor>
Writer<MsgFunctor>::~Writer() noexcept
{
	m_writeMsgFunctor.SetStopFlag();

	m_thread.Join();
}

template <typename MsgFunctor>
void Writer<MsgFunctor>::WriteMsg(MsgFunctor msg_)
{
	m_waitQ.Push(msg_);
}

template <typename MsgFunctor>
class WriteMsgFunctor : private Uncopyable
{
public:
    //Constructors
    explicit WriteMsgFunctor(WaitableQueue<std::queue<MsgFunctor> > &waitQ_);
    //~WriteMsgFunctor()noexcept = default;

    //Operators
	void operator()();

    //Functions
	void SetStopFlag();

private:
    //Member variables
	WaitableQueue<std::queue<MsgFunctor> > &m_waitQ;
	bool m_stopFlag;
};

template <typename MsgFunctor>
WriteMsgFunctor<MsgFunctor>::WriteMsgFunctor																   (WaitableQueue<std::queue<MsgFunctor> > &waitQ_)
	: m_waitQ(waitQ_), m_stopFlag(false)
{
	;
}

template <typename MsgFunctor>
void WriteMsgFunctor<MsgFunctor>::operator()() 
{
	while (!m_stopFlag)
	{
		MsgFunctor ret;

		if (m_waitQ.Pop(ret, static_cast<boost::chrono::milliseconds>(1000)))
		{
			ret();
		}
	}
}

template <typename MsgFunctor>
void WriteMsgFunctor<MsgFunctor>::SetStopFlag()
{
	m_stopFlag = true;
}

}//namespace ilrd

#endif  //ILRD_RD6768_WRITER
