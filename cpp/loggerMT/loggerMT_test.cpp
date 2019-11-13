/******************************************************************************/
/* author: 		Mirit Hadar											  	  */
/* Reviewer: 					       										  */
/* version: 	Draft			  		                                      */
/* Last update: 24-09-2019					                                  */
/******************************************************************************/

#include <iostream>
#include <fstream>
#include <boost/thread.hpp>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "loggerMT.hpp"

using namespace ilrd;
using namespace boost;

/***************************| Function declares |******************************/

void PrintFast(LoggerMT *logger_, int number_);

/*****************************| main function |********************************/

int main()
{
	LoggerMT test_logger;

	test_logger.SetOutputSeverity(LoggerMT::SDEBUG);

	std::ofstream test_log_file;

	test_log_file.open("test_log_file.txt");

	test_logger.SetOutput(test_log_file);

	for (size_t i = 0; i < 10; ++i)
	{
		thread print_fast(PrintFast, &test_logger, i);

		print_fast.detach();
	}

	sleep(1); // TODO : lower

	test_log_file.close();

	return 0;
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

		(logger_)->Log(LoggerMT::ERROR, num_as_char);
	}

	delete num_as_char;
}
