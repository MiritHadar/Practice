/*******************************************************************************
*	Description: sort							   		                       *
*	Author: Mirit Hadar									  	 	       		   *
*******************************************************************************/

/* #include <stddef.h>  
#include <stdio.h>   
#include <stdlib.h>  
#include <assert.h> 
#include <time.h>    
#include "sort.h"

#define UNUSED_VAR(x) (void)(x)
#define     MAX       10
#define     SIZE       3
#define     SIZE2      7


static int IsBefore(const void *data1, const void *data2);
static int IsBeforeOrSame(const void *data1, const void *data2);
static int IsBeforeHeapSort(const void *data1, const void *data2);
static void PrintBase(size_t *base, size_t num_element);
size_t ElemToIndex(const void *item, const void *args);
static int CmpFunc(const void *data1, const void *data2);

int main()
{
    size_t base[] = {4, 3, 2, 10, 12, 1, 5, 6};
    size_t base1[] = {4};
    size_t base2[] = {4, 4, 4, 4};
    size_t base3[] = {10, 20, 30};
    size_t base4[] = {4, 3, 2, 10, 12, 1, 5, 6};
    size_t base5[] = {4, 3, 0, 0, 4, 1};
    size_t base6[] = {8, 7, 6, 5, 4, 3, 2, 1};
    size_t counting_base[] = {100, 5, 48, 521, 166, 789, 524};
    size_t radix_base[] = {100, 5, 48, 521, 166, 789, 524};
    size_t merge_base[SIZE] = {10, 4, 8};
    size_t quick_base[SIZE2] = {3, 0, 8, 7, 1, 2, 4};
    size_t heap_base[SIZE2] = {3, 0, 8, 7, 1, 2, 4};
    size_t i = 0;

    size_t range = 0;
    size_t elem_size = sizeof(base[0]);
    size_t num_element = sizeof(base) / elem_size;
    size_t data2 = 2;
    size_t data5 = 5;
    size_t data4 = 4;
    size_t data20 = 20;
    void *ans = NULL;


    puts("***************Insertion**************");

    PrintBase(base, num_element);

    InsertionSort(base, num_element, elem_size, IsBefore);

    PrintBase(base, num_element);


    elem_size = sizeof(base1[0]);
    num_element = sizeof(base1) / elem_size;

    PrintBase(base1, num_element);

    InsertionSort(base1, num_element, elem_size, IsBefore);

    PrintBase(base1, num_element);


    elem_size = sizeof(base2[0]);
    num_element = sizeof(base2) / elem_size;

    PrintBase(base2, num_element);

    InsertionSort(base2, num_element, elem_size, IsBefore);

    PrintBase(base2, num_element);


    elem_size = sizeof(base3[0]);
    num_element = sizeof(base3) / elem_size;

    PrintBase(base3, num_element);

    InsertionSort(base3, num_element, elem_size, IsBefore);

    PrintBase(base3, num_element);


    puts("\n***************Bubble**************");

    elem_size = sizeof(base4[0]);
    num_element = sizeof(base4) / elem_size;

    PrintBase(base4, num_element);

    BubbleSort(base4, num_element, elem_size, IsBefore);

    PrintBase(base4, num_element);

    PrintBase(base4, num_element);

    BubbleSort(base4, num_element, elem_size, IsBefore);

    PrintBase(base4, num_element);

    elem_size = sizeof(base4[0]);
    num_element = sizeof(base6) / elem_size;

    PrintBase(base6, num_element);

    BubbleSort(base6, num_element, elem_size, IsBefore);

    PrintBase(base6, num_element);


    puts("\n***************Selection**************");

    elem_size = sizeof(base4[0]);
    num_element = sizeof(base4) / elem_size;

    PrintBase(base4, num_element);

    SelectionSort(base4, num_element, elem_size, IsBefore);

    PrintBase(base4, num_element);


    puts("\n***************Counting**************");

    elem_size = sizeof(counting_base[0]);
    num_element = sizeof(counting_base) / elem_size;
    range = 790;

    PrintBase(counting_base, num_element);

    CountingSort(counting_base, num_element, elem_size, ElemToIndex, NULL, range);

    PrintBase(counting_base, num_element);

    puts("\n*************RadixSort**************");

    elem_size = sizeof(radix_base[0]);
    num_element = sizeof(radix_base) / elem_size;
    range = 5;

    PrintBase(radix_base, num_element);

    RadixSort(radix_base, num_element, elem_size, ElemToIndex, NULL, 4);

    PrintBase(radix_base, num_element);


    puts("\n***************Merge****************");

   
    
    for (i = 0; i < SIZE2; ++i)
    {
        printf("%lu ", quick_base[i]);
    }

    puts("");

    MergeSort(quick_base, SIZE2, sizeof(size_t), IsBefore);

    for (i = 0; i < SIZE2; ++i)
    {
        printf("%lu ", quick_base[i]);
    }
    puts("");

    puts("\n***************Quick****************");

    for (i = 0; i < SIZE2; ++i)
    {
        printf("%lu ", quick_base[i]);
    }

    puts("");

    QuickSort(quick_base, SIZE2, sizeof(size_t), IsBeforeOrSame);

    for (i = 0; i < SIZE2; ++i)
    {
        printf("%lu ", quick_base[i]);
    }

    puts("");

    puts("\n***************BinarySearch****************");

    printf("%lu\n", *(size_t*)IterativeBinarySearch(quick_base, SIZE2, sizeof(size_t), IsBefore, &data2));
    if (NULL != IterativeBinarySearch(quick_base, SIZE2, sizeof(size_t), IsBefore, &data5))
    {
        puts("failed in binary search");
    }

    ans = IterativeBinarySearch(base3, 3, sizeof(size_t), IsBefore, &data20);

    if (20 != *(int*)ans)
    {
        puts("failed in binary search");
    }

    if (data4 != *(size_t*)JumpSearch(quick_base, SIZE2, sizeof(size_t), CmpFunc, &data4))
    {
        puts("failed in binary search");
    }
 
    puts("\n***************HeapSort****************");

    for (i = 0; i < SIZE2; ++i)
    {
        printf("%lu ", heap_base[i]);
    }

    puts("");
    
    HeapSort(heap_base, SIZE2, sizeof(size_t), IsBeforeHeapSort);

    for (i = 0; i < SIZE2; ++i)
    {
        printf("%lu ", heap_base[i]);
    }

    puts("");

    return 0;
}

static int IsBefore(const void *data1, const void *data2)
{
    assert(data1);
    assert(data2);

    return (*(size_t*)data1 < *(size_t*)data2);
}

static int IsBeforeHeapSort(const void *data1, const void *data2)
{
    assert(data1);
    assert(data2);

    return (*(size_t*)data1 > *(size_t*)data2);
}

static int IsBeforeOrSame(const void *data1, const void *data2)
{
    assert(data1);
    assert(data2);

    return (*(size_t*)data1 <= *(size_t*)data2);
}

static void PrintBase(size_t *base, size_t num_element)
{
    size_t i = 0;

    for (i = 0; i < num_element; ++i)
    {
        printf("%lu ", base[i]);
    }
    puts("");
}

size_t ElemToIndex(const void *item, const void *args)
{
    UNUSED_VAR(args);

    return (size_t)*(int*)item;
}

static int CmpFunc(const void *data1, const void *data2)
{
    assert(data1);
    assert(data2);

    return (*(size_t*)data1 - *(size_t*)data2);
}


int IsBeforeInt(const void *data1, const void *data2)
{
	if (*(int*)data1 < *(int*)data2)
	{
		return 1;
	} 
	
	return 0;
}


#include <stdio.h>
#include <assert.h>
#include "sort.h"

#define UNUSED_VAR(x) (void)(x)

typedef struct element
{
    size_t age;
    size_t id;
    char *name;
} element_t;


void TestBubbleSort();
void TestSelectionSort();
void TestInsertionSort();
void TestCountingSort();
void TestRadixSort();
void TestMergeSort();
void TestQuickSort();
void TestHeapSort();

size_t Struct2Ind(const void *item, const void *args);
int IsBeforeInt(const void *data1, const void *data2);
size_t IndexForUInt(const void *item, const void *args);


int main ()
{

	TestBubbleSort();
	TestSelectionSort();
	TestInsertionSort();
	TestCountingSort();
	TestRadixSort();
	TestMergeSort();
	TestQuickSort();
	TestHeapSort();


    return 0;
}

void TestBubbleSort()
{
	size_t i = 0;
	int arr1[] = {234, 23, 5, 568, 7, 1, 54, 8, 24352, -3, 0, 234};
	int sorted_arr1[] = {-3, 0, 1, 5, 7, 8, 23, 54, 234, 234, 568, 24352};
	int arr2[] = {1};
	int sorted_arr2[] = {1};
	int arr3[] = {2, 1};
	int sorted_arr3[] = {1, 2};

	BubbleSort(arr1, 12, 4, IsBeforeInt);

	for (i = 0; i < 12; ++i)
	{
		if (*(arr1 + i) != *(sorted_arr1 + i))
		{
			printf("error in bubble sort for arr1 ");
			break;
		}
	}

	BubbleSort(arr2, 1, 4, IsBeforeInt);

	for (i = 0; i < 1; ++i)
	{
		if (*(arr2 + i) != *(sorted_arr2 + i))
		{
			printf("error in bubble sort for arr2 ");
			break;
		}
	}

	BubbleSort(arr3, 2, 4, IsBeforeInt);

	for (i = 0; i < 1; ++i)
	{
		if (*(arr3 + i) != *(sorted_arr3 + i))
		{
			printf("error in bubble sort for arr3 ");
			break;
		}
	}
}

void TestSelectionSort()
{
	size_t i = 0;
	int arr1[] = {234, 23, 5, 568, 7, 1, 54, 8, 24352, -3, 0, 234};
	int sorted_arr1[] = {-3, 0, 1, 5, 7, 8, 23, 54, 234, 234, 568, 24352};
	int arr2[] = {1};
	int sorted_arr2[] = {1};
	int arr3[] = {2, 1};
	int sorted_arr3[] = {1, 2};

	SelectionSort(arr1, 12, 4, IsBeforeInt);

	for (i = 0; i < 12; ++i)
	{
		if (*(arr1 + i) != *(sorted_arr1 + i))
		{
			printf("error in selection sort for arr1 ");
			break;
		}
	}

	SelectionSort(arr2, 1, 4, IsBeforeInt);

	for (i = 0; i < 1; ++i)
	{
		if (*(arr2 + i) != *(sorted_arr2 + i))
		{
			printf("error in selection sort for arr2 ");
			break;
		}
	}

	SelectionSort(arr3, 2, 4, IsBeforeInt);

	for (i = 0; i < 1; ++i)
	{
		if (*(arr3 + i) != *(sorted_arr3 + i))
		{
			printf("error in selection sort for arr3 ");
			break;
		}
	}
}

void TestInsertionSort()
{
	size_t i = 0;
	int arr1[] = {234, 23, 5, 568, 7, 1, 54, 8, 24352, -3, 0, 234};
	int sorted_arr1[] = {-3, 0, 1, 5, 7, 8, 23, 54, 234, 234, 568, 24352};
	int arr2[] = {1};
	int sorted_arr2[] = {1};
	int arr3[] = {2, 1};
	int sorted_arr3[] = {1, 2};

	InsertionSort(arr1, 12, 4, IsBeforeInt);

	for (i = 0; i < 12; ++i)
	{
		if (*(arr1 + i) != *(sorted_arr1 + i))
		{
			printf("error in insertion sort for arr1 ");
			break;
		}
	}

	InsertionSort(arr2, 1, 4, IsBeforeInt);

	for (i = 0; i < 1; ++i)
	{
		if (*(arr2 + i) != *(sorted_arr2 + i))
		{
			printf("error in insertion sort for arr2 ");
			break;
		}
	}

	InsertionSort(arr3, 2, 4, IsBeforeInt);

	for (i = 0; i < 1; ++i)
	{
		if (*(arr3 + i) != *(sorted_arr3 + i))
		{
			printf("error in insertion sort for arr3 ");
			break;
		}
	}	
}

void TestCountingSort()
{
	size_t i = 0;
	
	int arr1[] = {234, 23, 5, 568, 7, 1, 54, 8, 24352, 0, 234};
	int sorted_arr1[] = {0, 1, 5, 7, 8, 23, 54, 234, 234, 568, 24352};
	
	int arr2[] = {1};
	int sorted_arr2[] = {1};
	int arr3[] = {2, 1};
	int sorted_arr3[] = {1, 2};

	CountingSort(arr1, 11, 4, IndexForUInt, NULL, 24353);

	for (i = 0; i < 11; ++i)
	{
		if (*(arr1 + i) != *(sorted_arr1 + i))
		{
			printf("error in counting sort for arr1 ");
			break;
		}
	}

	CountingSort(arr2, 1, 4, IndexForUInt, NULL, 2);

	for (i = 0; i < 1; ++i)
	{
		if (*(arr2 + i) != *(sorted_arr2 + i))
		{
			printf("error in counting sort for arr2 ");
			break;
		}
	}

	CountingSort(arr3, 2, 4, IndexForUInt, NULL, 3);

	for (i = 0; i < 1; ++i)
	{
		if (*(arr3 + i) != *(sorted_arr3 + i))
		{
			printf("error in counting sort for arr3 ");
			break;
		}
	}	
}



void TestRadixSort()
{
	size_t i = 0;
    element_t people[5] = 			{{28, 981, "David" }, 
                          			 {17, 2222, "Yossi" },
                         			 {16, 33, "Danny" },
                           			 {33, 445, "Itay"  },
                           			 {27, 999999, "Baruch"}};
    
	element_t people_sorted[5] = 	{{16, 33, "Danny" }, 
                           		  	 {33, 445, "Itay"  },
                          		  	 {28, 981, "David" },
                   		          	 {17, 2222, "Yossi" },
                       				 {27, 999999, "Baruch"}};

	element_t *people_ptr = people;
	element_t *people_sorted_ptr = people_sorted;

	RadixSort(people, 5, 24, Struct2Ind, NULL, 1000000);

	for (i = 0; i < 5; ++i)
	{
		if ((people_ptr + i)->id != (people_sorted_ptr + i)->id)
		{
			printf("error in radix sort");
			break;
		}
	}
}

size_t Struct2Ind(const void *item, const void *args)
{
    element_t *el = NULL;

    assert(NULL != item);

    el = (element_t *)item;

    return el->id;
}


void TestMergeSort()
{
	size_t i = 0;
	int arr1[] = {234, 23, 5, 568, 7, 1, 54, 8, 24352, -3, 0, 234};
	int sorted_arr1[] = {-3, 0, 1, 5, 7, 8, 23, 54, 234, 234, 568, 24352};
	int arr2[] = {1};
	int sorted_arr2[] = {1};
	int arr3[] = {2, 1};
	int sorted_arr3[] = {1, 2};
	int arr4[] = {38, 27, 43, 3, 9, 82, 10};
	int sorted_arr4[] = {3, 9, 10, 27, 38, 43, 82};

	MergeSort(arr1, 12, 4, IsBeforeInt);

	for (i = 0; i < 12; ++i)
	{
		if (*(arr1 + i) != *(sorted_arr1 + i))
		{
			printf("error in merge sort for arr1 ");
			break;
		}
	}

	MergeSort(arr2, 1, 4, IsBeforeInt);

	for (i = 0; i < 1; ++i)
	{
		if (*(arr2 + i) != *(sorted_arr2 + i))
		{
			printf("error in merge sort for arr2 ");
			break;
		}
	}

	MergeSort(arr3, 2, 4, IsBeforeInt);

	for (i = 0; i < 1; ++i)
	{
		if (*(arr3 + i) != *(sorted_arr3 + i))
		{
			printf("error in merge sort for arr3 ");
			break;
		}
	}	

	MergeSort(arr4, 7, 4, IsBeforeInt);

	for (i = 0; i < 7; ++i)
	{
		if (*(arr4 + i) != *(sorted_arr4 + i))
		{
			printf("error in merge sort for arr4 ");
			break;
		}
	}	
}


void TestQuickSort()
{
	size_t i = 0;
	int arr1[] = {234, 23, 5, 568, 7, 1, 54, 8, 24352, -3, 0, 234};
	int sorted_arr1[] = {-3, 0, 1, 5, 7, 8, 23, 54, 234, 234, 568, 24352};
	int arr2[] = {1};
	int sorted_arr2[] = {1};
	int arr3[] = {2, 1};
	int sorted_arr3[] = {1, 2};	
	int arr4[] = {38, 27, 43, 3, 9, 82, 10};
	int sorted_arr4[] = {3, 9, 10, 27, 38, 43, 82};


	QuickSort(arr1, 12, 4, IsBeforeInt);

	for (i = 0; i < 12; ++i)
	{
		if (*(arr1 + i) != *(sorted_arr1 + i))
		{
			printf("error in quick sort for arr1 ");
			break;
		}
	}

	QuickSort(arr2, 1, 4, IsBeforeInt);

	for (i = 0; i < 1; ++i)
	{
		if (*(arr2 + i) != *(sorted_arr2 + i))
		{
			printf("error in quick sort for arr2 ");
			break;
		}
	}

	QuickSort(arr3, 2, 4, IsBeforeInt);

	for (i = 0; i < 1; ++i)
	{
		if (*(arr3 + i) != *(sorted_arr3 + i))
		{
			printf("error in quick sort for arr3 ");
			break;
		}
	}	

	QuickSort(arr4, 7, 4, IsBeforeInt);

	for (i = 0; i < 7; ++i)
	{
		if (*(arr4 + i) != *(sorted_arr4 + i))
		{
			printf("error in quick sort for arr4 ");
			break;
		}
	}
}



void TestHeapSort()
{
	size_t i = 0;
	int arr1[] = {234, 23, 5, 568, 7, 1, 54, 8, 24352, -3, 0, 234};
	int sorted_arr1[] = {-3, 0, 1, 5, 7, 8, 23, 54, 234, 234, 568, 24352};
	int arr2[] = {1};
	int sorted_arr2[] = {1};
	int arr3[] = {2, 1};
	int sorted_arr3[] = {1, 2};
	int arr4[] = {38, 27, 43, 3, 9, 82, 10};
	int sorted_arr4[] = {3, 9, 10, 27, 38, 43, 82};

	HeapSort(arr1, 12, 4, IsBeforeInt);

	for (i = 0; i < 12; ++i)
	{
		if (*(arr1 + i) != *(sorted_arr1 + i))
		{
			printf("error in heap sort for arr1 ");
			break;
		}
	}

	HeapSort(arr2, 1, 4, IsBeforeInt);

	for (i = 0; i < 1; ++i)
	{
		if (*(arr2 + i) != *(sorted_arr2 + i))
		{
			printf("error in heap sort for arr2 ");
			break;
		}
	}

	HeapSort(arr3, 2, 4, IsBeforeInt);

	for (i = 0; i < 2; ++i)
	{
		if (*(arr3 + i) != *(sorted_arr3 + i))
		{
			printf("error in heap sort for arr3 ");
			break;
		}
	}

	HeapSort(arr4, 7, 4, IsBeforeInt);

	for (i = 0; i < 7; ++i)
	{
		if (*(arr4 + i) != *(sorted_arr4 + i))
		{
			printf("error in quick sort for arr4 ");
			break;
		}
	}
}

int IsBeforeInt(const void *data1, const void *data2)
{
	if (*(int*)data1 <= *(int*)data2)
	{
		return 1;
	} 
	
	return 0;
}

size_t IndexForUInt(const void *item, const void *args)
{
	UNUSED_VAR(args);

	return *(int*)item;
}*/


#include <stdio.h>
#include "sort.h"

#define UNUSED_VAR(x) (void)(x)

void TestIterative();
void TestRecursive();
void TestIterativeJumpSearch();


static int IsBeforeInt(const void *data1, const void *data2, void *param);
static int IsBeforeIntJmp(const void *data1, const void *data2, void *param);

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
	if(NULL != IterativeJumpSearch(arr1, 8 ,4, IsBeforeIntJmp, &arr1_serch[0]))
	{
		printf("error in first test line %d\n", __LINE__);
	}

	if(NULL != IterativeJumpSearch(arr2, 9 ,4, IsBeforeIntJmp, &arr1_serch[0]))
	{
		printf("error in first test line %d\n", __LINE__);
	}

	/*second test */
	if(&arr1[0] != IterativeJumpSearch(arr1, 8 ,4, IsBeforeIntJmp, &arr1_serch[1]))
	{
		printf("error in first test line %d\n", __LINE__);
	}

	if(&arr2[0] != IterativeJumpSearch(arr2, 9 ,4, IsBeforeIntJmp, &arr1_serch[1]))
	{
		printf("error in first test line %d\n", __LINE__);
	}

	/*thired test */
	if(NULL != IterativeJumpSearch(arr1, 8 ,4, IsBeforeIntJmp, &arr1_serch[2]))
	{
		printf("error in first test line %d\n", __LINE__);
	}

	if(NULL != IterativeJumpSearch(arr2, 9 ,4, IsBeforeIntJmp, &arr1_serch[2]))
	{
		printf("error in first test line %d\n", __LINE__);
	}


	/*forth test */
	if(&arr1[1] != IterativeJumpSearch(arr1, 8 ,4, IsBeforeIntJmp, &arr1_serch[3]))
	{
		printf("error in first test line %d\n", __LINE__);
	}

	if(&arr2[1] != IterativeJumpSearch(arr2, 9 ,4, IsBeforeIntJmp, &arr1_serch[3]))
	{
		printf("error in first test line %d\n", __LINE__);
	}	

	/*fifth test */
	if(&arr1[6] != IterativeJumpSearch(arr1, 8 ,4, IsBeforeIntJmp, &arr1_serch[4]))
	{
		printf("error in first test line %d\n", __LINE__);
	}

	if(&arr2[7] != IterativeJumpSearch(arr2, 9 ,4, IsBeforeIntJmp, &arr1_serch[4]))
	{
		printf("error in first test line %d\n", __LINE__);
	}		

	/*sixth test */
	if(NULL != IterativeJumpSearch(arr1, 8 ,4, IsBeforeIntJmp, &arr1_serch[5]))
	{
		printf("error in first test line %d\n", __LINE__);
	}

	if(NULL != IterativeJumpSearch(arr2, 9 ,4, IsBeforeIntJmp, &arr1_serch[5]))
	{
		printf("error in first test line %d\n", __LINE__);
	}	

	/*seventh test */
	if(&arr1[7] != IterativeJumpSearch(arr1, 8 ,4, IsBeforeIntJmp, &arr1_serch[6]))
	{
		printf("error in first test line %d\n", __LINE__);
	}

	if(&arr2[8] != IterativeJumpSearch(arr2, 9 ,4, IsBeforeIntJmp, &arr1_serch[6]))
	{
		printf("error in first test line %d\n", __LINE__);
	}	

	/*eighth test */
	if(NULL != IterativeJumpSearch(arr1, 8 ,4, IsBeforeIntJmp, &arr1_serch[7]))
	{
		printf("error in first test line %d\n", __LINE__);
	}

	if(NULL != IterativeJumpSearch(arr2, 9 ,4, IsBeforeIntJmp, &arr1_serch[7]))
	{
		printf("error in first test line %d\n", __LINE__);
	}
}


static int IsBeforeIntJmp(const void *data1, const void *data2, void *param)
{
	UNUSED_VAR(param);

	return *(int*)data1 - *(int*)data2;
}

static int IsBeforeInt(const void *data1, const void *data2, void *param)
{
	UNUSED_VAR(param);

	if (*(int*)data1 < *(int*)data2)
	{
		return 1;
	} 
	
	return 0;
}


