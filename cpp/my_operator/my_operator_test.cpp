/*
********************************************************************************

Developer : Mirit Hadar
Reviewer :
Last Update : 
Status :

********************************************************************************
*/

#include "my_operator.hpp"



int main(void)
{
	X x1(1);
	X x2(0);
	int i = 1;
	double d = 3.14;
	char c = 'Y';

	cout
		<< "x1:" << x1
		<< " x2:" << x2
		<< " " << i << " " << &i
		<< " " << d << " " << &d
		<< " " << c << endl;

	return 0;
}



