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
void TmpTest();

const char myFile[] = "test.txt";
const char tmpFile[] = "tmp.txt";
const char wrongFile[] = "wrong";

int main()
{
	//BasicTest();
	TmpTest();

	return 0;
}

void BasicTest()
{
	Calculator calc;
	calc.Calculate(myFile);
}

void TmpTest()
{
	Calculator calc;
	calc.Calculate(tmpFile);
}

