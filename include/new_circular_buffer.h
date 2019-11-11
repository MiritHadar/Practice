

#ifndef OL67_NEW_CIRCULAR_BUFFER	
#define OL67_NEW_CIRCULAR_BUFFER	

#include <sys/types.h>  /*ssize_t*/

typedef struct cb cb_t;

/*********************** Circular buffer functions ****************************/

/* capacity in byte */
cb_t *CBCreate(size_t capacity);

/* destroy buffer */
void CBDestroy(cb_t *cb);

/* EOVERFLOW when reached end of data */
int CBWrite(cb_t *cb, int num);

/* ENODATA buffer is empty */
int CBRead(cb_t *cb);

#endif	/*	OL67_NEW_CIRCULAR_BUFFER  */

