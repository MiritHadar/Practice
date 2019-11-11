#include <stdio.h>
#include "archive.h"
#include "sowitharchive.h"

static int g_int1;
static int g_int2 = 5;
static int g_int3 = 0;

static void s_func(int* arg_ptr)
{
	static int int6 = 10;
	int int7 = 20;

	printf("File: %s\n", __FILE__);
	printf("Line: %d\n", __LINE__);
	printf("Func: %s\n", __func__);
	printf("Date: %s\n", __DATE__);
	printf("Time: %s\n", __TIME__);
	printf("Counter: %d\n", __COUNTER__);
	printf("Timestamp: %s\n\n", __TIMESTAMP__);

	*arg_ptr += g_int2; 
	 
}

int f2(int arg)
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

	return f1(arg);
}
