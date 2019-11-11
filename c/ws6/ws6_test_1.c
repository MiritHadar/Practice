
/******************************************************************************
*	Description: Bitwise operations - header file					   *
*	Author: Mirit Hadar									  	        *
*	Reviewer: Ori Michaeli										   *
*	Status: Sent										 	        *
*	Last Update: 21.4.19										   *
*******************************************************************************/

#include <stdio.h> /*for printf*/
#include "ws6_1.h" /*header file*/

#define BITS 8

void TestPow2();
void TestIsPowerOf2();
void TestAddOne();
void TestByteMiror();

int main()
{
	unsigned int array[] = {6,7,11,1,0,42};
	TestPow2();
	TestIsPowerOf2();
	TestAddOne();
	ThreeBits(array, 6);
	TestByteMiror();
	return 0;
}

void TestPow2()
{
	unsigned int x = 4;
	int y = -1;
	long result = Pow2(x, y);
	printf("%u*(2^%d) = %lu\n", x, y, result);
	x = 3;
	y = 10;
	result = Pow2(x, y);
	printf("%u*(2^%d) = %lu\n", x, y, result);
}

void TestIsPowerOf2()
{
	int a = 0;
	int b = 1;
	int c = 1024;
	int result = IsPowerOf2(a);
	puts("\n\nTestIsPowerOf2 - with loop:");
	if(result == 1)
		{
			printf("\n%d is a power of 2\n", a);
		}
	else
		{
			printf("\n%d is NOT a power of 2\n", a);
		}

	result = IsPowerOf2(b);
	if(result == 1)
		{
			printf("\n%d is a power of 2\n", b);
		}
	else
		{
			printf("\n%d is NOT a power of 2\n", b);
		}

	result = IsPowerOf2(c);
	if(result == 1)
		{
			printf("\n%d is a power of 2\n", c);
		}
	else
		{
			printf("\n%d is NOT a power of 2\n", c);
		}

	/*implimentation of pow2 without loop*/
	puts("\n\nTestIsPowerOf2NoLoop - without loop:");
	result = IsPowerOf2NoLoop(a);
	if(result == 1)
		{
			printf("\n%d is a power of 2\n", a);
		}
	else
		{
			printf("\n%d is NOT a power of 2\n", a);
		}

	result = IsPowerOf2NoLoop(b);
	if(result == 1)
		{
			printf("\n%d is a power of 2\n", b);
		}
	else
		{
			printf("\n%d is NOT a power of 2\n", b);
		}

	result = IsPowerOf2NoLoop(c);
	if(result == 1)
		{
			printf("\n%d is a power of 2\n", c);
		}
	else
		{
			printf("\n%d is NOT a power of 2\n", c);
		}

}

void TestAddOne()
{
	int a = 0;
	int b = 9999;
	int c = 111111;
	int result = AddOne(a);
	printf("\n\nTestAddOne = %d\n", result);
	result = AddOne(b);
	printf("\n\nTestAddOne = %d\n", result);
	result = AddOne(c);
	printf("\n\nTestAddOne = %d\n", result);
}

void TestByteMiror()
{
	int byte = 7;
	int mirror = ByteMiror(byte);
	puts("\nByteMiror\n");
	printf("\n%d mirror %d\n", byte, mirror);

}


