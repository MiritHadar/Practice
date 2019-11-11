/*
********************************************************************************

Developer : Mirit Hadar
Reviewer :
Last Update : 
Status :

********************************************************************************
*/

#include "exception_ex1.hpp"


using namespace std;

namespace ilrd
{
void Fifi()
{
    throw 10;
    cerr << "Fifi() after throw" << endl;
}

void Foo()
{
    A a;
    Fifi();
    cerr << "Foo() after Fifi()" << endl;
}

void Bar()
{
    Foo();
    cerr << "Bar() after Foo()" << endl;
}

}//namespace ilrd



