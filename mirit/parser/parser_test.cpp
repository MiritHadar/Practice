/******************************************************************************/
/* Author: 		Mirit Hadar											  	      */
/* Version: 	Final			  		                                      */
/* Last update: 22-01-2020						                              */
/******************************************************************************/

#include <iostream>			//	cout 	

#include "parser.hpp"		//	Header file		

using namespace std;
using namespace l1ght;

const char myFile[] = "test.txt";
const char wrongFile[] = "wrong";

void FileTest();

int main()
{
	FileTest();

	return 0;
}

void FileTest()
{
	Parser p;
	vector<string> vec = p.Parse(myFile);
	for (vector<string>::iterator it = vec.begin(); it != vec.end(); ++it)
	{
		cout << ' ' << *it << endl;
	}
    //Parser::Parse(wrongFile);
}
