/*
********************************************************************************

Developer : Mirit Hadar
Revier :
Last Update : 
Status :

********************************************************************************
*/

#include "explicit.hpp"

X::X()
    : m_a(), m_b()
{
    printf("Default Ctor : %p, %d, %d\n", this, m_a, m_b);
     m_a = 8;
}

X::X(int a_, int b_)
    : m_a(a_), m_b(b_)
{
    printf("Ctor(int,int): %p, %d, %d\n", this, m_a, m_b);
}

X::X(const X& other_)
    : m_a(other_.m_a), m_b(other_.m_b)
    {
        printf("Copy Ctor: %p, %d, %d\n", this, m_a, m_b);
    }

X& X::operator=(const X& other_)
{
    m_a = other_.m_a;
    printf("Copy assingment: %p, %d, %d\n", this, m_a, m_b);

    return *this;
}

X::~X()
{
    printf("Dtor: %p, %d, %d\n", this, m_a, m_b);
}





