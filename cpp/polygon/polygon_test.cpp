/*
********************************************************************************

Developer : Mirit Hadar
Reviewer :
Last Update : 
Status :

********************************************************************************
*/

#include <stdio.h>
#include "polygon.hpp"



int main(void)
{
	puts("polygon test");
    Polygon p1(10);
	Polygon p2(p1);
	Counter c1;
	c1.m_a = 7;
	c1.m_b = 3;

	p1.Add(c1);
	p1.Print();
	p2.Print();

	if (p1.IsEqual(p2))
	{
		puts("test failed");
	}

	return 0;
}

