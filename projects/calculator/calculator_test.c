
#include <stdio.h>
#include "calculator.h"



int main()
{
    char *str1 = "(2 + 6) / 3";
	char *str2 = "2 + (6 / 3)";

    double result = Calculate(str1);
    printf("%s = %.1f\n", str1, result);

    result = Calculate(str2);
    printf("%s = %.1f\n", str2, result);

    return 0;
}

/*
#include "calculator.h"
#include "stdio.h"


int main(void)
{
	printf("%f\n", Calculate("5 + 8 / (2 + 6)"));
	printf("%f\n", Calculate("5 + 8 / 8"));
	printf("%f\n", Calculate("5 / (2 + 3)"));


	if (6 != Calculate("5 + 8 / (2 + 6)"))
	{
		printf("faild %d\n", __LINE__);
	}

	if (-136 != Calculate("(15 + (32 - 183))"))
	{
		printf("faild %d\n", __LINE__);
	}

	printf("result : %f\n", Calculate("(5 + (8 / 2 - 6/3) * 15 + (32 - 183 + (157 +3)) / 4)"));

	if (37.25 != Calculate("(5 + (8 / 2 - 6/3) * 15 + (32 - 183 + (157 +3)) / 4)"))
	{
		printf("faild %d\n", __LINE__);
	}

	if (5 != Calculate("5"))
	{
		printf("faild %d\n", __LINE__);
	}

	if (0 != Calculate("0"))
	{
		printf("faild %d\n", __LINE__);
	}


	return 0;
}*/
