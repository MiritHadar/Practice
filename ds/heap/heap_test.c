
/* #include <stdio.h>      
#include <assert.h>     

#include "heap.h"

#define     UNUSED(x)   (void)(x)
#define     SIZE    10

static int IsBefore(const void *before, const void *after, void *data);
static int IsMatch (const void *data1, const void *data2, void *param);
static void PrintHeap(heap_t *heap);

int main()
{
    size_t i = 0;
    int data[SIZE] = {2, 8, 8, 4, 6, 5, 4, 1, 0, 14};
    heap_t *heap = HeapCreate(sizeof(int), IsBefore);

    if (NULL == heap)
    {
        printf("%d - error in HeapCreate\n", __LINE__);
    }

    if (!HeapIsEmpty(heap))
    {
        printf("%d - error in HeapIsEmpty\n", __LINE__);
    }

    for (i = 0; i < SIZE; ++i)
    {
        HeapPush(heap, &(data[i]));
        printf("push : %d\n", *(int*)HeapPeek(heap));
    }

    PrintHeap(heap);

    if(0 != *(int*)HeapPeek(heap))
    {
        printf("%d - error in HeapPeek\n", __LINE__);
    }

    if(10 != HeapSize(heap))
    {
        printf("%d - error in HeapSize\n", __LINE__);
    }

    if (HeapIsEmpty(heap))
    {
        printf("%d - error in HeapIsEmpty or HeapPush\n", __LINE__);
    }

    printf("%d\n", *(int*)HeapPeek(heap));
    HeapPop(heap);
    printf("%d\n", *(int*)HeapPeek(heap));

    if(9 != HeapSize(heap))
    {
        printf("%d - error in HeapSize\n", __LINE__);
    }

    if(1 != *(int*)HeapPeek(heap))
    {
        printf("%d - error in HeapPeek\n", __LINE__);
    }

    HeapPop(heap);
    printf("%d\n", *(int*)HeapPeek(heap));
    HeapPop(heap);
    printf("%d\n", *(int*)HeapPeek(heap));

    HeapPop(heap);
    printf("%d\n", *(int*)HeapPeek(heap));

    HeapPop(heap);
    printf("%d\n", *(int*)HeapPeek(heap));

    HeapPop(heap);
    printf("%d\n", *(int*)HeapPeek(heap));

    HeapPop(heap);
    printf("%d\n", *(int*)HeapPeek(heap));

    HeapPop(heap);
    printf("%d\n", *(int*)HeapPeek(heap));

    HeapPop(heap);
    printf("%d\n", *(int*)HeapPeek(heap));


    if(1 != HeapSize(heap))
    {
        printf("%d - error in HeapSize\n", __LINE__);
    }

    if(14 != *(int*)HeapPeek(heap))
    {
        printf("%d - error in HeapPeek\n", __LINE__);
    }
    
    HeapPop(heap);

    for (i = 0; i < SIZE; ++i)
    {
        HeapPush(heap, &(data[i]));
    }

    if(10 != HeapSize(heap))
    {
        printf("%d - error in HeapSize\n", __LINE__);
    }

    for (i = 0; i < SIZE; ++i)
    {
        printf("%lu remove\n", i);
        HeapRemove(heap, IsMatch, &(data[i]), NULL);
    }


    HeapDestroy(heap);

    return 0;
}

static int IsBefore(const void *before, const void *after, void *data)
{
    assert(before && after);

    return (*(int*)before <= *(int*)after);
}

static int IsMatch (const void *data1, const void *data2, void *param)
{
    UNUSED(param);

    assert(data1 && data2);

    return *(int*)data1 == *(int*)data2;
}

static void PrintHeap(heap_t *heap)
{
    size_t i = 0;
    for (i = 0; i < SIZE; ++i)
    {
        printf("%d ", *((int*)HeapPeek(heap) + i));
    }
    puts("");
}  */

#include <stdio.h>
#include <assert.h>
#include <string.h>

#include "dynamic_vector.h"
#include "heap.h"

#define UNUSED(X) ((void)(X))
#define NUM_OF_STUDENTS (7)

#define UNUSED_VAR(x) (void)(x)

#define T1(n)	n,			n+1,		n+2,		n+3
#define T2(n)	T1(n+8),	T1(n+4),	T1(n+12),	T1(n)
#define T3(n)	T2(n+16),	T2(n+48),	T2(n),		T2(n+32)
#define TABLE	T3(192),	T3(128),	T3(0),		T3(64)

#define TABLE1	T3(128),	T3(64)
#define TABLE2	T3(192),	T3(0)

#define UNUSED_VAR(x) (void)(x)

#define     SIZE    10



struct heap
{   
    vector_t *vector;
    is_before_t is_before;
}; 

typedef struct student student_t;

struct student
{
    char name[15];
    size_t age;
    size_t id;
};

int IsMatchName(const void *data1, const void *data2, void *param);
int IsBeforeStudent(const void *before, const void *after, void *param);
int IsBeforeInt(const void *before, const void *after, void *param);
int IsMatchInt(const void *data1, const void *data2, void *param);
int IsBefore(const void *data1, const void *data2, void *param);
int IsMatchSizeT(const void *data1, const void *data2, void *param);
static void PrintHeap(heap_t *heap);


int TestCreateDestroy();
int TestInsert();
int TestInsertRemovePop();
int TestRemoveLeaf();
int TestRemoveAgain();
int TestStudent();
void TestIntNotPtrs();

int main()
{

    TestCreateDestroy();
    TestInsert();
    TestInsertRemovePop(); 
    TestRemoveLeaf();
    TestRemoveAgain();
    TestStudent(); 
	TestIntNotPtrs();
	
	
    return 0;
}

int TestCreateDestroy()
{
    heap_t *heap = NULL;

    heap = HeapCreate(sizeof(int), IsBeforeInt);

    if (NULL == heap)
    {
        return 1;
    }

    if (0 != HeapSize(heap))
    {
        printf("Error in line %d\n", __LINE__);
        return 1;
    }

    if (1 != HeapIsEmpty(heap))
    {
        printf("Error in line %d\n", __LINE__);
        return 1;        
    }

    HeapDestroy(heap);
    heap = NULL;

    return 0;
}

int TestInsert()
{
    heap_t *heap = NULL;
    int arr[10] = {0,1,2,3,4,5,6,7,8,9};
    size_t i = 0;

    heap = HeapCreate(sizeof(int), IsBeforeInt);

    if (NULL == heap)
    {
        return 1; 
    } 

    for (i = 0; i < 10; ++i)
    {
        assert(HeapPush(heap, arr + i) != 1);
    }

    HeapDestroy(heap);
    heap = NULL;

    return 0;
}

int TestInsertRemovePop()
{
    heap_t *heap = NULL;
    int arr[10] = {76, 11, 30, 52, 44, 23, 39, 89, 61, 82};
    int i = 0;
    int to_remove = 11;

    heap = HeapCreate(sizeof(int), IsBeforeInt);

    if (NULL == heap)
    {
        return 1;
    } 
    
    for (i = 0; i < 10; ++i)
    {
        assert(HeapPush(heap, arr + i) != 1);
        assert((i + 1) == HeapSize(heap));
    }


  
    HeapRemove(heap, IsMatchInt, &to_remove, NULL);
    
    assert(9 == HeapSize(heap));


 
    for (i = 0; i < 9; ++i)
    {
        HeapPop(heap);
    }

    HeapDestroy(heap);
    heap = NULL;
    
    return 0;
}

int TestRemoveLeaf()
{
    heap_t *heap = NULL;
    int arr[10] = {0,1,2,3,4,5,6,7,8,9};
    int i = 0;

    heap = HeapCreate(sizeof(int), IsBeforeInt);

    if (NULL == heap)
    {
        return 1;
    } 
    
    for (i = 0; i < 10; ++i)
    {
        assert(HeapPush(heap, arr + i) != 1);
        assert((i + 1) == HeapSize(heap));
    }

    HeapRemove(heap, IsMatchInt, &arr[0], NULL);

    HeapRemove(heap, IsMatchInt, &arr[2], NULL);

    HeapRemove(heap, IsMatchInt, &arr[3], NULL);
 
    HeapRemove(heap, IsMatchInt, &arr[0], NULL);
 
    HeapDestroy(heap);

    return 0;
}

int TestRemoveAgain()
{
    heap_t *heap = NULL;
    int arr[10] = {0,1,2,3,4,5,6,7,8,9};
    int i = 0;

    heap = HeapCreate(sizeof(int), IsBeforeInt);

    if (NULL == heap)
    {
        return 1;
    } 
    
    for (i = 0; i < 10; ++i)
    {
        assert(HeapPush(heap, arr + i) != 1);
        assert((i + 1) == HeapSize(heap));
    }

    HeapRemove(heap, IsMatchInt, &arr[2], NULL);
 
    HeapRemove(heap, IsMatchInt, &arr[3], NULL);
 
    HeapRemove(heap, IsMatchInt, &arr[6], NULL);
 
    HeapDestroy(heap);


    return 0;
}

int TestStudent()
{
    heap_t *heap = NULL;
    student_t students[NUM_OF_STUDENTS] = { {"Dov",    29, 123456},
                                            {"David",  28, 334455},
                                            {"Ori",    32, 554433},
                                            {"Gil",    29, 654321},
                                            {"Shay",   38, 126534},
                                            {"Avihay", 28, 451236},
                                            {"Ada",    16, 113546}};
    size_t i = 0;
    student_t *student1 = NULL;

    heap = HeapCreate(sizeof(student_t), IsBeforeStudent);

    if (NULL == heap)
    {
        return 1;
    }

    for (i = 0; i < NUM_OF_STUDENTS; ++i)
    {
        assert(0 == HeapPush(heap, &students[i]));
    }

    student1 = HeapPeek(heap);

    HeapDestroy(heap);

    return 0;
}


void TestIntNotPtrs()
{
	heap_t *heap 	= HeapCreate(sizeof(size_t), IsBefore);
	size_t datas[256] = {TABLE};
	size_t i = 0;


	if (!HeapIsEmpty(heap))
	{
		printf("is empty failed empty\nline : %d\n", __LINE__);
	}

	for (i = 0; i < 256; ++i)
	{
		if (HeapSize(heap) != i)
		{
			printf("is empty failed non-empty\nline : %d\n", __LINE__);
			break;
		}

		if (HeapPush(heap, datas + i))
		{
			printf("insert failed\nline : %d\n", __LINE__);
			break;
		}

		if (HeapIsEmpty(heap))
		{
			printf("is empty failed non-empty\nline : %d\n", __LINE__);
			break;
		}
	}

	for (i = 0; i < 256; ++i)
	{
		if (i != *(size_t*)HeapPeek(heap))
		{
			printf("peek failed\nline : %d i : %d\n", __LINE__, i);
			break;
		}

		if (0 != HeapPop(heap))
		{
			printf("dequeue failed\ni = %lu\nline : %d\n", i, __LINE__);
			break;
		}
        
        PrintHeap(heap);
	}

	if (!HeapIsEmpty(heap))
	{
		printf("is empty failed empty\nline : %d\n", __LINE__);
	}


	for (i = 0; i < 256; ++i)
	{
		if (HeapSize(heap) != i)
		{
			printf("is empty failed non-empty\nline : %d\n", __LINE__);
			break;
		}

		if (HeapPush(heap, datas + i))
		{
			printf("insert failed\nline : %d\n", __LINE__);
			break;
		}

		if (HeapIsEmpty(heap))
		{
			printf("is empty failed non-empty\nline : %d\n", __LINE__);
			break;
		}
	}

	HeapDestroy(heap);
}
int IsBeforeInt(const void *before, const void *after, void *param)
{
	UNUSED_VAR(param);

    return (*(int *)before < *(int *)after);
}

int IsMatchInt(const void *data1, const void *data2, void *param)
{
   	UNUSED_VAR(param);

    return (*(int *)data1 == *(int *)data2);
}

int IsBeforeStudent(const void *before, const void *after, void *param)
{
    student_t *student1 = NULL;
    student_t *student2 = NULL;

	UNUSED_VAR(param);

    assert(before);
    assert(after);

    student1 = (student_t *)before;
    student2 = (student_t *)after;

    return ((student1->age < student2->age));
}

int IsMatchName(const void *data1, const void *data2, void *param)
{
    student_t *student1 = NULL;
    student_t *student2 = NULL;

    assert(data1);
    assert(data2);

    student1 = (student_t *)data1;
    student2 = (student_t *)data2;

    return (0 == strcmp(student1->name, student2->name));
}

int IsBefore(const void *before, const void *after, void *param)
{
  	UNUSED_VAR(param);

	return *(size_t*)before > *(size_t*)after;
}

int IsMatchSizeT(const void *data1, const void *data2, void *param)
{
	UNUSED_VAR(param);

	return *(size_t*)data1 == *(size_t*)data2;
}

static void PrintHeap(heap_t *heap)
{
    size_t i = 0;
    for (i = 0; i < SIZE; ++i)
    {
        printf("%d ", *((size_t*)HeapPeek(heap) + i));
    }
    puts("");
}

/* #include <stdio.h> 
#include "heap.h"  

#define UNUSED(X) (void)X


static int IsBiggerInt(const void *num1, const void *num2, void *param);
static int IsMatch(const void *data1, const void *data2, void *param);



int main()
{
	heap_t *heap = NULL;
	int a = 3, b = 7, c = 4, d = 6, e = 1;
	int *pa = &a, *pb = &b, *pc = &c, *pd = &d, *pe = &e;

	heap = HeapCreate(sizeof(void *), IsBiggerInt);

	if (1 != HeapIsEmpty(heap))
	{
		puts("Error in HeapIsEmpty");
	}

	if (0 != HeapSize(heap))
	{
		puts("Error in HeapCreate or HeapSize");
	}

	HeapPush(heap, &pa);

	if (3 != **(int **)HeapPeek(heap))
	{
		puts("Error in HeapPush or HeapPeek");
	}

	HeapPush(heap, &pb);

	if (7 != **(int **)HeapPeek(heap))
	{
		puts("Error in HeapPush or HeapPeek");
	}

	if (2 != HeapSize(heap))
	{
		puts("Error in HeapPush or HeapSize");
	}

	HeapPush(heap, &pc);
	HeapPush(heap, &pd);
	HeapPush(heap, &pe);

	if (7 != **(int **)HeapPeek(heap))
	{
		puts("Error in HeapPush or HeapPeek");
	}

	if (5 != HeapSize(heap))
	{
		puts("Error in HeapPush");
	}

	if (0 != HeapIsEmpty(heap))
	{
		puts("Error in HeapIsEmpty");
	}

	HeapPop(heap);

	if (6 != **(int **)HeapPeek(heap))
	{
		puts("Error in HeapPop");
	}

	if (4 != HeapSize(heap))
	{
		puts("Error in HeapPop");
	}

	HeapPop(heap);

	if (4 != **(int **)HeapPeek(heap))
	{
		puts("Error in HeapPop");
	}

	if (3 != HeapSize(heap))
	{
		puts("Error in HeapPop");
	}

	HeapRemove(heap, IsMatch, &pe, NULL);

	if (2 != HeapSize(heap))
	{
		puts("Error in HeapRemove");
	}

	if (4 != **(int **)HeapPeek(heap))
	{
		puts("Error in HeapRemove");
	}

	HeapRemove(heap, IsMatch, &pa, NULL);
	HeapRemove(heap, IsMatch, &pc, NULL);

	if (1 != HeapIsEmpty(heap))
	{
		puts("Error in HeapIsEmpty");
	}

	HeapDestroy(heap);

	return 0;
}



static int IsBiggerInt(const void *num1, const void *num2, void *param)
{
    UNUSED(param);

	return **(int **)num1 > **(int **)num2; 
}

static int IsMatch(const void *data1, const void *data2, void *param)
{
	UNUSED(param);

	return **(int **)data1 == **(int **)data2;
}
 */