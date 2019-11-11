/*******************************************************************************
*	Description: Scheduler							   		                   *
*	Author: Mirit Hadar									  	 	       		   *
*	Reviewer: Ada Elkin									 	 	               *
*******************************************************************************/

#include <stdio.h>  
#include <stdlib.h> 
#include <unistd.h>

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
    
       
    SCHRun(sched);

    if (0 != SCHSize(sched))
    {
        printf("%d failure in Size after runninng\n", __LINE__);
    }
    
    
    SCHClear(sched);
    
    if (!SCHIsEmpty(sched))
    {
        printf("%d failure in SCHIsEmpty\n", __LINE__);
    }
    
    
    SCHDestroy(sched);
    
    return 0;
    
}


status_t PrintHelloWorld(void *data)
{
    UNUSED_VAR(data);
    
    puts("Hello World");
    
    return SINGLE;
}

status_t StopRunning(void *data)
{
    UNUSED_VAR(data);
    
    SCHStop((sched_t*)data);
    
    return SINGLE;
}

status_t CowSay(void *data)
{
    UNUSED_VAR(data);
    
    system("cowsay cool life");
    
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


/* #include <stdio.h>		
#include "sched.h"		


status_t SelfDistruction(void *data);
status_t DevilTest(void *data);
status_t DevilHelp(void *data);
status_t Job0(void *data);
status_t Job1(void *data);
status_t Job2(void *data);
status_t Job3(void *data);
status_t Job4(void *data);
status_t Stop(void *data);


void TestSched(void);


struct
{
	size_t cntr0;
	size_t cntr1;
	size_t cntr2;
	size_t cntr3;
	size_t cntr4;
} cntrs = {0, 0, 0, 0, 0};

struct devils_struct
{
	sched_t *sched;
	uuid_t *uids;
} devils_struct;

int main(void)
{
	TestSched();

	return 0;
}



void TestSched(void)
{
	sched_t *sched = SCHCreate();
	uuid_t uids[8];


	if (NULL == sched)
	{
		printf("Create failed line : %d\n", __LINE__);
	}

	if (0 != SCHSize(sched))
	{
		printf("Size failed line : %d\n", __LINE__);
	}

	if (!SCHIsEmpty(sched))
	{
		printf("IsEmpty failed line : %d\n", __LINE__);
	}

	uids[0] = SCHAdd(sched, 1, Job0, NULL);
	uids[1] = SCHAdd(sched, 2, Job1, NULL);
	uids[2] = SCHAdd(sched, 4, Job2, NULL);
	uids[3] = SCHAdd(sched, 8, Job3, NULL);
	uids[4] = SCHAdd(sched, 1, Job4, NULL);
	uids[5] = SCHAdd(sched, 17, Stop, sched);

	if (6 != SCHSize(sched))
	{
		printf("Size failed line : %d\n", __LINE__);
	}

	SCHRun(sched);

	if (16 != cntrs.cntr0)
	{
		printf("cntr0 fail : %lu\n line : %d\n", cntrs.cntr0, __LINE__);
	}

	if (8 != cntrs.cntr1)
	{
		printf("cntr0 fail : %lu\n line : %d\n", cntrs.cntr0, __LINE__);
	}

	if (4 != cntrs.cntr2)
	{
		printf("cntr0 fail : %lu\n line : %d\n", cntrs.cntr0, __LINE__);
	}

	if (2 != cntrs.cntr3)
	{
		printf("cntr0 fail : %lu\n line : %d\n", cntrs.cntr0, __LINE__);
	}

	if (1 != cntrs.cntr4)
	{
		printf("cntr0 fail : %lu\n line : %d\n", cntrs.cntr0, __LINE__);
	}

	if (5 != SCHSize(sched))
	{
		printf("Size failed line : %d\n", __LINE__);
	}

	if (0 != SCHRemove(sched, uids[3]))
	{
		printf("Remove failed line : %d\n", __LINE__);
	}

	if (4 != SCHSize(sched))
	{
		printf("Remove Size failed line : %d\n", __LINE__);
	}

	SCHClear(sched);

	if (0 != SCHSize(sched))
	{
		printf("Size failed line : %d\n", __LINE__);
	}

	if (!SCHIsEmpty(sched))
	{
		printf("IsEmpty failed line : %d\n", __LINE__);
	}


	devils_struct.sched = sched;
	devils_struct.uids = uids;

	uids[0] = SCHAdd(sched, 1, Job0, NULL);
	uids[1] = SCHAdd(sched, 2, Job1, NULL);
	uids[2] = SCHAdd(sched, 4, Job2, NULL);
	uids[3] = SCHAdd(sched, 8, Job3, NULL);
	uids[4] = SCHAdd(sched, 1, Job4, NULL);
	uids[5] = SCHAdd(sched, 17, Stop, sched);
	uids[6] = SCHAdd(sched, 1, DevilTest, NULL);
	uids[7] = SCHAdd(sched, 0, SelfDistruction, NULL);

	cntrs.cntr0 = 0;
	cntrs.cntr1 = 0;
	cntrs.cntr2 = 0;
	cntrs.cntr3 = 0;
	cntrs.cntr4 = 0;


	SCHRun(sched);

	if (2 != cntrs.cntr0)
	{
		printf("cntr0 fail : %lu\n line : %d\n", cntrs.cntr0, __LINE__);
	}

	if (0 != cntrs.cntr1)
	{
		printf("cntr1 fail : %lu\n line : %d\n", cntrs.cntr1, __LINE__);
	}

	if (4 != cntrs.cntr2)
	{
		printf("cntr2 fail : %lu\n line : %d\n", cntrs.cntr2, __LINE__);
	}

	if (0 != cntrs.cntr3)
	{
		printf("cntr3 fail : %lu\n line : %d\n", cntrs.cntr3, __LINE__);
	}

	if (1 != cntrs.cntr4)
	{
		printf("cntr4 fail : %lu\n line : %d\n", cntrs.cntr4, __LINE__);
	}

	(void)(uids);

	SCHDestroy(sched);
}

status_t Job0(void *data)
{
	(void)(data);

	++cntrs.cntr0;

	return CYCLE;
}

status_t Job1(void *data)
{
	(void)(data);

	++cntrs.cntr1;

	return CYCLE;
}

status_t Job2(void *data)
{
	(void)(data);

	++cntrs.cntr2;

	return CYCLE;
}

status_t Job3(void *data)
{
	(void)(data);

	++cntrs.cntr3;

	return CYCLE;
}

status_t Job4(void *data)
{
	(void)(data);

	++cntrs.cntr4;

	return SINGLE;
}

status_t Stop(void *data)
{
	(void)(data);

	SCHStop(data);

	return CYCLE;
}

status_t SelfDistruction(void *data)
{
	(void)(data);

	SCHRemove(devils_struct.sched, devils_struct.uids[7]);

	return SINGLE;
}
status_t DevilTest(void *data)
{
	(void)(data);

	SCHRemove(devils_struct.sched, devils_struct.uids[1]);
	SCHRemove(devils_struct.sched, devils_struct.uids[3]);

	SCHStop(devils_struct.sched);

	SCHAdd(devils_struct.sched, 1, DevilHelp, NULL);

	SCHRun(devils_struct.sched);

	return CYCLE;
}

status_t DevilHelp(void *data)
{
	(void)(data);

	SCHRemove(devils_struct.sched, devils_struct.uids[0]);
	SCHRemove(devils_struct.sched, devils_struct.uids[4]);

	SCHStop(devils_struct.sched);

	SCHAdd(devils_struct.sched, 1, DevilTest, NULL);

	SCHRun(devils_struct.sched);

	return CYCLE;
} */

/*
sched_t *SCHCreate();
void SCHDestroy(sched_t *sched);
uuid_t SCHAdd(sched_t *sched, time_t period_in_sec,
					do_func_t do_func, void *data);
int SCHRemove(sched_t *sched, uuid_t uid);
size_t SCHSize(const sched_t *sched);
int SCHIsEmpty(const sched_t *sched);
void SCHClear(sched_t *sched);
int SCHRun(sched_t *sched);
void SCHStop(sched_t *sched);
*/


