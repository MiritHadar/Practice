/*
********************************************************************************

Developer : Mirit Hadar
Reviewer :
Last Update : 
Status :

********************************************************************************
*/

#include "crack.hpp"

using namespace mirit;

void UniqueTest();

int main()
{
	UniqueTest();
	string str = "mirit hadar rules!";
	ReplaceSpaces(str);
	cout << str << endl;
	
	return 0;
}

void UniqueTest()
{
	const char *str1 = "mirit";
	if (false != IsAllStrUnique(str1))
	{
		cout << "error in: " << __LINE__ << endl;
	}

	const char *str2 = "mirate";
	if (true != IsAllStrUnique(str2))
	{
		cout << "error in: " << __LINE__ << endl;
	}

	if (false !=  IsAllStrUniqueNoDs(str1))
	{
		cout << "error in: " << __LINE__ << endl;
	}
	if (true != IsAllStrUniqueNoDs(str2))
	{
		cout << "error in: " << __LINE__ << endl;
	}
}


