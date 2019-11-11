
/******************************************************************************
*	Description: Bitwise operations - header file					   *
*	Author: Mirit Hadar									 	        *
*	Reviewer: Ori Michaeli										   *
*	Status: Sent											        *
*	Last Update: 21.4.19										   *
*******************************************************************************/
#include <stdio.h> /*for printf*/
#define BITS 8
#define NIBBLE 8



long Pow2(unsigned int x, int y)
{
	long result = 0;

	if (y <= 0)								/*for negative numbers and zero*/
	{
		result = x >> -y;
	}
	else
	{
		result = x << y;				    	/*for positive numbers*/
	}

	return result;
}

int IsPowerOf2(unsigned int n)
{

	int bit_counter = 0;			/*counting 1's*/

	if (n == 0)						/*if n is 1 - return false*/
		{
			return 0;
		}

	while ((bit_counter < 2) && (n != 0))	  /*check while no more then*/
	{										  /*  a single 1 was found  */
		
			if (1 == (n & 1))
			{
				++bit_counter;
			}
		n = n >> 1;				/*shift bits to the right*/
	}
	
	if (bit_counter == 1)
	{
		return 1;		/*success*/
	}
	
	return 0;			/*failure*/

}

int IsPowerOf2NoLoop(unsigned int n)
{	

	if (n == 0)						/*if n is 1 - return 0*/
	{
		return 0;
	}
	if ((n & (n - 1)) == 0)
	{
		return 1;				/*will return 1 for base 2 numbers*/
	}

	return 0;

}

int AddOne(unsigned int num)
{
	int count_shifts = 0;

	while (0 != (num & 1))
	{
		num = num >> 1; 			/*move to the right*/
		++count_shifts;
	}

	num = num | 1;		/*change zero to one*/

	while (0 < count_shifts) /*turn first 0 you meet to 1*/
	{
		num = num << 1; 			/*return to the left. add zeros*/
		--count_shifts;		
	}

	return num;				/*flip last digit from 0 to 1*/
}

void ThreeBits(unsigned int array[], unsigned int num_elements)
{
	int count_3 = 0; /*count nums with 3 bits*/
	int shifts = 0;	/*count shifts*/
	unsigned int i = 0;
	unsigned int current_num = 0;

	puts("\nThree bits on:");

	while (i < num_elements)		/*checking each number in array*/
	{

		current_num = array[i];

		while ((count_3 < 4) && (current_num != 0))
		{
			if ((current_num & 1) == 1)	/*count every 1 in bin number*/
			{
				++count_3;
			}
		
			current_num = current_num >> 1; /*get next digit*/
			++shifts;
		}

		if (3 == count_3)
		{
			printf("\nelement %d = %u\n",i, array[i]);
		}

		count_3 = 0;	 /*restart counter 3*/
		++i;
		shifts = 0;
	}
}

int ByteMiror(int byte)
{
	int shifts = 0;

	int moves_right = 3;	/*default for first 1 after 4 shifts*/
	/*int i = 0;				index*/

	if (byte == 0)			/*for 0 given return 0*/
	{
		return byte;
	}

	while ((byte & 1) == 0) 		/*while last digit is 0*/
	{
		byte >>= 1;					/*move to the left*/
		++shifts;
	}

	if (shifts > NIBBLE)		/*when first 1 appears after the middle*/
	{
		while(shifts > NIBBLE)
		{
			moves_right -= 2;	/*calculate the number of times to shift back*/
			--shifts;
		}
	}

	byte <<= moves_right;	/*move to the left as calculated*/
	
	return byte;

}

/*int ByteMirorNoLoop(int byte)
{
	
}(*/



















