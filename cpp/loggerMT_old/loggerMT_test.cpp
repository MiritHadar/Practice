/*
********************************************************************************

Developer : Mirit Hadar
Reviewer :
Last Update : 
Status :

********************************************************************************
*/
#include <string>
#include <iostream>
#include <fstream>     
#include "loggerMT.hpp"

using namespace std;
using namespace ilrd;
using namespace boost;

void PrintFast(LoggerMT *logger_, int number_);
void FileTest();
void SingleThread();

int main()
{
	//SingleThread();
	FileTest();

	return 0;
}

void SingleThread()
{
	LoggerMT myLogger(cout, ERROR);
	myLogger.Log("run a msg", ERROR);
	sleep(1);
	myLogger.SetOutput(cerr);
	myLogger.SetSeverity(WARNING);
}

void FileTest()
{
	LoggerMT test_logger;

	test_logger.SetSeverity(SDEBUG);

	std::ofstream test_log_file;

	test_log_file.open("test_log_file.txt");

	test_logger.SetOutput(test_log_file);

	for (size_t i = 0; i < 10; ++i)
	{
		thread print_fast(PrintFast, &test_logger, i);

		print_fast.detach();
	}

	sleep(1);

	test_log_file.close();
}

/******************************************************************************/

void PrintFast(LoggerMT *logger_, int number_)
{
	char *num_as_char = new char[10];

	memset(num_as_char, 0, 10);

	for (int i = 0; i < 10; ++i)
	{
		int bytes_written = sprintf(num_as_char, "%d", (i + number_ * 10));

		num_as_char[bytes_written] = '\n';

		(logger_)->Log(num_as_char, ERROR);
	}

	delete num_as_char;
}



