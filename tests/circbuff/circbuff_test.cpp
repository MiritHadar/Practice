/*
********************************************************************************

Developer : Mirit Hadar
Reviewer :
Last Update : 
Status :

********************************************************************************
*/

#include <iostream>
#include "circbuff.hpp"

using namespace std;

int main()
{
	CircBuffer<int> cb (1024);
	CircBuffer<char> cb1 ();
	cb.Add(1);
	cout << cb.GetSize() << endl;
	cout << cb.GetCapacity() << endl;
	cb.Remove();
	return 0;
}

