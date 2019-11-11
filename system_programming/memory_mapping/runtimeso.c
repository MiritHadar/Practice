#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "runtimeso.h"
#define BUFF_SZ 1024

static int g_int1;
static int g_int2 = 20;
static int g_int3 = 50;

static void rec_alloc_heap()
{
  char* buff = (char*)malloc(1024);

	printf("File: %s\n", __FILE__);
	printf("Line: %d\n", __LINE__);
	printf("Func: %s\n", __func__);
	printf("Date: %s\n", __DATE__);
	printf("Time: %s\n", __TIME__);
	printf("Counter: %d\n", __COUNTER__);
	printf("Timestamp: %s\n\n", __TIMESTAMP__);

  f3(17);
}

int f3(int arg)
{
  static int i = 10; 
  char c = 'x';
  int l_int = 4;
  short s = 0xFFFF;
  long l = ~0;
  const char array[] = "0123456789ABCDEF!!!";
  long l2 = sizeof(array);

  i += strlen(array);

	printf("File: %s\n", __FILE__);
	printf("Line: %d\n", __LINE__);
	printf("Func: %s\n", __func__);
	printf("Date: %s\n", __DATE__);
	printf("Time: %s\n", __TIME__);
	printf("Counter: %d\n", __COUNTER__);
	printf("Timestamp: %s\n\n", __TIMESTAMP__);

  rec_alloc_heap();
  printf("Allocated heap\n");

  return 0;
}

__attribute__((constructor))
void initialization_func() /*called when .so is loaded */
{
  printf("Loaded shared object\n");
}

__attribute__((destructor))
void shutdown_func() /* called when .so is closed */
{
  printf("Closed shared object\n");
}
