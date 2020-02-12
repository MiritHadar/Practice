/******************************************************************************/
/* author: 		Mirit Hadar											  	      */
/* Reviewer: 					       										  */
/* version: 	Final			  		                                      */
/* Last update: 23-10-2019					                                  */
/******************************************************************************/

#include <iostream>			//	cout 	

#include "reactor.hpp"		//	Header file		

using namespace std;
using namespace ilrd;

/*************************Test functions***************************************/
void TestInvalidFDException();
void TestAdd();
void TestAddAndRemove();
/******************************************************************************/

/*************************Helper functions*************************************/
void Foo();
void Bar();

/******************************************************************************/

class StopReactor
{
public:
	explicit StopReactor(Reactor &reactor_)
		:m_reactor(reactor_)
	{

	}

	void operator()()
	{	
		sleep(2);
		m_reactor.Stop();
	}

private:
	Reactor &m_reactor;
};

int main()
{
	//TestInvalidFDException();
	//TestAdd();
	TestAddAndRemove();

	return 0;
}

/******************************************************************************/
void TestInvalidFDException()
{
	Reactor r;

	r.AddFD(-1, FDListener::READ, NULL);
}

void TestAdd()
{
	Reactor reactor;

	reactor.AddFD(2, FDListener::WRITE, Foo);
	reactor.AddFD(10, FDListener::WRITE, Bar);
	reactor.AddFD(1, FDListener::READ, StopReactor(reactor));

	reactor.Run();
}

void TestAddAndRemove()
{
	Reactor reactor;

	reactor.AddFD(2, FDListener::WRITE, Foo);
	reactor.AddFD(10, FDListener::WRITE, Bar);
	reactor.AddFD(1, FDListener::READ, StopReactor(reactor));
	reactor.RemoveFD(2, FDListener::WRITE);

	reactor.Run();	
}

void Foo()
{
	sleep(1);
	cout << "FOO" << endl;
}


void Bar()
{
	sleep(1);
	cout << "BAR" << endl;
}







