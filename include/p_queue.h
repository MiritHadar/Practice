#ifndef OL67_PRIORITY_QUEUE
#define OL67_PRIORITY_QUEUE

#include <stddef.h>	/* size_t	*/

typedef struct pqueue pqueue_t;

/* Creates a PQueue and returnes a Pointer. */
pqueue_t *PQCreate(int (*is_before)(const void *d1, const void *d2, void *param), void *param);

/* destroy the PQueue. */
void PQDestroy(pqueue_t *pq);

/* Adds an element to a PQueue and returns 0 on success, other on failure. */
int PQEnqueue(pqueue_t *pq, void *data);

/* Removes the first element from a PQueue and returns pointer to data. */
void *PQDequeue(pqueue_t *pq);

/* Peaks on first element in PQueue and returns pointer to data. */
void *PQPeek(const pqueue_t *pq);

/* Checks if the PQueue is empty. */
int PQIsEmpty(const pqueue_t *pq);

/* Checks for PQueue size. */
size_t PQSize(const pqueue_t *pq);

/* Clears all element from PQ but does not destroy the PQ it self. */
void PQClear(pqueue_t *pq);

/* Erase an element from the PQueue. */
void *PQErase(pqueue_t *pq, 
		  int (*match_func)(const void *data, const void *to_compare, void *args), 
		  const void *to_match, void* args);

#endif		/*	OL67_PRIORITY_QUEUE	*/

