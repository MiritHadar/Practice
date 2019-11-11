/*#include <stdio.h>
#include "avl.h"

#define    UNUSED(x)    (void)(x)


int IsSmaller(const void *new_data, const void *node_data, void *param);
int PrintData(void *data, void *param);

int main()
{
    avl_t *tree = AVLCreate(IsSmaller, NULL);
    int data1 = 1;
    int data2 = 2;
    int data3 = 3;    
    int data4 = 4;
    int data5 = 5;
    int data6 = 6;
    int data7 = 7;
    int data8 = 8;
    int data9 = 9;    
    int data10 = 10;
    int data11 = 11;
    int data12 = 12;
    int data13 = 13;
    int data14 = 14;


    if (NULL == tree)
    {
        printf("line %d - failed create\n", __LINE__);
    }

    if (!AVLIsEmpty(tree))
    {
        printf("line %d - failed AVLIsEmpty\n", __LINE__);
    }

    if (0 != AVLCount(tree))
    {
        printf("line %d - failed AVLCount\n", __LINE__);

    }
    
    if (0 != AVLHeight(tree))
    {
        printf("line %d - failed AVLHeight\n", __LINE__);

    }

    if (AVLFind(tree, NULL))
	{
        printf("line %d - failed AVLFind\n", __LINE__);
	}
    
    AVLInsert(tree, &data7);
    AVLRemove(tree, &data7);
    PrintInOrder(tree);

    AVLInsert(tree, &data7);
   

    if (1 != AVLHeight(tree))
    {
        printf("line %d - failed AVLHeight\n", __LINE__);

    }

    AVLInsert(tree, &data3);
    AVLInsert(tree, &data11);
    AVLInsert(tree, &data12);
    AVLInsert(tree, &data13);

    AVLInsert(tree, &data14);
    AVLInsert(tree, &data2);
    AVLInsert(tree, &data1);

    PrintInOrder(tree);

    if (AVLIsEmpty(tree))
    {
        printf("line %d - failed Insert to empty tree\n", __LINE__);
    }

    AVLForEach(tree, PrintData, NULL);

    if (8 != AVLCount(tree))
    {
        printf("line %d - failed AVLCount\n", __LINE__);

    }

    if (4 != AVLHeight(tree))
    {
        printf("line %d - failed AVLHeight\n", __LINE__);

    }

    AVLRemove(tree, &data3);
    puts("\n\n");
    PrintInOrder(tree);
    AVLRemove(tree, &data2);
    puts("\n\n");
    PrintInOrder(tree);

    AVLDestroy(tree);

    return 0;
}

int IsSmaller(const void *new_data, const void *node_data, void *param)
{
    UNUSED(param);

    return (*(int*)new_data < *(int*)node_data);
}

int PrintData(void *data, void *param)
{
    UNUSED(param);

    if (NULL == data)
    {
        return 1;
    }

    printf("%d ", *(int*)data);

    return 0;
}*/

#include <stdio.h>    /* puts        */
#include "avl.h"      /* header file */

#define UNUSED(X) (void)X

int is_smaller(const void *before, const void *after, void *param);
int Plus17(void *data, void *param);
int Minus17(void *data, void *param);
void TestAVL();

int main()
{
    TestAVL();

    return 0;
}

void TestAVL()
{
    int a = 0, b = 1, c = 2, d = 3, e = 4, f = 5, g = 6, i = 7, k = 8, l = 9, m = 10, n = 11, s = 12, o = 13, p = 14;
    int x = 23;
    avl_t *tree = AVLCreate(is_smaller, NULL);
    avl_t *tree1 = AVLCreate(is_smaller, NULL);

    if(!AVLIsEmpty(tree))
    {
        puts("Error in IsEmpty");
    }

	AVLInsert(tree, &d);
	AVLInsert(tree, &g);
	AVLInsert(tree, &n);
	AVLInsert(tree, &o);
    AVLInsert(tree, &s);
	AVLInsert(tree, &i);
    AVLInsert(tree, &k);
	AVLInsert(tree, &l);
    AVLInsert(tree, &p);
	AVLInsert(tree, &m);
    AVLInsert(tree, &f);
    AVLInsert(tree, &a);
    AVLInsert(tree, &e);
    AVLInsert(tree, &b);
	AVLInsert(tree, &c);

    if(AVLIsEmpty(tree))
    {
        puts("Error in IsEmpty");
    }

    if (5 != AVLHeight(tree))
    {
        puts("Error in Insert");
    }

    if (15 != AVLCount(tree))
    {
        puts("Error in Insert");
    }

    AVLRemove(tree, &a);
    printf("%lu\n", AVLCount(tree));

    AVLRemove(tree, &b);
    printf("%lu\n", AVLCount(tree));

    if (4 != AVLHeight(tree))
    {
        puts("Error in Insert");
    }

    if (13 != AVLCount(tree))
    {
        puts("Error in Insert");
    }

    AVLForEach(tree, Plus17, NULL);

    if(23 != *(int *)AVLFind(tree, &x))
    {
        puts("Error in Find");
    }

    AVLForEach(tree, Minus17, NULL);

    if(NULL != AVLFind(tree, &x))
    {
        puts("Error in Find");
    }

    if(NULL != AVLRemove(tree, &x))
    {
        puts("Error in Find");
    }

    AVLRemove(tree, &d);
    printf("%lu\n", AVLCount(tree));

	AVLRemove(tree, &g);
    printf("%lu\n", AVLCount(tree));

	AVLRemove(tree, &n);
    printf("%lu\n", AVLCount(tree));

	AVLRemove(tree, &o);
    printf("%lu\n", AVLCount(tree));

    AVLRemove(tree, &s);
    printf("%lu\n", AVLCount(tree));

	AVLRemove(tree, &i);
    printf("%lu\n", AVLCount(tree));

    AVLRemove(tree, &k);
    printf("%lu\n", AVLCount(tree));

	AVLRemove(tree, &l);
    printf("%lu\n", AVLCount(tree));

    AVLRemove(tree, &p);
    printf("%lu\n", AVLCount(tree));

	AVLRemove(tree, &m);
    printf("%lu\n", AVLCount(tree));

    PrintInOrder(tree);

    AVLRemove(tree, &f);
    printf("%lu\n", AVLCount(tree));

    PrintInOrder(tree);

    AVLRemove(tree, &e);
    printf("%lu\n", AVLCount(tree));

    PrintInOrder(tree);

	AVLRemove(tree, &c);
    printf("%lu\n", AVLCount(tree));

    PrintInOrder(tree);

    if(!AVLIsEmpty(tree))
    {
        puts("Error in IsEmpty");
    } 

    AVLDestroy(tree);

    AVLInsert(tree1, &b);
	AVLInsert(tree1, &c);
	AVLInsert(tree1, &d);
	AVLInsert(tree1, &a);

    PrintInOrder(tree1);

    if (4 != AVLCount(tree1))
    {
        puts("Error in Insert");
    }

   	AVLRemove(tree1, &b);

    PrintInOrder(tree1);
   	AVLRemove(tree1, &a);
    PrintInOrder(tree1);
    AVLRemove(tree1, &c);
    PrintInOrder(tree1);

    AVLDestroy(tree1);
}


int is_smaller(const void *before, const void *after, void *param)
{
	UNUSED(param);

	return *(int *)before < *(int *)after;
}

int Plus17(void *data, void *param)
{
    UNUSED(param);

    *(int *)data += 17;

    return 0;
}

int Minus17(void *data, void *param)
{
    UNUSED(param);

    *(int *)data -= 17;

    return 0;
}