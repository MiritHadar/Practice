/*
********************************************************************************

Developer : Mirit Hadar
Reviewer :
Last Update : 
Status :

********************************************************************************
*/

#ifndef __OL67_try
#define __OL67_try

#include <iostream>

class A
{
public:
    //A() : m_a(0) { std::cout << "Ctor" << std::endl; }
    //A(A& other_) : m_a(other_.m_a) { std::cout << "CCtor" << std::endl; }
    //A& operator=(A& other_)
    //{  m_a = other_.m_a;
    //std::cout << "Assign CCtor" << std::endl; 
    //return *this; }

    //~A() { std::cout << "Dtor" << std::endl; }
private:
    int m_a;
};

class B : public A
{
private:
    //int m_b;
};

class C : public A
{

};

class D : virtual B, public C
{

};


#endif /* __OL67_try */


