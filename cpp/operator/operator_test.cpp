/*
********************************************************************************

Developer : Mirit Hadar
Reviewer :
Last Update : 
Status :

********************************************************************************
*/

#include <stdio.h>
#include "operator.hpp"

class X;



int main(void)
{
	X x1(3);
	X x2(6);

	printf("x1 + x2: %d\n", X(x1 + x2).GetValue());
	printf("x1 == x2: %d\n", (x1 == x2));
	10 - x1;

	return 0;
}

