
#include <stdio.h>
#include <signal.h>

struct X
{
/*     explicit X();
 */    int a;
    int b;
    ~X();
};

X::~X()
{
    puts("destroy");
}

int main()
{
    X x1;
    X x2;
    X x3;

    X& copy = x1;
    x1.a = 4;
    x1.b = 6;
    printf("%lu\n", sizeof(x1));
    printf("%lu\n", sizeof(copy));

    printf("a = %d b = %d\n", x1.a, x1.b);
    puts("not yet...............");

    return 0;
}

