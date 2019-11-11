/*
********************************************************************************

Developer : Mirit Hadar
Reviewer :
Last Update : 
Status :

********************************************************************************
*/

#ifndef __OL67_counter
#define __OL67_counter

#include <cstdio>        /*   I/O  */
#include <cstddef>       /* size_t */

#include <iostream>      /*  cout  */
using namespace std;

class StaticCounter
{
private:
    static size_t s_Cntr;

public:
    StaticCounter();
    size_t GetId();
    static void Print();

private:
    size_t m_id;
};

#endif /* __OL67_counter */


