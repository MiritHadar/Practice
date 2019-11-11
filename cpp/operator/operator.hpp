/*
********************************************************************************

Developer : Mirit Hadar
Reviewer :
Last Update : 
Status :

********************************************************************************
*/

#ifndef __OL67_operator
#define __OL67_operator

#include <stdio.h>

class X
{
public:

    X(int a) : m_a(a) { }

    bool operator==(const X& o_) const { return m_a == o_.m_a; }

    int GetValue() const { return m_a; }
    
private:
    int m_a;
    
};

int operator+(const X& x1_, const X& x2_);
void operator-(int b, const X& a_);

#endif /* __OL67_operator */


