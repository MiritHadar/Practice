/*
********************************************************************************

Developer : Mirit Hadar
Revier :
Last Update : 
Status :

********************************************************************************
*/

#ifndef __OL67_ws1_3
#define __OL67_ws1_3

#include <stdio.h>

struct X
{
    void Init(int a_);
    void Foo();
    void Bar() const;
    void Fifi(const X& x_);
    
    int m_a;
    int* m_p;
};

#endif /* __OL67_ws1_3 */


