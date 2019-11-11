#define _POSIX_SOURCE  				/*struct sigaction */
#define _XOPEN_SOURCE				/*sys V semaphore */

#define SEM_KEY  (0x1984)
#define UNUSED(x) (void)(x)

/**************************************************************************************/

#include <sys/types.h>				/*pid_t */
#include <unistd.h>					/*fork */
#include <stdio.h>					/*perror */
#include <stdlib.h>					/*exit */
#include <signal.h>					/*kill, struct sigaction */
#include <pthread.h>				/*pthread_t */
#include <semaphore.h>  			/* sem_t */
#include <errno.h>					/*errno */
#include <sys/sem.h>    			/* struct sembuf, semctl, semop */


/**************************************************************************************/

/*header fils */
#include "wdAPI.h"
#include "sched.h"
#include "uuid.h"

/**************************************************************************************/

/*functions */
static void *ActivateProcess(void *data);
static int CreateWD();
static void SigUsr1Define(int is_247);
static int ActivateSched(int is_247);
static int Synchronize();
static void SignalHandler247();
static void SignalHandlerWd();
status_t SendSignal(void *data);
status_t Ressurect247(void *data);
status_t RessurectWd(void *data);

/**************************************************************************************/

/*global var */
pid_t pid = 0;
pthread_t thread = 0;
sched_t *sched = NULL;
int flag = 0;

/**************************************************************************************/

/*enum*/
enum errors
{
    ERROR_IN_THREAD_CREATE,
    ERROR_IN_THREAD_CANCEL
};

/**************************************************************************************/

int WDstart(int is_247)
{
	int *actions_for_247 = NULL;

	actions_for_247 = malloc(sizeof(int));
	*actions_for_247 = is_247;

	if (is_247)
	{
		if (0 != pthread_create(&thread, NULL, ActivateProcess, actions_for_247))
    	{
        	printf("failure in creating thread");
    	    return ERROR_IN_THREAD_CREATE;
	    }
	}

	else
	{
		ActivateProcess(actions_for_247);
	}
	
	return 0;
}

/**************************************************************************************/

int WDStop()
{
	int status = 0;

	write(0, "stop function is activated\n", 27);

	kill(pid, SIGKILL);
	SCHStop(sched);
	SCHDestroy(sched);
	
	status = pthread_cancel(thread);
    if (0 != status)
    {
        printf("failure in canceling thread");
        return ERROR_IN_THREAD_CANCEL;
    }

	return 0;
}

/**************************************************************************************/

static void *ActivateProcess(void *data)
{
	int casted_actions_for_247 = *(int*)data;

	SigUsr1Define(casted_actions_for_247);

	if (1 == casted_actions_for_247)
	{
		if (0 != CreateWD())
		{
			printf("error in WD process creation\n");
			exit(1);    
		}		
	}

	else
	{
		pid = getppid();
	}
	
	if (0 != ActivateSched(casted_actions_for_247))
	{
		printf("error in schedular activate\n");
		exit(1);    
	}

	if (0 != Synchronize())
	{
		return NULL;
	}

	if (0 != SCHRun(sched))
	{
		printf("Error in SCHRun\n");	
		exit(1);	
	} 

	while(1);

	return NULL;
}

/**************************************************************************************/
 pthread_mutex_t *lock;
static int CreateWD()
{
	char *args[] = {"./wd.out", NULL};

	pid = fork();

	if (-1 == pid)
	{
		perror("error in process id");
		return 1;		
	}

    /*if the process is the chiled process */	
	if (0 == pid)
	{
		execvp(args[0], args);
        puts("fail");
	}

	return 0;
}

/**************************************************************************************/

static void SigUsr1Define(int is_247)
{
	struct sigaction actions = {0};

	if (is_247)
	{
		actions.sa_handler = SignalHandler247;        
	}
	
	else
	{
		actions.sa_handler = SignalHandlerWd;        
	}
	
	actions.sa_flags = SA_SIGINFO;	
	sigfillset(&actions.sa_mask);

	if (-1 == sigaction(SIGUSR1, &actions, NULL))
	{
		perror("error in sigaction. Failed to set SIGUSR1 handler");
		exit(1);    
	}
}

/**************************************************************************************/

static int ActivateSched(int is_247) 
{
	sched = SCHCreate();
	if (NULL == sched)
	{
		return 1;
	} 

	SCHAdd(sched, 2, SendSignal, NULL);
	if (is_247)
	{
		SCHAdd(sched, 2, Ressurect247, NULL);
	}

	else
	{
		SCHAdd(sched, 2, RessurectWd, NULL);
	}

	return 0;
}

/**************************************************************************************/

static int Synchronize()
{
/*     struct sembuf sem_wait = {0, -1, SEM_UNDO};
    struct sembuf sem_post = {0,  1, SEM_UNDO};

	semctl(semget(SEM_KEY, 1, 0666 | IPC_CREAT), 0, IPC_RMID, 0);

    int = sem_id = semget(SEM_KEY, 1, 0666 | IPC_CREAT);
    if (-1 == sem_id)
    {
        return 1;
    } */

	/* semctl(sem_id, 0, IPC_RMID, 0); */

 /*    if (0 != semop(sem_id, &sem_post, 1))
    {
		printf("%d\n", errno);
		perror("Error in semop post");

        return 1;
    }
    
    if (0 != semop(sem_id, &sem_wait, 2))
    {
        return 1;
    } */

    return 0; 
}

/**************************************************************************************/

static void SignalHandler247()
{
	write(0, "247 recived a signal\n\n", 22);

	flag = 0;
}

/**************************************************************************************/

static void SignalHandlerWd()
{
	write(0, "wd recived a signal\n\n", 21);

	flag = 0;
}

/**************************************************************************************/

status_t SendSignal(void *data)
{
	UNUSED(data);

/*     write(0, "247 sending signal to wd\n\n", 26); */
	
	kill(pid, SIGUSR1);

	return CYCLE;
}

/**************************************************************************************/

status_t Ressurect247(void *data)
{
	UNUSED(data);
	if (0 != flag)
	{
/* 		write(0, "247 about to ressurect wd\n\n", 27); */
		SCHStop(sched);

		if (0 != CreateWD())
		{
			printf("error in wdAPI process creation\n");
			exit(1);    
		}

		if (0 != Synchronize())
		{
			printf("Error in Synchronize\n");	
			exit(1);
		}

		if (0 != SCHRun(sched))
		{
			printf("Error in SCHRun\n");	
			exit(1);	
		} 

		flag = 0;
	}
	
	else
	{
		flag = 1;	
	}
	
	return CYCLE;
}

status_t RessurectWd(void *data)
{
	char *args[] = {"./24-7.out", NULL};

	UNUSED(data);

	if (0 != flag)
	{
/* 		write(0, "wd about to ressurect 247\n\n", 27); */

		execvp(args[0], args);
		puts("fail");
	}

	flag = 1;

	return CYCLE;
}
