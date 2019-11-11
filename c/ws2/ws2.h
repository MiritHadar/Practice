/******************************************************************************
*	Description: Implementation of the string.h header functions			   *
*	Author: Mirit Hadar													       *
*	Reviewer: Or Marziano													   *
*	Status: Sent														       *
*	Last Update: 11.4.19													   *
*******************************************************************************/


#ifndef __WS2_OL67
#define __WS2_OL67

size_t StrLen(const char *str);
int StrCmp(const char *string1, const char *string2);
char *StrCpy(char *dest, const char *src);
char *StrNCpy(char *dest, const char *src, size_t n);
int StrCaseCmp(const char *str1, const char *str2);
char *StrDup(const char *str);
void Swap(int **ptr1, int **ptr2);
void SevenBoom(int from, int to);
int IsPalindrome(const char *str);
char *StrChr(const char *str, int ch);
char *StrCat(char *dest, const char *src);
char *StrNCat(char *dest, const char *src, size_t n);
char *StrStr(const char *haystack, const char *needle);
size_t StrSpn(const char *s, const char *accept);
char *StrTok(char *str, const char *delim);
void RmSpaces(char *str);
int IsPolindrome(const char *str);
char *AddBigNums(const char *str1, const char *str2);









#endif /*__WS2_OL67*/

