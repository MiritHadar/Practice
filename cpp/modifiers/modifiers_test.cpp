/*
********************************************************************************

Developer : Mirit Hadar
Reviewer :
Last Update : 
Status :

********************************************************************************
*/

#include <stdio.h>
#include "modifiers.hpp"

int main(void)
{
	X x1;

	x1.Foo();
	x1.AccessPrivate();
	Foo(x1);
	AccessMutable(x1);
	
	return 0;
}

