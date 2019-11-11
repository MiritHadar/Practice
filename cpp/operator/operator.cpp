/*
********************************************************************************

Developer : Mirit Hadar
Reviewer :
Last Update : 
Status :

********************************************************************************
*/

#include "operator.hpp"


int operator+(const X& x1_, const X& x2_)
{
    return int(x1_.GetValue() + x2_.GetValue());
}

void operator-(int b, const X& a_)
{
    printf("%d\n", b - a_.GetValue());
}