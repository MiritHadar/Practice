/*
********************************************************************************

Developer : Mirit Hadar
Reviewer :
Last Update : 
Status :

********************************************************************************
*/

#ifndef __OL67_exception_ex1
#define __OL67_exception_ex1

#include <iostream>		/*	cout, runtime 	*/
#include <string>       /*  string          */

namespace ilrd
{

struct BadDog: public std::runtime_error
{
    BadDog(const std::string &s_ = "this is a bad dog")
        : std::runtime_error(s_)
    {
        ;
    }
};

void Fifi();
void Foo();
void Bar();

class A
{
public:
    A() { std::cout << "Ctor" << std::endl; }
    ~A() { std::cout << "Dtor" << std::endl; }
};

}//namespace ilrd



#endif /* __OL67_exception_ex1 */


