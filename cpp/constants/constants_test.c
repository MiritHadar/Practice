

#include <stdio.h>
#include "constants.hpp"

const int g_const = 7;
int g_non_const = 8;
const int i = 3;

int main(void)
{    
	int *ip = (int*)&i;
	*ip = 5;

	printf("%d %d\n", i, *ip);
	return 0;
}