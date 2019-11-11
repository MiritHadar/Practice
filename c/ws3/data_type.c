#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>



int main()

{
	puts("*******sizeof all variable types********** :\n");

	printf("short int = %lu\n", sizeof(short int));
	printf("unsigned short int = %lu\n", sizeof(unsigned short int));
	printf("long int = %lu\n", sizeof(long int));
	printf("unsigned long int = %lu\n", sizeof(unsigned long int));
	/*printf("long long int = %lu\n", sizeof(long long int)); not supported*/
	printf("signed char = %lu\n", sizeof(signed char));
	printf("unsigned int = %lu\n", sizeof(unsigned int));
	/*printf("unsigned long long int = %lu\n", sizeof(unsigned long long int));*/
	printf("unsigned char = %lu\n", sizeof(unsigned char));
	printf("float = %lu\n", sizeof(float));
	printf("int = %lu\n", sizeof(int));
	printf("double = %lu\n", sizeof(double));
	printf("long double = %lu\n", sizeof(long double));
	
	return 0;
}
