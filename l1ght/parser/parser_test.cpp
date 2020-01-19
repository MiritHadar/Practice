/******************************************************************************/
/* author: 		Mirit Hadar											  	  */
/* version: 	Final			  		                                      */
/* Last update: 				                                  */
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
	Parser::Parse(myFile);
	Parser::Parse(wrongFile);

	//cout << "FileTest" << endl;
}
