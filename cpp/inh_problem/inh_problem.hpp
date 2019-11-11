/*
********************************************************************************

Developer : Mirit Hadar
Reviewer :
Last Update : 
Status :

********************************************************************************
*/
#ifndef ILRD_RD6768_INHERITANCE
#define ILRD_RD6768_INHERITANCE

namespace ilrd
{

class Base
{
public:
    /*non explicit*/ Base(int a_ = 8);
    virtual ~Base();

    virtual void Print1() const;
    virtual void Print2() const;
    virtual void Print3() const;

private:
    int m_a;
};

class Derived : public Base
{
public:
    /*non explicit*/ Derived();
    ~Derived();
    void Print1() const;
    /* virtual */ void Print2() const;

private:
    int m_b;
};

class X
{
public:
    /* X() {std::cout << "X - Ctor" << this << std::endl;} */
    X(double d_) : m_a(d_){}
    virtual ~X() {/* std::cout << "X - Dtor" << this << std::endl; */}

private:
    double m_a;
};

class Y : public X
{
public:
  /*   Y() {std::cout << "Y - Ctor" << this << std::endl;} */
    Y(double d_, int i_) : X(d_), m_b(i_) {}
    /* ~Y() {std::cout << "Y - Dtor" << this << std::endl;} */
private:
    int m_b;
};

} //namespace ilrd

#endif /*ILRD_RD6768_INHERITANCE*/
