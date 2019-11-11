#define _POSIX_SOURCE  			/*struct sigaction */
#define _XOPEN_SOURCE			/*sys V semaphore */

#define SEM_KEY  (0x1984)
#define UNUSED(x) (void)(x)

/**************************************************************************************/

#include <stdio.h>              /*printf, perror */
#include <signal.h>				/*kill, struct sigaction */
#include <unistd.h>	 			/*fork, write */
#include <stdlib.h>				/*exit */
#include <semaphore.h>  		/* sem_t */
#include <sys/sem.h>    		/* struct sembuf, semctl, semop */

/**************************************************************************************/

/*header fils */
#include "sched.h"
#include "uuid.h"
#include "wdAPI.h"

/**************************************************************************************/

/*functions */
static void SigUsr1Define();
void SignalFrom247();
static int ActivateSched();
static int Synchronize();
status_t SendSignalTo247(void *data);
status_t Ressurect247(void *data);

/**************************************************************************************/

/*global var */
sched_t *sched = NULL;
int flag = 0;
pid_t pid = 0;

/**************************************************************************************/

int main()
{
	WDstart(0);

/* 	int status = 0;
	
	pid = getppid();

    SigUsr1Define();

	status = ActivateSched();
    if (0 != status)
	{
		printf("error in wd schedular activate\n");
		exit(1);    
	}

	if (0 != Synchronize())
	{
		return 1;
	}

	if (0 != SCHRun(sched))
	{
		printf("Error in wd SCHRun\n");	
		exit(1);	
	} 

	while (1); */

    return 0;
}

/**************************************************************************************/

static void SigUsr1Define()
{
	struct sigaction wd = {0};

    wd.sa_handler = SignalFrom247;        
	wd.sa_flags = SA_SIGINFO;
	sigfillset(&wd.sa_mask);	

    if (-1 == sigaction(SIGUSR1, &wd, NULL))
	{
		perror("error in sigaction. Failed to set SIGUSR1 handler");
		exit(1);    /*TODO check if exit or return */
	}
}

/**************************************************************************************/

void SignalFrom247()
{
	write(0, "wd received a signal from 247\n\n", 31);

	flag = 0;
}

/**************************************************************************************/

static int ActivateSched()
{
	sched = SCHCreate();
	if (NULL == sched)
	{
		printf("Error in SCHCreate in wd. aborting\n");
        return 1;
	} 

    SCHAdd(sched, 2, SendSignalTo247, NULL);
	SCHAdd(sched, 2, Ressurect247, NULL); 

	return 0;
}

/**************************************************************************************/

static int Synchronize()
{
/*     struct sembuf sem_wait = {0, -1, SEM_UNDO};
    struct sembuf sem_post = {0,  1, SEM_UNDO}; */

/* 	semctl(semget(SEM_KEY, 1, 0666 | IPC_CREAT), 0, IPC_RMID, 0); */

/*     int sem_id = semget(SEM_KEY, 1, 0666 | IPC_CREAT);
    if (-1 == sem_id)
    {
        return 1;
    }

    if (0 != semop(sem_id, &sem_post, 1))
    {
		puts("Error in wd semop");
        return 1;
    }
    
    if (0 != semop(sem_id, &sem_wait, 2))
    {
        return 1;
    } */

    return 0;
}

/**************************************************************************************/

status_t SendSignalTo247(void *data)
{
	UNUSED(data);

/*     write(0, "wd sending signal to 247\n\n", 26); */
	
	kill(pid, SIGUSR1);

	return CYCLE;
}

/**************************************************************************************/

status_t Ressurect247(void *data)
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


