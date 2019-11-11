
#include <cstddef>  /* size_t */
#include <iostream>    /* puts   */
#include <stdlib.h>  /* malloc   */

class Base
{
public:
/*      void New();
 */    ~Base();
};

Base::~Base()
{

}

class Derive : public Base
{
public:
/*     void New();
 */    ~Derive();
};

Derive::~Derive()
{

}

int main()
{
    Base *b;
    delete b;
    return 0;
}
