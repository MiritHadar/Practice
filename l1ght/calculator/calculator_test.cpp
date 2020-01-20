/******************************************************************************/
/* author: 		Mirit Hadar											  	      */
/* version: 	Final			  		                                      */
/* Last update: 							                                  */
/******************************************************************************/

#include <iostream>				//	cout 	

#include "calculator.hpp"		//	Header file		

using namespace std;
using namespace l1ght;

void BasicTest();

const char myFile[] = "test.txt";
const char wrongFile[] = "wrong";

int main()
{
	BasicTest();

	return 0;
}

void BasicTest()
{
	Calculator::Calculate(myFile);
}
