/*
********************************************************************************

Developer : Mirit Hadar
Reviewer :
Last Update : 
Status :

********************************************************************************
*/

#ifndef __OL67_my_operator
#define __OL67_my_operator

#include <iostream>
using namespace std;

//class X;

//ostream& operator<<(ostream& os_, const X& x_);

ostream& operator<<(ostream &os_, const char &c_);

class X
{
    friend ostream& operator<<(ostream& os_, const X& x_);

public:
    X(int a);
    int GetValue() const;

private:
    int m_a;
};


#endif /* __OL67_my_operator */


