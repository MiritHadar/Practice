/*##############################################################################
#                                                                              #
#     Description: Scheduler                                                   #
#     Author: Gil Kremer                                                       #
#     Reviewer: David                                                          #
#     Vershion: Draft                                                          #
#     Last Update: 21.05.19                                                    #
#                                                                              #
##############################################################################*/

#include <stdio.h>
#include <stdlib.h>
#include "sched.h"

#define UNUSED_VAR(x) (void)(x) 


status_t Single(void *data);
status_t Cycle(void *data);
status_t StopTask(void *sched);
status_t Cowsay(void *data);
status_t RemoveTask1(void *sched);
status_t RemoveTask2(void *sched);
status_t AddTask(void *sched);

uuid_t rm_uid1 = {0 , -1, 0};
uuid_t rm_uid2 = {0 , -1, 0};


int main()
{
sched_t *sched = SCHCreate();
	uuid_t uid1 = bad_uid;	
	uuid_t uid2 = bad_uid;
		

	if (NULL == sched)
	{
		printf("Error Creating scheduler line:%d", __LINE__);
	}	

	/* Test for size and is empty when empty */	
	if (0 != SCHSize(sched))
	{
		printf("Error in sched size! line:%d", __LINE__);
	}

	if (1 != SCHIsEmpty(sched))
	{
		printf("Error in sched is empty! line:%d", __LINE__);
	}

	/* adding two tasks */ 
	uid1 = SCHAdd(sched, 20, Single, NULL);	
	uid2 = SCHAdd(sched, 10, Cycle, NULL);
	
	/* Test for size and is empty when not empty */	
	if (2 != SCHSize(sched))
	{
		printf("Error in sched size! line:%d", __LINE__);
	}

	if (0 != SCHIsEmpty(sched))
	{
		printf("Error in sched is empty! line:%d", __LINE__);
	}

	/* Test for remove and size */	
	if (0 != SCHRemove(sched, uid1))
	{
		printf("Error in task SCHRemove! line:%d", __LINE__);
	}

	if (1 != SCHSize(sched))
	{
		printf("Error in sched size! line:%d", __LINE__);
	}

	uid1 = SCHAdd(sched, 20, Single, NULL);	

	/* Test for clear */	
	SCHClear(sched);
	/* Test for size and is empty when empty */	
	if (0 != SCHSize(sched))
	{
		printf("Error in sched size! line:%d", __LINE__);
	}

	if (1 != SCHIsEmpty(sched))
	{
		printf("Error in sched is empty! line:%d", __LINE__);
	}

	/* task that run single */ 
	uid1 = SCHAdd(sched, 4, Single, NULL);	
	/* task that run cycle */ 
	uid2 = SCHAdd(sched, 1, Cycle, NULL);	
	/* task to remove myself single */ 
	rm_uid1 = SCHAdd(sched, 3, RemoveTask1, sched);
	/* task to remove myself cycle */ 
	rm_uid2 = SCHAdd(sched, 6, RemoveTask2, sched);
	/* task that add new task */ 
	SCHAdd(sched, 8, AddTask, sched);
	/* task for cowsay valgraind */ 
	SCHAdd(sched, 14, Cowsay,  NULL);
	/* task for stop running */
	SCHAdd(sched, 15, StopTask, sched);
	

	SCHRun(sched);

	UNUSED_VAR(uid2);

	SCHDestroy(sched);

	return 0;
}




status_t Single(void *data)
{
	static int num1 = 0;

	UNUSED_VAR(data);

	printf("Single Task! run time:%d\n", num1);

	++num1;

	return 1;
}


status_t Cycle(void *data)
{
	static int num2 = 0;

	UNUSED_VAR(data);

	printf("Cycle Task! run time:%d\n", num2);

	++num2;

	return 0;
}

status_t Cowsay(void *data)
{
	UNUSED_VAR(data);

	system("cowsay -f daemon dont forget valgraind!");

	return 0;
}


status_t RemoveTask1(void *sched)
{
	puts("Remove myself (Cycle!) need to show only once");

	SCHRemove(sched, rm_uid1);

	return 0;
}


status_t RemoveTask2(void *sched)
{
	puts("Remove myself (Single!) need to show only once");

	SCHRemove(sched, rm_uid2);

	return 1;
}


status_t StopTask(void *sched)
{
	puts("Stop Task!");

	SCHStop(sched);

	return 0;
}


status_t AddTask(void *sched)
{
	puts("Task that adds (single task)!");
	SCHAdd(sched, 1, Single, NULL);	

	return 0;
}




