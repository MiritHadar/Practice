/*##############################################################################
#                                                                              #
#     Description:                                                             #
#     Author: Gil Kremer                                                       #
#     Reviewer:                                                                #
#     Vershion: Draft                                                          #
#     Last Update: XX.XX.XX                                                    #
#                                                                              #
##############################################################################*/

#include <stdio.h>
#include "ordered_binary_tree.h"

#define UNUSED_VAR(x) (void)(x)

static int BTPrintFunc(void *data, void *param);
int IntBefor(const void *data1, const void *data2, void *param);
void Test();

int main()
{
	Test();

	return 0;
}

void Test()
{
	int num_arr[11] = {0,1,2,3,4,5,6,7,8,9,10};
	size_t i = 0;
	void *data = NULL;
	bt_t *btree = NULL;
	bt_itr_t itr = {0};

	btree = BTCreate(IntBefor, NULL);
	if (NULL == btree)
	{
		printf("Error in creating tree! %d",__LINE__);
	}

	if (0 != BTCount(btree))
	{
		printf("Error in BTCount after remove! %d",__LINE__);
	}

	if (0 == BTIsEmpty(btree))
	{
		printf("Error in BTIsEmpty when empty! %d",__LINE__);
	}

	BTDestroy(btree);

	btree = BTCreate(IntBefor, NULL);
	if (NULL == btree)
	{
		printf("Error in creating tree! %d",__LINE__);
	}

	/* insert first element 6 to tree */
	if (1 == BTInsert(btree, &num_arr[6]))
	{
		printf("Error in BTInsert when empty! %d",__LINE__);
	}

	/* insert element 3 to tree */
	if (1 == BTInsert(btree, &num_arr[3]))
	{
		printf("Error in BTInsert when empty! %d",__LINE__);
	}

	/* insert element 4 to tree */
	if (1 == BTInsert(btree, &num_arr[4]))
	{
		printf("Error in BTInsert when empty! %d",__LINE__);
	}

	/* insert element 5 to tree */
	if (1 == BTInsert(btree, &num_arr[5]))
	{
		printf("Error in BTInsert when empty! %d",__LINE__);
	}

	/* insert element 1 to tree */
	if (1 == BTInsert(btree, &num_arr[1]))
	{
		printf("Error in BTInsert when empty! %d",__LINE__);
	}

	/* insert element 2 to tree */
	if (1 == BTInsert(btree, &num_arr[2]))
	{
		printf("Error in BTInsert when empty! %d",__LINE__);
	}

	/* insert element 8 to tree */
	if (1 == BTInsert(btree, &num_arr[8]))
	{
		printf("Error in BTInsert when empty! %d",__LINE__);
	}

	/* insert element 9 to tree */
	if (1 == BTInsert(btree, &num_arr[9]))
	{
		printf("Error in BTInsert when empty! %d",__LINE__);
	}

	/* insert element 7 to tree */
	if (1 == BTInsert(btree, &num_arr[7]))
	{
		printf("Error in BTInsert when empty! %d",__LINE__);
	}

	/* get the begin element (2)*/
	itr = BTBegin(btree);

	BTForEach(BTPrintFunc, NULL, BTBegin(btree), BTEnd(btree));
	puts("");

	itr = BTEnd(btree);

	/*for (i = 9; i > 0; --i)
	{
		itr = BTPrev(itr);
		if (i != *(int*)BTGetData(itr))
		{
			printf("Error in BTInsert when empty! %d",__LINE__);
		}
	}*/

	if (9 != BTCount(btree))
	{
		printf("Error in BTCount after remove! %d",__LINE__);
	}

	if (0 != BTIsEmpty(btree))
	{
		printf("Error in BTIsEmpty when full! %d",__LINE__);
	}
	
	/* find 3 in tree */ 
	itr = BTFind(btree, &num_arr[3]);
	if (3 != *(int*)BTGetData(itr))
	{
		printf("Error in find when exist: %d\n",__LINE__);
	}
	
	/* search elment not in list */ 
	itr = BTFind(btree, &num_arr[10]);
	if (!BTIsSame(itr, BTEnd(btree)))
	{
		printf("Error in BTFind when not in tree! %d",__LINE__);
	}

	/* search elment not in list */ 
	itr = BTFind(btree, &num_arr[0]);
	if (!BTIsSame(itr, BTEnd(btree)))
	{
		printf("Error in BTFind when not in tree! %d",__LINE__);
	}

	itr = BTFind(btree, &num_arr[3]);
	data = BTRemove(itr);
	if (3 != *(int*)data)
	{
		printf("Error remove element (3)! %d",__LINE__);
	}

	if (8 != BTCount(btree))
	{
		printf("Error in BTCount after remove! %d",__LINE__);
	}

	itr = BTFind(btree, &num_arr[2]);
	data = BTRemove(itr);
	if (2 != *(int*)data)
	{
		printf("Error remove element (3)! %d",__LINE__);
	}

	if (7 != BTCount(btree))
	{
		printf("Error in BTCount after remove! %d",__LINE__);
	}

	puts("After removing 2,3 from list:");
	BTForEach(BTPrintFunc, NULL, BTBegin(btree), BTEnd(btree));
	puts("");

	BTDestroy(btree);

	puts("Test Done run vlgraind!"); 
}


static int BTPrintFunc(void *data, void *param)
{
	UNUSED_VAR(param);

	printf("%d  ", *(int*)data);

	return 0;
}


int IntBefor(const void *data1, const void *data2, void *param)
{
	UNUSED_VAR(param); 

	return (*(int*)data1 < *(int*)data2);
}