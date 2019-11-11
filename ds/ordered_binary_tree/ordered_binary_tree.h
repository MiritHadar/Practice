/*==============================================================================
#		  ____  _                          _____              				   #
#		 | __ )(_)_ __   __ _ _ __ _   _  |_   _| __ ___  ___ 				   #
#		 |  _ \| | '_ \ / _` | '__| | | |   | || '__/ _ \/ _ \				   #
#		 | |_) | | | | | (_| | |  | |_| |   | || | |  __/  __/				   #
#		 |____/|_|_| |_|\__,_|_|   \__, |   |_||_|  \___|\___|				   #
#	 	  		                   |___/                      				   #
#																			   #
#=============================================================================*/

#ifndef __OL67_ORDERED_BINARY_TREE
#define __OL67_ORDERED_BINARY_TREE


#include <stddef.h>		/*	size_t	*/

/*============================ typedefs ======================================*/
typedef int (*act_func_t)(void *data, void *param);
typedef int (*sort_t)(const void *before, const void *after, void *param);

typedef struct bt_tree bt_t;

typedef struct bt_info
{
	struct bt_info_t *info;
} bt_itr_t;

/*=========================== Function Prototypes ============================*/

/* Creates the administrative struct for the binary tree */
bt_t *BTCreate(sort_t is_smaller, void *args);

/* Destroys a given tree */
void BTDestroy(bt_t *tree);

/* Find an item inside the tree */
bt_itr_t BTFind(const bt_t *tree, const void *data);

/* Returns an iterator to next node */
bt_itr_t BTNext(bt_itr_t itr);

/* Returns an iterator to previous node */
bt_itr_t BTPrev(bt_itr_t itr);

/* Returns the left-most node in the tree */
bt_itr_t BTBegin(const bt_t *tree);

/* Returns the right-most node in the tree */
bt_itr_t BTEnd(const bt_t *tree);

/**/
int BTIsSame(const bt_itr_t itr1, const bt_itr_t itr2);

/* Create a node and insert at the correct position in the tree */
int BTInsert(bt_t *tree, void *data);

/* Remove a node from the tree */
void *BTRemove(bt_itr_t itr);

/* Translate an iterator to its Data */
void *BTGetData(const bt_itr_t itr);

/* Returns the number of nodes in the tree */
size_t BTCount(const bt_t *tree);

/* Returns true if the tree is empty, 0 otherwise */
int BTIsEmpty(const bt_t *tree);

/* Performs an action on every node in the tree between from and to */
int BTForEach(act_func_t act_func, void *param, 
			  const bt_itr_t begin, const bt_itr_t end);


#endif /* __OL67_ORDERED_BINARY_TREE */
