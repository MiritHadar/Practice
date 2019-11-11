/*==============================================================================
#					 ___     ___       _____              					   #
#					/ \ \   / / |     |_   _| __ ___  ___ 					   #
#				   / _ \ \ / /| |       | || '__/ _ \/ _ \					   #
#				  / ___ \ V / | |___    | || | |  __/  __/					   #
#				 /_/   \_\_/  |_____|   |_||_|  \___|\___|					   #
#																			   #
#=============================================================================*/

#ifndef __OL67_AVL_TREE__
#define __OL67_AVL_TREE__

#include <stddef.h>		/*	size_t	*/

/*============================ typedefs ======================================*/
typedef int (*act_func_t)(void *data, void *param);
typedef int (*sort_t)(const void *before, const void *after, void *param);

typedef struct avl_tree avl_t;

/*=========================== Function Prototypes ============================*/

/* Creates the administrative struct for the binary tree */
avl_t *AVLCreate(sort_t is_smaller, void *args);

/* Destroys a given tree */
void AVLDestroy(avl_t *tree);

/* Returns a pointer to the data of a requested node */
void *AVLFind(const avl_t *tree, const void *data);

/* Create a node and insert at the correct position in the tree */
int AVLInsert(avl_t *tree, void *data);

/* Remove a node from the tree */
void *AVLRemove(avl_t *tree, void *data);

/* Returns the number of nodes in the tree */
size_t AVLCount(const avl_t *tree);

/* Returns true if the tree is empty, 0 otherwise */
int AVLIsEmpty(const avl_t *tree);

/* Performs an action on every node in the tree between from and to */
int AVLForEach(avl_t *tree, act_func_t act_func, void *param);

/* Returns the height of the tree */
size_t AVLHeight(avl_t *tree);

void PrintInOrder(avl_t *tree);



#endif /* __OL67_AVL_TREE__ */