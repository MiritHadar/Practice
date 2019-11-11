/*
********************************************************************************

Developer : Mirit Hadar
Reviewer :
Last Update : 
Status :

********************************************************************************
*/

#include <stdio.h>
#include "overload_template.hpp"


template<typename T>
void foo(T t)
{
    std::cout << t << " Generic foo\n";
}

void foo(int t)
{
    std::cout << t << " Specialized foo (for int param)\n";
}


int main(void)
{
	foo(5);
	foo<int>(5);

	return 0;
}

