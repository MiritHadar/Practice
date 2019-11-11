/*
********************************************************************************

Developer : Mirit Hadar
Reviewer :
Last Update : 
Status :

********************************************************************************
*/

#include <iostream>

class X
{
public:
    explicit X();
    operator int();
	operator unsigned int();
private:
    int m_a;
	unsigned int m_b;
};

X::X() : m_a(1), m_b(2) {}

X::operator int()
{
	return m_a;
}

X::operator unsigned int()
{
	return m_b;
}

void Fifi(double x_)
{
    std::cout << x_ << std::endl;
}

int main()
{
    X x1;
	//Fifi(9);
	Fifi(int(x1));

    return 0;
}
