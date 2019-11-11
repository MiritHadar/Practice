/*
********************************************************************************

Developer : Mirit Hadar
Reviewer :
Last Update : 
Status :

********************************************************************************
*/

#include <stdio.h>
#include <sstream>		/* ostringstream */

#include "logging.hpp"

using namespace ilrd;

int main(void)
{
	ostringstream def_str;
	const char *error = "big error!";
	const char *info = "info";
	const char *dbg = "debug";
	const char *warning = "warning!";

	/*auto test*/
	Logger myLog;
	myLog.SetOutputSeverity(myLog.WARNING);

	myLog.SetOutput(def_str);
	myLog.Log(myLog.ERROR, error);
	myLog.Log(myLog.INFO, info);
	myLog.Log(myLog.SDEBUG, dbg);

	ostringstream cmp_str;
	cmp_str << error << endl;

	if (def_str.str() != cmp_str.str())
	{
		cout << "failed myLog\n";
	}

	/*file test*/
	Logger logToFile;
	ofstream myFile;
	myFile.open("a.log");
	
	logToFile.SetOutputSeverity(logToFile.SDEBUG);
	logToFile.SetOutput(myFile);

	logToFile.Log(logToFile.ERROR, error);
	logToFile.Log(logToFile.WARNING, warning);
	logToFile.Log(logToFile.INFO, info);
	logToFile.Log(logToFile.SDEBUG, dbg);

	cmp_str << error << endl << warning << endl << info << dbg << endl;

	cout << ifstream("a.log").rdbuf();

	return 0;
}

