
/******************************************************************************
*	Description: Bitwise operations - header file					   *
*	Author: Mirit Hadar									 	        *
*	Reviewer: Ori Michaeli										   *
*	Status: Sent											        *
*	Last Update: 21.4.19										   *
*******************************************************************************/
#include <stdio.h> 		/*printf*/
#include <assert.h> 	/*assert*/
#define BITS 8
#define NIBBLE 4


unsigned char ByteMirorLoop(unsigned char byte)
{
	int right = 1;
	int left = 128;
	int tmp = 0;
	int i = 0;

	for (i = 0; i < NIBBLE; ++i)
	{
		tmp = byte & left;
		
	
		if ((byte & right) == right)		
		{
			byte = byte | left;	
		}

		else					
		{
			byte = byte & (~left);	
		}

		if (tmp != 0)
		{
			byte = byte | right;
		}

		else
		{
			byte = byte & (~right);	
		}

		right = right <<  1;
		left = left >> 1;

	}

	return byte;

}

unsigned char ByteMiror(unsigned char byte)
{
	byte = byte << 4 | byte >> 4;
	byte = (0xcc & byte) >> 2 | (0x33 & byte) << 2;
	byte = (0xaa & byte) >> 1 | (0x55 & byte) << 1;

	return byte;
}

int AreBits2And6On(unsigned char byte)
{
	int result = (byte & 0x44);				/*if both bits 2&6 are 1*/
	return ((result >> 6) & (result >> 2));  		    /*will return 1*/
	
}

int AreBits2Or6On(unsigned char byte)
{
	int result = (byte & 0x44);				/*if both bits 2&6 are 1*/
	int answer = (result >> 6) | ((result >> 2) & 1);     /*will return 1*/
	return answer;
}

int SwapBits3And5(unsigned char byte)
{
	
	unsigned char bit3 = ((byte >> 3) & 1);
	unsigned char bit5 = ((byte >> 5) & 1);

	byte = byte & ~0x08;	/*turn off the third bit*/
	byte = byte & ~0x20;	/* turn off the 5th bit */

	byte = byte | (bit3 << 5); /*put bit3 in the 5th bit*/
	byte = byte | (bit5 << 3); /*put bit5 in the 3th bit*/
	
	return byte;
}

unsigned int ClosestDividedBy16(unsigned int num)
{
	return (num & 0xf0); /*finds the num and adds to it 1111 at the right*/
							 /*hand side. then flips all those 1's to 0's*/
}

void Swap(unsigned int *first, unsigned int *second)
{
	assert(first);
	assert(second);

	printf("before: first %u\n\tsecond %u\n", *first, *second);
	*first = *first ^ *second;
	*second = *first ^ *second;
	*first = *first ^ *second;
	printf("after: first %u\n\tsecond %u\n\n", *first, *second);
}














