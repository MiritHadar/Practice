/*
********************************************************************************

Developer : Mirit Hadar
Reviewer :
Last Update : 
Status :

********************************************************************************
*/

#include "thread_pool.hpp"

using namespace ilrd;
using namespace details;

void Print1()
{
	std::cout << "First Func" << std::endl;
}

void Print2()
{
	std::cout << "Second Func" << std::endl;
}

void Print3()
{
	std::cout << "Third Func" << std::endl;
}

void Print4()
{
	std::cout << "Forth Func" << std::endl;
}

class Costumer : public GenericBase
{
public:
	void operator()()
	{
		std::cout << "Costumers class" << std::endl;
	}
};

void TestWithFunctor();
void TestWithSp();

int main()
{
	TestWithSp();
	return 0;
}

void TestWithSp()
{
	ThreadPool pool(2);
	pool.AddTask(new Costumer);
	pool.AddTask(new Costumer);
	pool.AddTask(new Costumer);
	
	sleep(1);
}
