/******************************************************************************/
/* author: 		Mirit Hadar											  	      */
/* Reviewer: 					       										  */
/* version: 	Final			  		                                      */
/* Last update: 04-11-2019					                                  */
/******************************************************************************/

#ifndef ILRD_RD6768_DISPATCHER
#define ILRD_RD6768_DISPATCHER

#if __cplusplus < 201103L
#define nullptr NULL
#define noexcept throw()
#endif

#include <boost/function.hpp>	// 	boost::function
#include <vector>				// 	vector

#include "uncopyable.hpp"		// 	For inaccessible CCtor and assign operator

namespace ilrd
{

template <typename DATA, typename SUBJECT>
class Dispatcher : private Uncopyable
{
public:

	class CallBack : private Uncopyable
	{
		typedef boost::function<void(DATA)>CBFunc;
		friend class Dispatcher;

	public:
		//Constructors
		explicit CallBack(CBFunc cbFunc_, SUBJECT *subject_);
		~CallBack() noexcept;

	private:
		void Update(const DATA &event_);
		CBFunc m_cbFunc;
		SUBJECT *m_subject;
	};

    //Constructors
    //explicit Dispatcher() = default;
    ~Dispatcher() noexcept;

    //Operators

    //Functions
	void Register(CallBack *cb_);
	void Unregister(CallBack *cb_);
	void Notify(const DATA &event_);

private:
    //Member variables
	std::vector<CallBack*> m_callbacks;
};

template <typename DATA, typename SUBJECT>
Dispatcher<DATA, SUBJECT>::CallBack::CallBack(CBFunc cbFunc_, SUBJECT *subject_)
	: m_cbFunc(cbFunc_), m_subject(subject_)
{
	m_subject->Register(this);
}

template <typename DATA, typename SUBJECT>
Dispatcher<DATA, SUBJECT>::CallBack::~CallBack() noexcept
{
	m_subject->Unregister(this);
}

template <typename DATA, typename SUBJECT>
void Dispatcher<DATA, SUBJECT>::CallBack::Update(const DATA &event_)
{
	m_cbFunc(event_);
}

template <typename DATA, typename SUBJECT>
void Dispatcher<DATA, SUBJECT>::Register(CallBack *cb_)
{
	m_callbacks.push_back(cb_);
}

template <typename DATA, typename SUBJECT>
void Dispatcher<DATA, SUBJECT>::Unregister(CallBack *cb_)
{
	m_callbacks.remove_if();//TODO: implement
}

template <typename DATA, typename SUBJECT>
void Dispatcher<DATA, SUBJECT>::Notify(const DATA &event_)
{
	m_callbacks.foreach();//TODO: implement
}

}//namespace ilrd

#endif  //ILRD_RD6768_DISPATCHER
