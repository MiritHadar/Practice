/*
********************************************************************************

Developer : Mirit Hadar
Reviewer :
Last Update : 
Status :

********************************************************************************
*/

#include <iostream>
#include <mutex>

#include "scope_guard.hpp"
#include "scope_lock.hpp"
#include "mutex.hpp"

namespace ilrd
{

class X
{
public:
    explicit X() : m_start(false) {;}
	void Start() { m_start = true; }
	void End() { m_start = false; }
	bool GetStart() { return m_start; }
private:
	bool m_start;
};

} // namespace ilrd

using namespace std;
using namespace ilrd;

void LockTest();
void MutexTest();
void GuardTest();

int main(void)
{
	//LockTest();
	//MutexTest();
	GuardTest();

	return 0;
}

void LockTest()
{
	mutex mut;
	ScopeLock<mutex>sl(mut);
	
	//trying to lock the locked mutex - should fail
	if (mut.try_lock())
	{
		cout << "failed Ctor" << endl;
	}

	sl.~ScopeLock();
	//trying to lock the open mutex - should succeed
	if (!mut.try_lock())
	{
		cout << "failed Dtor" << endl;
	}
}

void MutexTest()
{
	Mutex myMutex;
	ScopeLock<Mutex>slMyMut(myMutex);

	if (0 == myMutex.IsLocked())
	{
		cout << "failed Ctor" << endl;
	}

	slMyMut.~ScopeLock();

	if (1 == myMutex.IsLocked())
	{
		cout << "failed Dtor" << endl;
	}
}

void GuardTest()
{
	X x1;
	{
		ScopeGuard<X> sgX (x1, &X::Start, &X::End);
		if (true != x1.GetStart())
		{
			cout << "failed start" << endl;
		}
	}

	if (0 != x1.GetStart())
	{
		cout << "failed end" << endl;
	}

	Mutex m1;
	{
		ScopeGuard<Mutex> sgm (m1, &Mutex::lock, &Mutex::unlock);
		if (1 != m1.IsLocked())
		{
			cout << "failed lock" << endl;
		}
	}
	if (0 != m1.IsLocked())
	{
		cout << "failed unlock" << endl;
	}
}

