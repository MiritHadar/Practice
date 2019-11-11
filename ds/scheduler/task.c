/*******************************************************************************
*	Description: Task / Scheduler							   		           *
*	Author: Mirit Hadar									  	 	       		   *
*	Reviewer: Ada Elkin									 	 	               *
*******************************************************************************/

#include <stdlib.h>     /*for malloc */
#include <assert.h>     /*  assert   */
#include <time.h>       /*  time     */

#include "task.h"       /*task header*/
#include "uuid.h"       /*uuid header*/

#define UNUSED_VAR(x) (void)(x)


struct task
{
	uuid_t uuid;
	time_t period_in_sec;     /* interval in seconds between times to execute */
	time_t abs_time_to_run;
	do_func_t do_func;
	void *data;
};


task_t *TaskCreate(time_t period_in_sec, do_func_t do_func, void *data)
{
    task_t *task = {NULL};
    uuid_t new_uid = {0};
    time_t now = -1;
    
    assert(do_func);
    
    task = malloc(sizeof(task_t));

    if (NULL == task)
    {
        return NULL;   
    }
    
    new_uid = UUIDCreate();
    
    if (UUIDIsSame(new_uid, bad_uid))
    {
        TaskDestroy(task);
        return NULL;
    }
    
    while (-1 == now)
    {
        now = time(NULL);
    }
        
    task->uuid = new_uid;
    task->period_in_sec = period_in_sec;
    task->abs_time_to_run = (now + period_in_sec);
    task->do_func = do_func;
    task->data = data;
    
    return task;
}


void TaskDestroy(task_t *task)
{
    assert(task);
      
    task->uuid = bad_uid;
    task->period_in_sec = -1;
    task->abs_time_to_run = -1;
    task->do_func = NULL;
    task->data = NULL;
    
    free(task);     task = NULL;
}


uuid_t TaskGetUUID(const task_t *task)
{
    assert(task);
    
    return task->uuid;
}


status_t TaskExec(task_t *task)
{
    assert(task);
    
    return task->do_func(task->data);
}

/* return the next abs time to run in comparison to current time*/
time_t TaskGetTimeToRun(const task_t *task)
{
    assert(task);
    
    return task->abs_time_to_run;
}

void TaskUpdateTimeToRun(task_t *task)
{
    assert(task);
    
    task->abs_time_to_run += task->period_in_sec;
}









































