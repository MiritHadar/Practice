/*
********************************************************************************

Developer : Mirit Hadar
Reviewer :
Last Update : 
Status :

********************************************************************************
*/
#include <iostream>         // cout, endl
#include <string>           // string

#include "reactor.hpp"      // Reactor

using namespace std;
using namespace ilrd;

Logger logger;

void IoTest();
void UdpTest();

struct iosreams
{
public:
	static const int stdin = 0;
	static const int stdout = 1;
	static const int stderr = 2;
};

struct PrintHello
{
	void operator()()
	{
		cout << "Hello World!" << endl;
		sleep(3);
	}
};

struct StopReactor
{
public:
	explicit StopReactor(Reactor &reactor_)
		:m_reactor(reactor_) {}

	void operator()()
	{	
		string command;
        cin >> command;

		if ("stop" == command)
		{
			m_reactor.Stop();
		}
	}

private:
	Reactor &m_reactor;
};

int main()
{
	IoTest();
	//UdpTest();

	return 0;
}

void IoTest()
{
	Reactor react;
	react.AddFd(iosreams::stdout, FdListener::WRITE, PrintHello());
	react.AddFd(iosreams::stdin, FdListener::READ, StopReactor(react));

	react.Run();
}

void UdpTest()
{

}
