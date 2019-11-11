
/*******************************************************************************
*	Description: Bit Array							  			    *
*	Author: Mirit Hadar									  	         *
*	Reviewer: Ada Elkin										  	    *
*	Status: Sent										 	         *
*	Last Update: 2/5/19										  	    *
*******************************************************************************/

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>		/*malloc*/

#define UNUSED_VAR(x) (void)(x)
#define ONE (unsigned long)0x1
#define LEFT_ONE (unsigned long)0x8000000000000000
#define MOVE_END (unsigned long)63
#define HALF_WAY (unsigned int)32
#define MOVE_TO_END (unsigned long)63
#define GAP_ASCII 48
#define LONG_LEN 64
#define RIGHT_NIBBLE 15
#define NIBBLE 4

__attribute__((unused)) static char *ToString(long unsigned num, char *buffer);

unsigned long BArrAllOn()
{
	return 0xFFFFFFFFFFFFFFFF;	/*put 1*/
	/*better answer*/
    /*return ~(0ul);*/
}


unsigned long BArrAllOff()
{
	return 0x0;					/*put 0*/
}


unsigned long BArrSetBitOn(unsigned long num, size_t index)
{
	assert(index < LONG_LEN);

	return (num | ONE << index); 	/*return num with bit on*/
}


unsigned long BArrSetBitOff(unsigned long num, size_t index)
{
	assert(index < LONG_LEN);

	return (num & ~(ONE << index));
}


unsigned long BArrSetBit(unsigned long num, size_t index, int state)
{
	assert(index < LONG_LEN);
	
	if (state == 0)				/*turn off for 0*/
	{
		return (num & ~(ONE << index));
	}
	else						/*turn on for != 0*/
	{
		return (num | ONE << index);
	}
	
	/*better answer*/
    /*return (num ^ ((((num & (ONE << index)) >> index) ^ state) << index));*/
}


int BArrIsOn(unsigned long num, size_t index)	/*Is On*/
{
	assert(index < LONG_LEN);

	return !!((num >> index) & ONE);
}

int BArrIsOff(unsigned long num, size_t index)		/*Is Off*/
{
	assert(index < LONG_LEN);

	return (((num >> index) & ONE) ^ ONE);

}


unsigned long BArrFlipBit(unsigned long num, size_t index)
{
	assert(index < LONG_LEN);

	return num ^ (ONE << index);
}


unsigned long BArrRotateR(unsigned long num, size_t shifts)
{
    int right = 0;
	
    shifts &= (LONG_LEN - 1); /* prevent un-needed rotations */

    while (shifts > 0)
    {
        right = num & ONE;                    /*save right digit*/

        num >>= 1;                        /*shift all num once*/

        if (1 == right)        /*will change left digit to 1 if needed*/
        {
            num |= LEFT_ONE;
        }

        --shifts;
    }

    return num;
    /*better answer*/
    /*return ((num << shifts) | (num >> (64 - shifts));*/
}


unsigned long BArrRotateL(unsigned long num, size_t shifts)
{
    unsigned long left = 0;

    shifts &= (LONG_LEN - 1); /* prevent un-needed rotations */

    while (shifts > 0)
    {
        left = num & LEFT_ONE;        /*save left digit*/

        num <<= 1;                        /*shift all num once*/

        if (LEFT_ONE == left)        /*will change left digit to 1 if needed*/
        {
            num |= ONE;
        }

        --shifts;
    }

    return num;
    
    /*better answer*/
    /*return ((num >> shifts) | (num << (64 - shifts));*/
}


unsigned long BArrMirror(unsigned long num)
{
	int i = 0;
	unsigned long digit = 0;
	unsigned long mirror_num = 0x0;

	while (i < LONG_LEN)
	{
	
		digit = num & (ONE << i);	/*extract digits from right to left*/

		if (1 == (digit >> i))
		{
			mirror_num |= (LEFT_ONE >> i);	 /* put right digit at the */
		}								 /*left digit of mirror num*/
					     		
		++i;
	}

	return mirror_num;
}

size_t BArrCountOn(unsigned long num)
{
	int bits_on = 0;

	while (0 != num)
	{
		num &= (num-1);		
		++bits_on;
	}

	return bits_on;
}


size_t BArrCountOff(unsigned long num)
{
	int bits_off = LONG_LEN;

	while (0 != num)
	{
		num &= (num-1);
		--bits_off;
	}
	
	return bits_off;
}


static char *ToString(long unsigned num, char *buffer)
{
	size_t i = 0;

	assert(buffer);

	buffer += LONG_LEN;
	*buffer = '\0';
	
	while (i < LONG_LEN)
	{
		--buffer;
		*buffer = ((num >> i)& ONE) + GAP_ASCII;
		++i;
	}
		
	return buffer;
}


void BArrPrintBits(unsigned long num)
{
	char *buffer = malloc(sizeof(char) * (LONG_LEN + 1));
	if (NULL == buffer)
	{
		puts("malloc failed!");
		return;
	}

	#ifndef NDEBUG
	ToString(num, buffer);
	printf("%lu : %s\n", num, buffer);
	#else
	(void)(num);
	#endif

	free(buffer);	buffer = NULL;

}

unsigned long BArrMirrorLUT(unsigned long num)
{
	unsigned long mirror_num = 0;
	unsigned long new_nibble = 0;
	long move_left = LONG_LEN - NIBBLE;
	unsigned long right_nibble = 0;
	unsigned long lut_nibbles[16];

	lut_nibbles[0] = 0x0;
	lut_nibbles[1] = 0x8;
	lut_nibbles[2] = 0x4;
	lut_nibbles[3] = 0xc;
	lut_nibbles[4] = 0x2;
	lut_nibbles[5] = 0xa;
	lut_nibbles[6] = 0x6;
	lut_nibbles[7] = 0xe;
	lut_nibbles[8] = 0x1;
	lut_nibbles[9] = 0x9;
	lut_nibbles[10] = 0x5;
	lut_nibbles[11] = 0xd;
	lut_nibbles[12] = 0x3;
	lut_nibbles[13] = 0xb;
	lut_nibbles[14] = 0x7;
	lut_nibbles[15] = 0xf;

	while(move_left >= 0)
	{
		right_nibble = num & RIGHT_NIBBLE;	/* whats in the right nibble? */
		new_nibble = (lut_nibbles[right_nibble]) << move_left;
		mirror_num |= new_nibble;
		num >>= NIBBLE;					/*find next nibble*/
		move_left -= NIBBLE;
	}

	return mirror_num;

}


size_t BArrCountOnLUT(unsigned long num)
{
    size_t bits_on = 0;
    unsigned long lut_bits_on[16];

    /*setting the LUT to number of bits on in each index number*/
    lut_bits_on[0] = 0;
    lut_bits_on[1] = 1;
    lut_bits_on[2] = 1;
    lut_bits_on[3] = 2;
    lut_bits_on[4] = 1;
    lut_bits_on[5] = 2;
    lut_bits_on[6] = 2;
    lut_bits_on[7] = 3;
    lut_bits_on[8] = 1;
    lut_bits_on[9] = 2;
    lut_bits_on[10] = 2;
    lut_bits_on[11] = 3;
    lut_bits_on[12] = 2;
    lut_bits_on[13] = 3;
    lut_bits_on[14] = 3;
    lut_bits_on[15] = 4;

    while (num > 0)
    {
        bits_on += lut_bits_on[num & RIGHT_NIBBLE];/*find number of bits in   */
        num >>= NIBBLE;						 /*the right nibble and add */
    }									 /*that num to sum of bits  */

    return bits_on;
}






