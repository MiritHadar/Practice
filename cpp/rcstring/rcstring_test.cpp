/*
********************************************************************************

Developer : Mirit Hadar
Reviewer :
Last Update : 
Status :

********************************************************************************
*/

#include <iostream>
#include "rcstring.hpp"

using namespace std;
using namespace ilrd;

void BasicTest();
void CharProxyTest();
void CombinedPointerTest();

int main(void)
{
	BasicTest();
	CharProxyTest();
	CombinedPointerTest();
	return 0;
}

void BasicTest()
{
	RcString rc1("rc 1");
	if (1 != rc1.GetCounter())
	{
		cout << "failed Ctor " << __LINE__ << endl;

	}

	RcString rc2 = rc1;

	if (2 != rc2.GetCounter())
	{
		cout << "failed Ctor " << __LINE__ << endl;
	}
	if (2 != rc1.GetCounter())
	{
		cout << "failed Ctor " << __LINE__ << endl;
	}

	rc2 = rc2;
	
	if (2 != rc2.GetCounter())
	{
		cout << "failed Ctor " << __LINE__ << endl;
	}
}

void CharProxyTest()
{
	RcString rc1 = "proxy";
	if (1 != rc1.GetCounter())
	{
		cout << "failed Ctor " << __LINE__ << endl;
	}

	rc1[2] = 'z';
	if (1 != rc1.GetCounter())
	{
		cout << "failed Ctor " << __LINE__ << endl;
	}

	RcString rc2 = "proxy";
	if (1 != rc2.GetCounter())
	{
		cout << "failed Ctor " << __LINE__ << endl;
	}

	RcString rc3 = rc2;
	if (2 != rc3.GetCounter())
	{
		cout << "failed Ctor " << __LINE__ << endl;
	}
	rc2[0] = 'd';
	if (1 != rc2.GetCounter())
	{
		cout << "failed Ctor " << __LINE__ << endl;
	}
	if (1 != rc3.GetCounter())
	{
		cout << rc3.GetCounter() << endl;
		cout << "failed Ctor " << __LINE__ << endl;
	}

	const RcString rc_const = rc3;
	if (2 != rc3.GetCounter())
	{
		cout << "failed Ctor " << __LINE__ << endl;
	}
	char c = rc_const[2];
	if (2 != rc_const.GetCounter())
	{
		cout << "failed Ctor " << __LINE__ << endl;
	}

	c = rc3[3];
	if (c != 'x')
	{
		cout << "failed [] " << __LINE__ << endl;
	}

	if (2 != rc3.GetCounter())
	{
		cout << "failed assign Ctor " << __LINE__ << endl;
	}

	RcString rc5 = "mirit";
	RcString rc6 = "ben";
	rc5[0] = rc6[0];
}

void CombinedPointerTest()
{
	RcString rc1("hi");

	if (2 != rc1.GetLength())
	{
		cout << "failed combined GetLength" << endl;
	}

	if (1 != rc1.GetCounter())
	{
		cout << "failed combined GetCounter" << endl;
	}

	RcString rc2 = rc1;

	if (2 != rc1.GetCounter())
	{
		cout << "failed combined GetCounter" << endl;
	}

	RcString rc3("world");
	rc3 = rc2;
	rc3 = rc1;
	rc3 += rc1; 

	if('i' != rc3[3])
	{
		cout << "failed combined []" << endl;
	}

	const RcString rc4 = "mamamia";
	if ('a' != rc4[3])
	{
		cout << "failed combined const []" << endl;
	}

	if (rc4 < rc1)
	{
		cout << "failed combined <" << endl;
	}

}

