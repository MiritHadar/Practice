/******************************************************************************/
/* author:   	Mirit Hadar												  */		
/* reviewer: 	Ori Marziano												  */
/* version: 	                                                      */
/* Last update: 12.05.19                                                      */
/******************************************************************************/
#include <stdio.h>		/*printf, size_t	  */
#include <string.h>		/*strlen,srtcmp...	  */
#include <strings.h>	/*strcasecmp		  */
#include <stdlib.h>		/*malloc			  */
#include "ws2.h"		

void TestStrLen();
void TestStrCmp();
void TestStrCpy();
void TestStrNCpy();
void TestStrCaseCmp();
void TestStrChr();
void TestStrDup();
void TestStrCat();
void TestStrNCat();
void TestStrStr();
void TestStrSpn();
void TestStrTok();
void TestIsPalindrome();
void TestPointerSwap();
void TestRmSpaces();
void TestAddBigNums();

int main()
{
	TestStrLen();
	TestStrCmp();
	TestStrCpy();
	TestStrNCpy();
	TestStrCaseCmp();
	TestStrChr();
	TestStrDup();
	TestStrCat();
	TestStrNCat();
	TestStrStr();
	TestStrSpn();
	TestStrTok();
	TestIsPalindrome();
	SevenBoom(89, 30);
	TestPointerSwap();
	TestRmSpaces();
	TestAddBigNums();

	return 0;
}

/***********************************Test Section*******************************/

void TestStrLen()
{	
	if (StrLen("mirit hadar") != strlen("mirit hadar"))
	{
		printf("Error in StrLen\n");
	}
	if (StrLen("") != strlen(""))
	{
		printf("Error in NULL StrLen\n");
	}
}

void TestStrCmp()
{	
	const char *str1 = "ball";	
	const char *str2 = "balerine";
	
	if (StrCmp(str1,str2) > 0 && strcmp(str1,str2) <= 0)
	{
		printf("Error in StrCmp funcs\n");
	}
	if (StrCmp(str1,str2) < 0 && strcmp(str1,str2) >= 0)
	{
		printf("Error in StrCmp funcs\n");
	}
	if (0 == StrCmp(str1,str2) && 0 != strcmp(str1,str2))
	{
		printf("Error in StrCmp funcs\n");
	}
}

void TestStrCpy()
{
	const char *src = "Hello World";
	char dest[50] = "";

	if(StrCpy(dest, src) != strcpy(dest, src))
	{
		printf("Error in copying\n");
	}
	if(StrCpy(dest, "") != strcpy(dest, ""))
	{
		printf("Error in copying\n");
	}

}

void TestStrNCpy()
{
	const char *src = "Hello World";
	char dest[50] = "";
	size_t num_of_chars = 6;
	
	if (StrNCpy(dest, src, num_of_chars) != strncpy(dest, src, num_of_chars))
	{
		printf("Error in copying\n");
	}
	if (StrNCpy(dest, src, 5) != strncpy(dest, src, 5))
	{
		printf("Error in copying\n");
	}
	if (StrNCpy(dest, src, 4) != strncpy(dest, src, 4))
	{
		printf("Error in copying\n");
	}
	if (StrNCpy(dest, "", num_of_chars) != strncpy(dest, "", num_of_chars))
	{
		printf("Error in copying\n");
	}
}

void TestStrCaseCmp()
{
	const char *s1 = "MIRIT";
	const char *s2 = "MIrit";	

	if (StrCaseCmp(s1, s2) != strcasecmp(s1, s2))
	{
		puts("Error in StrCaseCmp");
	}
}
void TestStrChr()
{	
	const char str[] = "Hello World";	
	int c = 'z';
	
	if (StrChr(str, c) != strchr(str, c))
	{
		printf("Error in StrChr\n");
	}
	if (StrChr(str, 'e') != strchr(str, 'e'))
	{
		printf("Error in StrChr\n");
	}
	if (StrChr("", c) != strchr("", c))
	{
		printf("Error in StrChr\n");
	}
	if (StrChr(str, 0) != strchr(str, 0))
	{
		printf("Error in StrChr\n");
	}
	if (StrChr("", 0) != strchr("", 0))
	{
		printf("Error in StrChr\n");
	}
	
}

void TestStrDup()
{
	char *str1 = "Mirit Hadar";
	char *str2 = StrDup(str1);
	int result = StrCmp(str1, str2);

	if (0 != result)
	{
		puts("Error in StrDup");
	}

	str1 = StrDup("");
	result = StrCmp("", str1);
	if (0 != result)
	{
		puts("Error in StrDup");
	}
	
	free(str1);
	free(str2);

	str1 =NULL;
	str2 =NULL;
}

void TestStrCat()
{
	const char *src = "llo";
	char dest[100] = "he";
	char dest2[100] = "he";
		
	if (0 != StrCmp(StrCat(dest, src) , strcat(dest2, src)))
	{
		puts("Error in StrCat");
	}
	if (0 != StrCmp(StrCat(dest, ""), strcat(dest2, "")))
	{
		puts("Error in StrCat");
	}
	
}

void TestStrNCat()
{
	const char *src = "llo";
	char dest[100] = "he";
	
	if (StrNCat(dest, src, 2) != strncat(dest, src, 2))
	{
		puts("Error in StrNCat");
	}
	if (StrNCat(dest, src, 5) != strncat(dest, src, 5))
	{
		puts("Error in StrNCat");
	}
	if (StrNCat(dest, src, 7) != strncat(dest, src, 7))
	{
		puts("Error in StrNCat");
	}
	if (StrNCat(dest, "", 2) != strncat(dest, "", 2))
	{
		puts("Error in StrNCat");
	}
}

void TestStrStr()
{
	if (StrStr("helllo", "llo") != strstr("helllo", "llo"))
	{
		puts("Error in StrStr");
	}
	if (StrStr("hellloc", "llo") != strstr("hellloc", "llo"))
	{
		puts("Error in StrStr");
	}
	if (StrStr("llhelllo", "llo") != strstr("llhelllo", "llo"))
	{
		puts("Error in StrStr");
	}	
	
	if (StrStr("abc", "d") != strstr("abc", "d"))
	{
		puts("Error in StrStr");
	}
	if (StrStr("", "gjh") != strstr("", "gjh"))
	{
		puts("Error in StrStr");
	}
}

void TestStrSpn()
{	
	if (StrSpn("", "") != strspn("", ""))
	{
		puts("Error in NULL & NULL StrSpn");
	}
	if (StrSpn("sad", "") != strspn("sad", ""))
	{
		puts("Error in string & NULL StrSpn");
	}
	if (StrSpn("wer", "werd") != strspn("wer", "werd"))
	{
		puts("Error in short string & long string StrSpn");
	}
	if (StrSpn("", "gf") != strspn("", "gf"))
	{
		puts("Error in NULL string in string StrSpn");
	}
	if (StrSpn("abfd", "acb") != strspn("abfd", "acb"))
	{
		puts("Error in StrSpn");
	}
	if (StrSpn("sav", "av") != strspn("sav", "av"))
	{
		puts("Error in StrSpn");
	}
}

void TestStrTok()
{
	const char *delim = "ol";
	char str[50] = "hello worlcdl";
	char str1[50] = "hello worlcdl";
    char *token = StrTok(str, delim); 
	char *token2 = strtok(str1, delim);

	if (0 != StrCmp(token, token2))
	{
		puts("Initializied token in StrTok failed");
		return;
	}

    while (NULL != token)
	{  
		if (0 != StrCmp(token, token2))
		{
			puts("Initializied token in StrTok failed");
			return;
		}

   		token = StrTok(NULL, delim); 
		token2 = strtok(NULL, delim);
	}
}

void TestIsPalindrome()
{
	if (IsPalindrome("ab111ba") != 1)
	{
		puts("Error in IsPelindrome");
	}
	if (IsPalindrome("") != 1)
	{
		puts("Error in IsPelindrome\n");
	}
	if (IsPalindrome("ab1111ba") != 1)
	{
		puts("Error in IsPelindrome\n");
	}	
	if (IsPalindrome("1") != 1)
	{
		puts("Error in IsPelindrome\n");
	}
	if (IsPalindrome("ab111bc") != 0)
	{
		puts("Error in IsPelindrome");
	}
	if (IsPalindrome("ab1sd11bc") != 0)
	{
		puts("Error in IsPelindrome");
	}
}

void TestPointerSwap()
{
	int a = 3;
	int b = 7;
	int *pa = &a;
	int *pb = &b;
	
	if (*pa != a || *pb != b)
	{
		puts("Error in Pointer initialization");
	}

	Swap(&pa, &pb);

	if (*pa != b || *pb != a)
	{
		puts("Error in PointerSwap");
	}
}

void TestRmSpaces()
{
	char str[] = "  sadd sdf  d	v	";
	printf("String before RmSpaces:%s\n",str);
	RmSpaces(str);
	printf("String after RmSpaces:%s\n",str);
}


void TestAddBigNums()
{
	char *result = NULL;

	result = AddBigNums("99", "1");
	
	printf("AddBigNums = %s\n", result);
}
