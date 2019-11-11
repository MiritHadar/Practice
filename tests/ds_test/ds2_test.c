/*
********************************************************************************

Developer : Mirit Hadar
Reviewer :
Last Update : 
Status :

********************************************************************************
*/

#include <stdio.h>
#include "ds2.h"

const int SIZE = 10;

int main(void)
{
	size_t i = 0;
	dlist_t *org = DLLCreate();
	int nums[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

	for (i = 0; i < SIZE; ++i)
	{
		DLLPushBack(org, nums + i);
	}

	ArrangeInList(org, 6);

	/* printf("%d\n", Division(10, 5));
	printf("%d\n", Division(7, 5));
	printf("%d\n", Division(100, 10));
	printf("%d\n", RecMultiply(6, 10));
	printf("%d\n", RecMultiply(5, 7));
	printf("%d\n", RecMultiply(4, 0));
	printf("%d\n", RecMultiply(3, 6)); */

	return 0;
}

