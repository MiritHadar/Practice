/******************************************************************************/
/* Author: 		    Mirit Hadar											  	  */
/* Version: 	    Final			  		                                  */
/* Last update:     22-01-2020						                          */
/******************************************************************************/

#include <iostream>				// cout

#include "calculator.hpp"		// header file		

using namespace std;
using namespace mirit;

void Test(char *filename_);

int main(int argc, char *argv[])
{
	if (argc < 2)
	{
		cout << "No file name supplied" << endl;

		return 1;
	}

	Test(argv[1]);

	return 0;
}

void Test(char *filename_)
{
	Calculator calc;

	vector<double> results = calc.Calculate(filename_);
	cout << "Results of calculating expressions from " << filename_ << ":" << endl;
	for(size_t i = 0; i < results.size(); ++i)
	{
		cout << results[i] << endl;
	}
}