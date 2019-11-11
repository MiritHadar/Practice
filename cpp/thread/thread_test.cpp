/*
********************************************************************************

Developer : Mirit Hadar
Reviewer :
Last Update : 
Status :

********************************************************************************
*/

#include <unistd.h>		/* sleep */

#include "thread.hpp"

namespace ilrd
{
class FromUser
{
public:
	void PrintUser() { std::cout << "This is the class from the user" << std::endl; }
	void OtherFunc() { std::cout << "Don't print me out" << std::endl; }
};
}

using namespace std;
using namespace ilrd;

void BaseTest();
void PrintHello();
void FunctorTest();
void MemberFuncTest();

int main(void)
{
	//BaseTest();
	//FunctorTest();
	MemberFuncTest();

	return 0;
}

void BaseTest()
{	
	try
	{
		Thread t1(PrintHello);
		Thread t2(PrintHello);
		Thread t3(PrintHello);
		Thread t4(PrintHello);
		Thread t5(PrintHello);
		Thread t6(PrintHello);

		sleep(3);
		
		t1.Join();
		t2.Join();
		t3.Join();
		t4.Join();
		t5.Join();
		t6.Join();
	}
	catch(Thread_error &error)
	{
    	cout << error.what() << endl;	
	}
}

void PrintHello()
{
	cout << "Hello World!" << endl;
	sleep(1);
}

void FunctorTest()
{
	try
	{
		Functor f1;
		Functor f2;
		Functor f3;
		Functor f4;

		Thread functor_thread1(f1);
		Thread functor_thread2(f2);
		Thread functor_thread3(f3);
		Thread functor_thread4(f4);

		functor_thread1.Join();
		functor_thread2.Join();
		functor_thread3.Join();
		functor_thread4.Join();
	}
	catch(Thread_error &error)
	{
		cout << error.what() << endl;	
	}
}

void MemberFuncTest()
{
	try
	{
		FromUser fu1;
		FromUser fu2;
		FromUser fu3;
		FromUser fu4;

		Thread memberFuncThread1(fu1, &FromUser::PrintUser);
		Thread memberFuncThread2(fu2, &FromUser::PrintUser);
		Thread memberFuncThread3(fu3, &FromUser::PrintUser);
		Thread memberFuncThread4(fu4, &FromUser::PrintUser);

		memberFuncThread1.Join();
		memberFuncThread2.Join();
		memberFuncThread3.Join();
		memberFuncThread4.Join();
	}
	catch(Thread_error &error)
	{
		cout << error.what() << endl;	
	}
}