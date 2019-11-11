/*
********************************************************************************

Developer : Mirit Hadar
Reviewer :
Last Update : 
Status :

********************************************************************************
*/
#include <iostream>
//#include "conversion.h"

using namespace std;

class A
{

};

class B
{
public:
	B(A& a_);
};

B::B(A& a_)
{
	cout << "copy" << endl;
}

void Foo(const double& d)
{
	cout << &d << " " << d << " Foo" << endl;
}

void Bar(double& d)
{
	cout << &d << " " << d << " Bar" << endl;
}

int main(void)
{
	/* A a;
	B b = static_cast<B>(a); */
	int i = 7;
	Foo(i);
	Bar(static_cast<double>(i));

	return 0;
}

