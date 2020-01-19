

#include <stdio.h> /* fopen, getline*/

/* h file */
int Parse(const char *fileName_);

/* c file */
int Parse(const char *fileName_)
{
    FILE *fp = fopen(fileName_, "r");
    if (fp == NULL)
    {
        return 1;
    }
    
}

/* test file */
int main()
{

    return 0;
}