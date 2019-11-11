/*
********************************************************************************

Developer : Mirit Hadar
Reviewer :
Last Update : 
Status :

********************************************************************************
*/

#include <iostream>			/* cout */
#include "shared_ptr.hpp"
#include <cstring>

using namespace std;
using namespace ilrd;

class DOB
{
public:
	int m_day;
	int m_month;
	int m_year;
};

class Person
{
public:
	int m_age;
	DOB m_dob;
};

class Base
{
public:
	int m_base;
};

class Derived : public Base
{
public:
	int m_drv;
};

void PrintInt(SharedPtr<int> i)
{
	cout << *i << endl;
}

void PrintBase(SharedPtr<Base> b)
{
	cout << b->m_base << endl;
}

void IntTest();
void ClassTest();
void DeriveTest();
void ConstTest();

int main(void)
{
	IntTest();
	ClassTest();
 	DeriveTest();
	ConstTest();

	return 0;
}

void IntTest()
{
	SharedPtr<int>i(new int(10));
	SharedPtr<int>j(new int(12));
	*i = 6;
	*j = 7;

	if (6 != *i)
	{
		cout << "fail line : " << __LINE__;
	}

	if (6 != *(i.GetRawPtr()))
	{
		cout << "fail line : " << __LINE__;
	}

	i = i;
	i = j;

	if (7 != *j)
	{
		cout << "fail line : " << __LINE__;
	}

 	SharedPtr<int>k(j);
	if (7 != *k)
	{
		cout << "fail line : " << __LINE__;
	}
}

void ClassTest()
{
	SharedPtr<Person>p(new Person);
	p->m_age = 20;
	//SharedPtr<DOB>d(p);
}

void DeriveTest()
{
	SharedPtr<Derived>drv(new Derived);
	const SharedPtr<Base>base1(drv);
	SharedPtr<Base>base2 = drv;
	base2->m_base = 2;

	base2 = base2;
	base2 = base1;
}

void ConstTest()
{
	SharedPtr<Base>c_base(new Base);
	SharedPtr<const Base>base(new Base);

	base = c_base;
	SharedPtr<Base>second_base(c_base);
}



