/*
********************************************************************************

Developer : Mirit Hadar
Revier :
Last Update : 
Status :

********************************************************************************
*/

#include <stdio.h>
#include "refer.hpp"

struct X
{
	void Foo();
	void Foo() const;
};

void X::Foo()
{
	printf("Foo\n");
}

void X::Foo() const
{
	printf("const Foo\n");
}

int main(void)
{
	X x1;
	X const x2;
	const X &x3 = x1;

	x1.Foo();
	x2.Foo();
	x3.Foo();

	return 0;
}

