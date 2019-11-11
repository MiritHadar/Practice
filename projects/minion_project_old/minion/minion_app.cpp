/*
********************************************************************************

Developer : Mirit Hadar
Reviewer :
Last Update : 
Status :

********************************************************************************
*/

#include <cstdlib>		//atoi
#include "minion.hpp"

using namespace std;
using namespace ilrd;

Logger logger;

void InitLogger();

int main(int argc, char *argv[])
{
	InitLogger();
	Minion minion;
	cout << "minion made" << endl;
	minion.Run();

	return 0;
}

void InitLogger()
{
    logger.SetOutput(std::cerr);
    logger.SetOutputSeverity(Logger::SDEBUG);
}

