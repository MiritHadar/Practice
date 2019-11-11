
#include <stdlib.h>     /*malloc, abs*/
#include <stdio.h>      /*printf*/
#include <assert.h>     /*assert*/

#include "avl.h"

#define    UNUSED(x)    (void)(x)

typedef struct node
{
    void *data;
    struct node *left;
    struct node *right;
}avl_node_t;

struct avl_tree
{
    avl_node_t *root;
    sort_t sort_func;
    void *args;
};

/*static void PrintNodeInOrder(avl_node_t *node);*/
static int FindWhereToInsert(avl_t *tree, avl_node_t *node, void *data);
static int Insert(avl_node_t **node, void *data, int direction);
static int InsertToEmpty(avl_t **tree, void *data);
static int AVLForEachNode(avl_node_t *node, act_func_t act_func, void *param);
static int CountNodes(void *data, void *param);
static size_t AVLHeightNode(avl_node_t *node);
static int GetBalance(avl_node_t *node);
static void print2DUtil(avl_node_t *node, int space);
static void Rotate(avl_node_t *node, int balance);
static void RotateLL(avl_node_t *node);
static void RotateLR(avl_node_t *node);
static void RotateRR(avl_node_t *node);
static void RotateRL(avl_node_t *node);
static void ExchangeData(avl_node_t **node1, avl_node_t **node2);
static avl_node_t *FindNode(const avl_t *tree, avl_node_t *node, const void *data);
struct node *FindNext(avl_node_t *node);
avl_node_t *RemoveNode(avl_t *tree, avl_node_t *node, void *data);
static void DestroyNode(avl_node_t *node);


avl_t *AVLCreate(sort_t is_smaller, void *args)
{
    avl_t *tree = NULL;

    assert(is_smaller);

    tree = (avl_t*)malloc(sizeof(avl_t));

    if (NULL == tree)
    {
        return NULL;
    }

    tree->sort_func = is_smaller;
    tree->args = args;
    tree->root = NULL;

    return tree;
}

void AVLDestroy(avl_t *tree)
{
    assert(tree);

    DestroyNode(tree->root);

    free(tree);
}

static void DestroyNode(avl_node_t *node)
{
    if (NULL != node)
    {
        DestroyNode(node->left);
        DestroyNode(node->right);
        free(node);
    }
}

/****************************Find*********************************/
void *AVLFind(const avl_t *tree, const void *data)
{
    avl_node_t *node = NULL;

    assert(tree);

    if (AVLIsEmpty(tree))
    {
        return NULL;
    }

    node = FindNode(tree, tree->root, data);

    if (node == NULL)
    {
        return NULL;
    }

    return (void*)(node->data);
    
}

static avl_node_t *FindNode(const avl_t *tree, avl_node_t *node, const void *data)
{
    if (NULL == node)
    {
        return NULL;
    }
    if (tree->sort_func(data, node->data, NULL))
    {
        return FindNode(tree, node->left, data);
    }
    else if (tree->sort_func(node->data, data, NULL))
    {
        return FindNode(tree, node->right, data);
    }
    else
    {
        return node;
    }
}

/*****************************************************************************/

size_t AVLCount(const avl_t *tree)
{
    size_t counter = 0;

    AVLForEachNode(tree->root, CountNodes, &counter);

    return counter;
}


int CountNodes(void *data, void *counter)
{

    UNUSED(data);

    ++*(size_t*)counter;

    return 0;
}


int AVLIsEmpty(const avl_t *tree)
{
    return (NULL == tree->root);
}

/************************************ForEach***********************************/
int AVLForEach(avl_t *tree, act_func_t act_func, void *param)
{
    int status = 0;

    assert(tree);

    if (AVLIsEmpty(tree))
    {
        return 1;
    }
    
    status = AVLForEachNode(tree->root, act_func, param);
    puts("");

    return status;
}


static int AVLForEachNode(avl_node_t *node, act_func_t act_func, void *param)
{
    int status = 0;

    if (NULL == node)
    {
        return 0;
    }

    return (AVLForEachNode(node->left, act_func, param) + act_func(node->data, param) +  AVLForEachNode(node->right, act_func, param));
}

/*********************************Remove********************************** */
void *AVLRemove(avl_t *tree, void *data)
{
    avl_node_t *node = NULL;
    void *tmp_data = NULL;

    assert(tree);
    assert(data);

    if (AVLIsEmpty(tree))
    {
        return NULL;
    }

    node = tree->root;

    if (NULL == AVLFind(tree, data))
    {
        return NULL;
    }

    if (1 == AVLCount(tree))
    {
        tmp_data = node->data;
        tree->root = NULL;
        free(node);
        return tmp_data;
    }

    node = RemoveNode(tree, tree->root, data);
   
    return node->data;
}

avl_node_t *RemoveNode(avl_t *tree, avl_node_t *node, void *data)
{
    avl_node_t *tmp = NULL;
    int balance = 0;

    if (tree->sort_func(data, node->data, NULL))
    {
        if (NULL == node->left)
        {
            return NULL;
        }
        node->left = RemoveNode(tree, node->left, data);
    }
    else if (tree->sort_func(node->data, data, NULL))
    {
        if (NULL == node->right)
        {
            return NULL;
        }
        node->right = RemoveNode(tree, node->right, data);
    }
    else
    {
        /* in case of a leaf */
        if (NULL == node->right && NULL == node->left)
        {
            free(node);
            return NULL;
        }
        /* only right child */
        else if (NULL == node->left)
        {
            node->data = node->right->data;
            free(node->right);
            node->right = NULL;
        }
        /* only left child */
        else if (NULL == node->right)
        {
            node->data = node->left->data;
            free(node->left);
            node->left = NULL;
        }
        /* two kids */
        else
        {
            tmp = FindNext(node->right);
            node->data = tmp->data;
            node->right = RemoveNode(tree, node->right, tmp->data);
        }
    }

    balance = GetBalance(node);

    if (abs(balance) > 1)
    {
        Rotate(node, balance);
    }

    return node;
}

struct node *FindNext(avl_node_t *node) 
{ 
    if (node->left == NULL)
    {
        return node;
    }
    else
    {
        return FindNext(node->left);
    }
} 


/************************************Insert***********************************/
int AVLInsert(avl_t *tree, void *data)
{
    int status = 0;
    status = FindWhereToInsert(tree, (avl_node_t*)(tree->root), data);
    return status;
}

static int FindWhereToInsert(avl_t *tree, avl_node_t *node, void *data)
{
    int balance = 0;
    int status = 0;

    if (NULL == node)
    {
        status = InsertToEmpty(&tree, data);
    }

    else if (tree->sort_func(data, node->data, NULL))
    {
        if (NULL == node->left)
        {
            status = Insert(&node, data, 1);
        }
        else
        {
            FindWhereToInsert(tree, node->left, data);
        }
    }
    else if (tree->sort_func(node->data, data, NULL))
    {
        if (NULL == node->right)
        {
            status = Insert(&node, data, 2);
        }
        else
        {
            FindWhereToInsert(tree, node->right, data);
        }
    }
    else
    {
        return 1;
    }

    balance = GetBalance(node);

    if (abs(balance) > 1)
    {
        Rotate(node, balance);
    }

    return status;
}

/* direction 0 for empty tree, direction 1 for left, direction 2 for right */
static int Insert(avl_node_t **node, void *data, int direction)
{
    avl_node_t *new_node = NULL;

    new_node = (avl_node_t*)malloc(sizeof(struct node));

    if (NULL == new_node)
    {
        return 1;
    }

    switch (direction)
    {
        case 0:
            node = &new_node;
            break;

        case 1:
            (*node)->left = new_node;
            break;

        case 2:
            (*node)->right = new_node;
            break;
    }
    
    new_node->data = data;
    new_node->left = NULL;
    new_node->right = NULL;

    return 0;
}

static int InsertToEmpty(avl_t **tree, void *data)
{
    avl_node_t *new_node = malloc(sizeof(avl_node_t));

    if (NULL == new_node)
    {
        return 1;
    }

    new_node->data = data;
    new_node->left = NULL;
    new_node->right = NULL;
    (*tree)->root = new_node;

    return 0;
}

/*******************************Hight*********************************/
size_t AVLHeight(avl_t *tree)
{
    return AVLHeightNode(tree->root);
}

static size_t AVLHeightNode(avl_node_t *node)
{
    size_t height_left = 0;
    size_t height_right = 0;
   
    if (NULL == node)
    {
        return 0;
    }
    else
    {
        height_left = AVLHeightNode(node->left);
        height_right = AVLHeightNode(node->right);

        if (height_left > height_right)
        {
            return (height_left + 1);
        }
        else
        {
            return (height_right + 1);
        }
    }    
}

/*****************************Balance****************************/
static int GetBalance(avl_node_t *node)
{
    int balance = 0;

    if (node == NULL)
    {
        return 0;
    }
    else
    {
        balance = AVLHeightNode(node->left) - AVLHeightNode(node->right);
    }

    return balance;
}

static void Rotate(avl_node_t *node, int balance)
{
    switch (balance)
    {
    case 2:
        if (GetBalance(node->left) == 1)
        {
            RotateLL(node);
        }
        else
        {
            RotateLR(node);
        }
        break;
        
    case -2:
        if (GetBalance(node->right) == -1)
        {
            RotateRR(node);
        }
        else
        {
            RotateRL(node);
        }
    }
}


static void RotateLL(avl_node_t *node)
{
    avl_node_t *tmp_lll = node->left->left->left;
    avl_node_t *tmp_llr = node->left->left->right;
    avl_node_t *tmp_lr = node->left->right;
    avl_node_t *tmp_r = node->right;

    puts("LL");

    ExchangeData(&node, &(node->left));
    ExchangeData(&(node->left), &(node->left->left));
    node->right = node->left->left;

    /*reattache tmp nodes */
    node->right->right = tmp_r;
    node->right->left = tmp_lr;
    node->left->right = tmp_llr;
    node->left->left = tmp_lll;
}

static void RotateLR(avl_node_t *node)
{
    avl_node_t *tmp_ll = node->left->left;
    avl_node_t *tmp_lrl = node->left->right->left;
    avl_node_t *tmp_lrr = node->left->right->right;
    avl_node_t *tmp_r = node->right;

    puts("LR");

    ExchangeData(&node, &(node->left->right));
    node->right = node->left->right;

    /*reattache tmp nodes */
    node->left->left = tmp_ll;
    node->left->right = tmp_lrl;
    node->right->right = tmp_r;
    node->right->left = tmp_lrr;
}

static void RotateRR(avl_node_t *node)
{
    avl_node_t *tmp_l = node->left;
    avl_node_t *tmp_rl = node->right->left;
    avl_node_t *tmp_rrl = node->right->right->left;
    avl_node_t *tmp_rrr = node->right->right->right;

    puts("RR");

    ExchangeData(&node, &(node->right));
    ExchangeData(&(node->right), &(node->right->right));
    node->left = node->right->right;

    node->left->left = tmp_l;
    node->left->right = tmp_rl;
    node->right->left = tmp_rrl;
    node->right->right = tmp_rrr;
}

static void RotateRL(avl_node_t *node)
{
    avl_node_t *tmp_l = node->left;
    avl_node_t *tmp_rr = node->right->right;
    avl_node_t *tmp_rll = node->right->left->left;
    avl_node_t *tmp_rlr = node->right->left->right;

    puts("RL");

    ExchangeData(&node, &(node->right->left));
    node->left = node->right->left;

    node->left->left = tmp_l;
    node->left->right = tmp_rll;
    node->right->left = tmp_rlr;
    node->right->right = tmp_rr;
}


static void ExchangeData(avl_node_t **node1, avl_node_t **node2)
{
    void *tmp_data = (*node1)->data;
    (*node1)->data = (*node2)->data;
    (*node2)->data = tmp_data;
}
/****************************Prints****************************/
void PrintInOrder(avl_t *tree)
{
    assert(tree);

    /*PrintNodeInOrder((avl_node_t*)(tree->root));*/
    print2DUtil(tree->root, 0);

    puts("");
}

/*static void PrintNodeInOrder(avl_node_t *node)
{
    if (NULL != node)
    {
        PrintNodeInOrder(node->left);
        printf("%d ", *(int*)(node->data));
        PrintNodeInOrder(node->right);
    }
}*/

static void print2DUtil(avl_node_t *node, int space)  
{  
    int count = 5;
    int i = 0;
   
    if (node == NULL)  
        return;  
  
   
    space += count;  
  
    
    print2DUtil(node->right, space);  
  
  
    printf("\n");

    for (i = count; i < space; i++)
    {
        printf(" ");
    }  
    printf("%d \n", *(int *)node->data); 
  
  
    print2DUtil(node->left, space);  
} 