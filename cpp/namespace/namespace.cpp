/*
********************************************************************************

Developer : Mirit Hadar
Reviewer :
Last Update : 
Status :

********************************************************************************
*/

//#include "namespace.hpp"

#include <cstddef>      /* size_t */

namespace math
{
long Fibo(int n)
{}
double Sin(double d)
{}
double Cos(double d)
{}
}//math

namespace fibonaci
{
long lookupTable[256];
long Fibo(int n)
{}

namespace altversion
{
long Fibo(size_t n)
{}
}//altversion

}//fibonaci

namespace math
{
double Tang(double d)
{}
}

void A()
{
    int n = 3;
    fibonaci::Fibo(n);
    using math::Fibo;
    Fibo(n);

    math::Sin(3.14);
    math::Tang(3.14);
}

using namespace math;
using namespace fibonaci;
namespace alt=fibonaci::altversion;

void B()
{
    size_t n = 3;
    alt::Fibo(n);
    //Fibo(n);
    Cos(n);
}

int main()
{
    return 0;
}



