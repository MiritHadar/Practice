#include <stdio.h>
#include <stddef.h>
#include <string.h>

size_t RecursiveStrlen(char *str);
int GcdRecursiveMinus(int num1, int num2);
int GcdRecursiveModul(int num1, int num2);
int GcdIterator(int num1, int num2);
int RecursiveStrCmp(char *str1, char *str2);
char *RecursiveStrCpy(char *dest, const char *src);
char *RecursiveStrCat(char *dest, const char *src);
char *RecursiveStrStr(const char *haystack, const char *needle);
int Fibonacci(int n);


int main()
{
    int i = 0;
    char *str1 = "abc def";
    char *str2 = "abc de";
    char *str3 = "abc def";
    const char *src = "mirit pariente hadar";
    char dest1[20] = "good";
    char *src1 = " morning";
    char *dest1_ptr = dest1;
    char dest[50] = "";
    char *dest_ptr = dest;
    

    int result = GcdIterator(48, 18);
    printf("%d\n", result);
    result = GcdIterator(99, 9);
    printf("%d\n", result);
    result = GcdIterator(15, 13);
    printf("%d\n", result);

    result = GcdRecursiveModul(48, 18);
    printf("%d\n", result);
    result = GcdRecursiveModul(99, 9);
    printf("%d\n", result);
    result = GcdRecursiveModul(15, 13);
    printf("%d\n", result);

    printf("%lu\n", RecursiveStrlen("mirit hadar"));
    printf("cmp different : %d\n", RecursiveStrCmp(str1, str2));
    printf("cmp the same : %d\n", RecursiveStrCmp(str1, str3));

    for(i = 0; i < 10; ++i)
    {
      printf("%d ",Fibonacci(i));            
    }

    puts("");

    dest_ptr = RecursiveStrCpy(dest_ptr, src);

    printf("%s\n", dest_ptr);

    dest1_ptr = RecursiveStrCat(dest1, src1);

    printf("%s\n", dest1_ptr);

    printf("%s\n", RecursiveStrStr(dest1, src1));

}

size_t RecursiveStrlen(char *str)
{
    if ('\0' == *str)
    {
        return 0;
    }
    
    return (1 + RecursiveStrlen(str+1));
}

int GcdRecursiveModul(int num1, int num2)
{
    if (0 != num1 && 0 != num2)
    {
        return GcdRecursiveModul(num2 % num1, num1);
    }

    return num2;
}


int GcdRecursiveMinus(int num1, int num2)
{
    if (num1 == num2)
    {
        return num1;
    }
    if (num1 > num2)
    {
        return GcdRecursiveMinus(num2, num1 - num2);
    }
    else
    {
        return GcdRecursiveMinus(num2 - num1, num1);
    }
}

int GcdIterator(int num1, int num2)
{
    int big = num1;
    int small = num2;
    size_t i = 0;

    if (num1 >= num2)
    {
        big = num1;
        small = num2;
    }
    else
    {
        big = num2;
        small = num1;
    }
    
    if (big % small == 0)
    {
        return small;
    }

    for (i = (small / 2); i > 0; --i)
    {
        if ((big % i == 0) && (small % i == 0))
        {
            return i;
        }
    }
}

int Fibonacci(int n)
{
    if (n == 0)
    {
        return 0;
    }

    if (n == 1)
    {
        return 1;
    }

    return (Fibonacci(n - 1) + Fibonacci(n - 2));
}


int RecursiveStrCmp(char *str1, char *str2)
{
    if (*str1 != *str2 || *str1 == '\0')
    {
        return *str1 - *str2;
    }
    else
    {
        return RecursiveStrCmp(str1 + 1, str2 + 1);
    }
}

char *RecursiveStrCpy(char *dest, const char *src)
{
    if ('\0' == *src)
    {
        *dest = '\0';
        return dest;
    }
    else
    {
        *dest = *src;
        return RecursiveStrCpy(dest + 1, src + 1) - 1;
    }
}

char *RecursiveStrCat(char *dest, const char *src)
{
    /* proceed till finding end of string */
    if ('\0' != *dest)
    {
        RecursiveStrCat(dest + 1, src);
    }
    else
    {
        *dest = *src;

        if (*src != '\0')
        {
            RecursiveStrCat(dest + 1, src + 1);
        }

    }

    return dest;

}

char *RecursiveStrStr(const char *haystack, const char *needle)
{
    if ('\0' == haystack)
    {
        return NULL;
    }
    else if (0 == strncmp((char*)haystack, needle, strlen(needle)))
    {
        return (char*)haystack;
    }
    else
    {
        return RecursiveStrStr(haystack + 1, needle);
    }
}