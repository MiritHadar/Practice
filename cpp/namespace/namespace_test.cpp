/*
********************************************************************************

Developer : Mirit Hadar
Reviewer :
Last Update : 
Status :

********************************************************************************
*/
/* #include <iostream>

using namespace std;

namespace try
{
void foo();
}

void foo()
{
	cout << "hello world!" << endl;
}

using namespace try;

int main(void)
{
	try :: foo();
	return 0;
}
 */

#include <cstddef>      /* size_t */
#include <cstdio>       /* I / O  */

namespace math
{
void Fibo()
{
	printf("hello world\n");
}
}//math

using math::Fibo;

void A()
{
    Fibo();
}

int main()
{
	A();
}

