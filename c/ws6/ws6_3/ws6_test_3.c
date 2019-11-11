
/******************************************************************************
*	Description: Bitwise operations - header file					   *
*	Author: Mirit Hadar									  	        *
*	Reviewer: Ori Michaeli										   *
*	Status: Sent										 	        *
*	Last Update: 21.4.19										   *
*******************************************************************************/

#include <stdio.h> /*for printf*/
#include "ws6_3.h" /*header file*/

#define BITS 8

int main()
{
	int result = 0;
	float f = 1.5;

	printf ("BitsOnLoop\n");
	result = BitsOnLoop(12);
	printf("%d - %d\n", 12, result);
	result = BitsOnLoop(0);
	printf("%d - %d\n", 0, result);
	result = BitsOnLoop(255);
	printf("%d - %d\n", 255, result);
	result = BitsOnLoop(64);
	printf("%d - %d\n", 64, result);

	printf ("\nBitsOn\n");
	printf("%d has %lu bits on\n", 12, BitsOn(12));
	printf("%d has %lu bits on\n", 255, BitsOn(255));
	printf("%d has %lu bits on\n", 67, BitsOn(67));
	printf("%d has %lu bits on\n", 128, BitsOn(128));
	printf("%d has %lu bits on\n", 0, BitsOn(0));

	puts("\nFloatCast\n");
	FloatCast(f);

	return 0;
}

