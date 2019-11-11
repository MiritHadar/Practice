/*******************************************************************************
*	Description : VSA							   		                       *
*	Author : Mirit Hadar                                                       *
*   Version : Code									  	 	       	           *
*******************************************************************************/


#ifndef __VARIABLE_SIZED_ALLOCATION_H__
#define __VARIABLE_SIZED_ALLOCATION_H__

#include <stddef.h> /* size_t */

typedef struct vsa vsa_t; /* Buffer Block */
typedef struct element element_t; /* Optional - Memory Element */

/*	Receives: pointer to buffer block and the buffer size
*	Returns: Pointer to the VSA
*	Complexity: O(1)*/
vsa_t *VSAInit(void *buffer, size_t buffer_size);

/* Receives: Pointer of VSA and size of memory element to allocate.
*  Retruns: Pointer to the memory element.
*  Complexity: O(N) */
void *VSAAlloc(vsa_t *vsa, size_t element_size);

/* Receives: Pointer to the allocated memeory.
*  Action: Dealocate the pointer.
*  Complexity: O(1)*/
void VSAFree(void *memory_element);

/* Function for Debug Mode only
*  Receives: pointer of VSA.
*  Returns: Number of free space.
*  Complexity: O(N) */
size_t VSAFreeSpace(vsa_t *vsa);

void VSAPrint(vsa_t *vsa);


 #endif /*__VARIABLE_SIZED_ALLOCATION_H__*/

