/*
********************************************************************************

Developer : Mirit Hadar
Reviewer :
Last Update : 
Status :

********************************************************************************
*/

#ifndef __OL67_template
#define __OL67_template

#include <iostream>

template <typename T>
T& Max(T t1, T t2)
{
    return t1 > t2 ? &t1 : &t2;
}

void UsingTemplate();

#endif /* __OL67_template */


