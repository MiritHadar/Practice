/*
********************************************************************************

Developer : Mirit Hadar
Reviewer :
Last Update : 
Status :

********************************************************************************
*/

#include "logMsg.hpp"

using namespace ilrd;

void MsgTest();

int main()
{
	MsgTest();

	return 0;
}

void MsgTest()
{
	LogMsg myMsg("hello\n", cerr);
	FuncPrintLogMsg()(myMsg);
}
