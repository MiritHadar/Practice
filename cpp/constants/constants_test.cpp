/*
********************************************************************************

Developer : Mirit Hadar
Reviewer :
Last Update : 
Status :

********************************************************************************
*/

#include <stdio.h>
#include "constants.hpp"

const int g_const = 4;
int g_non_const = 8;

int main(void)
{
	const int i = 3;
	int *ip = (int*)&i;
	*ip = 5;

	printf("%d %d\n", i, *ip);
	return 0;
}

