/*
********************************************************************************

Developer : Mirit Hadar
Revier :
Last Update : 
Status :

********************************************************************************
*/

using namespace std;
#include <stdio.h>
#include <iostream>
#include "foo.hpp"

int main(void)
{
    float *f = new float(12.6);
    delete f;

    f = new float[15];
    delete[] f;

    Counter *c1 = new Counter;
    X *x1 = new X;
    Y *y1 = new Y;

    delete x1;
    delete c1;
    delete y1;

    X* xp = new X[10];
    delete xp;
    
    /*Counter x1;
    x1.m_a = 7;
    x1.Inc().Inc().Inc();
    printf("%d\n", x1.m_a);

	 Counter x1;
    Counter x2;

    Foo('k');

    x1.m_a = 7;
    x1.m_b = 0;

    x2.m_a = 0;
    x2.m_b = 16;

    x1.Inc();
    x1.Inc();
    x2.Dec();
    x2.Inc(4);

    printf("\nx1: \n");
    printf("x1.m_a : %d\n", x1.m_a);
    printf("x1.m_b : %d\n", x1.m_b);

    printf("\nx2: \n");
    printf("x2.m_a : %d\n", x2.m_a);
    printf("x2.m_a : %d\n", x2.m_b);

	printf("size of x1 : %lu\n", sizeof(x1));
	printf("size of x2 : %lu\n", sizeof(x2));

	Inc(); */

	return 0;
}


