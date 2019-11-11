
#include <stdio.h>	/*printf*/
#include <stdlib.h>	/*malloc*/
#include <string.h>
#include "ws9.h"

#define IS_LITTLE_ENDIAN (*(short*)("\1") == 1)

void MemsetTest();
void MemcpyTest();
void MemmoveTest();
void AtoiTest();
void ItoaTest();
void AtoiAnyBaseTest();
void ItoaAnyBaseTest();
void PrintCharsTest();
void IsLittleEndianTest();

int main()
{
	MemsetTest();
	MemcpyTest();
	MemmoveTest();
	AtoiTest();
	ItoaTest();
	AtoiAnyBaseTest();
	ItoaAnyBaseTest();
	PrintCharsTest();
	IsLittleEndianTest();
	printf ("IS_LITTLE_ENDIAN : %d\n", IS_LITTLE_ENDIAN);
	return 0;

} 

void MemsetTest()
{
	int num = 9;
	char *str = NULL;
	char *str_result = NULL; 
	char *base_str = NULL;
	
	str = malloc(48*sizeof(char));
	if (str == NULL)
	{
		puts("Error: allocating memory failed");
		return;
	}
	
	strcpy(str, "Hello World,Hello World,Hello World,Hello World");
	base_str = str;
	str_result = (char*)(Memset(&num, '#', 4));
	printf("Memset = %c%c%c%c\n",
		   *str_result, *(str_result+1), *(str_result+2),*(str_result+3));

	free(base_str); base_str = NULL;

}

void MemcpyTest()
{
	char *dest = NULL;
	char *src = NULL;

	dest = malloc(48*sizeof(char));
	if (dest == NULL)
	{
		puts("Error: allocating memory failed");
		return;
	}

	src = malloc(21*sizeof(char));
	if (src == NULL)
	{
		puts("Error: allocating memory failed");
		return;
	}

	strcpy(dest, "Hello World,Hello World,Hello World,Hello World");
	strcpy(src, "12345678901234567890");
	printf("Memcpy = %s\n", (char*)(Memcpy(dest, src, 12)));

	free(dest); dest = NULL;
	free(src); src = NULL;

}

void MemmoveTest()
{
	char dest[10] = "123456789";
	Memmove(dest+3, dest, 6);
	printf("memmove = %s\n", dest);
}

void AtoiTest()
{
	int num = 0;
	char *num_string = "-5456789";
	
	num = Atoi(num_string);
	printf("Atoi %d\n", num);
}

void ItoaTest()
{
	int num = 0;
	char num_string[1];
	
	Itoa(num_string, num);
	printf("Itoa %s\n", num_string);
}

void AtoiAnyBaseTest()
{
	int num = 0;
	char num_string[2] = "10";
	
	num = AtoiAnyBase(num_string, 16);
	printf("AtoiAnyBase %d\n", num);
}

void ItoaAnyBaseTest()
{
	int num = 3;
	char num_string1[10];
	char num_string2[10];
	char num_string3[10];
	char num_string4[10];

	printf("ItoaAnyBase %s\n", ItoaAnyBase(num_string1, num, 1));

	printf("ItoaAnyBase %s\n", ItoaAnyBase(num_string2, num, 8));

	printf("ItoaAnyBase %s\n", ItoaAnyBase(num_string3, num, 9));

	printf("ItoaAnyBase %s\n", ItoaAnyBase(num_string4, num, 36));
}

void PrintCharsTest()
{
	char arr1[] = "abcabcdbb";
	char arr2[] = "arcrbcdab";
	char arr3[] = "bcsbcsqqc";
	PrintChars(arr1, arr2, arr3, 9, 9, 9);
}

void IsLittleEndianTest()
{
	int result = IsLittleEndian();
	if (result == 0)
	{
		puts("IsLittleEndian : 0");
	}
	else
	{
		puts("IsLittleEndian : 1");
	}
}




