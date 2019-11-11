
#include <stdio.h>
#define VAR_SIZE(var) ((char*)(&var+1)-((char*)&var))
#define TYPE_SIZE(var) ((type*)0+1)(char*-0))

int main()
{

	int a = 5;
	printf("%lu\n", VAR_SIZE(a));

	return 0;
}
