
#define _GNU_SOURCE

#include <stdio.h>
#include <dlfcn.h>

typedef void (*func_t)(void);

int main(int argv, char **argc)
{
    Foo_dl();

    return 0;
}