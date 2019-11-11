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

//glob func
void Inc()
{
	printf("global function\n");
}

void Foo()
{
    puts("Foo void");
}

void Foo(int i)
{
    puts("Foo int");
}

void Foo(char c)
{
    puts("Foo char");
}

int Inc_int()
{
	printf("global function\n");
    return 0;
}

float Inc_float()
{
    return 0;
}


Counter &Counter::Inc()
{
    ++m_a;
    m_b += 2;

    return *this;
}

void Counter::Dec()
{
    --m_a;
    m_b /= 2;
}

void Counter::Test()
{
}

void Counter::Inc(unsigned int delta)
{
    m_b += delta;
}



