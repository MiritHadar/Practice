/*******************************************************************************
*	Description: Task / Scheduler							   		           *
*	Author: Mirit Hadar									  	 	       		   *
*	Reviewer: Ada Elkin									 	 	               *
*******************************************************************************/

#include <stdio.h>  /*printf, puts*/

#include "task.h"
#include "uuid.h"

#define UNUSED_VAR(x) (void)(x)

status_t PrintHelloWorld(void *data);

int main()
{
    task_t *task = TaskCreate(5, PrintHelloWorld, NULL);
    
    if (NULL == task)
    {
        printf("%d failure in TaskCreate\n", __LINE__);    
    }
    
    if (UUIDIsSame(TaskGetUUID(task), bad_uid))
    {
        printf("%d failure in TaskGetUUID\n", __LINE__);            
    }
    
    if (5 != TaskGetTimeToRun(task))
    {
        printf("%d failure in TaskGetTimeToRun\n", __LINE__);            
    }
    
    TaskExec(task);
    
    TaskUpdateTimeToRun(task);
    
    if (5 != TaskGetTimeToRun(task))
    {
        printf("%d failure in TaskGetTimeToRun\n", __LINE__);            
    }
    
    return 0;
}

/*do funcs*/
status_t PrintHelloWorld(void *data)
{
    UNUSED_VAR(data);
    
    puts("Hello World");
    
    /*single appearance*/
    return SINGLE;
}









