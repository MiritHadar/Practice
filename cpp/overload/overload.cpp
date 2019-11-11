/*
********************************************************************************

Developer : Mirit Hadar
Revier :
Last Update : 
Status :

********************************************************************************
*/

#include "overload.hpp"

typedef void (*func_t)(void);

void Foo()
{
    puts("I receive void");
}

void Foo(int i)
{
    puts("I receive int");
}

void Foo(char c)
{
    puts("I receive char");
}





