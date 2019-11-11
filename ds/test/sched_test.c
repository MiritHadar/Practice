/*******************************************************************************
*	Description: Scheduler							   		                   *
*	Author: Mirit Hadar									  	 	       		   *
*	Reviewer: Ada Elkin									 	 	               *
*******************************************************************************/

#include <stdio.h>  /*printf*/
#include <stdlib.h> /*system*/
#include <unistd.h> /*sleep */

#include "uuid.h"
#include "task.h"
#include "p_queue.h"
#include "sched.h"


#define UNUSED_VAR(x) (void)(x)

status_t PrintHelloWorld(void *data);
status_t StopRunning(void *data);
status_t CowSay(void *data);
status_t PrintNums(void *data);

sched_t *sched = NULL;
int main()
{
    uuid_t uid = bad_uid;
    sched = SCHCreate();

    if (NULL == sched)
    {
        printf("%d failure in SCHCreate\n", __LINE__);    
    }
    
    if (!SCHIsEmpty(sched))
    {
        printf("%d failure in SCHIsEmpty\n", __LINE__);
    }
    
    if (SCHSize(sched))
    {
        printf("%d failure in SCHSize\n", __LINE__);
    }  
    
    uid = SCHAdd(sched, 5, PrintHelloWorld, NULL);
    
    if (1 != SCHSize(sched))
    {
        printf("%d failure in SCHSize\n", __LINE__);
    } 
     
    if (SCHRemove(sched, uid))
    {
        printf("%d failure in remove\n", __LINE__);        
    }
    
    if (!SCHIsEmpty(sched))
    {
        printf("%d failure in SCHIsEmpty\n", __LINE__);
    }
    
    SCHAdd(sched, 7, PrintHelloWorld, NULL);
    SCHAdd(sched, 5, CowSay, NULL);
    SCHAdd(sched, 10, PrintNums, NULL);
    
    if (3 != SCHSize(sched))
    {
        printf("%d failure in SCHSize\n", __LINE__);
    }
    
/************************************RUN***************************************/ 
       
    SCHRun(sched);

    if (1 != SCHSize(sched))
    {
        printf("%d failure in Size after runninng\n", __LINE__);
    }
    
/***********************************Clear**************************************/    
    
    SCHClear(sched);
    
    if (!SCHIsEmpty(sched))
    {
        printf("%d failure in SCHIsEmpty\n", __LINE__);
    }
    
/**********************************Destroy*************************************/
    
    SCHDestroy(sched);
    
    return 0;
    
}

/*#################################Do Funcs###################################*/

status_t PrintHelloWorld(void *data)
{
    UNUSED_VAR(data);
    
    puts("Hello World");
    
    /*single appearance*/
    return SINGLE;
}

status_t StopRunning(void *data)
{
    UNUSED_VAR(data);
    
    SCHStop((sched_t*)data);
    
    /*single appearance*/
    return SINGLE;
}

status_t CowSay(void *data)
{
    UNUSED_VAR(data);
    
    system("cowsay cool life");
    
    /*single appearance*/
    return SINGLE;
}

status_t PrintNums(void *data)
{
    int i = 0;
    
    UNUSED_VAR(data);
    
    for (i = 0; i < 5; ++i)
    {
        printf("%d\n", i);
        sleep(1);
    }
    
    SCHStop(sched);
    
    return CYCLE;
}



