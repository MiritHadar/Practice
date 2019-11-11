/*
********************************************************************************

Developer : Mirit Hadar
Reviewer :
Last Update : 
Status :

********************************************************************************
*/

#include <list>          /*   stl list   */
#include <algorithm>     /*   stl find   */
#include <iterator>      /* stl iterator */
#include <iostream>		 /*		i / O	 */

#include "histo.hpp"

using namespace std;

static void Print(const Data& data_);

const size_t SIZE = 1000;
const char END_INPUT[] = ".";

int main(void)
{
	cout << "Type input:" << endl;

	list<Data> strList;
	char input[SIZE] = {0};
	Str str;
	list<Data>::iterator itrList;
	list<Data>::iterator listEnd = strList.end();

	do
	{
		listEnd = strList.end();
		cin.getline(input, sizeof(input));
		str = input;

		if (str == END_INPUT)
		{
			break;
		}

		itrList = find(strList.begin(), listEnd, str);

		//if input not found
		if (itrList == listEnd)
		{
			strList.insert(strList.end(), str);
		}
		//if input found
		else
		{
			++*itrList;
		}
		
	}while(1);

	for_each(strList.begin(), strList.end(), Print);

	return 0;
}

static void Print(const Data& data_)
{
    cout << data_ <<endl;
}
