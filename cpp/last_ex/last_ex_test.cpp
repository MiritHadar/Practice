/*
********************************************************************************

Developer : Mirit Hadar
Reviewer :
Last Update : 
Status :

********************************************************************************
*/

#include <iostream>			/*	cout 	    */
#include <typeinfo>         /*  bad_cast    */

using namespace std;

struct ThrowAtDeftCtor
{
    ThrowAtDeftCtor()
    {
        cerr << "ThrowAtDeftCtor Ctor" << endl;
        throw bad_cast();
    }

    ThrowAtDeftCtor(int)
    {
        cerr << "ThrowAtDeftCtor Ctor (int)" << endl;
    }
    ~ThrowAtDeftCtor()
    {
        cerr << "ThrowAtDeftCtor Dtor" << endl;
    }
};

struct NoThrow
{
    NoThrow()
    {
        cerr << "NoThrow Ctor" << endl;
    }
    ~NoThrow()
    {
        cerr << "NoThrow Dtor" << endl;
    }
};

class X
{
public:
    X() : m_tdc(2)
    {
        cerr << "X Ctor" << endl;
    }
    ~X()
    {
        cerr << "X Dtor" << endl;
    }

private:
    NoThrow m_nt;
    ThrowAtDeftCtor m_tdc;
};

class Y
{
private:
    ThrowAtDeftCtor m_dtc;
    NoThrow m_nt;
public:
    Y()
    {
        cerr << "Y Ctor" << endl;
    }

    ~Y()
    {
        cerr << "Y Dtor" << endl;
    }
};

class Z
{
private:
    NoThrow m_nt;
    ThrowAtDeftCtor m_dtc;
public:
    Z()
    {
        cerr << "Z Ctor" << endl;
    }
    ~Z()
    {
        cerr << "Z Dtor" << endl;
    }
};

class YPtrs
{
public:
    YPtrs()
        :m_dtc(new ThrowAtDeftCtor), m_nt(new NoThrow)
    {
        cerr << "YPtrs Ctor" << endl;
    }
    ~YPtrs()
    {
        cerr << "YPtrs Dtor" << endl;
        delete m_nt;
        delete m_dtc;
    }
private:
    ThrowAtDeftCtor *m_dtc;
    NoThrow *m_nt;
};

class ZPtrs
{
public:
    ZPtrs()
    {
        cerr << "ZPtrs Ctor" << endl;
        m_nt = new NoThrow;
        m_dtc = new ThrowAtDeftCtor;
    }
    ~ZPtrs()
    {
        cerr << "ZPtrs Dtor" << endl;
        delete m_dtc;
        delete m_nt;
    }
private:
    NoThrow *m_nt;
    ThrowAtDeftCtor *m_dtc;
};

int main()
{
    try
    {
        ZPtrs var1;
        //Y var1;
        //Z var1;
    }
    catch(exception &e)
    {
        std::cerr << "exception cout. what:" << e.what() << endl;
    }

	return 0;
}
