/*
********************************************************************************

Developer : Mirit Hadar
Reviewer :
Last Update : 
Status :

********************************************************************************
*/

#include <queue>
#include "waitable_queue.hpp"

using namespace std;
using namespace ilrd;

void BasicTest();
void ThreadTest();
void PushToQ();
void PopFromQ();

static WaitableQueue<queue <size_t> > g_wq;
static size_t g_counter = 0;

const int SIZE1 = 5;

int main(void)
{
	//BasicTest();
	ThreadTest();

	return 0;
}

void BasicTest()
{
	int arr[] = {1, 2, 3, 4, 5};
	WaitableQueue<queue <int> >wq;

	for (int i = 0; i < SIZE1; ++i)
	{
		wq.Push(arr[i]);
	}

	for (int i = 0; i < (SIZE1 + 1) ; ++i)
	{
		wq.Pop(arr[i]);
	}
}

void ThreadTest()
{
	boost::thread t_pop1(PopFromQ);
	//sleep(2);

	boost::thread t_push1(PushToQ);
	boost::thread t_push2(PushToQ);
	boost::thread t_push3(PushToQ);
	boost::thread t_push4(PushToQ);
	boost::thread t_push5(PushToQ);

	t_push1.join();
	t_push2.join();
	t_push3.join();
	t_push4.join();
	t_push5.join();
}

void PushToQ()
{
	g_wq.Push(++g_counter);
	cout << "push: " << g_counter << endl;
}

void PopFromQ()
{
	size_t out_ = 0;
	boost::chrono::milliseconds timeout_(3000);

	if (0 != g_wq.Pop(out_, timeout_))
	{
		cout << "pop: " << out_ << endl;
	}
	else
	{
		cout << "timeout" << endl;
	}
}