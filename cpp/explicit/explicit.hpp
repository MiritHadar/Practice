/*
********************************************************************************

Developer : Mirit Hadar
Revier :
Last Update : 
Status :

********************************************************************************
*/

#ifndef __OL67_explicit
#define __OL67_explicit

#include <stdio.h>

struct X
{
    explicit X(); 
    explicit X(int a_, int b_);
    ~X();
    X(const X& other_);
    X& operator = (const X& other_);

    int m_a;
    int m_b = 80;
};

struct Y
{
    X m_x;
    int m_i;
};

struct Counter
{
    int m_a;
    int m_b;
};


#endif /* __OL67_explicit */