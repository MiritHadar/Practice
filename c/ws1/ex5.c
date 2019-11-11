/*
A function that receives an int and flips it
*/

#include <stdio.h>

int flip(int num);

int main()
{
	int num=0;
	printf("type a number : ");
	scanf("%d", &num);
	printf("The reversed number is : %d\n", flip(num));
	return 0;
}

//the function that flips a number
int flip(int num)
{
	int ans, flipped_num=0; 
	
	int last_digit;
while (num != 0)
{
	last_digit = num%10; //take the last digit
	num /= 10; //shorten the num by 1 digit
	flipped_num += last_digit; //add the last digit extracted
	if (num > 0)
		flipped_num *= 10; //move digits right by 1
}
	
	return flipped_num;
}

