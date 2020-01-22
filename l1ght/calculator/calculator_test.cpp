/******************************************************************************/
/* author: 		Mirit Hadar											  	      */
/* version: 	Final			  		                                      */
/* Last update: 							                                  */
/******************************************************************************/

#include <iostream>				//	cout 	

#include "calculator.hpp"		//	Header file		

using namespace std;
using namespace l1ght;

void ExceptionTest();
void PlusMinusTest();
void MultiplyTest();
void DivisionTest();
void IntegrationTest();

const char wrongFile[] = "wrong";
const char multiDigitFile[] = "multi_digit_nums.txt";
const char multiplyFile[] = "multiply.txt";
const char divisionFile[] = "division_ad.txt";
const char integrationFile[] = "all_arithmetics.txt";

int main()
{
	//ExceptionTest();
	//PlusMinusTest();
	//MultiplyTest();
	//DivisionTest();
	IntegrationTest();

	return 0;
}

void ExceptionTest()
{
	Calculator calc;
	calc.Calculate(wrongFile);
}


void MultiplyTest()
{
	Calculator calc;
	vector<double> multiplyExpectedResults = {31, 87, 98, 170, 47149};
	vector<double> results = calc.Calculate(multiplyFile);
	for(size_t i = 0; i < results.size(); ++i)
	{
		if (results[i] != multiplyExpectedResults[i])
		{
			cout << "error at line " << __LINE__ << " at i = " << i << endl;
		}
	}
}

void PlusMinusTest()
{
	Calculator calc;
	vector<double> multiDigitExpectedResult = {1, 28, 28, 1001, 661};
	vector<double> results = calc.Calculate(multiDigitFile);
	for(size_t i = 0; i < results.size(); ++i)
	{
		if (results[i] != multiDigitExpectedResult[i])
		{
			cout << "error at line " << __LINE__ << " at i = " << i << endl;
		}
	}
}

void DivisionTest()
{
	Calculator calc;
	vector<int> divisionExpectedResult = {13, 1, 24, 0, 198, 60};
	vector<double> results = calc.Calculate(divisionFile);
	for(size_t i = 0; i < results.size(); ++i)
	{
		if (static_cast<int>(results[i]) != divisionExpectedResult[i])
		{
			cout << "error at line " << __LINE__ << " at i = " << i << " result = " << results[i] << endl;
		}
	}
}

void IntegrationTest()
{
	Calculator calc;
	vector<double> integrationExpectedResult = {};
	vector<double> results = calc.Calculate(integrationFile);
}


