/*******************************************************************************
*	Description: Stack							   		            		   *
*	Author: Mirit Hadar									  	 	       		   *
*	Reviewer: Evgeny Chernov									 	 	       *
*	Status:	Sent									 	  	         		   *
*	Last Update: 6.5.19										  	         	   *
*******************************************************************************/

#include <stdio.h>		/*puts*/
#include <stdlib.h>		/*free*/
#include "stack.h"

#define UNUSED_VAR(x) (void)(x)


void TestStackCreate();
void TestStackPush();
void TestStackPop();
void TestStackPeek();
void TestStackSizeDestroy();


int main()
{
	int data1 = 1;
	int data2 = 2;
	int data3 = 3;
	int data4 = 4;
	int data5 = 5;
	int i = 0;

	/*TestStackCreate();
	TestStackPush();
	TestStackPop();
	TestStackPeek();
	TestStackSizeDestroy();*/

	stack_t *s = StackCreate(5, sizeof(int));

	StackPush(s, &data5);
	StackPush(s, &data3);
	StackPush(s, &data1);
	StackPush(s, &data2);
	StackPush(s, &data4);

	printf("top before : %d\n", *(int*)StackPeek(s));
	printf("size %lu\n", StackSize(s));
	SortStack(s);
	for (i = 0; i < 5; ++i)
	{
		printf("%d ", *(int*)StackPeek(s));
		StackPop(s);
	}
	return 0;
}

void TestStackCreate()
{
	stack_t *s = StackCreate(20, 8); 
	if(NULL == s)
	{
		puts("Stack Create Failed!");
	}

	StackDestroy(s);				/*destroy*/
}

void TestStackPush()
{
	stack_t *s = StackCreate(3, 4);		/*create a stack of 3 ints*/
	int a = 10;

	if (0 != StackPush(s, &a))	/*push first int*/
	{
		puts("1 push failed");
	};

	if (0 != StackPush(s, &a))	/*push second int*/
	{
		puts("2 push failed");
	};

	if (0 != StackPush(s, &a))	/*push third int*/
	{
		puts("3 push failed");
	};

	if (1 != StackPush(s, &a))	/*push fourth int - and fail*/
	{
		puts("push failed - over flow occured");
	};
	
	StackDestroy(s);				/*destroy*/
}

void TestStackPop()
{
	stack_t *s = StackCreate(3, 4);		/*create a stack of 3 ints*/
	int a = 10;

	if (0 != StackPush(s, &a))	/*push first int*/
	{
		puts("1 push failed");
	};

	if (0 != StackPush(s, &a))	/*push second int*/
	{
		puts("2 push failed");
	};

	if (0 != StackPush(s, &a))	/*push third int*/
	{
		puts("3 push failed");
	};
	
	StackPop(s);	/*pop first */
	StackPop(s);	/*pop second*/
	StackPop(s);	/*pop third */
	StackPop(s);	/*pop - cause under flow */

	StackDestroy(s);				/*destroy*/
}

void TestStackPeek()
{
	stack_t *s = StackCreate(3, 1);		/*create a stack of 3 chars*/
	char a = 'a';
	char b = 'b';
	char c = 'c';

	if (0 != StackPush(s, &a))	/*push first char*/
	{
		puts("1 push failed");
	};

	if (0 != StackPush(s, &b))	/*push second char*/
	{
		puts("2 push failed");
	};

	if (0 != StackPush(s, &c))	/*push third char*/
	{
		puts("3 push failed");
	};
	

	StackPop(s);	/*pop 1*/

	if('b' != *(char*)StackPeek(s))
	{
		puts("1 peek failed");
	};

	StackPop(s);	/*pop 2*/
	if('a' != *(char*)StackPeek(s))
	{
		puts("2 peek failed");
	};

	StackPop(s);	/*pop 3*/
	if(NULL != StackPeek(s))
	{
		puts("3 peek failed");
	};
	StackPop(s);	/*pop - under flow*/
	StackDestroy(s);				/*destroy*/
}

void TestStackSizeDestroy()
{
	stack_t *s = StackCreate(7, 1);		/*create a stack of 3 chars*/
	long a = 1;
	long b = 2;
	long c = 3;

	StackPush(s, &a);
	StackPush(s, &b);
	StackPush(s, &c);
	StackPush(s, &c);
	StackPush(s, &c);

	if(5 != StackSize(s))
	{
		puts("1 Stack Size failed");	
	}

	StackDestroy(s);				/*destroy*/
}










