#include <stdlib.h>                 /*malloc*/
#include <assert.h>                 /*assert*/
#include "ordered_binary_tree.h"    /*header*/

#define     UNUSED(x)   (void)(x)

typedef struct node
{
    void *data;
    struct node *left;
    struct node *right;
    struct node *parent;
}bt_node_t;


struct bt_tree
{
    bt_node_t *root;
    sort_t sort_func;
    void *args;
};

static int BTCreateNode(bt_node_t **node, void *data, void *left, void *right, void *parent);
static void ExchangeStub(bt_node_t **remove_node);
static void ExcahngeData(bt_node_t **remove_node, bt_node_t **next_node);
static void KillNode(bt_node_t *remove_node);

void *bad_address = (void*)0xBADC0FFEE;


bt_t *BTCreate(sort_t is_smaller, void *args)
{
    bt_t *tree = NULL;
    bt_node_t *stub = NULL;

    tree = (bt_t*)malloc(sizeof(bt_t));

    if (NULL == tree)
    {
        return NULL;
    }

    BTCreateNode(&stub, NULL, bad_address, bad_address, NULL);

    if (NULL == stub)
    {
        free(tree);
        return NULL;
    }

    tree->root = stub;
    tree->sort_func = is_smaller;
    tree->args = args;

    return tree;
}

void BTDestroy(bt_t *tree)
{
    bt_itr_t current_itr = {NULL};
    bt_itr_t next_itr = {NULL};

    assert(tree);

    current_itr = BTBegin(tree);

    while (!BTIsSame(current_itr, BTEnd(tree)))
    {
        next_itr = BTNext(current_itr);
        free(current_itr.info);
        current_itr = next_itr;
    }

    free(BTEnd(tree).info);

    free(tree);
}

/* Find an item inside the tree */
bt_itr_t BTFind(const bt_t *tree, const void *data)
{
    bt_node_t *node = NULL;

    assert(tree);

    node = tree->root;

    while (NULL != node && bad_address != node->left)
    {
        if (tree->sort_func(data, node->data, NULL))
        {
            node = node->left;
        }
        else if (tree->sort_func(node->data, data, NULL))
        {
            node = node->right;
        }
        else
        {
            return *(bt_itr_t*)&node;
        }
    }

    return BTEnd(tree);
}


/* Returns an iterator to previous node */
bt_itr_t BTPrev(bt_itr_t itr)
{
    bt_node_t *prev_node = NULL;
    bt_node_t *node = ((bt_node_t*)itr.info);

    /* when there's a left child */
    if (NULL != node->left && bad_address != node->left)
    {
        prev_node = node->left;

        while (NULL != prev_node->right && bad_address != prev_node->right)
        {
            prev_node = prev_node->right;
        }
        return *(bt_itr_t*)&prev_node;
    }

    /* when there's not a left child*/
    prev_node = node->parent;

    while (NULL != prev_node && node == prev_node->left)
    {
        node = prev_node;
        prev_node = node->parent;
    }

    return *(bt_itr_t*)&prev_node;
}

/* Returns an iterator to next node */
bt_itr_t BTNext(bt_itr_t itr)
{
    bt_node_t *next_node = NULL;
    bt_node_t *node = ((bt_node_t*)itr.info);

    /* when there's a right child */
    if (NULL != node->right)
    {
        next_node = node->right;

        while (NULL != next_node->left && bad_address != next_node->left)
        {
            next_node = next_node->left;
        }

        return *(bt_itr_t*)&next_node;
    }
    
    /* when there's not a right child*/
    next_node = node->parent;

    while (NULL != next_node && node == next_node->right)
    {
        node = next_node;
        next_node = next_node->parent;
    }

    return *(bt_itr_t*)&next_node;
}

/* Returns the left-most node in the tree */
bt_itr_t BTBegin(const bt_t *tree)
{
    bt_node_t *first_node = NULL;

    assert(tree);

    first_node = tree->root;
    
    while (NULL != first_node->left && !BTIsEmpty(tree))
    {
        first_node = first_node->left;
    }

    return *(bt_itr_t*)&first_node;
}

/* Returns the right-most node in the tree*/
bt_itr_t BTEnd(const bt_t *tree)
{
    bt_node_t *last_node = NULL;

    assert(tree);

    last_node = tree->root;

    while (bad_address != last_node->right)
    {
        last_node = last_node->right;
    }
    return *(bt_itr_t*)&last_node;
} 


int BTIsSame(const bt_itr_t itr1, const bt_itr_t itr2)
{
    return (bt_node_t*)itr1.info == (bt_node_t*)itr2.info;
}

/* Create a node and insert at the correct position in the tree */
int BTInsert(bt_t *tree, void *data)
{
    bt_node_t *current_node = NULL;
    bt_node_t *new_node = NULL;
    bt_node_t *parent = NULL;
    int status = 0;

    assert(tree);
    assert(data);

    current_node = tree->root;

    if (BTIsEmpty(tree))
    {
        status = BTCreateNode(&new_node, data, NULL, current_node, NULL);
        tree->root = new_node;
        current_node->parent = new_node;

        return status;
    }

    while (NULL != current_node)
    {
        if (BTIsSame(*(bt_itr_t*)&current_node, BTEnd(tree)))
        {
            parent = current_node->parent;
            status = BTCreateNode(&new_node, data, NULL, current_node, parent);
            current_node->parent = new_node;
            parent->right = new_node;
            break;
        }

        if (tree->sort_func(data, current_node->data, NULL))
        {
            if (NULL != current_node->left)
            {
                current_node = current_node->left;
            }
            else
            {
                status = BTCreateNode(&new_node, data, NULL, NULL, current_node);
                current_node->left = new_node;
                break;
            }
        }
        else
        {
            if (NULL != current_node->right)
            {
                current_node = current_node->right;
            }
            else
            {
                status = BTCreateNode(&new_node, data, NULL, NULL, current_node);
                current_node->right = new_node;
                break;
            }
        }
    }

    return status;
}

/* Remove a node from the tree - Mustn't remove the End*/
void *BTRemove(bt_itr_t itr)
{
    bt_node_t *remove_node = ((bt_node_t*)itr.info);
    void *removed_data = remove_node->data;
    bt_node_t *prev_node = NULL;
    bt_node_t *next_node = NULL;

    /* when trying to remove the node connected to the stub, **without** a left child*/
    if (remove_node->right != NULL && (remove_node->right->right == bad_address) && remove_node->left == NULL)
    {
        next_node = remove_node->right;
        ExchangeStub(&remove_node);
        KillNode(next_node);
        return removed_data;
    }

    /* when trying to remove the node connected to the stub, **with** a left child */
    if (remove_node->right != NULL && (remove_node->right->right == bad_address) && remove_node->left != NULL)
    {
        next_node = (bt_node_t*)((BTPrev(*(bt_itr_t*)&remove_node)).info);
        ExcahngeData(&remove_node, &next_node);
        remove_node = next_node;
    }

    /* if trying to remove the root */
    if (NULL == remove_node->parent)
    {
        next_node = (bt_node_t*)((BTNext(*(bt_itr_t*)&remove_node)).info);
        ExcahngeData(&remove_node, &next_node);
        remove_node = next_node;
    }

    /* for a node with two kids commit data exchanges until found one with one kid or none */
    while (NULL != remove_node->right && NULL != remove_node->left)
    {
        next_node = (bt_node_t*)((BTNext(*(bt_itr_t*)&remove_node)).info);
        ExcahngeData(&remove_node, &next_node);
        remove_node = next_node;
    }

    /* removing a leaf */
    if (NULL == remove_node->right && NULL == remove_node->left)
    {
        prev_node = remove_node->parent;

        if (remove_node == prev_node->right)
        {
            prev_node->right = NULL;
        }
        else
        {
            prev_node->left = NULL;
        }
    }

    /*a node with a left child only*/
    else if (NULL == remove_node->right)
    {
        prev_node = remove_node->parent;
        next_node = remove_node->left;
        prev_node->left = next_node;
        next_node->parent = prev_node;
    }

    /*a node with a right child only - can be root*/
    else if (NULL == remove_node->left)
    {
        prev_node = remove_node->parent;
        next_node = remove_node->right;
        prev_node->right = next_node;
        next_node->parent = prev_node;
    }

    KillNode(remove_node);
    return removed_data;
}


/* Translate an iterator to its Data */
void *BTGetData(const bt_itr_t itr)
{
    return ((bt_node_t*)itr.info)->data;
}

/* Returns the number of nodes in the tree */
size_t BTCount(const bt_t *tree)
{
    bt_itr_t itr = {NULL};
    size_t count = 0;

    assert(tree);

    for(itr = BTBegin(tree); !(BTIsSame(itr, BTEnd(tree))); itr = BTNext(itr))
    {
        ++count;
    }

    return count;
}

/* Returns true if the tree is empty, 0 otherwise */
int BTIsEmpty(const bt_t *tree)
{
    return (tree->root->left == bad_address);
}

/* Performs an action on every node in the tree between from and to */
int BTForEach(act_func_t act_func, void *param, const bt_itr_t begin, const bt_itr_t end)
{
    bt_itr_t itr = begin;
    int status = 0;

    while (0 == status && !(BTIsSame(itr, end)))
    {
        status = act_func(((bt_node_t*)itr.info)->data, param);
        itr = BTNext(itr);
    }

    return status;
}

static int BTCreateNode(bt_node_t **node, void *data, void *left, void *right, void *parent)
{
    *node = (bt_node_t*)malloc(sizeof(struct node));

    if (NULL == node)
    {
        return 1;
    }
    
    (*node)->data = data;
    (*node)->left = left;
    (*node)->right = right;
    (*node)->parent = parent;
    
    return 0;
}

static void KillNode(bt_node_t *remove_node)
{
    remove_node->data = NULL;
    remove_node->left = NULL;
    remove_node->right = NULL;
    remove_node->parent = NULL;

    free(remove_node);
}

static void ExchangeStub(bt_node_t **remove_node)
{
    (*remove_node)->data = NULL;
    (*remove_node)->right = bad_address;
    (*remove_node)->left = bad_address;
}

static void ExcahngeData(bt_node_t **remove_node, bt_node_t **next_node)
{
    void *tmp_data = (*remove_node)->data;
    (*remove_node)->data = (*next_node)->data;
    (*next_node)->data = tmp_data;
}
