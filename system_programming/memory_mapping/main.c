#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>
#include <stdio.h>
#include "archive.h"

static int g_int1 = 0;
static int g_int2 = 17;
static int g_int3;
static char string[] = "hello!";
int FLAG = 0;


int (*f3_handle)(int);

int main(int argc, char** p)
{
	int x = 11;
	int a = 10;
	int c = 0;
	void* handle = 0;
	int int3 = 20;
	char* error = 0;

	FLAG = (argc > 1);
	
	c = MIN(++a, ++x); /*What is the value of c?*/
	printf("%d\n", c);
	f1(c);

	handle = dlopen("libruntimeso.so", RTLD_LAZY);
	if (!handle)
	{
		fprintf(stderr, "%s\n", dlerror());
		return -1;
	}

	dlerror();    /* Clear any existing error */
	
	f3_handle = dlsym(handle, "f3");

	error = dlerror();
	if (error)
	{
		fprintf(stderr, "%s\n", error);
        return -1;

	}

	f3_handle(g_int3);

	dlclose(handle);

	return 0;
}
