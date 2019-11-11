/*
********************************************************************************

Developer : Mirit Hadar
Reviewer :
Last Update : 
Status :

********************************************************************************
*/

#ifndef __OL67_inheritance
#define __OL67_inheritance

#include <iostream>     /* I / O */

class Base
{
public:
    /*non explicit*/Base(int a_ = 8);
    virtual ~Base();

    virtual void Print1() const;
    virtual void Print2() const;
    virtual void Print3() const;

private:
    int m_a;
};

class Derived: public Base
{
public:
    Derived();
    ~Derived();
    void Print1() const;
    void Print2() const;

private:
    int m_b;
};

#endif /* __OL67_inheritance */