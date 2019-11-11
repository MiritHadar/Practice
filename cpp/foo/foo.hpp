/*
********************************************************************************

Developer : Mirit Hadar
Revier :
Last Update : 
Status :

********************************************************************************
*/

#ifndef __OL67_ws1
#define __OL67_ws1

struct Counter
{
    Counter &Inc();
    void Dec();
	void Test();
    void Inc(unsigned int delta);
    int m_a;
    int m_b;
};

struct X
{
    int m_X;
};

struct Y
{
    int m_y;
};



void Foo();

void Foo(int i);

void Foo(char c);

int Inc_int();

float Inc_float();

#endif /* __OL67_ws1 */


