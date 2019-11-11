/*
********************************************************************************

Developer : Mirit Hadar
Reviewer :
Last Update : 
Status :

********************************************************************************
*/

#include "modifiers.hpp"

X::X()
    : m_a()
{
}

X::X(int a_)
    : m_a(a_)
{
}

void X::Foo()
{
    printf("from the class: %d\n", m_a);
}

void X::AccessPrivate()
{
    printf("AccessPrivate : %d\n", m_a);
}

void Foo(const X &x1)
{
    (X(x1)).AccessPrivate();
}

void AccessMutable(const X &x1)
{
    printf("before mutation : %d\n", x1.m_a);
    x1.m_a = 8;
    printf("after mutation : %d\n", x1.m_a);
}





