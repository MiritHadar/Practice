/*
********************************************************************************

Developer : Mirit Hadar
Revier :
Last Update : 
Status :

********************************************************************************
*/

#include <stdio.h>
#include <stdlib.h>

#include "explicit.hpp"

int main()
{
    Y *y1 = new Y[10];
	delete[] y1;

    /*X x2;
	X x3;

	printf("x1.m_a : %d\n", x1.m_a);
	printf("x1.m_b : %d\n", x1.m_b);

    X x2(7, 9);
    X x3(9, 10);
    X x4(x1);
	x3.m_a = 5;
	x3.m_b = 6;

	printf("x1.m_a : %d\n", x1.m_a);
	printf("x1.m_b : %d\n", x1.m_b);

	printf("%lu\n", sizeof(x1));
	printf("%lu\n", sizeof(x2));
	printf("%lu\n", sizeof(x4)); 

    x1 = x3;
 	printf("x1.m_a : %d\n", x1.m_a);
	printf("x1.m_b : %d\n", x1.m_b);
	printf("%lu\n", sizeof(x3));
	x1.~X();
	Y y1;
	y1.m_x.m_a = 250;
	y1.m_x.m_b = 750;
	Y y2(y1);
	Y y3;
 	y3 = y1;
 
	float *f = new float(12.6);
    delete f;

    f = new float[15];
    delete[] f;

    Counter *c1 = new Counter;
    X *x1 = new X;
    Y *y1 = new Y;
    delete y1;
    delete c1;
    delete x1;

	X *xp = new X[10];
	delete[] xp;

	int* ptr = (int*)malloc(1000 * sizeof(int));
	free(ptr);
	int *ptr2 = new int[1000];
	free(ptr2);*/
    return 0;
}
