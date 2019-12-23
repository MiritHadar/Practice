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
void SpaceTest();
void PolindromeTest();
void RemoveSpacesTest();

int main()
{
	UniqueTest();
	PolindromeTest();
	RemoveSpacesTest();

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

void SpaceTest()
{
	string str = "mirit hadar rules!";
	ReplaceSpaces(str);
	cout << str << endl;
}

void PolindromeTest()
{
	string evenPol = "kkoojj";
	string evenNonPol = "kkklli";
	if (1 != IsPolindrome(evenPol))
	{
		cout << "error in: " << __LINE__ << endl;
	}

	if (0 != IsPolindrome(evenNonPol))
	{
		cout << "error in: " << __LINE__ << endl;
	}

	const string oddPol = "kkk";
	const string oddNonPol = "fffgd";
	if (1 != IsPolindrome(oddPol))
	{
		cout << "error in: " << __LINE__ << endl;
	}

	// if (0 != IsPolindrome(oddNonPol))
	// {
	// 	cout << "error in: " << __LINE__ << endl;
	// }
}

void RemoveSpacesTest()
{
	string str = "a   b ";
	cout << "before: " << str << endl;

	RemoveSpacesInplace(str);
	cout << "after: " << str << "!" << endl;

	string str1 = "mirit kjkjkjkjk jkjkjk    jkjkj    ";
	cout << "before: " << str1 << endl;

	RemoveSpacesInplace(str1);
	cout << "after: " << str1 << "!" << endl;
}



