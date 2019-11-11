
/*
This function recieves an exponant and return the result of 10 in that exponent
*/

#include <stdio.h>

double power(int exp);

int main()
{
	printf("for negative : %.2f\n", power(1));
	printf("for zero : %.2f\n", power(0));
	printf("for positive : %.2f\n", power(-1));

	return 0;
}

double power(int exp)
{
	int i = 0;	
	double ans = 1;
	
	if (exp < 0) /*when exp is negative*/
	{
			exp *= -1;
			for (i = 0; i < exp; i++)
				ans = ans * 10;
			return 1/ans;
	}
	else /*when exp is zero ro positive*/
	{
		for (i = 0 ; i < exp ; ++i)
			ans *= 10;
		return ans;
	}
}



