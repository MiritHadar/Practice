
#include <stdio.h>
void Hanoi(int n, char from, char to, char using);

int main()
{
    Hanoi(3, 'A', 'C', 'B');
    return 0;
}

void Hanoi(int n, char from, char to, char using)
{
    if (n == 1)
    {
        printf("Move disk #1 from %c to %c\n", from, to); 
        return; 
    }
    Hanoi (n - 1, from, using, to);
    printf("Move disk #%d from %c to %c\n", n, from, to);
    Hanoi (n - 1, using, to, from);
}
