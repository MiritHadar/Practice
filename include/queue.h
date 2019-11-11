#ifndef OL67_QUEUE
#define OL67_QUEUE

typedef struct queue queue_t;

#include <stddef.h>		/*	size_t	*/

/*-----------------------------------------*/
/* description : Creates a Queue.          */
/*-----------------------------------------*/
/* returnes : Pointer to Queue(meta data). */
/*-----------------------------------------*/
queue_t *QCreate(void);

/*--------------------------------------------*/
/* description : Adds an element to a Queue.  */
/*--------------------------------------------*/
/* returnes : 0 on success, other on failure. */
/*--------------------------------------------*/
int QEnqueue(queue_t *queue, void *data);

/*-------------------------------------------------------*/
/* description : Removes the first element from a Queue. */
/*-------------------------------------------------------*/
/* returnes : Pointer to data of first element.          */
/*-------------------------------------------------------*/
void *QDequeue(queue_t *queue);

/*-------------------------------------------------*/
/* description : Checks if the Queue is empty.     */
/*-------------------------------------------------*/
/* returnes : 1 if queue is empty, 0 if not empty. */
/*-------------------------------------------------*/
int QIsEmpty(const queue_t *queue);

/*-----------------------------------------*/
/* description : Checks for Queue size.    */
/*-----------------------------------------*/
/* returnes : number of elements in Queue. */
/*-----------------------------------------*/
size_t QSize(const queue_t *queue);

/*--------------------------------------------------------*/
/* description : Peaks on first element in Queue.         */
/*--------------------------------------------------------*/
/* returnes : Pointer to data of first element in Queue.  */
/*--------------------------------------------------------*/
void *QPeek(const queue_t *queue);

/*-------------------------------------------*/
/* description : Destroys(Delete) the Queue. */
/*-------------------------------------------*/
/* returnes : Nothing.                       */
/*-------------------------------------------*/
void QDestroy(queue_t *queue);

/*------------------------------------------------------------*/
/* description : Appends from(queue) to the end of to(queue). */
/*               Leaves from(queue) empty.                    */
/*------------------------------------------------------------*/
/* returnes : Nothing.                                        */
/*------------------------------------------------------------*/
void QAppend(queue_t *to, queue_t *from);

void PrintQ(queue_t *queue);

#endif	/*	OL67_QUEUE	*/


