#include <stdio.h>
#include <assert.h>
#include <string.h>

#define WORD 8
#define UNUSED_VAR(x) (void)(x)
#define GAP_ASCII 48
#define GAP_ASCII_LETTERS 55
#define MAX_DIGIT 9
#define MAX_DIGIT_LETTER 57

#ifndef DNDEBUG
#define PRINTF(x) printf(x)
#define PUTS(x) puts(x)
#endif

static int DigitsInNum(int num);
static int DigitsInNumAnyBase(int num, int base);

void *Memset(void *s, int c, size_t n)
{
	int i = 0;
	char *s_char = (char*)s;	
	long c_long = c;

	assert(s);

	if (n >= WORD)			/*create a word of 8 c's if n>=8*/
	{
		for (i = 0; i < WORD; ++i)	
		{
			c_long <<= WORD;
			c_long = c_long | c;
		}
	}

	while (((*s_char & (WORD - 1)) != 0) & (n > 0)) /*untill beginning of word*/
	{												/*   copy byte by byte    */
		*s_char = c_long;
		++s_char;
		--n;
	}

	while (n / WORD > 0)					/* when reach the first */ 
	{										/* word,copy one by one */
		*(long*)s_char = c_long;
		s_char += WORD;
		n = n - WORD;
	}


	while (n > 0)	/*copy all remaining bytes one by one*/
	{
		*s_char = c;
		++s_char;
		--n;
	}
	
	return s;
		
}
	

void *Memcpy(void *dest, const void *src, size_t n)
{
	void *base_dest = dest;

	assert(dest);
	assert(src);

	while ((*(char*)dest & (WORD - 1)) != 0) /*untill beginning of word*/
	{									     /*    copy byte by byte   */
		*(char*)dest = *(char*)src;
		++*(char**)&src;
		++*(char**)&dest;
		--n;
	}

	while (n / WORD > 0)					/* when reach the first word*/
	{										/*	copy word by word		*/
		*(long*)dest = *(long*)src;
		*(char**)&dest += WORD;
		*(char**)&src += WORD;
		n = n - WORD;
	}

	while (n > 0)	/*copy all remaining bytes one by one*/
	{
		*(char*)dest = *(char*)src;
		++*(char**)&src;
		++*(char**)&dest;
		--n;
	}
	
	return base_dest;
}


void *Memmove(void *dest, const void *src, size_t n)
{

	char *dest_to_paste = (char*)(dest) + n - 1;
	char *src_to_copy = (char*)(src) + n - 1;
	char *dest_base = dest;

	assert(dest);
	assert(src);
	assert(n);

	if(dest == src)	/*if strings identical - return dest as is*/
	{
		return dest_base;
	}

	if (src < dest)	/*if overlapping may occur*/
	{
		while (dest_to_paste >= dest_base)
		{
			*dest_to_paste = *src_to_copy;
			--src_to_copy;
			--dest_to_paste;
		}
	}

	else				/*for no overlapping - regular copy*/
	{
		Memcpy(dest, src, n);
	}

	return (void*)dest_base;
}


int Atoi(const char *num_string)			 /*string -> int*/
{
	int num = 0;
	int sign = 1;	/*flag for negatives*/

	assert(num_string);

	if (*num_string == '-')	/*for negative nums turn on flag*/
	{
		sign = -1;
		++num_string;
	}

	while ('\0' != *num_string)		/*   convert each char to num  */
	{								/*and then move all digits left*/
		num *= 10;
		num = num + (int)(*num_string) - GAP_ASCII;
		++num_string;
	}

	return num * sign;
}


char *Itoa(char *str, int num_to_string)		/*int -> string*/
{
	char *base_str = str;	
	size_t len = DigitsInNum(num_to_string);	/*num of digits*/
	int last_digit = 0;

	if (num_to_string == 0)		/*for zero*/
	{
		*str = '0';
		return str;
	}

	if (num_to_string < 0)		/*put minus for negatives*/
	{
		*str = '-';
		num_to_string *= (-1);
		++str;
	}

	str += len;		/*put '\0' at last char*/
	*str = '\0';

	while (0 != num_to_string)
	{
		--str;
		last_digit = num_to_string % 10;	/*extract last digit*/
		*str = (char)last_digit + GAP_ASCII;
		num_to_string /= 10;
	}
	
	return base_str;
}


static int DigitsInNum(int num)
{
	int digits = 0;
	
	while(num != 0)
    {
        ++digits;	/*Increment digit count*/
        num /= 10;	/*Remove last digit of num*/
    }

    return digits;
}

int AtoiAnyBase(const char *str_to_int, int base)			  /*string -> int*/
{
	int num = 0;
	int sign = 1;	/*flag for negatives*/

	assert(str_to_int);
	assert(base);

	if (*str_to_int == '-')	/*for negative nums turn on flag*/
	{
		sign = -1;
		++str_to_int;
	}

	/*num_or_letter = (int)*num_string;*/
	
	while ('\0' != *str_to_int)		/*   convert each char to num  */
	{								/*and then move all digits left*/
		num *= base;

		if(*str_to_int > MAX_DIGIT_LETTER)
		{
			num = num + (int)(*str_to_int) - GAP_ASCII_LETTERS;  /*55*/
		}
		else
		{
			num = num + (int)(*str_to_int) - GAP_ASCII;			 /*48*/
		}

		++str_to_int;
	}

	return num * sign;
}


char *ItoaAnyBase (char *string, int num_to_string, int base) /*int -> string*/
{

	char *base_string = string;
	int num_or_letter = 0;
	size_t len = 0;

	assert(string);
	assert(base);
	
	if (0 == num_to_string)	/*for 0*/
	{
		*string = GAP_ASCII;
		++string;
		*string = '\0';
		return base_string;
	}

	if (num_to_string < 0)	/*put minus for negatives*/
	{
		*string = '-';
		num_to_string *= -1;
		++string;
	}

	if (1 == base)	/*for base 1*/
	{
	string = base_string;

		while (num_to_string > 0)
		{
			*string = base + GAP_ASCII;
			++string;
			--num_to_string;
		}

	*string = '\0';
	return base_string;
	}

	len = DigitsInNumAnyBase(num_to_string, base);	/*num of digits*/

	string += len;	/*put '\0' at last char*/
	*string = '\0';

	while (len > 0)
	{
		--string;		
		num_or_letter = num_to_string % base;

		if (num_or_letter > MAX_DIGIT)	/*letters*/
		{
			*string = num_or_letter + GAP_ASCII_LETTERS;
		}
		else							/*nums*/
		{
			*string = num_or_letter + GAP_ASCII;
		}

		num_to_string /= base;
		--len;
	}
	
	return base_string;
	
}


static int DigitsInNumAnyBase(int num, int base)
{
	int digits = 0;
	
	while(num != 0)
    {
        ++digits;		/* Increment digit count  */
        num /= base;	/*Remove last digit of num*/
    }

    return digits;
}


void PrintChars(char *arr1, char *arr2, char *arr3,size_t elements1,
									size_t elements2, size_t elements3)
{
	int lut_chars[256] = {0};
	
	while(elements1 > 0)
	{
		lut_chars[(int)*arr1] = 1;	/*sign 1 at LUT for all nums*/
		++arr1;						/*	 that appear in arr1	*/
		--elements1;
	}
	
	while(elements3 > 0)
	{
		lut_chars[(int)*arr3] = 0;	/*sign 0 at LUT for all nums*/
		++arr3;						/*   that appear in arr3	*/
		--elements3;
	}

	while(elements2 > 0)			/*find nums that are signed*/
	{								/*with 1 and print them out*/
		if (lut_chars[(int)*arr2] == 1)
		{
			printf("%c ", *arr2);
			lut_chars[(int)*arr2] = 0;	/*sign 0 number printed*/
		}
		
		++arr2;
		--elements2;
	}
	puts(" ");
}

int IsLittleEndian()
{
	short num = 1;
	char *ptr = (char*)&num;	/*point at the left digit*/

	return *ptr;	/*return the value of left digit 0 OR 1*/
	
}






