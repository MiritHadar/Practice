
#include <stdio.h>	/*printf*/
#include <stdlib.h> /*malloc & free*/
#include <string.h>	/*strcat, strcpy*/
#include <assert.h>	/*assert*/

#define SIZE_ARR 3	/*size of array*/
#define UNUSED_VAR(x) (void)(x)

typedef struct element element_t; /*struct inside struct*/

struct element
{
	void *data;	/*receiving data*/
	int (*AddFuncs)(element_t *el, int num); /*Add*/
	void (*PrintFuncs)(element_t *el);	/*Print*/
	void (*FreeFuncs)(element_t *el);	/*Free for string*/
};

/*Initialization Funcs*/
void InitInt(element_t *arr);
void InitFloat(element_t *arr);
int InitString(element_t *arr);

/*Action Funcs*/
int AddInt(element_t *el, int num);
int AddFloat(element_t *el, int num);
int AddString(element_t *el, int num);

void PrintInt(element_t *el);
void PrintFloat(element_t *el);
void PrintString(element_t *el);

void Free(element_t *el);
void VoidFree(element_t *el);

int DigitsInNum(int num);


int main()
{	
	int num = 40;	/*number to add*/
	int i = 0;

	/*array of 3 structure element*/
	element_t arr[SIZE_ARR];

	/*initialize*/
	InitInt(arr);
	InitFloat(arr + 1);
	InitString(arr + 2);

	for(i = 0; i < SIZE_ARR; ++i)
	{
		arr[i].AddFuncs(&arr[i] ,num);	/*Add*/
	}
	for(i = 0; i < SIZE_ARR; ++i)
	{
		arr[i].PrintFuncs(&arr[i]);	/*Print*/
	}
	for(i = 0; i < SIZE_ARR; ++i)
	{
		arr[i].FreeFuncs(&arr[i]);	/*Free*/
	}

	return 0;
}


void InitInt(element_t *el)
{
	assert(el);

	*(int*)&(el->data) = 678;
	el->AddFuncs = AddInt;
	el->PrintFuncs = PrintInt;
	el->FreeFuncs = VoidFree;
}

void InitFloat(element_t *el)
{
	assert(el);

	*(float*)&(el->data) = 0.0;
	el->AddFuncs = AddFloat;
	el->PrintFuncs = PrintFloat;
	el->FreeFuncs = VoidFree;
}

int InitString(element_t *el)
{
	assert(el);

	el->data = (char*)malloc(sizeof(char)*20);	/*allocate space*/
	if ((el->data) == NULL)
	{
		printf("Not enough memory space\n");
		return 0;
	}

	strcpy(el->data, "something");
	el->AddFuncs = AddString;
	el->PrintFuncs = PrintString;	
	el->FreeFuncs = Free;		
	return 1;
}

int AddInt(element_t *el, int num)	/*add to int*/
{
	assert(el);
	assert(num);

	*((int*)&(el->data)) += num;
	return 1;
}

int AddFloat(element_t *el, int num)	/*add to float*/
{
	assert(el);
	assert(num);

	*((float*)&(el->data)) += (float)num;
	return 1;
}

int AddString(element_t *el, int num)	/*concatenate a string*/
{
	unsigned int num_of_digits = DigitsInNum(num);
	char *cat_begin = NULL;
	size_t len = strlen(el->data);	
	char *tmp_str = NULL;
	
	assert(el);
	assert(num);

	tmp_str = (char*)malloc(sizeof(tmp_str) * num_of_digits);
	/*free memory if malloc failed*/
	if (NULL == tmp_str)
		{
			puts("Not enough memory space\n");
			return 0;
		}

	sprintf(tmp_str, "%d", num);
	cat_begin = (char *)realloc((void *)el->data, num_of_digits + len + 1);
	/*free memory if realloc failed*/
	if (NULL == cat_begin)
	{
		puts("Not enough memory space\n");
		free(tmp_str);
		free(el->data);

		return 0;
	}

	el->data = cat_begin;
	strcpy(cat_begin + len, tmp_str);
	free(tmp_str);

	return 1;
}

void PrintInt(element_t *el)
{
	assert(el);

	printf("PrintInt : %d\n", *(int*)&el->data);
}



void PrintFloat(element_t *el)
{
	assert(el);

	printf("PrintFloat : %f\n", *(float*)&el->data);
}

void PrintString(element_t *el)
{
	assert(el);
	printf("PrintString : %s\n", (char*)el->data);
}

void Free(element_t *el)
{
	free(el->data);
}


void VoidFree(element_t *el)
{
	UNUSED_VAR(el);
}

int DigitsInNum(int num)
{
	int digits = 0;

	while(num != 0)
    {
        /* Increment digit count */
        ++digits;

        /* Remove last digit of 'num' */
        num /= 10;
    }

    return digits;
}
















