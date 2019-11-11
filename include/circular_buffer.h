/*******************************************************************************
*	Description: circular_buffer							   		           *
*	Author: Mirit Hadar									  	 	       		   *
*	Reviewer: David Zarud									 	 	           *
*	Status:	Sent									 	  	         		   *
*	Last Update: 9.5.19									  	         	       *
*******************************************************************************/

#ifndef OL67_CIRCULAR_BUFFER	
#define OL67_CIRCULAR_BUFFER	

#include <sys/types.h>  /*ssize_t*/

typedef struct c_buff c_buff_t;

/*********************** Circular buffer functions ****************************/

/* capacity in byte */
c_buff_t *CBCreate(size_t capacity);

/* destroy buffer */
void CBDestroy(c_buff_t *cb);

/* capacity in byte */
size_t CBGetCapacity(const c_buff_t *cb);

/* free space in byte */
size_t CBGetFreeSpace(const c_buff_t *cb);

/* boolean value 0 or else */
int CBIsEmpty(const c_buff_t *cb);

/* EOVERFLOW when reached end of data */
ssize_t CBWrite(c_buff_t *cb, const void *buf ,size_t count);

/* ENODATA buffer is empty */
ssize_t CBRead(c_buff_t *cb, void *buf ,size_t count);

#endif	/*	OL67_CIRCULAR_BUFFER  */

