/*
********************************************************************************

Developer : Mirit Hadar
Revier :
Last Update : 
Status :

********************************************************************************
*/
#include "const.hpp"

void X::Init(int a_)
{
    this;
    m_a = a_;
    m_p = &m_a;
}

void X::Foo()
{
    this;

    ++m_a;
    --(*m_p);
}

void X::Bar() const
{
    this;
    printf("%d\n", m_a);
    printf("%d\n", *m_p);
    printf("%d\n", m_p);
}

/* void X::Fifi(const X& x_)
{
    x_.Foo();
    x_.Bar();
} */






