/******************************************************************************/
/* Author: 		Mirit Hadar											  	      */
/* Version: 	Final			  		                                      */
/* Last update: 22-01-2020						                              */
/******************************************************************************/

#include <iostream>				// cout 	
#include <stdlib.h>				// ftoa

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
	// ExceptionTest();
	// PlusMinusTest();
	// MultiplyTest();
	// DivisionTest();
	// IntegrationTest();

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
	vector<double> divisionExpectedResult = {13, 1, 24, 0, 198, 60};
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
	vector<int> integrationExpectedResult = {231, 3, 20, 419, 1180, 46};
	vector<double> results = calc.Calculate(integrationFile);
	for(size_t i = 0; i < results.size(); ++i)
	{
		if (static_cast<int>(results[i]) != integrationExpectedResult[i])
		{
			cout << "error at line " << __LINE__ << " at i = " << i << " result = " << results[i] << endl;
		}
	}
}


