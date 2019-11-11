/*
********************************************************************************

Developer : Mirit Hadar
Reviewer :
Last Update : 
Status :

********************************************************************************
*/

#include <stdio.h>
#include "bitset.hpp"

using namespace std;
using namespace ilrd;
 
/*void SetBitTest();
void ConstTest();
void OperatorsTest();
void ToStringTest(); */
void NewTest();

int main(void)
{
	/* SetBitTest();
	ConstTest();
	ToStringTest();
	OperatorsTest(); */
	NewTest();

	return 0;
}

/*void SetBitTest()
{
	BitSet<100> bs1;
	BitSet<100> bs2(bs1);
	bs1.SetBit(2, 1);
	if('4' != bs1.GetIndex(0))
	{
		cout << "failed line" << __LINE__ << endl;
	}

	bs1.SetBit(2, 0);
	if('0' != bs1.GetIndex(0))
	{
		cout << "failed line" << __LINE__ << endl;
	}

	bs2.SetBit(99, 1);
	if (!(bs2.IsSet(99)))
	{
		cout << "failed line" << __LINE__ << endl;
	}
	
	cout << "count: " << bs2.CountSetBits() << endl; 
}
 
void ConstTest()
{
	const BitSet<5> const_bs;
	if (const_bs[3] != 0)
	{
		cout << "failed line" << __LINE__ << endl;
	}
	if (const_bs.IsSet(7))
	{
		cout << "failed line" << __LINE__ << endl;
	}
}

void OperatorsTest()
{
	BitSet<100> bs1;
	bs1.SetBit(2, 1);
	BitSet<100> bs2;
	bs2.SetBit(2, 1);
	BitSet<100>bs3 = bs1 & bs2;
	if (!(bs3.IsSet(2)))
	{
		cout << "failed line" << __LINE__ << endl;
	}
	bs1 ^= bs2;
	if (bs1.IsSet(2))
	{
		cout << "failed line" << __LINE__ << endl;
	}
	bs1 |= bs2;
	if (!(bs1.IsSet(2)))
	{
		cout << "failed line " << __LINE__ << endl;
	}
	
	BitSet<100> bs4;
	bs4.FlipBit(3);
	if (!(bs1.IsSet(3)))
	{
		cout << "failed line " << __LINE__ << endl;
	}
	bs4.FlipBit(3);
	if (bs1.IsSet(3))
	{
		cout << "failed line" << __LINE__ << endl;
	}
	//bs4 = ~bs1; not working
}
void ToStringTest()
{
	
}
 */

void NewTest()
{
	BitSet<10> newBs;
	const BitSet<10> other(~newBs);
	cout << other[2];
}
