#include <stdio.h>                    /* puts        */
#include "ordered_binary_tree.h"      /* header file */


#define UNUSED(X) (void)X




int is_smaller(const void *before, const void *after, void *param);
void PrintBinaryTree(const bt_t *tree);
void TestBTEasy();
void TestBTMiddle();
void TestBTHard();
int Plus17(void *data, void *param);


int main()
{
	TestBTEasy();
	TestBTMiddle();
	TestBTHard();

	return 0;
}


int is_smaller(const void *before, const void *after, void *param)
{
	UNUSED(param);

	return *(int *)before < *(int *)after;
}

void PrintBinaryTree(const bt_t *tree)
{
	bt_itr_t itr_begin = BTBegin(tree);
	bt_itr_t itr_end = BTEnd(tree);
	bt_itr_t itr = {NULL};
	
	for (itr = itr_begin; !BTIsSame(itr, itr_end); itr = BTNext(itr))
	{
		printf("%d ", *(int *)BTGetData(itr));
	}

	printf("\n");

	for (itr = BTPrev(itr_end); !BTIsSame(itr, itr_begin); itr = BTPrev(itr))
	{
		printf("%d ", *(int *)BTGetData(itr));
	}
	printf("%d ", *(int *)BTGetData(itr));

	printf("\n");
}

void TestBTEasy()
{
	bt_t *tree = BTCreate(is_smaller, NULL);
	bt_itr_t itr_begin = {NULL};
	bt_itr_t itr_end = {NULL};
	bt_itr_t itr = {NULL};
	bt_itr_t itr_temp = {NULL};
	size_t a = 5, b = 3, c = 7, d = 8, e = 1, f = 2, g = 4, i = 9, k = 6, j = 0;
	size_t index = 0;

	if(0 == BTIsEmpty(tree))
	{
		puts("Error in BTIsEmpty");
	}

	if(0 != BTCount(tree))
	{
		puts("Error in BTCount");
	}

	BTInsert(tree, &a);

	if(1 == BTIsEmpty(tree))
	{
		puts("Error in BTIsEmpty");
	}

	if(1 != BTCount(tree))
	{
		puts("Error in BTCount");
	}

	BTInsert(tree, &b);
	BTInsert(tree, &c);
	BTInsert(tree, &d);
	BTInsert(tree, &e);
	BTInsert(tree, &f);
	BTInsert(tree, &g);
	BTInsert(tree, &i);
	BTInsert(tree, &k);
	BTInsert(tree, &j);

	itr_begin = BTBegin(tree);
	itr_end = BTEnd(tree);

	if(10 != BTCount(tree))
	{
		puts("Error in BTCount");
	}

	for (index = 0, itr = itr_begin; index < 10 && !BTIsSame(itr, itr_end); ++index, itr = BTNext(itr))
	{
		if (index != *(size_t *)BTGetData(itr))
		{
			puts("Error in BTInsert");
		}
	}

	for (index = 0, itr = BTPrev(itr_end); index < 10 && !BTIsSame(itr, itr_begin); ++index, itr = BTPrev(itr))
	{
		if (9 - index != *(size_t *)BTGetData(itr))
		{
			puts("Error in BTInsert");
		}
	}

	/* remove all odd numbers */
	for (itr = itr_begin; !BTIsSame(itr, itr_end); itr = BTNext(itr))
	{
		itr_temp = BTNext(itr);
		BTRemove(itr);
		itr = itr_temp;
	}

	itr_begin = BTBegin(tree);
	itr_end = BTEnd(tree);

	for (index = 0, itr = itr_begin; index < 10 && !BTIsSame(itr, itr_end); ++index, itr = BTNext(itr))
	{
		if (2 * index + 1 != *(size_t *)BTGetData(itr))
		{
			puts("Error in BTRemove");
		}
	}

	BTDestroy(tree);
}

void TestBTMiddle()
{
	bt_t *tree = BTCreate(is_smaller, NULL);
	bt_itr_t itr_begin = {NULL};
	bt_itr_t itr_end = {NULL};
	bt_itr_t itr = {NULL};

	size_t a = 5, b = 3, c = 7, d = 8, e = 1, f = 2, g = 4, i = 9, k = 6, j = 0;
	size_t index = 0;
	size_t x = 5;
	size_t y = 9;
	size_t z = 11;

	BTInsert(tree, &a);
	BTInsert(tree, &b);
	BTInsert(tree, &c);
	BTInsert(tree, &d);
	BTInsert(tree, &e);
	BTInsert(tree, &f);
	BTInsert(tree, &g);
	BTInsert(tree, &i);
	BTInsert(tree, &k);
	BTInsert(tree, &j);

	itr_begin = BTBegin(tree);
	itr_end = BTEnd(tree);

	if(5 != *(size_t *)BTGetData(BTFind(tree, &x)))
	{
		puts("Error in BTFind");
	}

	if(9 != *(size_t *)BTGetData(BTFind(tree, &y)))
	{
		puts("Error in BTFind");
	}

	if(!BTIsSame(itr_end, BTFind(tree, &z)))
	{
		puts("Error in BTFind");
	}

	BTForEach(Plus17, NULL, itr_begin, itr_end);

	for (index = 0, itr = itr_begin; index < 10 && !BTIsSame(itr, itr_end); ++index, itr = BTNext(itr))
	{
		if (index + 17 != *(size_t *)BTGetData(itr))
		{
			puts("Error in BTForEach");
		}
	}

	BTDestroy(tree);
}

int Plus17(void *data, void *param)
{
	UNUSED(param);

	(*(size_t *)data) += 17;

	return 0;
}

void TestBTHard()
{
	bt_t *tree = BTCreate(is_smaller, NULL);
	bt_itr_t itr = {NULL};
	size_t a = 5;

	BTInsert(tree, &a);

	itr = BTBegin(tree);

	BTRemove(itr);

	if(1 != BTIsEmpty(tree))
	{
		puts("Error in Hard Test");
	}

	BTDestroy(tree);
}

