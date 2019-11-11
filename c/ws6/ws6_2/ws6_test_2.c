
/******************************************************************************
*	Description: Bitwise operations - header file					   *
*	Author: Mirit Hadar									  	        *
*	Reviewer: Ori Michaeli										   *
*	Status: Sent										 	        *
*	Last Update: 21.4.19										   *
*******************************************************************************/

#include <stdio.h> /*for printf*/
#include "ws6_2.h" /*header file*/

#define BITS 8

void TestByteMiror();

int main()
{
	int result = 0;
	unsigned int array[] = {1,2,12,25,255,0};
	
	TestByteMiror();
	printf ("\n2 AND 6 :\n");
	printf ("\n%d\n", AreBits2And6On(7));
	printf ("\n%d\n", AreBits2And6On(132));
	printf ("\n%d\n", AreBits2And6On(0x44));
	printf ("\n%d\n", AreBits2And6On(255));

	printf ("\n2 OR 6 :\n");
	printf ("\n%d\n", AreBits2Or6On(4));
	printf ("\n%d\n", AreBits2Or6On(64));
	printf ("\n%d\n", AreBits2Or6On(0x44));
	printf ("\n%d\n", AreBits2Or6On(8));

	puts("\n\nSwapBits3And5");
	result = SwapBits3And5(12);
	printf ("\n%d = %d\n\n", 12, result);

	printf ("ClosestDividedBy16\n");
	printf ("%u = %d\n", 31, ClosestDividedBy16(31));
	printf ("%u = %d\n", 0, ClosestDividedBy16(0));
	printf ("%u = %d\n", 12, ClosestDividedBy16(12));
	printf ("%u = %d\n", 1, ClosestDividedBy16(1));
	printf ("%u = %d\n", 128, ClosestDividedBy16(128));
	printf ("%u = %d\n", 22, ClosestDividedBy16(22));

	puts("\nSwap\n");
	Swap(&(array[0]),&(array[1]));
	Swap(&(array[1]),&(array[2]));
	Swap(&(array[3]),&(array[4]));
	Swap(&(array[4]),&(array[5]));

	return 0;
}

void TestByteMiror()
{
	unsigned char byte = 1;
	unsigned char mirror = ByteMirorLoop(byte);
	printf("\n%d mirror %d\n", byte, mirror);

	byte = 2;
	mirror = ByteMirorLoop(byte);
	printf("\n%d mirror %d\n", byte, mirror);

	byte = 4;
	mirror = ByteMirorLoop(byte);
	printf("\n%d mirror %d\n", byte, mirror);

	byte = 8;
	mirror = ByteMirorLoop(byte);
	printf("\n%d mirror %d\n", byte, mirror);

	byte = 1;
	mirror = ByteMiror(byte);
	printf("\n%d mirror %d\n", byte, mirror);

	byte = 2;
	mirror = ByteMiror(byte);
	printf("\n%d mirror %d\n", byte, mirror);

	byte = 4;
	mirror = ByteMiror(byte);
	printf("\n%d mirror %d\n", byte, mirror);

	byte = 8;
	mirror = ByteMiror(byte);
	printf("\n%d mirror %d\n", byte, mirror);

}





