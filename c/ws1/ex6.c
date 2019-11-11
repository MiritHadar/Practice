#include <stdio.h>

void swap(int *num1, int *num2);

int main()
{
	int num1=0, num2=0;
	Mirit();
	printf("type number 1 : ");
	scanf("%d", &num1);
	printf("type number 2 : ");
	scanf("%d", &num2);
	swap(&num1, &num2);
	printf("after swap : %d , %d\n", num1, num2);
	return 0;
}


void swap(int *pnum1, int *pnum2)
{
	int temp;
	temp = *pnum1;
	*pnum1 = *pnum2;
	*pnum2 = temp;
}

void Mirit()
{
	puts("mirit rules");
}

