/*
********************************************************************************

Developer : Mirit Hadar
Reviewer :
Last Update : 
Status :

********************************************************************************
*/

#include "my_operator.hpp"


ostream& operator<<(ostream& os_, const X& x_)
{
    return os_ << x_.m_a;
}

ostream& operator<<(ostream& os_, const char &c_)
{
    return os_ << &c_;
}

X::X(int a)
    : m_a(a)
{}

int X::GetValue() const
{
    return m_a;
}



