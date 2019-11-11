
#include <stdio.h>

#define MAX_BIT 32


size_t BitsOnLoop(int num)
{
	int bits = 0;

	while (0 != num)
	{
		num = num & (num - 1); /*	   turn each bit to 0		*/
		++bits;				   /*stop looping when no 1 remaines*/
	}

	return bits;

}


size_t BitsOn(int num)	/*count how meny 1's in each section*/
{
	num = ((num & 0xaaaaaaaa) >> 1) + (num & 0x55555555);
	num = (((num & 0xcccccccc) >> 2) + ((num & 0x33333333)));
	num = (((num & 0xf0f0f0f0) >> 4) + ((num & 0x0f0f0f0f)));
	num = (((num & 0xff00ff00) >> 8) + ((num & 0x00ff00ff)));
	num = (((num & 0xffff0000) >> 16) + ((num & 0x0000ffff)));

	return num;
}


void FloatCast(float f_num)
{
	float *pf_num = &f_num;
	int i = 0;
	unsigned int mask = 0x80000000;	/*i gets "1000 0000..." in binary*/
	int max_byte = 32;	

	while (i < max_byte)					/*prints each digit of f_num,*/
	{							  /*after getting rid of 0's in the beginning*/
		printf("%d", (*(int*)pf_num & mask) >> (max_byte - i - 1));

		mask >>= 1;	/*move 1 to the right*/
		++i;
	}

	puts("");
}






