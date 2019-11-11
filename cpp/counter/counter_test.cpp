/*
********************************************************************************

Developer : Mirit Hadar
Reviewer :
Last Update : 
Status :

********************************************************************************
*/

#include <stdio.h>
#include "counter.hpp"

int main(void)
{
	StaticCounter x1;
	StaticCounter x2;

	x1.GetId();
	x2.GetId();
	x1.Print();

	StaticCounter::Print();

	return 0;
}

