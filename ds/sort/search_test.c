
#include <stdio.h>
#include "sort.h"

#define UNUSED_VAR(x) (void)(x)

void TestIterative();
void TestRecursive();
void TestIterativeJumpSearch();



int IsBeforeInt(const void *data1, const void *data2);

int main ()
{
    TestIterative();
  	TestRecursive();
	TestIterativeJumpSearch();

    return 0;
}

void TestIterative()
{
	int arr1[] = {100, 200, 300, 400, 500, 600, 700, 800};
	int arr1_serch[] = {50, 100, 150, 200, 700, 750, 800, 850};
	int arr2[] = {100, 200, 300, 350, 400, 500, 600, 700, 800};

	/*first test */
	if(NULL != IterativeBinarySearch(arr1, 8 ,4, IsBeforeInt, &arr1_serch[0]))
	{
		printf("error in first test line %d\n", __LINE__);
	}

	if(NULL != IterativeBinarySearch(arr2, 9 ,4, IsBeforeInt, &arr1_serch[0]))
	{
		printf("error in first test line %d\n", __LINE__);
	}

	/*second test */
	if(&arr1[0] != IterativeBinarySearch(arr1, 8 ,4, IsBeforeInt, &arr1_serch[1]))
	{
		printf("error in first test line %d\n", __LINE__);
	}

	if(&arr2[0] != IterativeBinarySearch(arr2, 9 ,4, IsBeforeInt, &arr1_serch[1]))
	{
		printf("error in first test line %d\n", __LINE__);
	}

	/*thired test */
	if(NULL != IterativeBinarySearch(arr1, 8 ,4, IsBeforeInt, &arr1_serch[2]))
	{
		printf("error in first test line %d\n", __LINE__);
	}

	if(NULL != IterativeBinarySearch(arr2, 9 ,4, IsBeforeInt, &arr1_serch[2]))
	{
		printf("error in first test line %d\n", __LINE__);
	}


	/*forth test */
	if(&arr1[1] != IterativeBinarySearch(arr1, 8 ,4, IsBeforeInt, &arr1_serch[3]))
	{
		printf("error in first test line %d\n", __LINE__);
	}

	if(&arr2[1] != IterativeBinarySearch(arr2, 9 ,4, IsBeforeInt, &arr1_serch[3]))
	{
		printf("error in first test line %d\n", __LINE__);
	}	

	/*fifth test */
	if(&arr1[6] != IterativeBinarySearch(arr1, 8 ,4, IsBeforeInt, &arr1_serch[4]))
	{
		printf("error in first test line %d\n", __LINE__);
	}

	if(&arr2[7] != IterativeBinarySearch(arr2, 9 ,4, IsBeforeInt, &arr1_serch[4]))
	{
		printf("error in first test line %d\n", __LINE__);
	}		

	/*sixth test */
	if(NULL != IterativeBinarySearch(arr1, 8 ,4, IsBeforeInt, &arr1_serch[5]))
	{
		printf("error in first test line %d\n", __LINE__);
	}

	if(NULL != IterativeBinarySearch(arr2, 9 ,4, IsBeforeInt, &arr1_serch[5]))
	{
		printf("error in first test line %d\n", __LINE__);
	}	

	/*seventh test */
	if(&arr1[7] != IterativeBinarySearch(arr1, 8 ,4, IsBeforeInt, &arr1_serch[6]))
	{
		printf("error in first test line %d\n", __LINE__);
	}

	if(&arr2[8] != IterativeBinarySearch(arr2, 9 ,4, IsBeforeInt, &arr1_serch[6]))
	{
		printf("error in first test line %d\n", __LINE__);
	}

	/*eighth test */
	if(NULL != IterativeBinarySearch(arr1, 8 ,4, IsBeforeInt, &arr1_serch[7]))
	{
		printf("error in first test line %d\n", __LINE__);
	}

	if(NULL != IterativeBinarySearch(arr2, 9 ,4, IsBeforeInt, &arr1_serch[7]))
	{
		printf("error in first test line %d\n", __LINE__);
	}
}

void TestRecursive()
{
	int arr1[] = {100, 200, 300, 400, 500, 600, 700, 800};
	int arr1_serch[] = {50, 100, 150, 200, 700, 750, 800, 850};
	int arr2[] = {100, 200, 300, 350, 400, 500, 600, 700, 800};

	/*first test */
	if(NULL != RecursiveBinarySearch(arr1, 8 ,4, IsBeforeInt, &arr1_serch[0]))
	{
		printf("error in first test line %d\n", __LINE__);
	}

	if(NULL != RecursiveBinarySearch(arr2, 9 ,4, IsBeforeInt, &arr1_serch[0]))
	{
		printf("error in first test line %d\n", __LINE__);
	}

	/*second test */
	if(&arr1[0] != RecursiveBinarySearch(arr1, 8 ,4, IsBeforeInt, &arr1_serch[1]))
	{
		printf("error in first test line %d\n", __LINE__);
	}

	if(&arr2[0] != RecursiveBinarySearch(arr2, 9 ,4, IsBeforeInt, &arr1_serch[1]))
	{
		printf("error in first test line %d\n", __LINE__);
	}

	/*thired test */
	if(NULL != RecursiveBinarySearch(arr1, 8 ,4, IsBeforeInt, &arr1_serch[2]))
	{
		printf("error in first test line %d\n", __LINE__);
	}

	if(NULL != RecursiveBinarySearch(arr2, 9 ,4, IsBeforeInt, &arr1_serch[2]))
	{
		printf("error in first test line %d\n", __LINE__);
	}


	/*forth test */
	if(&arr1[1] != RecursiveBinarySearch(arr1, 8 ,4, IsBeforeInt, &arr1_serch[3]))
	{
		printf("error in first test line %d\n", __LINE__);
	}

	if(&arr2[1] != RecursiveBinarySearch(arr2, 9 ,4, IsBeforeInt, &arr1_serch[3]))
	{
		printf("error in first test line %d\n", __LINE__);
	}	

	/*fifth test */
	if(&arr1[6] != RecursiveBinarySearch(arr1, 8 ,4, IsBeforeInt, &arr1_serch[4]))
	{
		printf("error in first test line %d\n", __LINE__);
	}

	if(&arr2[7] != RecursiveBinarySearch(arr2, 9 ,4, IsBeforeInt, &arr1_serch[4]))
	{
		printf("error in first test line %d\n", __LINE__);
	}		

	/*sixth test */
	if(NULL != RecursiveBinarySearch(arr1, 8 ,4, IsBeforeInt, &arr1_serch[5]))
	{
		printf("error in first test line %d\n", __LINE__);
	}

	if(NULL != RecursiveBinarySearch(arr2, 9 ,4, IsBeforeInt, &arr1_serch[5]))
	{
		printf("error in first test line %d\n", __LINE__);
	}	

	/*seventh test */
	if(&arr1[7] != RecursiveBinarySearch(arr1, 8 ,4, IsBeforeInt, &arr1_serch[6]))
	{
		printf("error in first test line %d\n", __LINE__);
	}

	if(&arr2[8] != RecursiveBinarySearch(arr2, 9 ,4, IsBeforeInt, &arr1_serch[6]))
	{
		printf("error in first test line %d\n", __LINE__);
	}	

	/*eighth test */
	if(NULL != RecursiveBinarySearch(arr1, 8 ,4, IsBeforeInt, &arr1_serch[7]))
	{
		printf("error in first test line %d\n", __LINE__);
	}

	if(NULL != RecursiveBinarySearch(arr2, 9 ,4, IsBeforeInt, &arr1_serch[7]))
	{
		printf("error in first test line %d\n", __LINE__);
	}	
}

void TestIterativeJumpSearch()
{
	int arr1[] = {100, 200, 300, 400, 500, 600, 700, 800};
	int arr1_serch[] = {50, 100, 150, 200, 700, 750, 800, 850};
	int arr2[] = {100, 200, 300, 350, 400, 500, 600, 700, 800};

	/*first test */
	if(NULL != IterativeJumpSearch(arr1, 8 ,4, IsBeforeInt, &arr1_serch[0]))
	{
		printf("error in first test line %d\n", __LINE__);
	}

	if(NULL != IterativeJumpSearch(arr2, 9 ,4, IsBeforeInt, &arr1_serch[0]))
	{
		printf("error in first test line %d\n", __LINE__);
	}

	/*second test */
	if(&arr1[0] != IterativeJumpSearch(arr1, 8 ,4, IsBeforeInt, &arr1_serch[1]))
	{
		printf("error in first test line %d\n", __LINE__);
	}

	if(&arr2[0] != IterativeJumpSearch(arr2, 9 ,4, IsBeforeInt, &arr1_serch[1]))
	{
		printf("error in first test line %d\n", __LINE__);
	}

	/*thired test */
	if(NULL != IterativeJumpSearch(arr1, 8 ,4, IsBeforeInt, &arr1_serch[2]))
	{
		printf("error in first test line %d\n", __LINE__);
	}

	if(NULL != IterativeJumpSearch(arr2, 9 ,4, IsBeforeInt, &arr1_serch[2]))
	{
		printf("error in first test line %d\n", __LINE__);
	}


	/*forth test */
	if(&arr1[1] != IterativeJumpSearch(arr1, 8 ,4, IsBeforeInt, &arr1_serch[3]))
	{
		printf("error in first test line %d\n", __LINE__);
	}

	if(&arr2[1] != IterativeJumpSearch(arr2, 9 ,4, IsBeforeInt, &arr1_serch[3]))
	{
		printf("error in first test line %d\n", __LINE__);
	}	

	/*fifth test */
	if(&arr1[6] != IterativeJumpSearch(arr1, 8 ,4, IsBeforeInt, &arr1_serch[4]))
	{
		printf("error in first test line %d\n", __LINE__);
	}

	if(&arr2[7] != IterativeJumpSearch(arr2, 9 ,4, IsBeforeInt, &arr1_serch[4]))
	{
		printf("error in first test line %d\n", __LINE__);
	}		

	/*sixth test */
	if(NULL != IterativeJumpSearch(arr1, 8 ,4, IsBeforeInt, &arr1_serch[5]))
	{
		printf("error in first test line %d\n", __LINE__);
	}

	if(NULL != IterativeJumpSearch(arr2, 9 ,4, IsBeforeInt, &arr1_serch[5]))
	{
		printf("error in first test line %d\n", __LINE__);
	}	

	/*seventh test */
	if(&arr1[7] != IterativeJumpSearch(arr1, 8 ,4, IsBeforeInt, &arr1_serch[6]))
	{
		printf("error in first test line %d\n", __LINE__);
	}

	if(&arr2[8] != IterativeJumpSearch(arr2, 9 ,4, IsBeforeInt, &arr1_serch[6]))
	{
		printf("error in first test line %d\n", __LINE__);
	}	

	/*eighth test */
	if(NULL != IterativeJumpSearch(arr1, 8 ,4, IsBeforeInt, &arr1_serch[7]))
	{
		printf("error in first test line %d\n", __LINE__);
	}

	if(NULL != IterativeJumpSearch(arr2, 9 ,4, IsBeforeInt, &arr1_serch[7]))
	{
		printf("error in first test line %d\n", __LINE__);
	}
}


int IsBeforeInt(const void *data1, const void *data2)
{
	return *(int*)data1 - *(int*)data2;
}