/*
********************************************************************************

Developer : Mirit Hadar
Reviewer :
Last Update : 
Status :

********************************************************************************
*/

#include <cstdlib>		//atoi
#include "server.hpp"

using namespace ilrd;
using namespace std;

Logger myLogger;
Logger::Severity loggerSeverity;

const size_t MSG_SIZE = 10;

int main(int argc, char *argv[])
{
	UDPServer us;

	char msgToSend[] = "sending...";
	char msgReceived[] = "received";

	while (1)
	{
		us.Receive(msgReceived, MSG_SIZE);
		cout << msgReceived << endl;
		us.Send(msgToSend, MSG_SIZE);
	}

	return 0;
}

