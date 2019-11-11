/*
********************************************************************************

Developer : Mirit Hadar
Reviewer :
Last Update : 
Status :

********************************************************************************
*/

#include <stdio.h>
#include "template.hpp"



int main(void)
{
	int arr[12];
	std::cout << Max<int>(3,5) << " "
			  << Max<double>(3.7, 12.9) << " ";
	
	std::cout << Max<int*>(arr, arr+8) << std::endl;
	std::cout << Max<char>('a', 'b') << std::endl;

	std::cout << Max("first", "second") << std::endl;
	std::cout << Max("third", "fourth") << std::endl;

	UsingTemplate();

	return 0;
}

