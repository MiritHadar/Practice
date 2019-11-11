/******************************************************************************
*	Description: Implementation of the string.h header functions			   *
*	Author: Mirit Hadar													       *
*	Reviewer: 													  			   *
*	Status: 														           *
*	Last Update: 													           *
*******************************************************************************/


#ifndef __WS9_OL67
#define __WS9_OL67
#include <stddef.h>

void *Memset(void *s, int c, size_t n);
void *Memcpy(void *dest, const void *src, size_t n);
void *Memmove(void *dest, const void *src, size_t n);
int Atoi(const char *num_string);
char *Itoa(char *str, int num_to_string);
int AtoiAnyBase(const char *str_to_int, int base);
char *ItoaAnyBase (char *string, int num_to_string, int base);
void PrintChars(char *, char *, char *,size_t, size_t, size_t);
int IsLittleEndian();

#endif /*__WS2_OL67*/
