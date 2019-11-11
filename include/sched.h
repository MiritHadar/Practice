#ifndef OL67_SCHED
#define OL67_SCHED

#include <time.h>	/* time_t, size_t	*/
#include "uuid.h"	/* uuid funcs, var	*/



#ifndef STATUS
#define STATUS
typedef enum {CYCLE, SINGLE} status_t;

typedef status_t (*do_func_t)(void *data);
#endif

typedef struct sched sched_t;


/* Creates a new scheduler			*/
sched_t *SCHCreate();

/* Destroys the given scheduler 	*/
void SCHDestroy(sched_t *sched);

/* Adds a new job to the scheduler	*/
uuid_t SCHAdd(sched_t *sched, time_t period_in_sec,
					do_func_t do_func, void *data);

/* Removes a task 0 for success 	*/
int SCHRemove(sched_t *sched, uuid_t uid);

/* Returns the number of jobs		*/
size_t SCHSize(const sched_t *sched);

/* Checks if the scheduler is empty	*/
int SCHIsEmpty(const sched_t *sched);

/* Clears the scheduler				*/
void SCHClear(sched_t *sched);

/* Runs the jobs - 0 success, 1 failure	*/
int SCHRun(sched_t *sched);

/* Stop the run function			*/
void SCHStop(sched_t *sched);


#endif /* OL67_SCHED */
