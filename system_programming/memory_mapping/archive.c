#include <stdlib.h>
#include <stdio.h>
#include "archive.h"


static int g_int1;
static int g_int2 = 5;
static int g_int3 = 0;

static char* s_func(int* arg_ptr)
{
	char* local_c_ptr = 0;
	static int int6 = 10;
	*arg_ptr += g_int2;

	printf("File: %s\n", __FILE__);
	printf("Line: %d\n", __LINE__);
	printf("Func: %s\n", __func__);
	printf("Date: %s\n", __DATE__);
	printf("Time: %s\n", __TIME__);
	printf("Counter: %d\n", __COUNTER__);
	printf("Timestamp: %s\n\n", __TIMESTAMP__);
	 
	local_c_ptr = malloc(1024 * (*arg_ptr));
	
	f2(*arg_ptr);	

	return 0;
}

int f1(int arg)
{
	int int7 = 20;

	printf("File: %s\n", __FILE__);
	printf("Line: %d\n", __LINE__);
	printf("Func: %s\n", __func__);
	printf("Date: %s\n", __DATE__);
	printf("Time: %s\n", __TIME__);
	printf("Counter: %d\n", __COUNTER__);
	printf("Timestamp: %s\n\n", __TIMESTAMP__);

	s_func(&arg);

	return 0;
}
