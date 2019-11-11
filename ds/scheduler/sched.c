/*******************************************************************************
*	Description: Scheduler							   		                   *
*	Author: Mirit Hadar									  	 	       		   *
*	Reviewer: Ada Elkin									 	 	               *
*******************************************************************************/

#include <stdlib.h>     /*malloc,free*/
#include <assert.h>     /*assert     */
#include <unistd.h>     /*sleep      */

#include "uuid.h"       /*uuid       */
#include "task.h"       /*task       */
#include "p_queue.h"    /*p_queue    */
#include "sched.h"      /*sched      */

#define UNUSED_VAR(x) (void)(x)

static int IsBefore(const void *time1, const void *time2, void *param);
static int IsEqual(const void *data, const void *to_compare, void *args);

struct sched
{
	pqueue_t *pq;
	task_t *current_task;
	int is_run_done;		/* 0 = keep runnig; 1 = finished running */
};


sched_t *SCHCreate()
{
   sched_t *sched = malloc(sizeof(sched_t));
   
    if (NULL == sched)
    {
        return NULL;
    }
    
    sched->pq = PQCreate(IsBefore, NULL);
    sched->is_run_done = 0;
    sched->current_task = NULL;
    
    if (NULL == sched->pq)
    {
        free(sched); sched = NULL;
    }
    
    return sched;
}


void SCHDestroy(sched_t *sched)
{
    assert(sched);
    
    SCHClear(sched);
    PQDestroy(sched->pq);
    
    sched->current_task = NULL;
    sched->pq = NULL;
    
    free(sched);    sched = NULL;
}


uuid_t SCHAdd(sched_t *sched, time_t period_in_sec,
					do_func_t do_func, void *data)
{
    task_t *task = NULL;
    
    assert(do_func);
    assert(sched);
    
    task = TaskCreate(period_in_sec, do_func, data);
    
    if (NULL == task)
    {
        return bad_uid;
    }
    
    if (0 != PQEnqueue(sched->pq, task))
    {
       TaskDestroy(task);
       
       return bad_uid;
    }
    
    return TaskGetUUID(task);
}

/* Removes a task 0 for success */
int SCHRemove(sched_t *sched, uuid_t uid)
{
    task_t *task_to_destroy = NULL;
    
   
    if (NULL != sched->current_task &&
                            UUIDIsSame(uid, TaskGetUUID(sched->current_task)))
    {
        TaskDestroy(sched->current_task);
        sched->current_task = NULL;
        
        return 0;
    }
    
    task_to_destroy = PQErase(sched->pq, IsEqual, &uid, NULL);
    
     if (NULL != task_to_destroy)
    {
        TaskDestroy(task_to_destroy);
        task_to_destroy = NULL;
        
        return 0;
    }
    return 1;
}


/* Runs the jobs - 0 success, 1 failure	*/
int SCHRun(sched_t *sched)
{
    time_t now = -1;
    
    assert(sched);
    
    sched->is_run_done = 0;
    
    /*loop while "stop" didn't occur and tasks still remain*/
    while (0 == sched->is_run_done && (!SCHIsEmpty(sched)))
    {    
      /*         returns tasks that return cycle back to the Q           */
      /*destroy the old task - in case that last task has "run" in side it*/
        if (NULL != sched->current_task)
        {
	        TaskDestroy(sched->current_task);
	        sched->current_task = NULL;
        }
    
        /*get next task for operation*/
        sched->current_task = PQDequeue(sched->pq);
        
        while ((TaskGetTimeToRun(sched->current_task) - time(NULL)) > 0)
        {
            if (-1 != time(NULL))
            {
                now = time(NULL);
                sleep(TaskGetTimeToRun(sched->current_task) - now);
            }
        }
        
        /*execute and then for cyclic update and enqueue*/
        if (CYCLE == TaskExec(sched->current_task) &&
                                               NULL != sched->current_task)
        {
            TaskUpdateTimeToRun(sched->current_task);
            
            if (0 != PQEnqueue(sched->pq, sched->current_task))
            {
                TaskDestroy(sched->current_task);
                return 1;
            }
            
            sched->current_task = NULL;
        }
    }
    
    return 0;
}


size_t SCHSize(const sched_t *sched)
{
    assert(sched);
    
    return PQSize(sched->pq);
}

int SCHIsEmpty(const sched_t *sched)
{
    assert(sched);
    
    return PQIsEmpty(sched->pq);
}


void SCHClear(sched_t *sched)
{
    
    assert(sched);
    
    while (!PQIsEmpty(sched->pq))
    {
        TaskDestroy(PQDequeue(sched->pq));
    }
    
    if (NULL != sched->current_task)
    {
        TaskDestroy(sched->current_task);
        sched->current_task = NULL;
    }
}


void SCHStop(sched_t *sched)
{
    assert(sched);
    
    sched->is_run_done = 1;
}


/*******************************Comparing Func*********************************/

/*receives 2 tasks and compares there times*/
static int IsBefore(const void *task1, const void *task2, void *param)
{
    UNUSED_VAR(param);
    
    /*returns 1 if time 1 is **Before** time 2*/
    return (TaskGetTimeToRun(task1)) < (TaskGetTimeToRun(task2));
}


/*********************************Match Func***********************************/
static int IsEqual(const void *task, const void *uid_to_compare, void *args)
{                                      
    UNUSED_VAR(args);
    
    return (UUIDIsSame(TaskGetUUID((task_t*)task), *(uuid_t*)uid_to_compare));
}

