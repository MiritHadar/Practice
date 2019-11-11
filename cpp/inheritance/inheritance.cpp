/*
********************************************************************************

Developer : Mirit Hadar
Reviewer :
Last Update : 
Status :

********************************************************************************
*/

#include "inheritance.hpp"

Base::Base(int a_)
        : m_a(a_)
{
    std::cout << "B::Ctor" << std::endl;
}

Base::~Base()
{
    std::cout << "B::Dtor" << std::endl;
}

void Base::Print1() const
{
    std::cout << "B::Print1 B::m_a - "<< m_a <<std::endl;
}

void Base::Print2() const
{
    std::cout << "B::Print2" <<std::endl;
}

void Base::Print3() const
{
    std::cout << "B::Print3"<<std::endl;
}

Derived::Derived()
    : m_b(0)
{
    std::cout << "X::Ctor" <<std::endl;
}

Derived::~Derived()
{
    std::cout << "X::Dtor" <<std::endl;
}

void Derived::Print1() const
{
    std::cout << "X::Print1 X::m_b - " << m_b <<std::endl;
    Base::Print1();
    std::cout << "X::Print1 end" <<std::endl;
}

void Derived::Print2() const
{
    std::cout << "X::Print2" <<std::endl;
}
