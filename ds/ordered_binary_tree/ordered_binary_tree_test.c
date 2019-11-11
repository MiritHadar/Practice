

#include <stdio.h>                  /*printf*/
#include <assert.h>                 /*assert*/

#include "ordered_binary_tree.h"    /*header*/

#define     UNUSED(x)   (void)(x)


int IsSmaller(const void *new_data, const void *node_data, void *param);
void PrintTreeInOrder(bt_t *tree);
static int PrintNodes(void *data, void *param);

/*int main()
{
    bt_t *tree = BTCreate(IsSmaller, NULL);
    bt_itr_t itr_to_find = {NULL};

    int data1 = 1;
    int data2 = 2;
    int data3 = 3;
    int data4 = 4;
    int data5 = 5;

    if (!BTIsEmpty(tree))
    {
        printf("line %d - failed is empty\n", __LINE__);
    }

    if (0 != BTCount(tree))
    {
        printf("line %d - failed count zero\n", __LINE__);
    }

    if (1 == BTInsert(tree, &data2))
    {
        printf("line %d - failed insert\n", __LINE__);        
    }

    BTInsert(tree, &data1);
    BTInsert(tree, &data4);
    BTInsert(tree, &data3);

    if (BTIsEmpty(tree))
    {
        printf("line %d - failed to insert/is empty\n", __LINE__);
    }

    PrintTreeInOrder(tree);

    if (4 != BTCount(tree))
    {
        printf("line %d - failed count zero\n", __LINE__);
    }

    BTForEach(PrintNodes, NULL, BTBegin(tree), BTEnd(tree));

/*****************Find*****************/

    itr_to_find = BTFind(tree, &data5);

    if (!BTIsSame(itr_to_find, BTEnd(tree)))
    {
        printf("line %d - failed find - absent data\n", __LINE__);
    }

    itr_to_find = BTFind(tree, &data3);

    if (*(int*)(BTGetData(itr_to_find)) != data3)
    {
        printf("line %d - failed find\n", __LINE__);
    }

    if (*(int*)(BTGetData(BTPrev(itr_to_find))) != data2)
    {
        printf("line %d - failed prev\n", __LINE__);

    }

    
/****************Remove****************/

    if (*(int*)BTRemove(itr_to_find) != data3)
    {
        printf("line %d - failed remove leaf\n", __LINE__);
    }

    PrintTreeInOrder(tree);

    if (3 != BTCount(tree))
    {
        printf("line %d - failed count\n", __LINE__);
    }

    itr_to_find = BTFind(tree, &data2);

    if (*(int*)BTRemove(itr_to_find) != data2)
    {
        printf("line %d - failed remove root\n", __LINE__);
    }

    PrintTreeInOrder(tree);

    if (2 != BTCount(tree))
    {
        printf("line %d - failed count\n", __LINE__);
    }

    itr_to_find = BTFind(tree, &data4);

    if (*(int*)BTRemove(itr_to_find) != data4)
    {
        printf("line %d - failed remove root\n", __LINE__);
    }

    PrintTreeInOrder(tree);

    if (1 != BTCount(tree))
    {
        printf("line %d - failed count\n", __LINE__);
    }

    itr_to_find = BTFind(tree, &data1);

    if (*(int*)BTRemove(itr_to_find) != data1)
    {
        printf("line %d - failed remove last node in the tree\n", __LINE__);
    }

    PrintTreeInOrder(tree);

    BTDestroy(tree);

    return 0;
}


int IsSmaller(const void *new_data, const void *node_data, void *param)
{
    UNUSED(param);

    return (*(int*)new_data < *(int*)node_data);
}

void PrintTreeInOrder(bt_t *tree)
{
    bt_itr_t itr = {NULL};

    assert(tree);

    if (BTIsEmpty(tree))
    {
        puts("0");
        return;
    }

    for(itr = BTBegin(tree); !BTIsSame(itr, BTEnd(tree)); itr = BTNext(itr))
    {
        printf("%d ", *(int*)BTGetData(itr));
    }

    puts("");
}

static int PrintNodes(void *data, void *param)
{
    UNUSED(param);
    printf("PrintNodes - %d ", *(int*)data);
    puts("");

    return 0;
}
