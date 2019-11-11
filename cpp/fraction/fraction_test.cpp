/*
********************************************************************************

Developer : Mirit Hadar
Reviewer :
Last Update : 
Status :

********************************************************************************
*/

#include <stdio.h>
#include "fraction.hpp"

using namespace ilrd;
using namespace std;

void DoublePlusMinus();
void IsEqual();
void AssignToMe();
void FinalTest();
void CombinedTest();
void CounterTest();
void ImpConvert();

int main(void)
{
	//DoublePlusMinus();
	//IsEqual();
	//AssignToMe();
	//CombinedTest();
	//FinalTest();
	//CounterTest();
	ImpConvert();

	return 0;
}

void DoublePlusMinus()
{
	Fraction f10(1,2);
	Fraction f11 = f10;
	Fraction f12;

	f12 = ++f10 + ++f11;
	f12.Print();

	f12 = f10++ + f11++;
	f12.Print();

	f12 = f10 - f11;
	f12.Print();
}

void IsEqual()
{
	Fraction f1(3, 0);
	Fraction f2(3, 1);

	if (f1 == f2)
	{
		printf("failed %d\n", __LINE__);
	}
	if (f2 == 4)
	{
		printf("failed %d\n", __LINE__);
	}
}

void AssignToMe()
{
	Fraction f1(1, 2);
	Fraction f2(1, 2);
	Fraction f3(1, 2);

	f1 = f2 + f3;
	if (f1 != 1)
	{
		printf("failed %d\n", __LINE__);
	}
}

void CombinedTest()
{
	Fraction f1(1,2), f2(3, 4), f3(1, 4), f4;

	if (f2 - f1 != f3)
	{
		printf("failed %d\n", __LINE__);
	}

	f4 = -f3;

	if (f4 != -(f2 - f1))
	{
		printf("failed %d\n", __LINE__);
	}

	f4 = +f3;

	if (f4 != -(f2 - f1))
	{
		printf("failed %d\n", __LINE__);
	}

	f4 = ++f1;
	
	if (f1 != f4)
	{
		printf("failed %d\n", __LINE__);
	}

	f4 = f1++;
	f1.Print();
	f4.Print();
	if (f1 != f4 + 1)
	{
		printf("failed %d\n", __LINE__);
	}

	if (--f1 != f4)
	{
		printf("failed %d\n", __LINE__);
	}

}

void FinalTest()
{
	Fraction f1(1,2), f2(3, 4), f3, f4;

	f3 = +f1 + -(++f2);
	f4 = (f1++) - +(f2--);
	f1.Print();
	f2.Print();
	f3.Print();
	f4.Print();
}

void CounterTest()
{
	Fraction f1, f2;
	Fraction f3 = f2;
	Fraction::PrintCntr();
	std::cout << f1;
	std::cout << f3;
}

void ImpConvert()
{
	Fraction f1(4);
	Fraction f2(5);
	//std::cout << f1;
	//std::cout << ConvToInt(f1) << endl;
	//printf("res = %d\n", (f1 + 3));
	printf("res = %d\n", ((3) - f1));
}



