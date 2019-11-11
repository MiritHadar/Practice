#ifndef OL67_TASK
#define OL67_TASK

#include <time.h>	/* time_t			*/
#include "uuid.h"	/* uuid funcs, var	*/



#ifndef STATUS
#define STATUS
 /*0 for cycly / 1 for single*/
typedef enum {CYCLE, SINGLE} status_t;

typedef status_t (*do_func_t)(void *data);
#endif

typedef struct task task_t;



/* Creates a new task		*/
task_t *TaskCreate(time_t period_in_sec, do_func_t do_func, void *data);

/* Destroys the given task 	*/
void TaskDestroy(task_t *task);

/* Returns the task's uid	*/
uuid_t TaskGetUUID(const task_t *task);

/* Uses the do func			*/
status_t TaskExec(task_t *task);

/* Returns the task's time to run*/
time_t TaskGetTimeToRun(const task_t *task);

/* updates task's next time to run */
void TaskUpdateTimeToRun(task_t *task);

#endif /* OL67_TASK */
