/*
********************************************************************************

Developer : Mirit Hadar
Reviewer :
Last Update : 
Status :

********************************************************************************
*/

#include "writer.hpp"

using namespace std;
using namespace ilrd;

void WriterTest();

int main()
{
	WriterTest();
	return 0;
}

void WriterTest()
{
	Writer write;
	LogMsg log;
	write.PushMsg(log);
}


