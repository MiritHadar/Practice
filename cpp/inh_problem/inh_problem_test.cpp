/*
********************************************************************************

Developer : Mirit Hadar
Reviewer :
Last Update : 
Status :

********************************************************************************
*/

#include <iostream>			/*	cout 	*/

#include "inheritance.hpp"	/*	Header file		*/

using namespace ilrd;

void Foo(X x)
{
    std::cout << "Foo" << std::endl;
}

int main(void)
{

    Y y1(0.0, 0), y2(14.2, 5);
    Y y3(0.0, 0), y4(14.2, 5);

    X& x1 = y1;
    X& x2 = y2;

    x1 = x2;
    y3 = y4;

	return 0;
}

