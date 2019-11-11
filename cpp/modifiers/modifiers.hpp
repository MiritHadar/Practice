/*
********************************************************************************

Developer : Mirit Hadar
Reviewer :
Last Update : 
Status :

********************************************************************************
*/

#ifndef __OL67_modifiers
#define __OL67_modifiers

#include <stdio.h>

class X
{
public:
    explicit X();
    explicit X(int a_);
    void Foo();
    void AccessPrivate();

    mutable int m_a;
};

void Foo(const X &x1);
void AccessMutable(const X &x1);

#endif /* __OL67_modifiers */


