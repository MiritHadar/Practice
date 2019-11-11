/******************************************************************************
*	Description: Implementation of the string.h header functions			   *
*	Author: Mirit Hadar													       *
*	Reviewer: Or Marziano													   *
*	Status: Sent														       												   *
*******************************************************************************/


#include <stdio.h>      /* for size_t variable	  */
#include <string.h>     /* for string functions   */
#include <stdlib.h>     /* for malloc			  */
#include <assert.h> 	/* for assert   		  */
#include <ctype.h>      /* for tolower            */
#include "ws2.h"

#define LEFT_DIGIT_OFF        38
#define CHAR_TO_INT(x)    (x-48)
#define INT_TO_CHAR(x)    (x+48)
#define ASCII_SUM_10         106

/*
this function returns the length of a string
*/

size_t StrLen(const char *str)
{

	const char *str_start = str;	
	
	assert(str);
	
	while ('\0' != *str)
	{
		++str;
	}	

	return (str - str_start);
}



/*
this function receives two strings and returns true if there are identical
*/

int StrCmp(const char *string1, const char *string2)
{
    assert(string1);
    assert(string2);
    
	while ((*string1 == *string2) && ('\0' != *string1))
	{
		++string1;
		++string2;
	}

return *string1 - *string2;

}



/*
this function receives two strings and copies the second one (src)
in to the first (dest)
*/
char *StrCpy (char *dest, const char *src)
{
    char *base_dest = NULL;
    
    assert(dest);
    assert(src);
    
    base_dest = dest;
    
    while ('\0' != *src)
    {
        *dest = *src;
        ++src;
        ++dest;
    }

    *dest = '\0';
    
    return base_dest;
}


/*
this function receives two strings and copies n elements
from the second one (src) in to the first (dest)
*/
char *StrNCpy(char *dest, const char *src, size_t n)
{
    char *base_dest = NULL;
    
	assert(dest);
	assert(src);
	
	base_dest = dest;
	
	while ('\0' != *src && n > 0)
	{
        *dest = *src;
        ++dest;
        ++src;
	    --n;
	}
	
    while ( n > 0)
	{
		*dest = '\0';
		++dest;
		--n;
	}
	
	return base_dest;
}


/*
this function recieves two strings and compares them ignoring lower
and upper cases. 
*/
int StrCaseCmp(const char *str1, const char *str2)
{
	assert(str1);
	assert(str2);
	while ((*str1 != '\0') && (tolower(*str1) == tolower(*str2)))
	{
		++str1;
		++str2;
	}

	return (tolower(*str1) - tolower(*str2));
}

/*
this function receives a string and duplicates it
*/
char *StrDup(const char *str)
{

	char *newStr = NULL;
	
	/*allocating space in the memory*/
	newStr = (char*)malloc(strlen(str) * sizeof(char)+1);
	
	if (NULL == newStr)
		{
			fprintf(stderr, "non allocation\n");
			return NULL;
		}	

	return StrCpy(newStr, str);
}



/*
this function recieves two pointers to ints and swaps them
*/
void Swap(int **ptr1, int **ptr2)
{
	int *tmp = NULL;
	
	assert(ptr1);	
	assert(ptr2);	
	
	tmp = *ptr1;
	*ptr1 = *ptr2;
	*ptr2 = tmp;
}


/*
this function recieves a range and prints out all the numbers within the range
except numbers that contain 7 and that devide by 7 with no remainder - 
then will print "BOOM"
*/
void SevenBoom(int from, int to)
{
	int i, tmp, flag = 0;
	
	for (i = from; i <= to; ++i)
	{
		flag =0; /*zeroing the flag*/
		
		if (i % 7 == 0) 
		{
			printf ("BOOM "); /*print BOOM instead #1*/
			flag = 1;
		}
		
		if (flag ==0)
		{
			tmp = i;

			while ((tmp != 0) && (flag == 0))
			{		
				if (tmp % 10 == 7)
				{		
					printf("BOOM "); /*print BOOM instead #2*/
					flag = 2;
				}

				tmp /= 10;				
			}
			
			if (flag == 0)
			{
				printf ("%d ", i); /*print number #0*/
			}
		}
	}
}

/*
this function recieves a string and returns 1 if it is a polidrome,
returns 0 if it is not
*/
int IsPalindrome(const char *str)
{
	const char *end = str + StrLen(str) - 1;
	
	assert(str);

	while (str < end)
	{
		if (*str != *end)
		{
			return 0;   /*when found a diff hear return false*/
		}
		--end;
		++str;
	} 
	
	return 1;
}

/*
this function recieves a string and a char and returns a pointer
to place of the char in the string
*/
char *StrChr(const char *str, int ch)
{
    assert(str);
    assert(ch >= 0 );
    
    while ('\0' != *str)
    {
        if (*str == ch)
        {
            return (char*)str;
        }
        
        ++str;
    }
    
    if (*str == ch)
    {
        return (char*)str;
    }
    
    return NULL;
}



/*
this function recieves a dest string and a dest string and concatenates
the src in to the dest
*/

char *StrCat(char *dest, const char *src)
{
    
	char *base_dest = dest;
	
	assert(dest);
	assert(src);

	dest += StrLen(dest);
	dest = StrCpy(dest, src);

	return base_dest;
}


char *StrNCat(char *dest, const char *src, size_t n)
{
	char *base = dest;

	assert(NULL != dest);
	assert(NULL != src);
	
	dest += StrLen(dest);
	dest = StrNCpy(dest, src, n);	

	return (base);
}


char *StrStr(const char *haystack, const char *needle)
{
	const char *needle_base = needle;
	const char *haystack_base = haystack;

	assert(haystack);
	assert(needle);

	if (NULL == StrChr(haystack, *needle))
	{
		return NULL;
	}
	
	while (NULL != StrChr(haystack, *needle))
	{
		haystack = StrChr(haystack, *needle);	
		haystack_base = haystack;
		
		while (*haystack == *needle && '\0' != *needle)
		{
			++haystack;
			++needle;
		}
		if ('\0' == *needle)
		{	
			return (char*)haystack_base;
		}
		else
		{
			
			haystack = haystack_base + 1;
		}
		needle = needle_base;
	}

	return (char*)haystack_base;
}


/*StrSpn*/
size_t StrSpn(const char *s, const char *accept)
{
	size_t result = 0;
	
	assert(NULL != s);
	assert(NULL != accept);

	while (NULL != StrChr(accept, *s) && '\0' != *s)
	{
		++s;
		++result;
	}	

	return result;
}


/*StrTok*/
char *StrTok(char *str, const char *delim)
{
	static char *stt_str = NULL;
	char *base = NULL;
	
	assert(delim);
	
	if (NULL != str)
	{
		stt_str = str;
	}
    

	while (NULL != StrChr(delim, *stt_str) && '\0' != *stt_str)
	{	
		*stt_str = '\0';
		++stt_str;	
	}
	
	if ('\0' != *stt_str)
	{
		base = stt_str;
    }
    
	while (NULL == StrChr(delim, *stt_str) && '\0' != *stt_str)
	{
		++stt_str;
	}

	if ('\0' != *stt_str)
	{
        *stt_str = '\0';
		++stt_str;
	}
	
	return base;
}


/*RmSpaces*/
void RmSpaces(char *str)
{
	char *token = str;

	assert(NULL != str);	

	token = StrTok(str, "\t \n");

	while (NULL != token)
	{
		str = StrCpy(str, token);
		str += StrLen(str);
		*str = ' ';
		++str;	
		token = StrTok(NULL, "\t \n");
	}
	
	--str;
	*str = '\0';
	
}

/*Adds two big numbers represented by strings*/
char *AddBigNums(const char *str1, const char *str2)
{
	int carry = 0;
	char const *shorter = NULL;
	char const *longer = NULL;
	char *result = NULL;
	size_t long_len = 0;	
	size_t short_len = 0;
	
	if (strlen(str1) >= strlen(str2))
	{
	    longer = str1;
	    shorter = str2;
	    long_len = strlen(str1);
	    short_len = strlen(str2);
	}
	else
	{
        longer = str2;
	    shorter = str1;
	    long_len = strlen(str2);
	    short_len = strlen(str1);	    
	}
	
	result = malloc(sizeof(longer) + 8);
	result += strlen(longer) + 1;
	longer += strlen(longer);
	shorter += strlen(shorter);
	
	*result = '\0';
	
	while (short_len > 0)
	{
        --result;
	    --shorter;
	    --longer;
	    
	    if (*longer + *shorter + carry >= ASCII_SUM_10)
	    {
	        *result = CHAR_TO_INT(*longer) + CHAR_TO_INT(*shorter) + carry + LEFT_DIGIT_OFF;
	         carry = 1;
	    }
	    else
	    {
	        *result = CHAR_TO_INT(*longer) + CHAR_TO_INT(*shorter) + carry + 48;
	        carry = 0;
	    }
	     
	    --long_len;
	    --short_len;
	}
	/*TODO*/
	while (long_len > 0)
	{
	    --longer;
	    --result;
	    
	    if (*longer + carry >= ASCII_SUM_10)
	    {
             *result = CHAR_TO_INT(*longer) + carry + LEFT_DIGIT_OFF;
	         carry = 1;
	    }
	    else
	    {
	        *result = CHAR_TO_INT(*longer) + carry + 48;
	        carry = 0;
	    }
	    
	    --long_len;

	}
	
	--result;
	
	if (1 == carry)
	{
	    *result = INT_TO_CHAR(carry);
	}
	else
	{
	    *result = '\0';
	    ++result;
	}
	
	return result;
}



